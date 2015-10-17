/*
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

#include <Uefi.h>

#include "BhyveCsm16.h"

#include "Debug.h"
#include "Printf.h"

#define KEYBOARD_MAX_TRY                256

#define KEYBOARD_8042_DATA_REGISTER     0x60
#define	KEYBOARD_8042_STATUS_REGISTER   0x64
#define	KEYBOARD_8042_COMMAND_REGISTER  0x64

#define KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA  0x1
#define	KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA   0x2

#define KEYBOARD_8042_COMMAND_WRITE                       0x60
#define KEYBOARD_8042_COMMAND_DISABLE_MOUSE_INTERFACE     0xA7
#define KEYBOARD_8042_COMMAND_CONTROLLER_SELF_TEST        0xAA
#define KEYBOARD_8042_COMMAND_DISABLE_KEYBOARD_INTERFACE  0xAD
#define	KEYBOARD_8042_COMMAND_ENABLE_KEYBOARD_INTERFACE   0xAE

#define KEYBOARD_8048_COMMAND_SELECT_SCAN_CODE_SET  0xF0
#define KEYBOARD_8048_COMMAND_CLEAR_OUTPUT_DATA     0xF4
#define KEYBOARD_8048_RETURN_8042_ACK               0xFA

//  KEYBOARD COMMAND BYTE
//  7: Reserved
//  6: PC/XT translation mode convert
//  5: Disable Auxiliary device interface
//  4: Disable keyboard interface
//  3: Reserved
//  2: System Flag: selftest successful
//  1: Enable Auxiliary device interrupt
//  0: Enable Keyboard interrupt
#define KEYBOARD_CMMBYTE_TRANSLATE      (0x1 << 6)
#define KEYBOARD_CMMBYTE_DISABLE_AUX    (0x1 << 5)
#define KEYBOARD_CMMBYTE_DISABLE_KB     (0x1 << 4)
#define KEYBOARD_CMMBYTE_SELFTEST_OK	(0x1 << 2)
#define KEYBOARD_CMMBYTE_ENABLE_AUXINT  (0x1 << 1)
#define KEYBOARD_CMMBYTE_ENABLE_KBINT   (0x1 << 0)

STATIC UINT8
KeyReadStatusRegister(VOID)
{
  return (IoRead8(KEYBOARD_8042_STATUS_REGISTER));
}

STATIC UINT8
KeyReadDataRegister(VOID)
{
  return (IoRead8(KEYBOARD_8042_DATA_REGISTER));
}

STATIC VOID
KeyWriteDataRegister(UINT8 Data)
{
  IoWrite8(KEYBOARD_8042_DATA_REGISTER, Data);
}

STATIC VOID
KeyWriteCommandRegister(UINT8 Data)
{
  IoWrite8(KEYBOARD_8042_COMMAND_REGISTER, Data);
}

EFI_STATUS
KeyboardWaitForValue(UINT8 Value)
{
  UINTN  TryTime;
  UINT8  Data;

  DEBUG (("XXX KeyboardWaitForValue() Value=0x%x\n", Value));
  for (TryTime = 0; TryTime < KEYBOARD_MAX_TRY; TryTime++) {
    if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA) != 0) {
      Data = KeyReadDataRegister();
      DEBUG (("XXX KeyboardWaitForValue() Data=0%x\n", Data));
      if (Data == Value)
	return EFI_SUCCESS;
    }
  }

  return EFI_TIMEOUT;
}

STATIC EFI_STATUS
KeyboardRead(UINT8 *Data)
{
  if (KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA) {
    *Data = KeyReadDataRegister();
    return EFI_SUCCESS;
  }

  return EFI_TIMEOUT;
}

STATIC EFI_STATUS
KeyboardWrite (
  IN UINT8                   Data
  )
{
  UINTN                   TryTime;

  //
  // Wait For Input Buffer Empty
  //
  for (TryTime = 0; TryTime < KEYBOARD_MAX_TRY; TryTime++) {
    if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA) == 0)
      break;
  }

  if (TryTime == KEYBOARD_MAX_TRY) {
    return (EFI_DEVICE_ERROR);
  }

  KeyWriteDataRegister(Data);

  return EFI_SUCCESS;
}

STATIC EFI_STATUS
KeyboardCommand (
  IN UINT8  Data
  )
{
  UINTN  TryTime;

  //
  // Wait For Input Buffer Empty
  //
  for (TryTime = 0; TryTime < KEYBOARD_MAX_TRY; TryTime++) {
    if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA) == 0)
      break;
  }

  if (TryTime == KEYBOARD_MAX_TRY) {
    return (EFI_DEVICE_ERROR);
  }

  KeyWriteCommandRegister(Data);

  //
  // Wait For Input Buffer Empty again
  //
  for (TryTime = 0; TryTime < KEYBOARD_MAX_TRY; TryTime++) {
    if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA) == 0)
      break;
  }

  if (TryTime == KEYBOARD_MAX_TRY) {
    return (EFI_DEVICE_ERROR);
  }

  return EFI_SUCCESS;
}

#define SCANCODE_CONTROL                                0x1d
#define SCANCODE_L_SHIFT                                0x2a
#define SCANCODE_R_SHIFT                                0x36
#define SCANCODE_ALT                                    0x38
#define SCANCODE_CAPS_LOCK                              0x3a
#define SCANCODE_NUM_LOCK                               0x45
#define SCANCODE_SCROLL_LOCK                            0x46
#define SCANCODE_INSERT                                 0x52

struct KeyEntry {
  UINT16  Normal;
  UINT16  Shift;
  UINT16  Control;
  UINT16  Alt;
};

struct KeyEntry KeyOneByteEntries[] = {
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key  0 */
  { 0x011b, 0x011b, 0x011b, 0xffff }, /* key  1 - Escape key */
  { 0x0231, 0x0221, 0xffff, 0x7800 }, /* key  2 - '1' */
  { 0x0332, 0x0340, 0x0300, 0x7900 }, /* key  3 - '2' */
  { 0x0433, 0x0423, 0xffff, 0x7a00 }, /* key  4 - '3' */
  { 0x0534, 0x0524, 0xffff, 0x7b00 }, /* key  5 - '4' */
  { 0x0635, 0x0625, 0xffff, 0x7c00 }, /* key  6 - '5' */
  { 0x0736, 0x075e, 0x071e, 0x7d00 }, /* key  7 - '6' */
  { 0x0837, 0x0826, 0xffff, 0x7e00 }, /* key  8 - '7' */
  { 0x0938, 0x092a, 0xffff, 0x7f00 }, /* key  9 - '8' */
  { 0x0a39, 0x0a28, 0xffff, 0x8000 }, /* key 10 - '9' */
  { 0x0b30, 0x0b29, 0xffff, 0x8100 }, /* key 11 - '0' */
  { 0x0c2d, 0x0c5f, 0x0c1f, 0x8200 }, /* key 12 - '-' */
  { 0x0d3d, 0x0d2b, 0xffff, 0x8300 }, /* key 13 - '=' */
  { 0x0e08, 0x0e08, 0x0e7f, 0xffff }, /* key 14 - backspace */
  { 0x0f09, 0x0f00, 0xffff, 0xffff }, /* key 15 - tab */
  { 0x1071, 0x1051, 0x1011, 0x1000 }, /* key 16 - 'Q' */
  { 0x1177, 0x1157, 0x1117, 0x1100 }, /* key 17 - 'W' */
  { 0x1265, 0x1245, 0x1205, 0x1200 }, /* key 18 - 'E' */
  { 0x1372, 0x1352, 0x1312, 0x1300 }, /* key 19 - 'R' */
  { 0x1474, 0x1454, 0x1414, 0x1400 }, /* key 20 - 'T' */
  { 0x1579, 0x1559, 0x1519, 0x1500 }, /* key 21 - 'Y' */
  { 0x1675, 0x1655, 0x1615, 0x1600 }, /* key 22 - 'U' */
  { 0x1769, 0x1749, 0x1709, 0x1700 }, /* key 23 - 'I' */
  { 0x186f, 0x184f, 0x180f, 0x1800 }, /* key 24 - 'O' */
  { 0x1970, 0x1950, 0x1910, 0x1900 }, /* key 25 - 'P' */
  { 0x1a5b, 0x1a7b, 0x1a1b, 0xffff }, /* key 26 - '[' */
  { 0x1b5d, 0x1b7d, 0x1b1d, 0xffff }, /* key 27 - ']' */
  { 0x1c0d, 0x1c0d, 0x1c0a, 0xffff }, /* key 28 - CR */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 29 - left control */
  { 0x1e61, 0x1e41, 0x1e01, 0x1e00 }, /* key 30 - 'A' */
  { 0x1f73, 0x1f53, 0x1f13, 0x1f00 }, /* key 31 - 'S' */
  { 0x2064, 0x2044, 0x2004, 0x2000 }, /* key 32 - 'D' */
  { 0x2166, 0x2146, 0x2106, 0x2100 }, /* key 33 - 'F' */
  { 0x2267, 0x2247, 0x2207, 0x2200 }, /* key 34 - 'G' */
  { 0x2368, 0x2348, 0x2308, 0x2300 }, /* key 35 - 'H' */
  { 0x246a, 0x244a, 0x240a, 0x2400 }, /* key 36 - 'J' */
  { 0x256b, 0x254b, 0x250b, 0x2500 }, /* key 37 - 'K' */
  { 0x266c, 0x264c, 0x260c, 0x2600 }, /* key 38 - 'L' */
  { 0x273b, 0x273a, 0xffff, 0xffff }, /* key 39 - ';' */
  { 0x2827, 0x2822, 0xffff, 0xffff }, /* key 40 - ''' */
  { 0x2960, 0x297e, 0xffff, 0xffff }, /* key 41 - '`' */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 42 - left shift */
  { 0x2b5c, 0x2b7c, 0x2b1c, 0xffff }, /* key 43 - '' */
  { 0x2c7a, 0x2c5a, 0x2c1a, 0x2c00 }, /* key 44 - 'Z' */
  { 0x2d78, 0x2d58, 0x2d18, 0x2d00 }, /* key 45 - 'X' */
  { 0x2e63, 0x2e43, 0x2e03, 0x2e00 }, /* key 46 - 'C' */
  { 0x2f76, 0x2f56, 0x2f16, 0x2f00 }, /* key 47 - 'V' */
  { 0x3062, 0x3042, 0x3002, 0x3000 }, /* key 48 - 'B' */
  { 0x316e, 0x314e, 0x310e, 0x3100 }, /* key 49 - 'N' */
  { 0x326d, 0x324d, 0x320d, 0x3200 }, /* key 50 - 'M' */
  { 0x332c, 0x333c, 0xffff, 0xffff }, /* key 51 - ',' */
  { 0x342e, 0x343e, 0xffff, 0xffff }, /* key 52 - '.' */
  { 0x352f, 0x353f, 0xffff, 0xffff }, /* key 53 - '/' */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 54 - right shift - */
  { 0x372a, 0xffff, 0x3772, 0xffff }, /* key 55 - prt-scr - */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 56 - left alt - */
  { 0x3920, 0x3920, 0x3920, 0x3920 }, /* key 57 - space bar */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 58 - caps-lock -  */
  { 0x3b00, 0x5400, 0x5e00, 0x6800 }, /* key 59 - F1 */
  { 0x3c00, 0x5500, 0x5f00, 0x6900 }, /* key 60 - F2 */
  { 0x3d00, 0x5600, 0x6000, 0x6a00 }, /* key 61 - F3 */
  { 0x3e00, 0x5700, 0x6100, 0x6b00 }, /* key 62 - F4 */
  { 0x3f00, 0x5800, 0x6200, 0x6c00 }, /* key 63 - F5 */
  { 0x4000, 0x5900, 0x6300, 0x6d00 }, /* key 64 - F6 */
  { 0x4100, 0x5a00, 0x6400, 0x6e00 }, /* key 65 - F7 */
  { 0x4200, 0x5b00, 0x6500, 0x6f00 }, /* key 66 - F8 */
  { 0x4300, 0x5c00, 0x6600, 0x7000 }, /* key 67 - F9 */
  { 0x4400, 0x5d00, 0x6700, 0x7100 }, /* key 68 - F10 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 69 - num-lock - */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 70 - scroll-lock -  */
  { 0x4700, 0x4737, 0x7700, 0xffff }, /* key 71 - home */
  { 0x4800, 0x4838, 0xffff, 0xffff }, /* key 72 - cursor up */
  { 0x4900, 0x4939, 0x8400, 0xffff }, /* key 73 - page up */
  { 0x4a2d, 0x4a2d, 0xffff, 0xffff }, /* key 74 - minus sign */
  { 0x4b00, 0x4b34, 0x7300, 0xffff }, /* key 75 - cursor left */
  { 0xffff, 0x4c35, 0xffff, 0xffff }, /* key 76 - center key */
  { 0x4d00, 0x4d36, 0x7400, 0xffff }, /* key 77 - cursor right */
  { 0x4e2b, 0x4e2b, 0xffff, 0xffff }, /* key 78 - plus sign */
  { 0x4f00, 0x4f31, 0x7500, 0xffff }, /* key 79 - end */
  { 0x5000, 0x5032, 0xffff, 0xffff }, /* key 80 - cursor down */
  { 0x5100, 0x5133, 0x7600, 0xffff }, /* key 81 - page down */
  { 0x5200, 0x5230, 0xffff, 0xffff }, /* key 82 - insert */
  { 0x5300, 0x532e, 0xffff, 0xffff }, /* key 83 - delete */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 84 - sys key */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 85 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key 86 */
  { 0x8500, 0x5787, 0x8900, 0x8b00 }, /* key 87 - F11 */
  { 0x8600, 0x5888, 0x8a00, 0x8c00 }, /* key 88 - F12 */
};

