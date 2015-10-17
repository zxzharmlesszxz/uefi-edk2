/*
 * Copyright (c) 2007 - 2010, Intel Corporation. All rights reserved.<BR>
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

#ifndef _BHYVECSM16_SMBIOS_H_
#define _BHYVECSM16_SMBIOS_H_

#pragma pack(1)

typedef struct {
  UINT8                 AnchorString[4];
  UINT8                 EntryPointStructureChecksum;
  UINT8                 EntryPointLength;
  UINT8                 MajorVersion;
  UINT8                 MinorVersion;
  UINT16                MaxStructureSize;
  UINT8                 EntryPointRevision;
  UINT8                 FormattedArea[5];
  UINT8                 IntermediateAnchorString[5];
  UINT8                 IntermediateChecksum;
  UINT16                TableLength;
  UINT32                TableAddress;
  UINT16                NumberOfSmbiosStructures;
  UINT8                 SmbiosBcdRevision;
} SMBIOS_TABLE_STRUCTURE;

#pragma pack()

#endif
