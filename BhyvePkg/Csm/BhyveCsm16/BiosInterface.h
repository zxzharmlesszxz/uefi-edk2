/*
 * Copyright (c) 2006 - 2013, Intel Corporation. All rights reserved.<BR>
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
#ifndef _BIOS_INTERFACE_
#define _BIOS_INTERFACE_

/*
  40:00-01 Com1
  40:02-03 Com2
  40:04-05 Com3
  40:06-07 Com4
  40:08-09 Lpt1
  40:0A-0B Lpt2
  40:0C-0D Lpt3
  40:0E-0E Ebda segment
  40:10-11 MachineConfig
  40:12    Bda12 - skip
  40:13-14 MemSize below 1MB
  40:15-16 Bda15_16 - skip
  40:17    Keyboard Status 1
  40:18    Keyboard Status 2
  40:19    Bda19 - skip
  40:1A-1B Key buffer head
  40:1C-1D Key buffer tail
  40:1E-3D Key buffer
  40:3E-3F FloppyData 3E = Calibration status 3F = Motor status
  40:40    FloppyTimeout
  40:41-49 Bda41_49 - skip
  40:4A    Text Columns
  40:4B-4F Bda4B_4F - skip
  40:50-5F Cursor postion
  40:60-6B Bda60_6B - skip
  40:6C-6F Timer Counter
  40:70-74 Bda70_74 - skip
  40:75    Number of HDD drives
  40:76-77 Bda76_77 - skip
  40:78-79 78 = Lpt1 timeout, 79 = Lpt2 timeout
  40:7A-7B 7A = Lpt3 timeout, 7B = Lpt4 timeout
  40:7C-7D 7C = Com1 timeout, 7D = Com2 timeout
  40:7E-7F 7E = Com3 timeout, 7F = Com4 timeout
  40:80-81 Pointer to start of key buffer
  40:82-83 Pointer to end of key buffer
  40:84    Number of text rows minus 1
  40:85-86 Number of scan lines per character
  40:87    Video mode options
  40:88    Video features bit and switches
  40:89    Video display data area
  40:8A    Video Display Combination Code (DCC)
  40:8B-8F Bda8B_8F - skip
  40:90    Floppy data rate
  40:91-95 Bda91_95 - skip
  40:96    Keyboard Status 3
  40:97    Keyboard Status 4
  40:98-101 skip
*/
#pragma pack(1)
typedef struct {
  UINT16  Com1;
  UINT16  Com2;
  UINT16  Com3;
  UINT16  Com4;
  UINT16  Lpt1;
  UINT16  Lpt2;
  UINT16  Lpt3;
  UINT16  Ebda;
  UINT16  MachineConfig;
  UINT8   Bda12;
  UINT16  MemSize;
  UINT8   Bda15_16[0x02];
  UINT8   KeyboardStatus1;
  UINT8   KeyboardStatus2;
  UINT8   Bda19;
  UINT16  KeyBufferHead;
  UINT16  KeyBufferTail;
  UINT16  KeyBuffer[0x10];
  UINT16  FloppyData;
  UINT8   FloppyTimeout;
  UINT8   Bda41_49[0x09];
  UINT8   TextColumns;
  UINT8   Bda4B_4F[0x05];
  UINT16  CursorPosition[0x08];
  UINT8   Bda60_6B[0xC];
  UINT32  TimerCounter;
  UINT8   Bda70_74[0x5];
  UINT8   NumberOfDrives;
  UINT8   Bda76_77[0x02];
  UINT16  Lpt1_2Timeout;
  UINT16  Lpt3_4Timeout;
  UINT16  Com1_2Timeout;
  UINT16  Com3_4Timeout;
  UINT16  KeyBufferStart;
  UINT16  KeyBufferEnd;
  UINT8   TextRowsMinusOne;
  UINT16  ScanLinesPerChar;
  UINT8   VideoModeOptions;
  UINT8   VideoFeatureBitsSwitches;
  UINT8   VideoDisplayDataArea;
  UINT8   VideoDCC;
  UINT8   Bda8B_8F[0x05];
  UINT8   FloppyXRate;
  UINT8   Bda91_95[0x05];
  UINT8   KeyboardStatus3;
  UINT8   KeyboardStatus4;
} BDA;
#pragma pack()

//
// 0040:0017 - KEYBOARD - STATUS FLAGS 1
//   7 Insert active
//   6 Caps Lock active
//   5 Num Lock active
//   4 Scroll Lock active
//   3 either Alt pressed
//   2 either Ctrl pressed
//   1 Left Shift pressed
//   0 Right Shift pressed
#define KBSF1_INSERT_BIT             (0x1 << 7)
#define KBSF1_CAPS_LOCK_BIT          (0x1 << 6)
#define KBSF1_NUM_LOCK_BIT           (0x1 << 5)
#define KBSF1_SCROLL_LOCK_BIT        (0x1 << 4)
#define KBSF1_ALT_PRESSED            (0x1 << 3)
#define KBSF1_CTRL_PRESSED           (0x1 << 2)
#define KBSF1_LEFT_SHIFT_PRESSED     (0x1 << 1)
#define KBSF1_RIGHT_SHIFT_PRESSED    (0x1 << 0)

// 0040:0018 - KEYBOARD - STATUS FLAGS 2
//   7: insert key is depressed
//   6: caps-lock key is depressed
//   5: num-lock key is depressed
//   4: scroll lock key is depressed
//   3: suspend key has been toggled
//   2: system key is pressed and held
//   1: left ALT key is pressed
//   0: left CTRL key is pressed
#define KBSF2_SUSPEND_PRESSED        (0x1 << 3)
#define KBSF2_SYSREQ_PRESSED         (0x1 << 2)
#define KBSF2_LEFT_ALT_PRESSED       (0x1 << 1)
#define KBSF2_LEFT_CTRL_PRESSED      (0x1 << 0)

// 0040:0096 - KEYBOARD - STATUS FLAGS 3
//   4: 101/102 enhanced keyboard installed
//   1: last scancode was E0
//   0: last scancode was E1
#define KBSF3_LAST_CODE_WAS_E1       (0x1 << 0)
#define KBSF3_LAST_CODE_WAS_E0       (0x1 << 1)
#define KBSF3_ENHANCED_KBD           (0x1 << 4)

// 0040:0097 - KEYBOARD - STATUS FLAGS 4

#endif