struct KeyEntry KeyTwoByteEntries[] = {
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 0 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 4 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 5 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 6 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 7 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 8 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 9 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 a */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 b */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 c */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 d */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 e */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 f */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 10 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 11 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 12 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 13 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 14 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 15 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 16 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 17 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 18 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 19 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1a */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1b */
  { 0x1c0d, 0x1c0d, 0x1c0a, 0xffff }, /* key e0 1c - numeric keypad enter */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1d - right control */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1e */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 1f */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 20 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 21 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 22 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 23 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 24 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 25 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 26 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 27 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 28 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 29 */
  { 0xffff, 0xffff, 0x7200, 0xffff }, /* key e0 2a - numlock */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2b */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2c */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2d */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2e */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 2f */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 30 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 31 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 32 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 33 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 34 */
  { 0x352f, 0x352f, 0xffff, 0xffff }, /* key e0 35 - '/' */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 36 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 37 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 38 - right alt */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 39 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3a */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3b */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3c */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3d */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3e */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 3f */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 40 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 41 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 42 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 43 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 44 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 45 */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 46 */
  { 0x4700, 0x4700, 0x7700, 0xffff }, /* key e0 47 - home */
  { 0x4800, 0x4800, 0xffff, 0xffff }, /* key e0 48 - cursor up */
  { 0x4900, 0x4900, 0x8400, 0xffff }, /* key e0 49 - page up */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 4a */
  { 0x4b00, 0x4b00, 0x7300, 0xffff }, /* key e0 4b - cursor left */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 4c */
  { 0x4d00, 0x4d00, 0x7400, 0xffff }, /* key e0 4d - cursor right */
  { 0xffff, 0xffff, 0xffff, 0xffff }, /* key e0 4e */
  { 0x4f00, 0x4f00, 0x7500, 0xffff }, /* key e0 4f - end */
  { 0x5000, 0x5000, 0xffff, 0xffff }, /* key e0 50 - cursor down */
  { 0x5100, 0x5100, 0x7600, 0xffff }, /* key e0 51 - page down */
  { 0x5200, 0x5200, 0xffff, 0xffff }, /* key e0 52 - insert */
  { 0x5300, 0x5300, 0xffff, 0xffff }, /* key e0 53 - delete */
};

