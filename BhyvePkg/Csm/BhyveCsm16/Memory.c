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

#include <Uefi.h>

#include "Debug.h"
#include "Printf.h"

struct MemPool {
  UINT32  MemPoolBase;
  UINT32  MemPoolSize;
};

struct MemPool ESegmentMemPool;
struct MemPool FSegmentMemPool;

VOID
ESegmentInitializePool (
  UINT32  MemoryBase,
  UINT32  MemoryMax
  )
{
  DEBUG (("XXX ESegmentInitializePool() Base 0x%x Max 0x%x\n",
            MemoryBase, MemoryMax));

  ESegmentMemPool.MemPoolBase = MemoryBase;
  ESegmentMemPool.MemPoolSize = MemoryMax - MemoryBase;
}

VOID
FSegmentInitializePool (
  UINT32  MemoryBase,
  UINT32  MemoryMax
  )
{
  DEBUG (("XXX FSegmentInitializePool() Base 0x%x Max 0x%x\n",
	  MemoryBase, MemoryMax));

  FSegmentMemPool.MemPoolBase = MemoryBase;
  FSegmentMemPool.MemPoolSize = MemoryMax - MemoryBase;
}

EFI_STATUS
ESegmentAllocatePool (
  UINT32 MemorySize,
  UINT32 Alignment,
  UINT32 *Address
  )
{
  UINT32 Base;

  DEBUG (("XXX ESegmentAllocatePool() Size 0x%x Alignment = 0x%x\n",
	  MemorySize, Alignment));

  Base = ((ESegmentMemPool.MemPoolBase + (Alignment - 1)) & ~(Alignment - 1));
  if (Base - ESegmentMemPool.MemPoolBase > ESegmentMemPool.MemPoolSize) {
    return (-1);
  }

  DEBUG (("XXX ESegmentAllocatePool() Address = 0x%x\n", Base));
  *Address = Base;
  ESegmentMemPool.MemPoolSize -= (Base - ESegmentMemPool.MemPoolBase + MemorySize);
  ESegmentMemPool.MemPoolBase = Base + MemorySize;

  return (EFI_SUCCESS);
}

EFI_STATUS
FSegmentAllocatePool (
  UINT32 MemorySize,
  UINT32 Alignment,
  UINT32 *Address
  )
{
  UINT32 Base;

  DEBUG (("XXX FSegmentAllocatePool() Size 0x%x Alignment = 0x%x\n",
	  MemorySize, Alignment));

  Base = ((FSegmentMemPool.MemPoolBase + (Alignment - 1)) & ~(Alignment - 1));
  if (Base - FSegmentMemPool.MemPoolBase > FSegmentMemPool.MemPoolSize) {
    return (-1);
  }

  DEBUG (("XXX FSegmentAllocatePool() Address = 0x%x\n", Base));
  *Address = Base;
  FSegmentMemPool.MemPoolSize -= (Base - FSegmentMemPool.MemPoolBase + MemorySize);
  FSegmentMemPool.MemPoolBase = Base + MemorySize;

  return (EFI_SUCCESS);
}
