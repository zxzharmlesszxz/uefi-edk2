/*
 * Copyright (c) 2006 - 2011, Intel Corporation. All rights reserved.<BR>
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

#include "Printf.h"
#include "String.h"

UINTN
EFIAPI
StrLen (
  IN      CONST CHAR16              *String
  )
{
  UINTN                             Length;

  for (Length = 0; *String != L'\0'; String++) {
    Length++;
  }

  return Length;
}

INTN
EFIAPI
StrCmp (
  IN      CONST CHAR16              *FirstString,
  IN      CONST CHAR16              *SecondString
  )
{
  while ((*FirstString != L'\0') && (*FirstString == *SecondString)) {
    FirstString++;
    SecondString++;
  }
  return *FirstString - *SecondString;
}

CHAR16 *
EFIAPI
StrStr (
  IN      CONST CHAR16              *String,
  IN      CONST CHAR16              *SearchString
)
{
  CONST CHAR16 *FirstMatch;
  CONST CHAR16 *SearchStringTmp;

  if (*SearchString == L'\0') {
    return (CHAR16 *) String;
  }

  while (*String != L'\0') {
    SearchStringTmp = SearchString;
    FirstMatch = String;

    while ((*String == *SearchStringTmp)
	   && (*String != L'\0')) {
      String++;
      SearchStringTmp++;
    }

    if (*SearchStringTmp == L'\0') {
      return (CHAR16 *) FirstMatch;
    }

    if (*String == L'\0') {
      return NULL;
    }

    String = FirstMatch + 1;
  }

  return NULL;
}

BOOLEAN
EFIAPI
StrEndsWith (
  IN CONST CHAR16 *String,
  IN CONST CHAR16 *SearchString)
{
  UINTN Length, SearchLength;

  Length = StrLen(String);
  SearchLength = StrLen(SearchString);
  if (SearchLength > Length) {
    return FALSE;
  }

  return !StrCmp(String + Length - SearchLength, SearchString);
}

INTN
EFIAPI
CompareMem (
  IN      CONST VOID                *DestinationBuffer,
  IN      CONST VOID                *SourceBuffer,
  IN      UINTN                     Length
  )
{
  while ((--Length != 0) &&
         (*(INT8*)DestinationBuffer == *(INT8*)SourceBuffer)) {
    DestinationBuffer = (INT8*)DestinationBuffer + 1;
    SourceBuffer = (INT8*)SourceBuffer + 1;
  }
  return (INTN)*(UINT8*)DestinationBuffer - (INTN)*(UINT8*)SourceBuffer;
}

VOID *
EFIAPI
CopyMem (
  OUT VOID       *DestinationBuffer,
  IN CONST VOID  *SourceBuffer,
  IN UINTN       Length
  )
{
  UINT8                             *Destination8;
  CONST UINT8                       *Source8;

  if (SourceBuffer > DestinationBuffer) {
    Destination8 = (UINT8*)DestinationBuffer;
    Source8 = (CONST UINT8*)SourceBuffer;
    while (Length-- != 0) {
      *(Destination8++) = *(Source8++);
    }
  } else if (SourceBuffer < DestinationBuffer) {
    Destination8 = (UINT8*)DestinationBuffer + Length;
    Source8 = (CONST UINT8*)SourceBuffer + Length;
    while (Length-- != 0) {
      *(--Destination8) = *(--Source8);
    }
  }
  return DestinationBuffer;
}

VOID *
EFIAPI
ZeroMem (
  OUT     VOID                      *Buffer,
  IN      UINTN                     Length
  )
{
  do {
    ((UINT16*)Buffer)[--Length] = 0;
  } while (Length != 0);
  return Buffer;
}

UINT8
DecimalToBcd8 (
  UINT8  Value
  )
{
#if 0
  ASSERT (Value < 100);
#endif
  return (UINT8) (((Value / 10) << 4) | (Value % 10));
}
