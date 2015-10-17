/*
 * Copyright (c) 2015, Pluribus Networks, Inc.
 *
 * This program and the accompanying materials are licensed and made
 * available under the terms and conditions of the BSD License which
 * accompanies this distribution.  The full text of the license may be
 * found at http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS"
 * BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED.
 */

#include <Uefi.h>

#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/ElTorito.h>
#include <IndustryStandard/Mbr.h>
#include <IndustryStandard/LegacyBiosMpTable.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/Legacy8259.h>

#include "BhyveCsm16.h"

#include "Debug.h"
#include "Keyboard.h"
#include "Legacy8254.h"
#include "Memory.h"
#include "Mmu.h"
#include "Printf.h"
#include "Smbios.h"
#include "String.h"
#include "Video.h"

#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))

EFI_SYSTEM_TABLE      *gST;
EFI_BOOT_SERVICES     *gBS;
EFI_RUNTIME_SERVICES  *gRT;

EFI_LEGACY_MP_TABLE_FLOATING_POINTER          mMpTableFP;
EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER  mAcpiRsdPtr;
SMBIOS_TABLE_STRUCTURE                        mSmbiosTableStructure;

EFI_COMPATIBILITY16_TABLE mEfiCompatibility16Table = {
  SIGNATURE_32 ('I', 'F', 'E', '$'),
  0,
  sizeof (EFI_COMPATIBILITY16_TABLE),
  0,
  0,
  0,
  0,
  0,
  F_SEGMENT,
  0x400
};

UINT32 mHiPmmMemory;
UINT32 mPML4;
IA32_IDT_GATE_DESCRIPTOR  *mIdtEntries;
IA32_DESCRIPTOR mIDT;
UINT32 mStack;

UINT8 __attribute__((section (".tail"))) mBuildDate[] = BUILD_DATE;

extern VOID  *_end;

VOID
Loop(VOID)
{
  DEBUG(("XXX Loop()\n"));
  for (;;) ;
  //__asm__ __volatile__ ("iretq");
}

extern VOID X64InterruptVectorEntry0x40(VOID);
extern VOID X64InterruptVectorEntry0x41(VOID);

#if 0
#include "FakeIdt.h" // XXX Test Idts
#endif

STATIC
VOID
CsmLegacy16InitializeYourself(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_TO_COMPATIBILITY16_INIT_TABLE  *EfiToLegacy16InitTable;
  IA32_IDT_GATE_DESCRIPTOR  IdtEntry;
  UINTN  Index;

  DEBUG (("XXX CsmLegacy16InitializeYourself()\n"));

  EfiToLegacy16InitTable = (EFI_TO_COMPATIBILITY16_INIT_TABLE *)(UINT64)((Regs->X.ES << 4) + (Regs->X.BX));

  for (Index = 0; Index < 256; Index++) {
    *(((UINT32 *)0) + Index) = *(((UINT32 *)&IVT) + Index);
  }

  ESegmentInitializePool(0xE0000, 0xEFFFF);
  FSegmentInitializePool((UINT32)(UINT64)&_end, 0xFFFFF);

  gST = (EFI_SYSTEM_TABLE *)(UINT64)mEfiCompatibility16Table.EfiSystemTable;
  gBS = gST->BootServices;
  gRT = gST->RuntimeServices;

  mHiPmmMemory = EfiToLegacy16InitTable->HiPmmMemory;
  mStack = mHiPmmMemory + 0x1000 - 0x8;

  mPML4 = mHiPmmMemory + 0x1000;
  CreateIdentityMappingPageTables(mPML4);
  WriteCr3((VOID *)(UINT64)mPML4);

  mIdtEntries = (IA32_IDT_GATE_DESCRIPTOR *)(UINTN)mHiPmmMemory + 0x1000 + 0x6000;
  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Loop;
  IdtEntry.Bits.Selector     = 0x8;
  IdtEntry.Bits.Reserved_0   = 0;
  IdtEntry.Bits.GateType     = IA32_IDT_GATE_TYPE_INTERRUPT_32;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Loop) >> 16);
  IdtEntry.Bits.OffsetUpper  = 0;
  for (Index = 0; Index < 256; Index++) {
    CopyMem (&mIdtEntries[Index], &IdtEntry, sizeof (IdtEntry));
  }

