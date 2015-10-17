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

#ifndef _BHYVECSM16_MEMORY_H_
#define _BHYVECSM16_MEMORY_H_

VOID
ESegmentInitializePool (
  UINT32  MemoryBase,
  UINT32  MemoryMax
  );

VOID
FSegmentInitializePool (
  UINT32  MemoryBase,
  UINT32  MemoryMax
  );


EFI_STATUS
ESegmentAllocatePool (
  UINT32 MemorySize,
  UINT32 Alignment,
  UINT32 *Address
  );

EFI_STATUS
FSegmentAllocatePool (
  UINT32 MemorySize,
  UINT32 Alignment,
  UINT32 *Address
  );

#endif