static VOID
ProcessReleasedScancode(UINT8 Scancode)
{
  switch (Scancode) {
  case SCANCODE_INSERT:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_INSERT_BIT;
    break;
  case SCANCODE_CAPS_LOCK:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_CAPS_LOCK_BIT;
    break;
  case SCANCODE_NUM_LOCK:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_NUM_LOCK_BIT;
    break;
  case SCANCODE_SCROLL_LOCK:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_SCROLL_LOCK_BIT;
    break;
  case SCANCODE_ALT:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_ALT_PRESSED;
    break;
  case SCANCODE_CONTROL:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_CTRL_PRESSED;
    break;
  case SCANCODE_L_SHIFT:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_LEFT_SHIFT_PRESSED;
    break;
  case SCANCODE_R_SHIFT:
    mBdaPtr->KeyboardStatus1 &= ~KBSF1_RIGHT_SHIFT_PRESSED;
    break;
  }
}

static VOID
ProcessPressedScancode(UINT8 Scancode)
{
  struct KeyEntry *KeyEntries;
  UINT16  Key;
  UINT16  Newtail;

  DEBUG (("XXX ProcessPressedScancode()\n"));
  switch (Scancode) {
  case SCANCODE_INSERT:
    mBdaPtr->KeyboardStatus1 |= KBSF1_INSERT_BIT;
    break;
  case SCANCODE_CAPS_LOCK:
    mBdaPtr->KeyboardStatus1 |= KBSF1_CAPS_LOCK_BIT;
    break;
  case SCANCODE_NUM_LOCK:
    mBdaPtr->KeyboardStatus1 |= KBSF1_NUM_LOCK_BIT;
    break;
  case SCANCODE_SCROLL_LOCK:
    mBdaPtr->KeyboardStatus1 |= KBSF1_SCROLL_LOCK_BIT;
    break;
  case SCANCODE_ALT:
    mBdaPtr->KeyboardStatus1 |= KBSF1_ALT_PRESSED;
    break;
  case SCANCODE_CONTROL:
    mBdaPtr->KeyboardStatus1 |= KBSF1_CTRL_PRESSED;
    break;
  case SCANCODE_L_SHIFT:
    mBdaPtr->KeyboardStatus1 |= KBSF1_LEFT_SHIFT_PRESSED;
    break;
  case SCANCODE_R_SHIFT:
    mBdaPtr->KeyboardStatus1 |= KBSF1_RIGHT_SHIFT_PRESSED;
    break;
  }

  if ((mBdaPtr->KeyboardStatus3 & KBSF3_LAST_CODE_WAS_E0) != 0) {
    DEBUG(("XXX E0 Scancode = 0x%x\n", Scancode));
    KeyEntries = KeyTwoByteEntries;
    DEBUG(("XXX KeyEntries = 0x%p\n", KeyEntries));
    DEBUG(("XXX KeyEntries[0].Normal = 0x%x\n", KeyEntries[0].Normal));
    DEBUG(("XXX KeyEntries[0x10].Normal = 0x%x\n", KeyEntries[0x10].Normal));
    DEBUG(("XXX KeyEntries[0x1c].Normal = 0x%x\n", KeyEntries[0x1c].Normal));
    DEBUG(("XXX KeyEntries[0x35].Normal = 0x%x\n", KeyEntries[0x35].Normal));
    DEBUG(("XXX KeyEntries[0x50].Normal = 0x%x\n", KeyEntries[0x50].Normal));
  } else {
    KeyEntries = KeyOneByteEntries;
  }

  if ((mBdaPtr->KeyboardStatus1 & KBSF1_ALT_PRESSED) != 0) {
    Key = KeyEntries[Scancode].Alt;
  } else if ((mBdaPtr->KeyboardStatus1 & KBSF1_CTRL_PRESSED) != 0) {
    Key = KeyEntries[Scancode].Control;
  } else if ((mBdaPtr->KeyboardStatus1 & KBSF1_LEFT_SHIFT_PRESSED) != 0 ||
	     (mBdaPtr->KeyboardStatus1 & KBSF1_RIGHT_SHIFT_PRESSED) != 0) {
    Key = KeyEntries[Scancode].Shift;
  } else {
    Key = KeyEntries[Scancode].Normal;
  }

  DEBUG(("XXX Key = 0x%x\n", Key));
  if (Key == 0xffff)
    return;

  Newtail = mBdaPtr->KeyBufferTail + 2;
  if (Newtail == mBdaPtr->KeyBufferEnd)
    Newtail = mBdaPtr->KeyBufferStart;

  if (Newtail == mBdaPtr->KeyBufferHead)
    return;

  *(UINT16 *)((UINT8 *)(UINTN)0x400 + mBdaPtr->KeyBufferTail) = Key;
  mBdaPtr->KeyBufferTail = Newtail;
}