#ifdef FAKE_IDTS
  InitFakeIdtEntries();
#endif

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)X64InterruptVectorEntry0x40;
  IdtEntry.Bits.Selector     = 0x8;
  IdtEntry.Bits.Reserved_0   = 0;
  IdtEntry.Bits.GateType     = IA32_IDT_GATE_TYPE_INTERRUPT_32;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)X64InterruptVectorEntry0x40) >> 16);
  IdtEntry.Bits.OffsetUpper  = 0;
  CopyMem (&mIdtEntries[0x40], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)X64InterruptVectorEntry0x41;
  IdtEntry.Bits.Selector     = 0x8;
  IdtEntry.Bits.Reserved_0   = 0;
  IdtEntry.Bits.GateType     = IA32_IDT_GATE_TYPE_INTERRUPT_32;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)X64InterruptVectorEntry0x41) >> 16);
  IdtEntry.Bits.OffsetUpper  = 0;
  CopyMem (&mIdtEntries[0x41], &IdtEntry, sizeof (IdtEntry));

  mIDT.Base = (UINTN)mIdtEntries;
  mIDT.Limit = (UINT16)((sizeof (IA32_IDT_GATE_DESCRIPTOR) * 256) - 1);


  /*
   * This isn't possible at compile time because of the cast from a
   * 64-bit value to a 32-bit one.
   */
  mEfiCompatibility16Table.AcpiRsdPtrPointer = (UINT32)(UINT64)&mAcpiRsdPtr;

  Regs->X.AX = 0;
}

STATIC
VOID
CsmLegacy16UpdateBbs(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_TO_COMPATIBILITY16_BOOT_TABLE  *EfiToLegacy16BootTable;
  DEBUG (("XXX CsmLegacy16UpdateBbs() Regs->AX = 0x%x, Regs->X.BX = 0x%x, Regs->X.CX = 0x%x, Regs->X.DX = 0x%x, Regs->X.ES = 0x%x\n", Regs->X.AX, Regs->X.BX, Regs->X.CX, Regs->X.DX, Regs->X.ES));

  EfiToLegacy16BootTable = (EFI_TO_COMPATIBILITY16_BOOT_TABLE *)(UINT64)((Regs->X.ES << 4) + (Regs->X.BX));

  Regs->X.AX = 0;
}

extern VOID JumpLongModeToRealMode(UINT16 Stack);

//
// Extract INT32 from char array
//
#define UNPACK_INT32(a) (INT32)( (((UINT8 *) a)[0] <<  0) | \
                                 (((UINT8 *) a)[1] <<  8) | \
                                 (((UINT8 *) a)[2] << 16) | \
                                 (((UINT8 *) a)[3] << 24) )

//
// Extract UINT32 from char array
//
#define UNPACK_UINT32(a) (UINT32)( (((UINT8 *) a)[0] <<  0) | \
                                   (((UINT8 *) a)[1] <<  8) | \
                                   (((UINT8 *) a)[2] << 16) | \
                                   (((UINT8 *) a)[3] << 24) )

VOID                   *mBootSector = (VOID *)0x7C00;

EFI_HANDLE             *mDeviceHandle;
EFI_BLOCK_IO_PROTOCOL  *mDeviceBlockIo;
UINT8                  mDriveNumber;

BDA                    *mBdaPtr = (BDA *)(UINTN)0x400;

VOID
EnterRealMode(EFI_IA32_REGISTER_SET *Regs, UINT16 Segment, UINT16 Offset)
{
  VOID  *Stack;

  Stack = (VOID *)(0x2000 - 0x8);

  Stack -= 2;
  /* EFLAGS image */
  *(UINT16 *)(Stack) = 0;

  Stack -= 2;
  /* return code segment selector */
  *(UINT16 *)(Stack) = Segment;

  Stack -= 2;
  /* return instruction pointer */
  *(UINT16 *)(Stack) = Offset;

  Stack -= 4;
  /* junk (old argument to LongToReal) */
  *(UINT16 *)(Stack) = 0x0;

  Stack -= 4;
  /* junk (old frame pointer) */
  *(UINT16 *)(Stack) = 0;

  Stack -= sizeof (EFI_IA32_REGISTER_SET);
  CopyMem(Stack, Regs, sizeof (EFI_IA32_REGISTER_SET));

  Stack -= 4;
  /* stack pointer */
  *(UINT32 *)(Stack) = (UINT32)(UINTN)(Stack + 4);

  Stack -= 4;
  /* %cr3 */
  *(UINT32 *)(Stack) = mPML4;

  JumpLongModeToRealMode((UINT16)(UINTN)Stack);
}

