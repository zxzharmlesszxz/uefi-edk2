/*
 * Copyright (c) 2014, Pluribus Networks, Inc.
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

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <IndustryStandard/LegacyBiosMpTable.h>

#define EFI_SYSTEM_TABLE_MAX_ADDRESS 0xFFFFFFFF
#define SYS_TABLE_PAD(ptr) (((~ptr) + 1) & 0x07)

EFI_PHYSICAL_ADDRESS  *mMpsTable;
UINT32                mMpsTableLength;

STATIC EFI_STATUS
ShadowMpsTable (
  IN OUT VOID          **Table,
  UINT32               *TableLength
  )
{
  UINT32                                       Data32;
  UINT32                                       FPLength;
  EFI_LEGACY_MP_TABLE_FLOATING_POINTER         *MpsFloatingPointerOri;
  EFI_LEGACY_MP_TABLE_FLOATING_POINTER         *MpsFloatingPointerNew;
  EFI_LEGACY_MP_TABLE_HEADER                   *MpsTableOri;
  EFI_LEGACY_MP_TABLE_HEADER                   *MpsTableNew;
  VOID                                         *OemTableOri;
  VOID                                         *OemTableNew;
  EFI_STATUS                                   Status;
  EFI_PHYSICAL_ADDRESS                         BufferPtr;

  //
  // Get MP configuration Table
  //
  MpsFloatingPointerOri = (EFI_LEGACY_MP_TABLE_FLOATING_POINTER *)(*Table);

  //
  // Get Floating pointer structure length
  //
  FPLength = MpsFloatingPointerOri->Length * 16;
  Data32   = FPLength + SYS_TABLE_PAD (FPLength);
  MpsTableOri = (EFI_LEGACY_MP_TABLE_HEADER *)(UINTN)(MpsFloatingPointerOri->PhysicalAddress);
  if (MpsTableOri != NULL) {
    Data32 += MpsTableOri->BaseTableLength;
    Data32 += MpsTableOri->ExtendedTableLength;
    if (MpsTableOri->OemTablePointer != 0x00) {
      Data32 += SYS_TABLE_PAD (Data32);
      Data32 += MpsTableOri->OemTableSize;
    }
    *TableLength = Data32;
  } else {
    *TableLength = 0;
    return EFI_SUCCESS;
  }
  //
  // Relocate memory
  //
  BufferPtr = EFI_SYSTEM_TABLE_MAX_ADDRESS;
  Status = gBS->AllocatePages (
                  AllocateMaxAddress,
                  EfiLoaderData,
                  EFI_SIZE_TO_PAGES(Data32),
                  &BufferPtr
                  );
  if (EFI_ERROR (Status)) {
    return (Status);
  }

  MpsFloatingPointerNew = (EFI_LEGACY_MP_TABLE_FLOATING_POINTER *)(UINTN)BufferPtr;
  CopyMem (MpsFloatingPointerNew, MpsFloatingPointerOri, FPLength);

  //
  // If Mp Table exists
  //
  if (MpsTableOri != NULL) {
    //
    // Get Mps table length, including Ext table
    //
    BufferPtr = BufferPtr + FPLength + SYS_TABLE_PAD (FPLength);
    MpsTableNew = (EFI_LEGACY_MP_TABLE_HEADER *)(UINTN)BufferPtr;
    CopyMem (MpsTableNew, MpsTableOri, MpsTableOri->BaseTableLength + MpsTableOri->ExtendedTableLength);

    if ((MpsTableOri->OemTableSize != 0x0000) && (MpsTableOri->OemTablePointer != 0x0000)){
        BufferPtr += MpsTableOri->BaseTableLength + MpsTableOri->ExtendedTableLength;
        BufferPtr += SYS_TABLE_PAD (BufferPtr);
        OemTableNew = (VOID *)(UINTN)BufferPtr;
        OemTableOri = (VOID *)(UINTN)MpsTableOri->OemTablePointer;
        CopyMem (OemTableNew, OemTableOri, MpsTableOri->OemTableSize);
        MpsTableNew->OemTablePointer = (UINT32)(UINTN)OemTableNew;
    }
    MpsTableNew->Checksum = 0;
    MpsTableNew->Checksum = CalculateCheckSum8 ((UINT8 *)MpsTableNew, MpsTableOri->BaseTableLength);
    MpsFloatingPointerNew->PhysicalAddress = (UINT32)(UINTN)MpsTableNew;
    MpsFloatingPointerNew->Checksum = 0;
    MpsFloatingPointerNew->Checksum = CalculateCheckSum8 ((UINT8 *)MpsFloatingPointerNew, FPLength);
  }

  //
  // Change the pointer
  //
  *Table = MpsFloatingPointerNew;

  return EFI_SUCCESS;
}

VOID
ShadowSystemTables (
  VOID
  )
{
  VOID    *Table;
  UINT32  TableLength;

  Table = (VOID *)0xF0000;
  TableLength = 0;

  ShadowMpsTable(&Table, &TableLength);
  mMpsTable = Table;
  mMpsTableLength = TableLength;
}

VOID
FixupMpsTable (
  UINT32  TablePtr
  )
{
  EFI_LEGACY_MP_TABLE_FLOATING_POINTER         *MpsFloatingPointer;
  UINT32                                       FPLength;

  MpsFloatingPointer = (EFI_LEGACY_MP_TABLE_FLOATING_POINTER *)mMpsTable;
  FPLength = MpsFloatingPointer->Length * 16;

  MpsFloatingPointer->PhysicalAddress = TablePtr + FPLength + SYS_TABLE_PAD (FPLength);
  MpsFloatingPointer->Checksum = 0;
  MpsFloatingPointer->Checksum = CalculateCheckSum8 ((UINT8 *)MpsFloatingPointer, FPLength);
}
