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
#include <IndustryStandard/LegacyVgaBios.h>

#include "BhyveCsm16.h"

#include "Debug.h"
#include "Edd.h"
#include "Printf.h"
#include "String.h"

#pragma pack(1)
typedef struct {
  UINT64                BaseAddr;
  UINT64                Length;
  UINT32                Type;
} EFI_E820_ENTRY64;
#pragma pack()

/*
 * Equipment Determination
 */
VOID
InterruptVector0x11(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x11()\n"));
  DEBUG (("XXX InterruptVector0x11() Regs->H.AL=0%x\n", Regs->H.AL));
  DEBUG (("XXX InterruptVector0x11() Regs->H.AH=0%x\n", Regs->H.AH));
  DEBUG (("XXX InterruptVector0x11() Regs->X.AX=0%x\n", Regs->X.AX));
  Regs->X.AX = 0;
}

/*
 * Conventional Memory Size
 */
VOID
InterruptVector0x12(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x12()\n"));
  DEBUG (("XXX InterruptVector0x12() Regs->H.AL=0%x\n", Regs->H.AL));
  DEBUG (("XXX InterruptVector0x12() Regs->H.AH=0%x\n", Regs->H.AH));
  DEBUG (("XXX InterruptVector0x12() Regs->X.AX=0%x\n", Regs->X.AX));

  /*
   * Report just 640kb which isn't quite true.
   */
  Regs->E.EFlags.CF = 0;
  Regs->E.EAX = 640;
}