VOID
BootElTorito(EFI_BLOCK_IO_PROTOCOL *Device)
{
  EFI_STATUS               Status;
  CDROM_VOLUME_DESCRIPTOR  *VolDescriptor;
  ELTORITO_CATALOG         *Catalog;
  UINT32                   Lba;
  UINTN                    Check;
  UINTN                    Index;
  UINT16                   *CheckBuffer;
  UINTN                    MaxIndex;
  EFI_IA32_REGISTER_SET    Regs;

  DEBUG (("XXX BootElTorito() Device=%p\n", Device));

  if (Device->Media->BlockSize != 2048) {
    return;
  }

  Status = gBS->AllocatePool (EfiRuntimeServicesData, Device->Media->BlockSize, (VOID **)&VolDescriptor);
  if (EFI_ERROR (Status)) {
    DEBUG (("XXX BootElTorito() AllocatePool() failed\n"));
    return;
  }
  ZeroMem(VolDescriptor, Device->Media->BlockSize);

  do {
    Status = Device->ReadBlocks(Device, Device->Media->MediaId, 17, Device->Media->BlockSize, VolDescriptor);
  } while (Status == EFI_MEDIA_CHANGED);

  if (EFI_ERROR (Status) && (Status != EFI_MEDIA_CHANGED)) {
    DEBUG (("XXX BootElTorito() unable to read volume descriptor: %r\n", Status));
    return;
  }

  if (CompareMem (VolDescriptor->BootRecordVolume.SystemId, CDVOL_ELTORITO_ID, sizeof (CDVOL_ELTORITO_ID) - 1) != 0) {
    DEBUG (("XXX BootElTorito() invalid El Torito signature\n"));
    return;
  }

  Lba = UNPACK_INT32 (VolDescriptor->BootRecordVolume.EltCatalog);

  Catalog = (ELTORITO_CATALOG *) VolDescriptor;

  Status = Device->ReadBlocks(Device, Device->Media->MediaId, Lba, Device->Media->BlockSize, Catalog);
  if (EFI_ERROR (Status)) {
    DEBUG (("XXX BootElTorito() unable to read catalog\n"));
    return;
  }

  if (Catalog->Catalog.Indicator != ELTORITO_ID_CATALOG || Catalog->Catalog.Id55AA != 0xAA55) {
    DEBUG (("XXX BootElTorito() invalid boot catalog signature\n"));
    return;
  }

  // Validation Entry
  Check       = 0;
  CheckBuffer = (UINT16 *) Catalog;
  for (Index = 0; Index < sizeof (ELTORITO_CATALOG) / sizeof (UINT16); Index += 1) {
    Check += CheckBuffer[Index];
  }
  if ((Check & 0xFFFF) != 0) {
    DEBUG (("XXX BootElTorito() boot catalog header checksum failed\n"));
    return;
  }

  // Initial/Default Entry
  Catalog += 1;
  if (Catalog->Boot.Indicator != ELTORITO_ID_SECTION_BOOTABLE || Catalog->Boot.Lba == 0) {
    DEBUG (("XXX BootElTorito() not bootable\n"));
      return;
  }
  if (Catalog->Boot.MediaType != ELTORITO_NO_EMULATION) {
    DEBUG (("XXX BootElTorito() unsupported El Torito boot media type %x\n", Catalog->Boot.MediaType));
    return;
  }

  Status = Device->ReadBlocks(Device, Device->Media->MediaId, Catalog->Boot.Lba, Catalog->Boot.SectorCount * Device->Media->BlockSize, mBootSector);
  if (EFI_ERROR(Status)) {
    DEBUG (("XXX BootElTorito() unable to read boot sector\n"));
    return;
  }

  ZeroMem(&Regs, sizeof (EFI_IA32_REGISTER_SET));
  Regs.E.EDX = mDriveNumber;
  EnterRealMode(&Regs, 0, (UINT16)(UINTN)mBootSector);
}

