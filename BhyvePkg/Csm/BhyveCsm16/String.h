/*
 * Copyright (c) 2004 - 2008, Intel Corporation. All rights reserved.<BR>
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

#ifndef _BHYVECSM16_STRING_H_
#define _BHYVECSM16_STRING_H_

BOOLEAN
EFIAPI
StrEndsWith (
  IN      CONST CHAR16              *String,
  IN      CONST CHAR16              *SearchString);

INTN
EFIAPI
CompareMem (
  IN      CONST VOID                *DestinationBuffer,
  IN      CONST VOID                *SourceBuffer,
  IN      UINTN                     Length
  );

VOID *
EFIAPI
CopyMem (
  OUT VOID       *DestinationBuffer,
  IN CONST VOID  *SourceBuffer,
  IN UINTN       Length
  );

VOID *
EFIAPI
ZeroMem (
  OUT     VOID                      *Buffer,
  IN      UINTN                     Length
  );

UINT8
DecimalToBcd8 (
  IN      UINT8                     Value
  );

#endif
