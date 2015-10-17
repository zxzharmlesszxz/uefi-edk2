/*
 * Copyright (c) 2006 - 2007, Intel Corporation. All rights reserved.<BR>
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

#ifndef _BHYVE_CSM16_H_
#define _BHYVE_CSM16_H_

#include <Protocol/BlockIo.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/Legacy8259.h>
#include <Protocol/LegacyBios.h>

#include "BiosInterface.h"

#define E_SEGMENT  0xE000
#define F_SEGMENT  0xF000

#define LEGACY8259_MODE_BASE_VECTOR_MASTER  0x40
#define LEGACY8259_MODE_BASE_VECTOR_SLAVE   0x48

#define CPU_EFLAGS_IF  0x200

extern VOID                  *IVT;
extern VOID                  *_end;

extern EFI_SYSTEM_TABLE      *gST;
extern EFI_BOOT_SERVICES     *gBS;
extern EFI_RUNTIME_SERVICES  *gRT;

extern EFI_HANDLE                 *mDeviceHandle;
extern EFI_BLOCK_IO_PROTOCOL      *mDeviceBlockIo;
extern UINT8                      mDriveNumber;
extern EFI_COMPATIBILITY16_TABLE  mEfiCompatibility16Table;
extern EFI_LEGACY_8259_PROTOCOL   *mLegacy8259;

extern BDA                        *mBdaPtr;

#define IA32_IDT_GATE_TYPE_INTERRUPT_32  0x8E

///
/// Byte packed structure for an x64 Interrupt Gate Descriptor.
///
typedef union {
  struct {
    UINT32  OffsetLow:16;   ///< Offset bits 15..0.
    UINT32  Selector:16;    ///< Selector.
    UINT32  Reserved_0:8;   ///< Reserved.
    UINT32  GateType:8;     ///< Gate Type.  See #defines above.
    UINT32  OffsetHigh:16;  ///< Offset bits 31..16.
    UINT32  OffsetUpper:32; ///< Offset bits 63..32.
    UINT32  Reserved_1:32;  ///< Reserved.
  } Bits;
  struct {
    UINT64  Uint64;
    UINT64  Uint64_1;
  } Uint128;
} IA32_IDT_GATE_DESCRIPTOR;

///
/// Byte packed structure for an IDTR, GDTR, LDTR descriptor.
///
#pragma pack (1)
typedef struct {
  UINT16  Limit;
  UINTN   Base;
} IA32_DESCRIPTOR;
#pragma pack ()

STATIC inline
EFIAPI
IoRead8 (
  IN      UINTN                     Port
  )
{
  UINT8   Data;

  __asm__ __volatile__ ("inb %w1,%b0" : "=a" (Data) : "d" ((UINT16)Port));
  return Data;
}

STATIC inline
UINT8
EFIAPI
IoWrite8 (
  IN      UINTN                     Port,
  IN      UINT8                     Value
  )
{
  __asm__ __volatile__ ("outb %b0,%w1" : : "a" (Value), "d" ((UINT16)Port));
  return Value;
}

STATIC inline
UINT8
EFIAPI
IoWrite32 (
  IN      UINTN                     Port,
  IN      UINT32                    Value
  )
{
  __asm__ __volatile__ ("outl %0,%w1" : : "a" (Value), "d" ((UINT16)Port));
  return Value;
}

STATIC inline
VOID
EnableInterrupts (
  VOID
  )
{
  __asm__ __volatile__ ("sti"::: "memory");
}

STATIC inline
VOID
DisableInterrupts (
  VOID
  )
{
  __asm__ __volatile__ ("cli"::: "memory");
}

STATIC inline
UINTN
EFIAPI
ReadEflags (
  VOID
  )
{
  UINTN Eflags;

  __asm__ __volatile__ (
    "pushfq; pop %0"
    : "=r" (Eflags)
    );

  return Eflags;
}

STATIC inline
UINT64
EFIAPI
ReadTsc (
  VOID
  )
{
  UINT32 Low, High;

  __asm __volatile__ ("rdtsc" : "=a" (Low), "=d" (High));
  return (Low | ((UINT64)High << 32));
}

STATIC inline
VOID *
EFIAPI
WriteCr3 (
  VOID  *Cr3
	     )
{
  __asm__ __volatile__ (
    "mov  %0, %%cr3"
    :
    : "r" (Cr3)
			);
  return Cr3;
}

STATIC inline
VOID
WriteIdtr (
  IN      CONST IA32_DESCRIPTOR     *Idtr
  )
{
  __asm__ __volatile__ (
    "lidt %0"
    :
    : "m" (*Idtr)
    );
}

#endif
