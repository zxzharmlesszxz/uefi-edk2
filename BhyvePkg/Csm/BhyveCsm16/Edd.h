/*
 * Copyright (c) 1999 - 2010, Intel Corporation. All rights reserved.<BR>
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

#ifndef _BHYVECSM16_EDD_H_
#define _BHYVECSM16_EDD_H_

#pragma pack(1)

typedef struct {
  UINT8   Bus;
  UINT8   Device;
  UINT8   Function;
  UINT8   Controller;
  UINT32  Reserved;
} EDD_PCI;

typedef struct {
  UINT16  Base;
  UINT16  Reserved;
  UINT32  Reserved2;
} EDD_LEGACY;

typedef union {
  EDD_PCI     Pci;
  EDD_LEGACY  Legacy;
} EDD_INTERFACE_PATH;

typedef struct {
  UINT8 Master;
  UINT8 Reserved[15];
} EDD_ATA;

typedef struct {
  UINT8 Master;
  UINT8 Lun;
  UINT8 Reserved[14];
} EDD_ATAPI;

typedef struct {
  UINT16  Pun;
  UINT64  Lun;
  UINT8   Reserved[6];
} EDD_SCSI;

typedef struct {
  UINT64  SerialNumber;
  UINT64  Reserved;
} EDD_USB;

typedef struct {
  UINT64  Guid;
  UINT64  Reserved;
} EDD_1394;

typedef struct {
  UINT64  Wwn;
  UINT64  Lun;
} EDD_FIBRE;

typedef union {
  EDD_ATA   Ata;
  EDD_ATAPI Atapi;
  EDD_SCSI  Scsi;
  EDD_USB   Usb;
  EDD_1394  FireWire;
  EDD_FIBRE FibreChannel;
} EDD_DEVICE_PATH;

//
// EDD_DRIVE_PARAMETERS.Flags defines
//
#define EDD_GEOMETRY_VALID          0x02
#define EDD_DEVICE_REMOVABLE        0x04
#define EDD_WRITE_VERIFY_SUPPORTED  0x08
#define EDD_DEVICE_CHANGE           0x10
#define EDD_DEVICE_LOCKABLE         0x20

typedef struct {
  UINT16              StructureSize;
  UINT16              Flags;
  UINT32              MaxCylinders;
  UINT32              MaxHeads;
  UINT32              SectorsPerTrack;
  UINT64              PhysicalSectors;
  UINT16              BytesPerSector;
  UINT32              Fdpt;
  UINT16              Key;
  UINT8               DevicePathLength;
  UINT8               Reserved1;
  UINT16              Reserved2;
  CHAR8               HostBusType[4];
  CHAR8               InterfaceType[8];
  EDD_INTERFACE_PATH  InterfacePath;
  EDD_DEVICE_PATH     DevicePath;
  UINT8               Reserved3;
  UINT8               Checksum;
} EDD_DRIVE_PARAMETERS;

typedef struct {
  UINT8   PacketSizeInBytes;
  UINT8   Reserved1;
  UINT8   NumberOfBlocks;
  UINT8   Reserved2;
  UINT32  SegOffset;
  UINT64  Lba;
  UINT64  TransferBuffer;
} EDD_DEVICE_ADDRESS_PACKET;

typedef struct {
  UINT8   PacketSizeInBytes;
  UINT8   BootMediaType;
  UINT8   DriveNumber;
  UINT8   ControllerIndex;
  UINT32  Lba;
  UINT16  DeviceSpecification;
  UINT16  UserBufferSegment;
  UINT16  LoadSegment;
  UINT16  LoadSectorCount;
  UINT8   CylinderCount;
  UINT8   SectorCount;
  UINT8   HeadCount;
} EDD_DEVICE_SPECIFICATION_PACKET;

#pragma pack()

#endif