VOID
InterruptVector0x13(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_STATUS                      Status;
  EDD_DEVICE_ADDRESS_PACKET       *AddressPacket;
  EDD_DRIVE_PARAMETERS            *DriveParameters;
  EDD_DEVICE_SPECIFICATION_PACKET *SpecificationPacket;
  UINT16 DriveNumber;
  UINT16  NumberOfHeads, NumberOfCylinders, NumberOfSectorsPerTrack;
  UINT16  Head, Cylinder, Sector;
  EFI_LBA Lba;
  UINT16  NumberOfBlocks;

  DPRINTF (DBG_VERB, ("XXX InterruptVector0x13()\n"));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Regs->H.AL=0%x\n", Regs->H.AL));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Regs->H.AH=0%x\n", Regs->H.AH));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Regs->X.AX=0%x\n", Regs->X.AX));


  switch (Regs->H.AH) {
  case 0x00:    /* Reset */
    Regs->E.EFlags.CF = 0;
    break;
  case 0x02:    /* Read */
    DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Read Drive=0x%x Pointer=0x%x:0x%x\n", Regs->H.DL, Regs->E.ES, Regs->X.BX));
    DPRINTF (DBG_VERB, ("XXX Segment 0x%x Offset=0x%x\n", Regs->E.ES, Regs->X.BX));
    DriveNumber = Regs->H.DL;
    if (DriveNumber != mDriveNumber ||
        mDeviceBlockIo->Media->RemovableMedia) {
      Regs->E.EFlags.CF = 1;    /* Error */
      Regs->H.AH = 0;
    } else {
      NumberOfBlocks = Regs->H.AL;
      Head = (Regs->H.DH & 0x3f);
      Cylinder = (Regs->H.CL & 0xc0) << 2;
      Cylinder |= Regs->H.CH & 0xff;
      Sector = (Regs->H.CL & 0x3f);
      DPRINTF (DBG_INFO, ("XXX NumberOfBlocks 0x%x\n", NumberOfBlocks));
      DPRINTF (DBG_INFO, ("XXX Head = %d Cylinder = %d Sector = %d\n", Head, Cylinder, Sector));

      NumberOfHeads = 16;
      NumberOfSectorsPerTrack = 63;
      NumberOfCylinders = ((mDeviceBlockIo->Media->LastBlock + 1) * mDeviceBlockIo->Media->BlockSize) / (NumberOfHeads * NumberOfSectorsPerTrack);
      if (NumberOfCylinders > 16383) {
        NumberOfCylinders = 16383;
      }

      DPRINTF (DBG_INFO, ("XXX Heads = %d Cylinders = %d Sectors = %d\n", NumberOfHeads, NumberOfCylinders, NumberOfSectorsPerTrack));

      Lba = (Cylinder * NumberOfHeads + Head) * NumberOfSectorsPerTrack + (Sector - 1);
      DPRINTF (DBG_INFO, ("XXX Lba = 0x%lx\n", Lba));
      Status = mDeviceBlockIo->ReadBlocks(mDeviceBlockIo, mDeviceBlockIo->Media->MediaId, Lba, NumberOfBlocks * mDeviceBlockIo->Media->BlockSize, (VOID *)(UINT64)((Regs->E.ES << 4) + (UINT16)Regs->X.BX));

      DPRINTF (DBG_INFO, ("XXX Status = 0x%x\n", Status));
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0;
    }
    break;
  case 0x08:    /* Drive Parameters */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x13() Drive Parameters Drive=0x%x\n", Regs->H.DL));
    DriveNumber = Regs->H.DL;
    if (DriveNumber != mDriveNumber ||
        mDeviceBlockIo->Media->RemovableMedia) {
      Regs->E.EFlags.CF = 1;    /* Error */
      Regs->H.AH = 0xff;
      Regs->H.CL = 1;
      Regs->H.DH = 1;
      Regs->H.CH = 1;
      DPRINTF (DBG_INFO, (" Drive Params error x\n"));
    } else {
      UINT16  NumberOfHeads, NumberOfCylinders, NumberOfSectorsPerTrack;
      UINT16  MaxHead, MaxCylinder, MaxSector;

      DPRINTF (DBG_INFO, (" Drive Params call\n"));

      NumberOfHeads = 16;
      NumberOfSectorsPerTrack = 63;
      NumberOfCylinders = ((mDeviceBlockIo->Media->LastBlock + 1) * mDeviceBlockIo->Media->BlockSize) / (NumberOfHeads * NumberOfSectorsPerTrack);
      if (NumberOfCylinders > 16383) {
        NumberOfCylinders = 16383;
      }

      MaxHead = NumberOfHeads - 1;
      MaxCylinder = NumberOfCylinders - 1;
      MaxSector = NumberOfSectorsPerTrack;      /* index starts with 1! */

      Regs->E.EFlags.CF = 0;
      Regs->E.EAX = 0;
      Regs->H.DL = mDriveNumber;
      Regs->H.DH = (MaxHead & 0x3f);
      Regs->H.CL = ((MaxCylinder >> 2) & 0xc0) | (MaxSector & 0x3f);
      Regs->H.CH = MaxCylinder & 0xff;
    }
    break;
  case 0x15:    /* DASD Type */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x13 DASD Type Drive=0x%x\n", Regs->H.DL));
    DriveNumber = Regs->H.DL;
    if (DriveNumber != mDriveNumber) {
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0x0;         /* Drive not present */
    } else {
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0x3;         /* Fixed disk present */
    }
    break;
  case 0x41:    /* Check Extensions Present */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x13() Check Extensions Present Drive=0x%x Regs->X.BX=0%x\n", Regs->H.DL, Regs->X.BX));
    DriveNumber = Regs->H.DL;
    if (DriveNumber != mDriveNumber || Regs->X.BX != 0x55aa) {
      Regs->E.EFlags.CF = 1;
      Regs->H.AH = 0x1;         /* Invalid Command */
    } else {
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0x21;        /* EDD 1.1 */
      Regs->X.BX = 0xaa55;
      if (mDeviceBlockIo->Media->RemovableMedia) {
        /* Fixed disk access & Drive locking and ejecting & Enhanced
         * disk drive support */
        Regs->X.CX = 0x7;
      } else {
        /* Fixed disk access & Enhanced disk drive support */
        Regs->X.CX = 0x5;
      }
    }
    break;
  case 0x42:    /* Extended Read */
    DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Extended Read Drive=0%x Packet=0x%x:0x%x\n", Regs->H.DL, Regs->E.DS, Regs->X.SI));
    AddressPacket = (EDD_DEVICE_ADDRESS_PACKET *)(UINT64)((Regs->X.DS << 4) + (Regs->X.SI));

    DPRINTF (DBG_VERB, ("XXX Packet->NumberOfBlocks=%d\n", AddressPacket->NumberOfBlocks));
    DPRINTF (DBG_VERB, ("XXX Packet->Lba=0x%llx\n", AddressPacket->Lba));
    DPRINTF (DBG_VERB, ("XXX Packet->SegOffset=0x%x\n", AddressPacket->SegOffset));
    DPRINTF (DBG_VERB, ("XXX Packet->TransferBuffer=0x%llx\n", AddressPacket->TransferBuffer));
    DPRINTF (DBG_VERB, ("XXX Segment 0x%x Offset=0x%x %x\n", AddressPacket->SegOffset >> 16, AddressPacket->SegOffset & 0xffff, (((AddressPacket->SegOffset >> 16) << 4) + (UINT16)AddressPacket->SegOffset)));

    Status = mDeviceBlockIo->ReadBlocks(mDeviceBlockIo, mDeviceBlockIo->Media->MediaId, AddressPacket->Lba, AddressPacket->NumberOfBlocks * mDeviceBlockIo->Media->BlockSize, (VOID *)(UINT64)(((AddressPacket->SegOffset >> 16) << 4) + (UINT16)AddressPacket->SegOffset));

    DPRINTF (DBG_VERB, ("XXX Status = 0x%x\n", Status));
    Regs->E.EFlags.CF = 0;
    Regs->H.AH = 0;
    break;
  case 0x43:    /* Extended Write */
    DPRINTF (DBG_VERB, ("XXX InterruptVector0x13() Extended Write Drive=0%x Packet=0x%x:0x%x\n", Regs->H.DL, Regs->E.DS, Regs->X.SI));
    AddressPacket = (EDD_DEVICE_ADDRESS_PACKET *)(UINT64)((Regs->X.DS << 4) + (Regs->X.SI));

    DPRINTF (DBG_VERB, ("XXX Packet->NumberOfBlocks=%d\n", AddressPacket->NumberOfBlocks));
    DPRINTF (DBG_VERB, ("XXX Packet->Lba=0x%llx\n", AddressPacket->Lba));
    DPRINTF (DBG_VERB, ("XXX Packet->SegOffset=0x%x\n", AddressPacket->SegOffset));
    DPRINTF (DBG_VERB, ("XXX Packet->TransferBuffer=0x%llx\n", AddressPacket->TransferBuffer));
    DPRINTF (DBG_VERB, ("XXX Segment 0x%x Offset=0x%x %x\n", AddressPacket->SegOffset >> 16, AddressPacket->SegOffset & 0xffff, (((AddressPacket->SegOffset >> 16) << 4) + (UINT16)AddressPacket->SegOffset)));

    Status = mDeviceBlockIo->WriteBlocks(mDeviceBlockIo, mDeviceBlockIo->Media->MediaId, AddressPacket->Lba, AddressPacket->NumberOfBlocks * mDeviceBlockIo->Media->BlockSize, (VOID *)(UINT64)(((AddressPacket->SegOffset >> 16) << 4) + (UINT16)AddressPacket->SegOffset));

    DPRINTF (DBG_VERB, ("XXX Status = 0x%x\n", Status));
    Regs->E.EFlags.CF = 0;
    Regs->H.AH = 0;
    break;
  case 0x48:    /* Extended Drive Parameters */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x13() Extended Drive Parameters Drive=0%x Packet=0x%x:0x%x\n", Regs->H.DL, Regs->E.DS, Regs->X.SI));
    DriveNumber = Regs->H.DL;
    DriveParameters = (EDD_DRIVE_PARAMETERS *)(UINT64)((Regs->X.DS << 4) + (Regs->X.SI));
    if (DriveNumber != mDriveNumber ||
        DriveParameters->StructureSize < 26) {
      Regs->E.EFlags.CF = 1;    /* Error */
      Regs->H.AH = 0;
    } else {
      DriveParameters->Flags = 0;
      if (mDeviceBlockIo->Media->RemovableMedia) {
        DriveParameters->Flags |= (EDD_DEVICE_REMOVABLE | EDD_DEVICE_CHANGE | EDD_DEVICE_LOCKABLE);
      } else {
        NumberOfHeads = 16;
        NumberOfSectorsPerTrack = 63;
        NumberOfCylinders = ((mDeviceBlockIo->Media->LastBlock + 1) * mDeviceBlockIo->Media->BlockSize) / (NumberOfHeads * NumberOfSectorsPerTrack);
        if (NumberOfCylinders > 16383) {
          NumberOfCylinders = 16383;
        }

        DriveParameters->MaxCylinders = NumberOfCylinders;
        DriveParameters->MaxHeads = NumberOfHeads;
        DriveParameters->SectorsPerTrack = NumberOfSectorsPerTrack;

        DriveParameters->Flags |= EDD_GEOMETRY_VALID;
      }

      DriveParameters->PhysicalSectors = mDeviceBlockIo->Media->LastBlock + 1;
      DriveParameters->BytesPerSector = mDeviceBlockIo->Media->BlockSize;
      DriveParameters->Fdpt = 0xffffffff;

      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0;
    }
    break;
  case 0x4b:    /* Terminate Disk Emulation */
    switch (Regs->H.AL) {
    case 0x0:   /* Return Status and Terminate Emulation */
      Regs->E.EFlags.CF = 1;    /* System not in emulation mode. */
      break;
    case 0x1:   /* Return Status only, Do Not Terminate Emulation */
      SpecificationPacket = (EDD_DEVICE_SPECIFICATION_PACKET *)(UINT64)((Regs->X.DS << 4) + (Regs->X.SI));
      SpecificationPacket->BootMediaType = 0;   /* No Emulation */
      if (mDeviceBlockIo->Media->RemovableMedia && mDeviceBlockIo->Media->ReadOnly) {
        SpecificationPacket->DriveNumber = mDriveNumber;
      } else {
        /* Definitely it's a "no emulation" drive. */
        SpecificationPacket->DriveNumber = 0xff;
      }
      Regs->E.EFlags.CF = 0;
      Regs->X.AX = 0;
      break;
    }
    break;
  default:
    DPRINTF (DBG_CRIT, ("!!! unhandled int13 %x\n", Regs->H.AH));
  }
}