static VOID
ProcessScancode(UINT8 Scancode)
{
  DEBUG(("XXX ProcessScancode() 0x%x\n", Scancode));
  if (Scancode == 0xe0) {
    mBdaPtr->KeyboardStatus3 |= KBSF3_LAST_CODE_WAS_E0;
    return;
  }
  if (Scancode == 0xe1) {
    mBdaPtr->KeyboardStatus3 |= KBSF3_LAST_CODE_WAS_E1;
    return;
  }

  if ((Scancode & 0x80) != 0) {
    ProcessReleasedScancode(Scancode & 0x7F);
  } else {
    ProcessPressedScancode(Scancode);
  }

  if (Scancode != 0xe0) {
    mBdaPtr->KeyboardStatus3 &= ~KBSF3_LAST_CODE_WAS_E0;
  }
  if (Scancode != 0xe1) {
    mBdaPtr->KeyboardStatus3 &= ~KBSF3_LAST_CODE_WAS_E1;
  }
}

STATIC VOID
InterruptVector0x16ReadScancode(EFI_IA32_REGISTER_SET *Regs)
{
  UINT16  Key;

  DEBUG (("XXX InterruptVector0x16ReadScancode()\n"));
  DEBUG (("XXX KeyBufferHead = 0x%x KeyBufferTail = 0x%x\n", mBdaPtr->KeyBufferHead, mBdaPtr->KeyBufferTail));

  do {
    EnableInterrupts();
    DisableInterrupts();
  } while (mBdaPtr->KeyBufferHead == mBdaPtr->KeyBufferTail);

  Key = *(UINT16 *)((UINT8 *)(UINTN)0x400 + mBdaPtr->KeyBufferHead);
  Regs->X.AX = Key;
  Regs->E.EFlags.ZF = 0;
  switch (Regs->H.AL) {
  case '\n':
    DEBUG (("XXX InterruptVector0x16ReadScancode() Regs->H.AL=0%x '\\n'\n", Regs->H.AL));
    break;
  case '\r':
    DEBUG (("XXX InterruptVector0x16ReadScancode() Regs->H.AL=0%x '\\r'\n", Regs->H.AL));
    break;
  default:
    DEBUG (("XXX InterruptVector0x16ReadScancode() Regs->H.AL=0%x ('%c')\n", Regs->H.AL, Regs->H.AL));
    break;
  }
  DEBUG (("XXX InterruptVector0x16ReadScancode() Regs->H.AH=0%x\n", Regs->H.AH));
  DEBUG (("XXX InterruptVector0x16ReadScancode() Regs->X.AX=0%x\n", Regs->X.AX));

  mBdaPtr->KeyBufferHead += 2;
  if (mBdaPtr->KeyBufferHead == mBdaPtr->KeyBufferEnd)
    mBdaPtr->KeyBufferHead = mBdaPtr->KeyBufferStart;

  DEBUG (("XXX InterruptVector0x16ReadScancode() KeyBufferHead = 0x%x KeyBufferTail = 0x%x\n", mBdaPtr->KeyBufferHead, mBdaPtr->KeyBufferTail));
}

