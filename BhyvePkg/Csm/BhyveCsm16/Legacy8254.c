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

#include "BhyveCsm16.h"

#include "Debug.h"
#include "Legacy8254.h"

//
// 8254 Timer registers
//
#define LEGACY_8254_TIMER0_COUNT_PORT    0x40
#define LEGACY_8254_TIMER_CONTROL_PORT   0x43

//
// Timer 0, Read/Write LSB then MSB, Rate generator, binary count use.
//
#define LEGACY_8254_TIMER0_CONTROL_WORD  0x34

VOID
Legacy8254SetCount (
  IN UINT16  Count
  )
{
  DEBUG(("XXX Legacy8254SetCount() Count=0x%x\n", Count));
  IoWrite8 (LEGACY_8254_TIMER_CONTROL_PORT, LEGACY_8254_TIMER0_CONTROL_WORD);
  IoWrite8 (LEGACY_8254_TIMER0_COUNT_PORT, (UINT8) (Count & 0xFF));
  IoWrite8 (LEGACY_8254_TIMER0_COUNT_PORT, (UINT8) ((Count >> 8) & 0xFF));
}


