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

#ifndef _BHYVECSM16_PRINTF_H_
#define _BHYVECSM16_PRINTF_H_

#ifdef  DEBUG_PORT
VOID
EFIAPI
DebugPrint (
  IN  CONST CHAR8  *Format,
  ...
  );
#endif

#endif