VOID
InterruptVector0x15(EFI_IA32_REGISTER_SET *Regs)
{
  UINT32  Signature;
  UINT32  Continuation;
  VOID    *BufferPointer;
  UINT32  BufferLength;
  UINTN   Length;

  DPRINTF (DBG_VERB, ("XXX InterruptVector0x15()\n"));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->H.AL=0%x\n", Regs->H.AL));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->H.AH=0%x\n", Regs->H.AH));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.AX=0%x\n", Regs->X.AX));


  switch (Regs->H.AH) {
  case 0x00:
    switch (Regs->H.AL) {
    case 0xc0:  /* Byte-swapped Return System Configuration Parameters */
      /* Work around grub 0.97 bug with ah/al swapped */
      Regs->E.EFlags.CF = 1;
      Regs->H.AH = 0x86;
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 AH=0x00 unhandled\n"));
      break;      
    }
    break;
  case 0x24:
    switch (Regs->H.AL) {
    case 0x00:  /* Disable A20 */
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0;
      break;
    case 0x01:  /* Enable A20 */
      Regs->E.EFlags.CF = 0;
      Regs->H.AH = 0;
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 AH=0x24 unhandled\n"));
      break;
    }
    break;
  case 0x53:
    switch (Regs->H.AL) {
    case 0x0:   /* Advanced Power Management Installation Check */
      /*
       * APM not present
       */
      Regs->E.EFlags.CF = 1;
      Regs->E.EAX = 0x86;
      break;
    case 0x4:   /* Advanced Power Management Interface Disconnect */
      /*
       * Interface not connected
       */
      Regs->E.EFlags.CF = 1;
      Regs->E.EAX = 0x03;
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 AH=0x53 unhandled\n"));
      break;
    }
    break;
  case 0x88:    /* Get Extended Memory Size */
    DPRINTF (DBG_INFO, ("XXX Get Extended Memory Size\n"));
    /*
     * Report 15mb contiguous starting at 1024k as available which
     * isn't quite true.
     */
    Regs->E.EFlags.CF = 0;
    Regs->E.EAX = 15360;
    break;
  case 0xc0:    /* Return System Configuration Parameters */
    /*
     * Not supported.
     */
    Regs->H.AH = 0x86;
    Regs->E.EFlags.CF = 1;
    break;
  case 0xe8:
    switch (Regs->H.AL) {
    case 0x20:  /* Query System Address Map */
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.EBX=0%x\n", Regs->E.EBX));
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.ECX=0%x\n", Regs->E.ECX));
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.EDX=0%x\n", Regs->E.EDX));
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.ES=0%x\n", Regs->X.ES));
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x15() Regs->X.DI=0%x\n", Regs->X.DI));

      Signature = Regs->E.EDX;
      BufferPointer = (VOID *)(UINT64)((Regs->X.ES << 4) + (Regs->X.DI));
      BufferLength = Regs->E.ECX;
      Continuation = Regs->E.EBX;

      if (Signature == SIGNATURE_32 ('P', 'A', 'M', 'S') &&
	  BufferLength >= sizeof (EFI_E820_ENTRY64) &&
	  Continuation < mEfiCompatibility16Table.E820Length) {
	EFI_E820_ENTRY64 *EfiE820Entry64;

	EfiE820Entry64 = (EFI_E820_ENTRY64 *)(UINT64)(mEfiCompatibility16Table.E820Pointer + Continuation);

	CopyMem (BufferPointer,
		 EfiE820Entry64,
		 sizeof (EFI_E820_ENTRY64));
	Continuation += sizeof (EFI_E820_ENTRY64);
	if (mEfiCompatibility16Table.E820Length <= Continuation) {
	  Continuation = 0;
	}

	Regs->E.EFlags.CF = 0;
	Regs->E.EAX = SIGNATURE_32 ('P', 'A', 'M', 'S');
	Regs->E.ECX = sizeof (EFI_E820_ENTRY64);
	Regs->E.EBX = Continuation;
	Regs->E.EDX = 0;
      } else {
	Regs->E.EFlags.CF = 1;
	Regs->E.EAX = 0;
      }
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 AH=0xe8 unhandled\n"));
      break;
    }
    break;
  case 0xec:
    switch (Regs->H.AL) {
    case 0x00:  /* Detect Target Operating Mode */
      DPRINTF (DBG_VERB, ("XXX 0x15 - Detect Op Mode Regs->X.EBX=0%x\n", Regs->E.EBX));
      switch (Regs->H.BL) {
      case 0x01:
      case 0x02:
      case 0x03:
	Regs->H.AH = 0x00;
	Regs->E.EFlags.CF = 0;
	break;
      default:
	Regs->H.AH = 0x00;
	Regs->E.EFlags.CF = 1;
	break;
      }	
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 AH=0xec unhandled\n"));
      break;
    }
    break;
  case 0x86:
    DPRINTF (DBG_VERB, ("XXX 0x15 - 0x86 wait\n"));
    Regs->H.AL = 0x00;
    Regs->E.EFlags.CF = 0;
    break;
  default:
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x15 unhandled AH %x AL %x\n", Regs->H.AH, Regs->H.AL));
    break;
  }
}