VOID
BootMbr(EFI_BLOCK_IO_PROTOCOL *Device)
{
  EFI_STATUS             Status;
  MASTER_BOOT_RECORD     *Mbr;
  UINTN                  Index;
  UINT32                 StartingLBA;
  UINT32                 SizeInLBA;
  EFI_IA32_REGISTER_SET  Regs;

  DEBUG (("XXX BootMbr() Device=%p\n", Device));

  if (Device->Media->BlockSize != 512) {
    return;
  }

  Mbr = (MASTER_BOOT_RECORD *)mBootSector;
  // Read the MBR
  Status = Device->ReadBlocks(Device, Device->Media->MediaId, 0, Device->Media->BlockSize, Mbr);
  if (EFI_ERROR(Status)) {
    DEBUG (("XXX BootMbr() unable to read MBR: %r\n", Status));
    return;
  }

  if (Mbr->Signature != MBR_SIGNATURE) {
    DEBUG (("XXX BootMbr() invalid MBR signature 0x%04x (not 0xAA55)\n", Mbr->Signature));
    return;
  }

  ZeroMem(&Regs, sizeof (EFI_IA32_REGISTER_SET));
  Regs.E.EDX = mDriveNumber;
  EnterRealMode(&Regs, 0, (UINT16)(UINTN)mBootSector);
}

EFI_GUID gEfiEventCsmBootGuid = { 0x05253738, 0x5BD2, 0x4311, { 0xB3, 0x8D, 0x8D, 0xE4, 0x64, 0x69, 0x17, 0x10 }};
EFI_GUID gEfiEventCsmPrepareToBootGuid = { 0X6B145B5F, 0X6E45, 0X4BCC, { 0XAD, 0XDE, 0X31, 0X23, 0X71, 0X7D, 0X27, 0X0C }};
EFI_EVENT  mCsmPrepareToBootEvent;
EFI_EVENT  mCsmBootEvent;

VOID
EFIAPI
CsmPrepareToBootEvent (
  IN  EFI_EVENT        Event,
  IN  VOID             *Context
  )
{
  EFI_GUID    gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
  EFI_GUID    gEfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
  EFI_GUID    gEfiDevicePathToTextProtocolGuid = EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID;
  EFI_STATUS  Status;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL  *DevicePathToTextProtocol;
  EFI_BLOCK_IO_PROTOCOL             *BlockIo;
  EFI_HANDLE  *HandleBuffer;
  UINTN       HandleCount;
  UINTN       Index;

  DEBUG (("XXX CsmPrepareToBootEvent()\n"));

  Status = gBS->LocateProtocol (
                 &gEfiDevicePathToTextProtocolGuid,
                 NULL,
                 (VOID **)&DevicePathToTextProtocol
                 );
  if (EFI_ERROR(Status)) {
    DEBUG (("XXX CsmPrepareToBootEvent() LocateProtocol() gEfiDevicePathToTextProtocolGuid failed\n"));
    goto Fail;
  }

  Status = gBS->LocateHandleBuffer (
                 ByProtocol,
                 &gEfiBlockIoProtocolGuid,
                 NULL,
                 &HandleCount,
                 &HandleBuffer
                 );
  if (EFI_ERROR(Status)) {
    DEBUG (("XXX LocateHandleBuffer() gEfiBlockIoProtocolGuid failed\n"));
    goto Fail;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    EFI_DEVICE_PATH_PROTOCOL           *DevicePath;
    CHAR16*                            DevicePathTxt;

    Status = gBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   (VOID **) &DevicePath
                   );
    if (EFI_ERROR (Status)) {
      continue;
    }

    DevicePathTxt = DevicePathToTextProtocol->ConvertDevicePathToText (DevicePath, FALSE, TRUE);
    DEBUG (("XXX Handle = %p DevicePathTxt = %s\n", HandleBuffer[Index], DevicePathTxt));

    Status = gBS->HandleProtocol (
                  HandleBuffer[Index],
                  &gEfiBlockIoProtocolGuid,
                  (VOID **) &BlockIo
                  );
    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  if (Index >= HandleCount) {
    goto Fail;
  }

  mDeviceHandle = HandleBuffer[Index];
  mDeviceBlockIo = BlockIo;
  if (mDeviceBlockIo->Media->RemovableMedia) {
    // set the cdrom drive number greater than 'BDA NumberOfDrives'
    mDriveNumber = 0x80 + mBdaPtr->NumberOfDrives;
  } else {
    mDriveNumber = 0x80;
  }

  return;

Fail:
  DEBUG (("XXX CsmPrepareToBootEvent() Fail: spinning...\n"));
  for (;;) {
  }
}