STATIC VOID
InterruptVector0x16PreviewScancode(EFI_IA32_REGISTER_SET *Regs)
{
  UINT16  Key;

  //DEBUG (("XXX InterruptVector0x16PreviewScancode()\n"));
  //DEBUG (("XXX InterruptVector0x16PreviewScancode() KeyBufferHead = 0x%x KeyBufferTail = 0x%x\n", mBdaPtr->KeyBufferHead, mBdaPtr->KeyBufferTail));
  if (mBdaPtr->KeyBufferHead == mBdaPtr->KeyBufferTail) {
    Regs->E.EFlags.ZF = 1;
  } else {
    Regs->E.EFlags.ZF = 0;
    Key = *(UINT16 *)((UINT8 *)(UINTN)0x400 + mBdaPtr->KeyBufferHead);
    Regs->X.AX = Key;
    switch (Regs->H.AL) {
    case '\n':
//      DEBUG (("XXX InterruptVector0x16PreviewScancode() Regs->H.AL=0%x '\\n'\n", Regs->H.AL));
      break;
    case '\r':
//      DEBUG (("XXX InterruptVector0x16PreviewScancode() Regs->H.AL=0%x '\\r'\n", Regs->H.AL));
      break;
    default:
//      DEBUG (("XXX InterruptVector0x16PreviewScancode() Regs->H.AL=0%x ('%c')\n", Regs->H.AL, Regs->H.AL));
      break;
    }
//    DEBUG (("XXX InterruptVector0x16PreviewScancode() Regs->H.AH=0%x\n", Regs->H.AH));
//    DEBUG (("XXX InterruptVector0x16PreviewScancode() Regs->X.AX=0%x\n", Regs->X.AX));
  }
}