/*
 * Real-Time Clock & PCI
 */
VOID
InterruptVector0x1a(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_TIME  BootTime;

  DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() Regs->H.AL=0%x\n", Regs->H.AL));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() Regs->H.AH=0%x\n", Regs->H.AH));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() Regs->X.AX=0%x\n", Regs->X.AX));

  switch (Regs->H.AH) {
  case 0x0:     /* Get RTC Counter */
    //DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() Get RTC Count\n"));
    Regs->H.AL = 0;
    Regs->X.CX = (mBdaPtr->TimerCounter) >> 16;
    Regs->X.DX = (mBdaPtr->TimerCounter) & 0xFFFF;
    break;
  case 0x2:     /* Get Real-Time Clock Time */
    //DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() Get Real-Time Clock Time\n"));
    gRT->GetTime (&BootTime, NULL);
    Regs->H.CH = DecimalToBcd8(BootTime.Hour);
    Regs->H.CL = BootTime.Minute;
    Regs->H.DH = BootTime.Second;
    Regs->H.DL = BootTime.Daylight ? 1 : 0;
    Regs->X.Flags.CF = 0;
    break;
  case 0x4:    /* Read Real-Time Clock Date */ // XXX Leon
    gRT->GetTime (&BootTime, NULL);
    Regs->H.CH = DecimalToBcd8(20);
    Regs->H.CL = DecimalToBcd8((UINT8)(BootTime.Year-2000));
    Regs->H.DH = DecimalToBcd8(BootTime.Month);
    Regs->H.DL = DecimalToBcd8(BootTime.Day);
    Regs->X.Flags.CF = 0;
    break;
  case 0xB1:
    //DPRINTF (DBG_VERB, ("XXX InterruptVector0x1a() 0xB1 Regs->H.AL=0x%x\n", Regs->H.AL));
    Regs->E.EDX = SIGNATURE_32 ('P', 'C', 'I', ' ');
    Regs->H.AH = 0x0;
    Regs->H.AL = 0x0;
    Regs->H.BL = 0x02;
    Regs->H.BH = 0x10;
    Regs->X.Flags.CF = 0;
    break;
  case 0xBB:
    // TPM
    Regs->E.EAX = 0;
    break;
  default:
    DPRINTF (DBG_WARN, ("XXXX int1a unhandled %x\n", Regs->H.AH));
    break;
  }
}

VOID
InterruptVector0x08(EFI_IA32_REGISTER_SET *Regs)
{
  EFI_TIME  BootTime;
  UINT32    LocalTime;

  //DPRINTF (DBG_VERB, ("XXX InterruptVector0x08()\n"));

  gRT->GetTime (&BootTime, NULL);
  LocalTime = BootTime.Hour * 3600 + BootTime.Minute * 60 + BootTime.Second;

  //
  // Multiply result by 18.2 for number of ticks since midnight.
  // Use 182/10 to avoid floating point math.
  //
  LocalTime = (LocalTime * 182) / 10;
  mBdaPtr->TimerCounter = LocalTime;

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq0);
}

VOID
InterruptVector0x0a(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0a()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq2);
}

VOID
InterruptVector0x0b(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0b()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq3);
}

VOID
InterruptVector0x0c(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0c()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq4);
}

VOID
InterruptVector0x0d(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0d()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq5);
}

VOID
InterruptVector0x0e(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0e()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq6);
}

VOID
InterruptVector0x0f(EFI_IA32_REGISTER_SET *Regs)
{
  DEBUG (("XXX InterruptVector0x0f()\n"));

  mLegacy8259->EndOfInterrupt (mLegacy8259, Efi8259Irq7);
}