EFI_LEGACY_8259_PROTOCOL  *mLegacy8259;

VOID
EFIAPI
CsmBootEvent (
  IN  EFI_EVENT        Event,
  IN  VOID             *Context
  )
{
  EFI_GUID    gEfiLegacy8259ProtocolGuid = EFI_LEGACY_8259_PROTOCOL_GUID;
  EFI_STATUS  Status;

  DEBUG (("XXX CsmBootEvent()\n"));
  DEBUG (("XXX Eflags = 0x%x\n", ReadEflags()));
  DEBUG (("XXX Tsc = 0x%lx\n", ReadTsc()));

  DisableInterrupts();

  Status = gBS->LocateProtocol(&gEfiLegacy8259ProtocolGuid,
                               NULL, (VOID **) &mLegacy8259);

  //
  // Set the 8259 Master base to 0x68 and the 8259 Slave base to 0x70
  // Initialize the keyboard and controller
  //
  KeyboardInitialize();

  //
  // Initialize the VGA
  //
  VGAInitialize();

  //
  // Set the 8259 Master and Slaves base interrupt vectors
  //
  mLegacy8259->SetVectorBase(mLegacy8259,
                             LEGACY8259_MODE_BASE_VECTOR_MASTER,
                             LEGACY8259_MODE_BASE_VECTOR_SLAVE);

  mLegacy8259->EnableIrq(mLegacy8259, Efi8259Irq0, FALSE);
  mLegacy8259->EnableIrq(mLegacy8259, Efi8259Irq1, TRUE);

  Legacy8254SetCount (0xffff);

  //
  // RaiseTPL() can enable interrupts.  We don't want that, so neuter it.
  //
  *(UINT8 *)gST->BootServices->RaiseTPL = 0xc3;
  *(UINT8 *)gST->BootServices->RestoreTPL = 0xc3;

  if (mDeviceBlockIo->Media->RemovableMedia && mDeviceBlockIo->Media->ReadOnly) {
    BootElTorito(mDeviceBlockIo);
  }  else {
    BootMbr(mDeviceBlockIo);
  }
}

STATIC
VOID
CsmLegacy16PrepareToBoot(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_TO_COMPATIBILITY16_BOOT_TABLE  *EfiToLegacy16BootTable;
  UINT8                              OldEfiRaiseTpl;
  UINT8                              OldEfiRestoreTpl;
  EFI_STATUS                         Status;

  DEBUG (("XXX CsmLegacy16PrepareToBoot() Regs->AX = 0x%x, Regs->X.BX = 0x%x, Regs->X.CX = 0x%x, Regs->X.DX = 0x%x\n", Regs->X.AX, Regs->X.BX, Regs->X.CX, Regs->X.DX));

  EfiToLegacy16BootTable = (EFI_TO_COMPATIBILITY16_BOOT_TABLE *)(UINT64)((Regs->X.ES << 4) + (Regs->X.BX));

  CopyMem (&mMpTableFP,
           (VOID *)(UINT64)mEfiCompatibility16Table.MpTablePtr,
           sizeof (EFI_LEGACY_MP_TABLE_FLOATING_POINTER));

  CopyMem (&mSmbiosTableStructure,
           (VOID *)(UINT64)EfiToLegacy16BootTable->SmbiosTable,
           sizeof (SMBIOS_TABLE_STRUCTURE));

  OldEfiRaiseTpl = *(UINT8 *)gST->BootServices->RaiseTPL;
  *(UINT8 *)gST->BootServices->RaiseTPL = 0xc3;
  OldEfiRestoreTpl = *(UINT8 *)gST->BootServices->RestoreTPL;
  *(UINT8 *)gST->BootServices->RestoreTPL = 0xc3;

  Status = gST->BootServices->CreateEventEx (
                  EVT_RUNTIME | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  CsmPrepareToBootEvent,
                  NULL,
                  &gEfiEventCsmPrepareToBootGuid,
                  &mCsmPrepareToBootEvent
                  );
  gST->BootServices->SignalEvent (mCsmPrepareToBootEvent);

  Status = gST->BootServices->CreateEventEx (
                  EVT_RUNTIME | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  CsmBootEvent,
                  NULL,
                  &gEfiEventCsmBootGuid,
                  &mCsmBootEvent
                  );

  *(UINT8 *)gST->BootServices->RaiseTPL = OldEfiRaiseTpl;
  *(UINT8 *)gST->BootServices->RestoreTPL = OldEfiRestoreTpl;

  Regs->X.AX = 0;
}