/*
 * Keyboard I/O
 */
VOID
InterruptVector0x16(EFI_IA32_REGISTER_SET *Regs)
{
//  DEBUG (("XXX InterruptVector0x16() Regs->H.AL=0%x\n", Regs->H.AL));
//  DEBUG (("XXX InterruptVector0x16() Regs->H.AH=0%x\n", Regs->H.AH));
//  DEBUG (("XXX InterruptVector0x16() Regs->X.AX=0%x\n", Regs->X.AX));

  EnableInterrupts();
  DisableInterrupts();

  switch (Regs->H.AH) {
  case 0x0:     /* Read Keyboard Input */
//    DEBUG (("XXX InterruptVector0x16() Read Keyboard Input\n"));
    InterruptVector0x16ReadScancode(Regs);
    break;
  case 0x1:     /* Query Keyboard Status / Preview Key */
//    DEBUG (("XXX InterruptVector0x16() Query Keyboard Status / Preview Key\n"));
    InterruptVector0x16PreviewScancode(Regs);
    break;
  case 0x2:     /* Read Keyboard Shift Status */
//    DEBUG (("XXX InterruptVector0x16() Read Keyboard Shift Status\n"));
    Regs->H.AL = mBdaPtr->KeyboardStatus1;
    DEBUG (("XXX Regs->H.AL = 0x%x\n", Regs->H.AL));
    break;
  case 0x3:	/* Set Keyboard Typematic Rate */
    break;
  case 0x5:     /* Store keycode */
    Regs->H.AL = 1;
    break;
  case 0x10:
//    DEBUG (("XXX InterruptVector0x16() Read Extended Keyboard Input\n"));
    InterruptVector0x16ReadScancode(Regs);
    break;
  case 0x11:     /* Query Extended Keyboard Status / Preview Key */
//    DEBUG (("XXX InterruptVector0x16() Query Extended Keyboard Status / Preview Key\n"));
    InterruptVector0x16PreviewScancode(Regs);
    break;
  case 0x12:    /* Read Extended Keyboard Shift Status */
//    DEBUG (("XXX InterruptVector0x16() Read Extended Keyboard Shift Status\n"));
    Regs->H.AL = mBdaPtr->KeyboardStatus1;
    Regs->H.AH = mBdaPtr->KeyboardStatus2;
    break;
  default:
    DEBUG (("XXX InterruptVector0x16() Regs->H.AL=0%x\n", Regs->H.AL));
    DEBUG (("XXX InterruptVector0x16() Regs->H.AH=0%x\n", Regs->H.AH));
    DEBUG (("XXX InterruptVector0x16() Regs->X.AX=0%x\n", Regs->X.AX));
    DEBUG (("XXX keyboard unhandled\n"));
//    for (;;) ;
    break;
  }
}

