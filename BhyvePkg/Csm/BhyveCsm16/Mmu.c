/*
 * Copyright (c) 2006 - 2013, Intel Corporation. All rights reserved.<BR>
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

#include <Uefi.h>

#include "Mmu.h"

#define EFI_MAX_ENTRY_NUM     512

#define EFI_PML4_ENTRY_NUM    1
#define EFI_PDPTE_ENTRY_NUM   4
#define EFI_PDE_ENTRY_NUM     EFI_MAX_ENTRY_NUM

#define EFI_SIZE_OF_PAGE      0x1000
#define EFI_PAGE_SIZE_2M      0x200000

/*
 *  Create 4G PAE 2M pagetable
 */
VOID
CreateIdentityMappingPageTables (
  UINT8                                         *PageTablePtr
  )
{
  UINT64                                        PageAddress;
  int                                           PML4Index;
  int                                           PDPTEIndex;
  int                                           PDEIndex;
  X64_PAGE_MAP_AND_DIRECTORY_POINTER_2MB_4K     *PageMapLevel4Entry;
  X64_PAGE_MAP_AND_DIRECTORY_POINTER_2MB_4K     *PageDirectoryPointerEntry;
  X64_PAGE_TABLE_ENTRY_2M                       *PageDirectoryEntry2MB;

  PageAddress = 0;

  //
  //  Page Table structure 3 level 2MB.
  //
  //                   Page-Map-Level-4-Table        : bits 47-39
  //                   Page-Directory-Pointer-Table  : bits 38-30
  //
  //  Page Table 2MB : Page-Directory(2M)            : bits 29-21
  //
  //

  PageMapLevel4Entry = (X64_PAGE_MAP_AND_DIRECTORY_POINTER_2MB_4K *)PageTablePtr;

  for (PML4Index = 0; PML4Index < EFI_PML4_ENTRY_NUM; PML4Index++, PageMapLevel4Entry++) {
    //
    // Each Page-Map-Level-4-Table Entry points to the base address of a Page-Directory-Pointer-Table Entry
    //  
    PageTablePtr += EFI_SIZE_OF_PAGE;
    PageDirectoryPointerEntry = (X64_PAGE_MAP_AND_DIRECTORY_POINTER_2MB_4K *)PageTablePtr;

    //
    // Make a Page-Map-Level-4-Table Entry
    //
    PageMapLevel4Entry->Uint64 = (UINT64)PageDirectoryPointerEntry;
    PageMapLevel4Entry->Bits.ReadWrite = 1;
    PageMapLevel4Entry->Bits.Present = 1;

    for (PDPTEIndex = 0; PDPTEIndex < EFI_PDPTE_ENTRY_NUM; PDPTEIndex++, PageDirectoryPointerEntry++) {
      //
      // Each Page-Directory-Pointer-Table Entry points to the base address of a Page-Directory Entry
      //       
      PageTablePtr += EFI_SIZE_OF_PAGE;
      PageDirectoryEntry2MB = (X64_PAGE_TABLE_ENTRY_2M *)PageTablePtr;

      //
      // Make a Page-Directory-Pointer-Table Entry
      //
      PageDirectoryPointerEntry->Uint64 = (UINT64)PageDirectoryEntry2MB;
      PageDirectoryPointerEntry->Bits.ReadWrite = 1;
      PageDirectoryPointerEntry->Bits.Present = 1;

      for (PDEIndex = 0; PDEIndex < EFI_PDE_ENTRY_NUM; PDEIndex++, PageDirectoryEntry2MB++) {
        //
        // Make a Page-Directory Entry
        //
        PageDirectoryEntry2MB->Uint64 = (UINT64)PageAddress;
        PageDirectoryEntry2MB->Bits.ReadWrite = 1;
        PageDirectoryEntry2MB->Bits.Present = 1;
        PageDirectoryEntry2MB->Bits.MustBe1 = 1;

        PageAddress += EFI_PAGE_SIZE_2M;
      }
    }
  }
}