STATIC
VOID
CsmLegacy16Boot(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX CsmLegacy16Boot()\n"));

  gST->BootServices->SignalEvent (mCsmBootEvent);

  /*
   * Return to give our 'callback' a chance to run.
   */
}

STATIC
VOID
CsmLegacy16DispatchOprom(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX CsmLegacy16DispatchOprom() Regs->AX = 0x%x, Regs->X.BX = 0x%x, Regs->X.CX = 0x%x, Regs->X.DX = 0x%x\n", Regs->X.AX, Regs->X.BX, Regs->X.CX, Regs->X.DX));

  Regs->X.AX = 0;
}

STATIC
VOID
CsmLegacy16GetTableAddress(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_STATUS  Status;
  UINT32      Address;

  DEBUG (("XXX CsmLegacy16GetTableAddress() Regs->AX = 0x%x, Regs->X.BX = 0x%x, Regs->X.CX = 0x%x, Regs->X.DX = 0x%x\n", Regs->X.AX, Regs->X.BX, Regs->X.CX, Regs->X.DX));

  switch (Regs->X.BX) {
  case 0x0:
  case 0x2:
    Status = ESegmentAllocatePool(Regs->X.CX, Regs->X.DX, &Address);
    Regs->X.BX = Address & 0xFFFF;
    Regs->X.DS = E_SEGMENT;
    Regs->X.AX = 0;
    break;
  case 0x1:
    Status = FSegmentAllocatePool(Regs->X.CX, Regs->X.DX, &Address);
    Regs->X.BX = Address & 0xFFFF;
    Regs->X.DS = F_SEGMENT;
    Regs->X.AX = 0;
    break;
  default:
    Regs->X.AX = -1;
    break;
  }
}

VOID
CsmMain(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX CsmMain() Regs->X.AX=0x%x\n", Regs->X.AX));

  switch (Regs->X.AX) {
  case Legacy16InitializeYourself:
    CsmLegacy16InitializeYourself(Regs);
    break;
  case Legacy16UpdateBbs:
    CsmLegacy16UpdateBbs(Regs);
    break;
  case Legacy16PrepareToBoot:
    CsmLegacy16PrepareToBoot(Regs);
    break;
  case Legacy16Boot:
    CsmLegacy16Boot(Regs);
    break;
  case Legacy16DispatchOprom:
    CsmLegacy16DispatchOprom(Regs);
    break;
  case Legacy16GetTableAddress:
    CsmLegacy16GetTableAddress(Regs);
    break;
  default:
    Regs->X.AX = -1;
    break;
  }
}

VOID
InterruptVector0x00(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x00()\n"));
}

VOID
InterruptVector0x01(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x01()\n"));
}

VOID
InterruptVector0x02(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x02()\n"));
}

VOID
InterruptVector0x03(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x03()\n"));
}

VOID
InterruptVector0x04(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x04()\n"));
}

VOID
InterruptVector0x05(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x05()\n"));
}

VOID
InterruptVector0x06(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x06()\n"));
}

VOID
InterruptVector0x07(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x07()\n"));
}