VOID
KeyboardInitialize(VOID)
{
  EFI_STATUS  Status;
  UINT8       CommandByte;
  UINTN       TryTime;

  mBdaPtr->KeyBufferStart = 0x1E;
  mBdaPtr->KeyBufferEnd = 0x3E;
  mBdaPtr->KeyBufferHead = mBdaPtr->KeyBufferTail = mBdaPtr->KeyBufferStart;

  mBdaPtr->KeyboardStatus3 = KBSF3_ENHANCED_KBD;

  if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA) != 0) {
    while (!EFI_ERROR (Status) && TryTime < KEYBOARD_MAX_TRY) {
      Status = KeyboardRead(&CommandByte);
      TryTime ++;
    }

    if (TryTime == KEYBOARD_MAX_TRY) {
      return;
    }
  }

  Status = KeyboardCommand(KEYBOARD_8042_COMMAND_DISABLE_KEYBOARD_INTERFACE);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardCommand(KEYBOARD_8042_COMMAND_DISABLE_MOUSE_INTERFACE);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardCommand(KEYBOARD_8042_COMMAND_CONTROLLER_SELF_TEST);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWaitForValue(0x55);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWrite(KEYBOARD_8048_COMMAND_SELECT_SCAN_CODE_SET);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWaitForValue(KEYBOARD_8048_RETURN_8042_ACK);
  if (EFI_ERROR (Status)) {
    return;
  }
 
  Status = KeyboardWrite(0x02); // scan code set 2
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWaitForValue(KEYBOARD_8048_RETURN_8042_ACK);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWrite(KEYBOARD_8048_COMMAND_CLEAR_OUTPUT_DATA);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWaitForValue(KEYBOARD_8048_RETURN_8042_ACK);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardCommand(KEYBOARD_8042_COMMAND_WRITE);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = KeyboardWrite(KEYBOARD_CMMBYTE_TRANSLATE |
			 KEYBOARD_CMMBYTE_DISABLE_AUX |
			 KEYBOARD_CMMBYTE_SELFTEST_OK |
			 KEYBOARD_CMMBYTE_ENABLE_KBINT);
  if (EFI_ERROR (Status)) {
    return;
  }

  DEBUG (("XXX KeyboardInitialize() done (0x%lx)\n", ReadTsc()));
}

VOID
InterruptVector0x09(EFI_IA32_REGISTER_SET *Regs)
{
  UINT8                   Data;

  DEBUG (("XXX InterruptVector0x09() (0x%lx)\n", ReadTsc()));

  KeyboardCommand(KEYBOARD_8042_COMMAND_DISABLE_KEYBOARD_INTERFACE);

  if ((KeyReadStatusRegister() & KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA) != 0) {
    Data = KeyReadDataRegister();
    ProcessScancode(Data);
  }

  KeyboardCommand(KEYBOARD_8042_COMMAND_ENABLE_KEYBOARD_INTERFACE);

  mLegacy8259->EndOfInterrupt(mLegacy8259, Efi8259Irq1);

  DEBUG (("XXX InterruptVector0x09() done\n"));
}

