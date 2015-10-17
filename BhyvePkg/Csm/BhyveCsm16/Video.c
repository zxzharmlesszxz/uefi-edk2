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

#define DEBUG_PORT      0x220
#include "Debug.h"
#include "Printf.h"
#include "String.h"

#define VGA_BUF_ADDR            0xA0000
#define VGA_BUF_LENGTH          0x10000

#define VGA_GFX_INDEX           0x3CE
#define VGA_GFX_DATA            0x3CF

#define VGA_CRTC_INDEX          0x3D4
#define VGA_CRTC_DATA           0x3D5

#define VGA_WRITE_ATTR_INDEX    0x3C0
#define VGA_WRITE_ATTR_DATA     0x3C0

#define VGA_SEQ_INDEX           0x3C4
#define VGA_SEQ_DATA            0x3C5

#define VGA_PALETTE_WRITE       0x3C8
#define VGA_PALETTE_READ        0x3C7
#define VGA_PALETTE_DATA        0x3C9

#define VGA_INPUT_STATUS_1      0x3DA
#define VGA_WRITE_MISC_PORT     0x3C2

#define VGA_READ_FEATURE_PORT   0x3CA
#define VGA_WRITE_FEATURE_PORT  0x3DA

#define VGA_SEQ_CNT     5
#define VGA_CRT_CNT     25
#define VGA_ATR_CNT     21
#define VGA_GFX_CNT     9

enum MemoryModel {
  MemoryModelText,
  MemoryModelPackedPixel
};

struct VGAState {
  enum MemoryModel MemoryModel;

  /* Miscellaneous output register. */
  unsigned char MiscOutput;

  /* Sequencer registers. */
  unsigned char SequencerData[VGA_SEQ_CNT];

  /* CRT Controller registers. */
  unsigned char CRTCData[VGA_CRT_CNT];

  /* Graphics controller registers. */
  unsigned char GraphicsData[VGA_GFX_CNT];

  /* Attribute controller registers. */
  unsigned char AttrData[VGA_ATR_CNT];
};

static const struct VGAState VGAMode3 = {
  MemoryModelText,

  /* Miscellaneous output register. */
  0x67,

  /* Sequencer registers. */
  { 0x01, 0x00, 0x03, 0x00, 0x02 },

  /* CRT controller registers. */
  {
    0x5f, 0x4f, 0x50, 0x82, 0x55, 0x81, 0xbf, 0x1f, 0x00, 0x4f,
    0x0d, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x8e, 0x8f, 0x28,
    0x1f, 0x96, 0xb9, 0xa3, 0xff,
  },

  /* Graphics controller registers. */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0e, 0x0f, 0xff },

  /* Attribute controller registers. */
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x0c, 0x00, 0x0f, 0x08, 0x00,
  },
};

static const struct VGAState VGAMode12 = {
  MemoryModelPackedPixel,

  /* Miscellaneous output register. */
  0xe3,

  /* Sequencer registers. */
  {0x03, 0x21, 0x0f, 0x00, 0x06},

  /* CRT controller registers. */
  {
    0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0x0b, 0x3e, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0xea, 0x8c,
    0xdf, 0x28, 0x00, 0xe7, 0x04, 0xe3, 0xff,
  },

  /* Graphics controller registers. */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0f, 0xff },

  /* Attribute controller registers. */
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x01, 0x00, 0x0f, 0x00, 0x00,
  },
};

STATIC CONST UINT8 colorData[4] = {
  0x00, 0x15, 0x2a, 0x3f,
};

#define palette_entry(r,g,b)  (((r) << 4)|((g) << 2)|(b))

static const unsigned char mode_03_palette[] = {
  palette_entry(0, 0, 0),
  palette_entry(0, 0, 2),
  palette_entry(0, 2, 0),
  palette_entry(0, 2, 2),
  palette_entry(2, 0, 0),
  palette_entry(2, 0, 2),
  palette_entry(2, 2, 0),
  palette_entry(2, 2, 2),
  palette_entry(0, 0, 1),
  palette_entry(0, 0, 3),
  palette_entry(0, 2, 1),
  palette_entry(0, 2, 3),
  palette_entry(2, 0, 1),
  palette_entry(2, 0, 3),
  palette_entry(2, 2, 1),
  palette_entry(2, 2, 3),
  palette_entry(0, 1, 0),
  palette_entry(0, 1, 2),
  palette_entry(0, 3, 0),
  palette_entry(0, 3, 2),
  palette_entry(2, 1, 0),
  palette_entry(2, 1, 2),
  palette_entry(2, 3, 0),
  palette_entry(2, 3, 2),
  palette_entry(0, 1, 1),
  palette_entry(0, 1, 3),
  palette_entry(0, 3, 1),
  palette_entry(0, 3, 3),
  palette_entry(2, 1, 1),
  palette_entry(2, 1, 3),
  palette_entry(2, 3, 1),
  palette_entry(2, 3, 3),
  palette_entry(1, 0, 0),
  palette_entry(1, 0, 2),
  palette_entry(1, 2, 0),
  palette_entry(1, 2, 2),
  palette_entry(3, 0, 0),
  palette_entry(3, 0, 2),
  palette_entry(3, 2, 0),
  palette_entry(3, 2, 2),
  palette_entry(1, 0, 1),
  palette_entry(1, 0, 3),
  palette_entry(1, 2, 1),
  palette_entry(1, 2, 3),
  palette_entry(3, 0, 1),
  palette_entry(3, 0, 3),
  palette_entry(3, 2, 1),
  palette_entry(3, 2, 3),
  palette_entry(1, 1, 0),
  palette_entry(1, 1, 2),
  palette_entry(1, 3, 0),
  palette_entry(1, 3, 2),
  palette_entry(3, 1, 0),
  palette_entry(3, 1, 2),
  palette_entry(3, 3, 0),
  palette_entry(3, 3, 2),
  palette_entry(1, 1, 1),
  palette_entry(1, 1, 3),
  palette_entry(1, 3, 1),
  palette_entry(1, 3, 3),
  palette_entry(3, 1, 1),
  palette_entry(3, 1, 3),
  palette_entry(3, 3, 1),
  palette_entry(3, 3, 3),
};

extern unsigned char FONTDATA[];

STATIC const struct VGAState *CurrentState;

STATIC int CurrentVideoMode;
STATIC int CurrentActivePage;

STATIC VOID
VGASetFont(VOID)
{
  UINT8 *to, *from;
  int i, j;

  DPRINTF(DBG_WARN, ("XXX VGASetFont()\n"));

  /* Sync-reset the sequencer registers */
  IoWrite8(VGA_SEQ_INDEX, 0x00);
  IoWrite8(VGA_SEQ_DATA, 0x01);       /* Low order two bits are reset bits */

  /*
   * Enable write to plane 2
   */
  IoWrite8(VGA_SEQ_INDEX, 0x02);
  IoWrite8(VGA_SEQ_DATA, 0x04);

  /*
   * Sequentially access data
   */
  IoWrite8(VGA_SEQ_INDEX, 0x04);
  IoWrite8(VGA_SEQ_DATA, 0x07);

  /* Sync-reset ended */
  IoWrite8(VGA_SEQ_INDEX, 0x00);
  IoWrite8(VGA_SEQ_DATA, 0x03);       /* Low order two bits are reset bits */

  /*
   * Select plane 2 Read Mode 0
   */
  IoWrite8(VGA_GFX_INDEX, 0x04);
  IoWrite8(VGA_GFX_DATA, 0x02);

  /*
   * System addresses sequentially access data, follow Memory
   * Mode register bit 2 in the sequencer
   */
  IoWrite8(VGA_GFX_INDEX, 0x05);
  IoWrite8(VGA_GFX_DATA, 0x00);

  /*
   * Set the range of host memory addresses decoded by VGA
   * hardware -- A0000h-BFFFFh (128K region)
   */
  IoWrite8(VGA_GFX_INDEX, 0x06);
  IoWrite8(VGA_GFX_DATA, 0x00);

  /*
   * This assumes 8x16 characters, which yield the traditional 80x25
   * screen.
   */
  for (i = 0; i < 256; i++) {
    from = &FONTDATA[i * 16];
    to = (UINT8 *)VGA_BUF_ADDR + i * 0x20;
    for (j = 0; j < 16; j++)
      *to++ = *from++;
  }

  /* Sync-reset the sequencer registers */
  IoWrite8(VGA_SEQ_INDEX, 0x00);
  IoWrite8(VGA_SEQ_DATA, 0x01);       /* Low order two bits are reset bits */

  /* Enable write to plane 0 and 1 */
  IoWrite8(VGA_SEQ_INDEX, 0x02);
  IoWrite8(VGA_SEQ_DATA, 0x03);

  /*
   * Enable character map selection and odd/even addressing
   */
  IoWrite8(VGA_SEQ_INDEX, 0x04);
  IoWrite8(VGA_SEQ_DATA, 0x03);

  /*
   * Select font map
   */
  IoWrite8(VGA_SEQ_INDEX, 0x03);
  IoWrite8(VGA_SEQ_DATA, 0x00);

  /* Sync-reset ended */
  IoWrite8(VGA_SEQ_INDEX, 0x00);
  IoWrite8(VGA_SEQ_DATA, 0x03);       /* Low order two bits are reset bits */

  /* Select plane 0 */
  IoWrite8(VGA_GFX_INDEX, 0x04);
  IoWrite8(VGA_GFX_DATA, 0x00);

  /* Enable odd/even addressing mode */
  IoWrite8(VGA_GFX_INDEX, 0x05);
  IoWrite8(VGA_GFX_DATA, 0x10);

  /*
   * Set the range of host memory addresses decoded by VGA
   * hardware -- B8000h-BFFFFh (32K region)
   */
  IoWrite8(VGA_GFX_INDEX, 0x06);
  IoWrite8(VGA_GFX_DATA, 0x0e);
}

STATIC VOID
VGASetCursorPosition(UINTN Page, UINT8 X, UINT8 Y)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;
  UINT16  CursorLocation;

  DPRINTF (DBG_VERB, ("XXX VGASetCursorPosition() Page %d X %d Y %d\n", Page, X, Y));
  BdaPtr->CursorPosition[Page] = (Y << 8) | X;

  CursorLocation = (Y * mBdaPtr->TextColumns + X);
  DPRINTF (DBG_VERB, ("XXX VGASetCursorPosition() CursorLocation = 0x%x\n", CursorLocation));
  IoWrite8(VGA_CRTC_INDEX, 0xe);
  IoWrite8(VGA_CRTC_DATA, CursorLocation >> 8);
  IoWrite8(VGA_CRTC_INDEX, 0xf);
  IoWrite8(VGA_CRTC_DATA, CursorLocation & 0xFF);
}

STATIC VOID
VGAGetCursorPosition(UINTN Page, UINT8 *X, UINT8 *Y)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;
  UINT16  XY;

  XY = BdaPtr->CursorPosition[Page];
  *X = XY & 0xff;
  *Y = XY >> 8;
  DPRINTF (DBG_VERB, ("XXX VGAGetCursorPosition() Page %d X %d Y %d\n", Page, *X, *Y));
}


STATIC VOID
VGASetVideoMode(UINTN  ModeNumber, BOOLEAN Retain)
{
  int j, k;

  DPRINTF (DBG_INFO, ("XXX VGASetVideoMode() Mode=0x%x Retain=%s\n", ModeNumber, Retain ? L"TRUE" : L"FALSE"));

  switch (ModeNumber) {
  case 0x3:
    CurrentState = &VGAMode3;
    mBdaPtr->TextColumns = 80;
    mBdaPtr->TextRowsMinusOne = 25 - 1;
    mBdaPtr->ScanLinesPerChar = 16;
    break;
  case 0x12:
    CurrentState = &VGAMode12;
    mBdaPtr->TextColumns = 80;
    mBdaPtr->TextRowsMinusOne = 30 - 1;
    mBdaPtr->ScanLinesPerChar = 16;
    break;
  default:
    DPRINTF (DBG_CRIT, ("XXX spinning \n"));
    for (;;);
    return;
  }

  /* Turn the video off while we are doing this.... */
  IoWrite8(VGA_SEQ_INDEX, 1);
  IoWrite8(VGA_SEQ_DATA, CurrentState->SequencerData[1]);

  /* Set the attribute flip-flop to "index" */
  IoRead8(VGA_INPUT_STATUS_1);

  /* Give palette to CPU, turns off video */
  IoWrite8(VGA_WRITE_ATTR_INDEX, 0x00);

  /* Set the general registers */
  IoWrite8(VGA_WRITE_MISC_PORT, CurrentState->MiscOutput);
  IoWrite8(VGA_WRITE_FEATURE_PORT, 0x00);

  /* Load the sequencer registers */
  for (k = 0; k < VGA_SEQ_CNT; k++) {
    IoWrite8(VGA_SEQ_INDEX, k);
    IoWrite8(VGA_SEQ_DATA, CurrentState->SequencerData[k]);
  }
  IoWrite8(VGA_SEQ_INDEX, 0x00);
  IoWrite8(VGA_SEQ_DATA, 0x03);       /* Low order two bits are reset bits */

  /* Load the CRTC registers.
   * CRTC registers 0-7 are locked by a bit in register 0x11. We need
   * to unlock these registers before we can start setting them.
   */
  IoWrite8(VGA_CRTC_INDEX, 0x11);
  IoWrite8(VGA_CRTC_DATA, 0x00);      /* Unlocks registers 0-7 */
  for (k = 0; k < VGA_CRT_CNT; k++) {
    IoWrite8(VGA_CRTC_INDEX, k);
    IoWrite8(VGA_CRTC_DATA, CurrentState->CRTCData[k]);
  }

  /* Load the attribute registers */
  IoRead8(VGA_INPUT_STATUS_1);        /* Set the attribute flip-flop to "index" */
  for (k = 0; k < VGA_ATR_CNT; k++) {
    IoWrite8(VGA_WRITE_ATTR_INDEX, k);
    IoWrite8(VGA_WRITE_ATTR_DATA, CurrentState->AttrData[k]);
  }

  /* Load graphics registers */
  for (k = 0; k < VGA_GFX_CNT; k++) {
    IoWrite8(VGA_GFX_INDEX, k);
    IoWrite8(VGA_GFX_DATA, CurrentState->GraphicsData[k]);
  }

  /* Set up the palette. */
  IoWrite8(VGA_PALETTE_WRITE, 0);
  for (k = 0; k < 256; k++) {
    j = mode_03_palette[k % 64];
    IoWrite8(VGA_PALETTE_DATA, colorData[(j >> 4) & 3]);
    IoWrite8(VGA_PALETTE_DATA, colorData[(j >> 2) & 3]);
    IoWrite8(VGA_PALETTE_DATA, colorData[j & 3]);
  }

  /* Re-enable video */
  if (!Retain) {
    /* First, clear memory to zeros */
    ZeroMem((VOID *)VGA_BUF_ADDR, VGA_BUF_LENGTH);

    switch (ModeNumber) {
    case 0x3:
#if 1
      for (k = 0; k < 25; k++) {
        for (j = 0; j < 80; j++) {
          *(UINT8 *)((UINTN)0xB8000 + (k * mBdaPtr->TextColumns + j) * 2) = ' ';
          *(UINT8 *)((UINTN)0xB8000 + ((k * mBdaPtr->TextColumns + j) * 2) + 1) = 0x7;
        }
      }
#endif
      break;
    }
  }

  /* Set the attribute flip-flop to "index" */
  IoRead8(VGA_INPUT_STATUS_1);

  /* Give the palette back to the VGA */
  IoWrite8(VGA_WRITE_ATTR_INDEX, 0x20);

  // Really re-enable video.
  IoWrite8(VGA_SEQ_INDEX, 1);
  IoWrite8(VGA_SEQ_DATA, (CurrentState->SequencerData[1] & ~0x20));

  switch (ModeNumber) {
  case 0x3:
    VGASetFont();
    break;
  }

  for (k = 0; k < 8; k++) {
    VGASetCursorPosition(k, 0, 0);
  }

  CurrentVideoMode = ModeNumber;
}

STATIC VOID
VGAReadCharPosition(UINTN Page, UINTN X, UINTN Y, UINT8 *Ch, INT8 *Attr)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;

  *Ch = *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2);
  *Attr = *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1);
  DPRINTF (DBG_VERB, ("XXX VGAReadCharPosition() X %d Y %d Attr 0x%x/Char '%c'\n", X, Y, *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1), *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2) ));
}

STATIC VOID
VGAReadChar(UINT8 *Ch, UINT8 *Attr)
{
  UINT8 X, Y;

  VGAGetCursorPosition(CurrentActivePage, &X, &Y);
  VGAReadCharPosition(CurrentActivePage, X, Y, Ch, Attr);
}

STATIC VOID
VGAWriteCharPositionPackedPixel(UINTN X, UINTN Y, UINT8 Ch, UINT8 Color)
{
  UINTN N, Offset;
  UINT8 *Pattern;

  DPRINTF (DBG_VERB, ("XXX VGAWriteCharPositionPackedPixel() X %d Y %d Char '%c' Color 0x%x\n", X, Y, Ch, Color));

  /*
   * Enable all planes
   */
  IoWrite8(VGA_SEQ_INDEX, 0x02);
  IoWrite8(VGA_SEQ_DATA, 0x0f);

  /*
   * Use set/reset to produce color
   */
  IoWrite8(VGA_GFX_INDEX, 0x00);
  IoWrite8(VGA_GFX_DATA, Color);
  IoWrite8(VGA_GFX_INDEX, 0x01);
  IoWrite8(VGA_GFX_DATA, 0xf);

  /*
   * Select write mode 3
   */
  IoWrite8(VGA_GFX_INDEX, 0x05);
  IoWrite8(VGA_GFX_DATA, 0x03);

  /*
   * Select function 'replace' and no rotate
   */
  IoWrite8(VGA_GFX_INDEX, 0x03);
  IoWrite8(VGA_GFX_DATA, 0x00);

  for (N = 0; N < 16; N++) {
    Offset = (Y * 16 + N) * mBdaPtr->TextColumns + X;
    Pattern = &FONTDATA[Ch * 16];

    /*
     * Setup the bit mask.
     */
    IoWrite8(VGA_GFX_INDEX, 0x08);
    IoWrite8(VGA_GFX_DATA, Pattern[N]);

    *((UINT8 *)VGA_BUF_ADDR + Offset) = Pattern[N];
  }
}

STATIC VOID
VGAWriteCharPosition(UINTN X, UINTN Y, UINT8 Ch, INT8 Attr)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;

  switch (CurrentState->MemoryModel) {
  case MemoryModelText:
    DPRINTF (DBG_VERB, ("XXX VGAWriteCharPosition() X %d Y %d Attr 0x%x/Char '%c'\n", X, Y, Attr, Ch));
    *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2) = Ch;
    if (Attr >= 0)
      *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1) = Attr;
    break;
  case MemoryModelPackedPixel:
    VGAWriteCharPositionPackedPixel(X, Y, Ch, Attr);
    break;
  }
}

STATIC VOID
VGAWriteChars(UINTN Page, UINTN Count, UINT8 Ch, UINT8 Attr)
{
  UINT8 X, Y;

  VGAGetCursorPosition(Page, &X, &Y);
  while (Count--) {
    VGAWriteCharPosition(X + Count, Y, Ch, Attr);
  }
}

STATIC VOID
VGAWriteTeletype(UINT8 Ch)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;
  UINT8 X, Y;

  VGAGetCursorPosition(CurrentActivePage, &X, &Y);

  switch (Ch) {
  case 0x07:    /* bell */
    break;
  case 0x08:    /* backspace */
    if (X > 0) {
      X--;
    }
    break;
  case 0x09:    /* tab */
    X = X + ((X + 8) & ~7);
    break;
  case 0x0a:    /* new line */
    Y++;
    break;
  case 0x0b:    /* vertical tab */
    break;
  case 0x0c:    /* form feed */
    break;
  case 0x0d:    /* carriage return */
    X = 0;
    break;
  default:
    VGAWriteCharPosition(X++, Y, Ch, -1);
    break;
  }

  if (X >= BdaPtr->TextColumns) {
    X = 0;
    Y++;
  }
  if (Y >= (BdaPtr->TextRowsMinusOne + 1)) {
    Y = (BdaPtr->TextRowsMinusOne + 1) - 1;
  }

  VGASetCursorPosition(CurrentActivePage, X, Y);
}

STATIC VOID
VGAScrollUp(UINTN X1, UINTN Y1, UINTN X2, UINTN Y2, UINTN Lines, UINT8 FillAttr)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;
  UINTN X, Y;
  UINT8 Ch, Attr;

  DPRINTF(DBG_VERB, ("XXX VGAScrollUp() X1 %d Y1 %d X2 %d Y2 %d Lines %d Attr 0x%x\n", X1, Y1, X2, Y2, Lines, Attr));

  
#if 0   /* XXX */
        if (X2 > 79)
                for (;;) ;
#endif

  if (Lines == 0)
    Lines = (BdaPtr->TextRowsMinusOne + 1);

  Lines = MIN(Y2 + 1 - Y1, Lines);

  // Scroll
  for (Y = Y1 + Lines; Y <= Y2; Y++) {
    for (X = X1; X <= X2; X++) {
      Ch = *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2);
      Attr = *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1);
      *(UINT8 *)((UINTN)0xB8000 + ((Y - Lines) * BdaPtr->TextColumns + X) * 2) = Ch;
      *(UINT8 *)((UINTN)0xB8000 + (((Y - Lines) * BdaPtr->TextColumns + X) * 2) + 1) = Attr;
    }
  }

  // Fill
  for (Y = Y2 + 1 - Lines; Y < Y2 + 1; Y++) {
    for (X = X1; X <= X2; X++) {
      *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2) = ' ';
      *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1) = FillAttr;
    }
  }
}

STATIC VOID
VGAScrollDown(UINTN X1, UINTN Y1, UINTN X2, UINTN Y2, UINTN Lines, UINT8 FillAttr)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;
  UINTN X, Y;
  UINT8 Ch, Attr;

  DPRINTF(DBG_VERB, ("XXX VGAScrollDown() X1 %d Y1 %d X2 %d Y2 %d Lines %d Attr 0x%x\n", X1, Y1, X2, Y2, Lines, Attr));

  if (Lines == 0)
    Lines = (BdaPtr->TextRowsMinusOne + 1);

  Lines = MIN(Y2 + 1 - Y1, Lines);

  // Scroll
  for (Y = Y1 + Lines; Y <= Y2; Y++) {
    for (X = X1; X <= X2; X++) {
      Ch = *(UINT8 *)((UINTN)0xB8000 + ((Y - Lines) * BdaPtr->TextColumns + X) * 2);
      Attr = *(UINT8 *)((UINTN)0xB8000 + (((Y - Lines) * BdaPtr->TextColumns + X) * 2) + 1);
      *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2) = Ch;
      *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1) = Attr;
    }
  }

  // Fill
  for (Y = Y2 + 1 - Lines; Y < Y2 + 1; Y++) {
    for (X = X1; X <= X2; X++) {
      *(UINT8 *)((UINTN)0xB8000 + (Y * BdaPtr->TextColumns + X) * 2) = ' ';
      *(UINT8 *)((UINTN)0xB8000 + ((Y * BdaPtr->TextColumns + X) * 2) + 1) = FillAttr;
    }
  }
}

STATIC VOID
InterruptVector0x10Palette(EFI_IA32_REGISTER_SET *Regs)
{
  UINTN  Count;
  UINT8  *Value;

  switch (Regs->H.AL) {
  case 0x00:	/* Set Individual Palette Register */
    DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Set Individual Palette Register\n"));
    IoRead8(VGA_INPUT_STATUS_1);
    IoWrite8(VGA_WRITE_ATTR_INDEX, Regs->H.BL);
    IoWrite8(VGA_WRITE_ATTR_DATA, Regs->H.BH);
    break;
  case 0x02:	/* Set All Palette Registers and OverScan Register */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x10() Set All Palette Registers\n"));
    Value = (UINT8 *)(UINT64)((Regs->X.ES << 4) + (Regs->X.DX));
    for (Count = 0; Count < 16; Count++) {
      DPRINTF (DBG_VERB, ("XXX [%02d] = 0x%x\n", Count, *Value));
      IoRead8(VGA_INPUT_STATUS_1);
      IoWrite8(VGA_WRITE_ATTR_INDEX, Count);
      IoWrite8(VGA_WRITE_ATTR_DATA, *Value);
      Value++;
    }
    break;
  case 0x10:	/* Set Individual Color Register */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x10() Set Individual Color Register\n"));
    IoWrite8(VGA_PALETTE_WRITE, Regs->X.BX);
    IoWrite8(VGA_PALETTE_DATA, Regs->H.DH);
    IoWrite8(VGA_PALETTE_DATA, Regs->H.CH);
    IoWrite8(VGA_PALETTE_DATA, Regs->H.CL);
    break;
  case 0x12:	/* Set Block of Color Registers */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x10() Set Block of Color Registers\n"));
    Value = (UINT8 *)(UINT64)((Regs->X.ES << 4) + (Regs->X.DX));
    IoWrite8(VGA_PALETTE_WRITE, Regs->X.BX);
    for (Count = 0; Count < Regs->X.CX; Count++) {
      DPRINTF (DBG_VERB, ("XXX [%02d] = 0x%x\n", Count, *Value));
      IoWrite8(VGA_PALETTE_DATA, *Value);
      Value++;
      DPRINTF (DBG_VERB, ("XXX [%02d] = 0x%x\n", Count, *Value));
      IoWrite8(VGA_PALETTE_DATA, *Value);
      Value++;
      DPRINTF (DBG_VERB, ("XXX [%02d] = 0x%x\n", Count, *Value));
      IoWrite8(VGA_PALETTE_DATA, *Value);
      Value++;
    }
    break;
  default:
    DPRINTF (DBG_WARN, ("XXX video (Palette) unhandled\n"));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10()\n"));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AL=0%x\n", Regs->H.AL));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AH=0%x\n", Regs->H.AH));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->X.AX=0%x\n", Regs->X.AX));
    //for (;;) ;
    break;
  }
}

/*
 * Video IO
 */
VOID
InterruptVector0x10(EFI_IA32_REGISTER_SET *Regs)
{
  BDA  *BdaPtr = (BDA *)(UINTN)0x400;

  DPRINTF (DBG_VERB, ("XXX InterruptVector0x10()\n"));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Regs->H.AL=0%x\n", Regs->H.AL));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Regs->H.AH=0%x\n", Regs->H.AH));
  DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Regs->X.AX=0%x\n", Regs->X.AX));

  switch (Regs->H.AH) {
  case 0x00:    /* Set Video Mode */
    DPRINTF (DBG_INFO, ("XXX InterruptVector0x10() Set Mode Mode=0x%x Retain=%s\n", Regs->H.AL & 0x7f, (Regs->H.AL & 0x80) ? L"TRUE" : L"FALSE"));
    VGASetVideoMode(Regs->H.AL & 0x7f, (Regs->H.AL & 0x80) != 0);
    break;
  case 0x01:    /* Set Cursor Type */
    break;
  case 0x02:    /* Set Cursor Postion */
    VGASetCursorPosition(Regs->H.BH, Regs->H.DL, Regs->H.DH);
    break;
  case 0x03:    /* Get Cursor Postion */
    VGAGetCursorPosition(Regs->H.BH, &Regs->H.DL, &Regs->H.DH);
    break;
  case 0x05:    /* Select Active Display Page */
    break;
  case 0x06:    /* Window Scroll Up */
    VGAScrollUp(Regs->H.CL, Regs->H.CH, Regs->H.DL, Regs->H.DH, Regs->H.AL, Regs->H.BH);
    break;
  case 0x07:    /* Window Scroll Down */
    VGAScrollDown(Regs->H.CL, Regs->H.CH, Regs->H.DL, Regs->H.DH, Regs->H.AL, Regs->H.BH);
    break;
  case 0x08:    /* Read Attribute / Character at Current Cursor Position */
    VGAReadChar(&Regs->H.AL, &Regs->H.AH);
    break;
  case 0x09:    /* Write Attribute / Character at Current Cursor Position */
    DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Count %d Attr 0x%x/Char '%c' at Current Position\n", Regs->X.CX, Regs->X.CX, Regs->H.AL));
    switch (Regs->H.AL) {
    case '\n':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Attr 0x%x / Char '\\n' (0x%02x)\n", Regs->H.BL, Regs->H.AL));
      break;
    case '\r':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Attr 0x%x / Char '\\r' (0x%02x)\n", Regs->H.BL, Regs->H.AL));
      break;
    default:
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Attr 0x%x / Ch '%c' (0x%02x)\n", Regs->H.BL, Regs->H.AL, Regs->H.AL));
      break;
    }
    VGAWriteChars(Regs->H.BH, Regs->X.CX, Regs->H.AL, Regs->H.BL);
    break;
  case 0x0a:    /* Write Character at Current Cursor Position */
    switch (Regs->H.AL) {
    case '\n':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write (Attr 0x%x) Char '\\n' (0x%02x)\n", Regs->H.AL));
      break;
    case '\r':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write (Attr 0x%x) Char '\\r' (0x%02x)\n", Regs->H.AL));
      break;
    default:
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write (Attr 0x%x) Ch '%c'\n", Regs->H.AL, Regs->H.AL));
      break;
    }
    //DEBUG (("XXX InterruptVector0x10() Write Count %d Char '%c' at Current Position\n", Regs->X.CX, Regs->H.AL));
    if (CurrentState->MemoryModel == MemoryModelText) {
      VGAWriteChars(Regs->H.BH, Regs->X.CX, Regs->H.AL, -1);
    } else {
      VGAWriteChars(Regs->H.BH, Regs->X.CX, Regs->H.AL, Regs->H.BL);
    }
    break;
  case 0x0e:    /* Write Teletype Character */
    switch (Regs->H.AL) {
    case '\n':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Teletype Char '\\n' (0x%02x)\n", Regs->H.AL));
      break;
    case '\r':
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Teletype Char '\\r' (0x%02x)\n", Regs->H.AL));
      break;
    default:
      DPRINTF (DBG_VERB, ("XXX InterruptVector0x10() Write Teletype Char '%c' (0x%02x)\n", Regs->H.AL, Regs->H.AL));
      break;
    }
    VGAWriteTeletype(Regs->H.AL);
    break;
  case 0x0f:    /* Get Video State */
    Regs->H.AL = CurrentVideoMode;
    Regs->H.AH = BdaPtr->TextColumns;
    Regs->H.BH = CurrentActivePage;
    break;
  case 0x10:    /* Palette */
    InterruptVector0x10Palette(Regs);
    break;
  case 0x11:    /* Character Generator */
    switch (Regs->H.AL) {
    case 0x30:  /* Get Font Information */
      switch (Regs->H.BH) {
      case 0x6: /* Return BIOS 8x16 font pointer */
        Regs->X.ES = (((UINTN)FONTDATA) & ~0xffff) >> 4;
        Regs->X.BP = ((UINTN)FONTDATA) & 0xffff;

        DPRINTF (DBG_INFO, ("XXX Get font information 0x%x Regs->X.ES=0%x Regs->X.BP=0x%x\n", FONTDATA, Regs->X.ES, Regs->X.BP));
        break;
      }
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX video (Character Generator) unhandled\n"));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10()\n"));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AL=0%x\n", Regs->H.AL));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AH=0%x\n", Regs->H.AH));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->X.AX=0%x\n", Regs->X.AX));
      //for (;;) ;
      break;
    }
    break;
  case 0x12:    /* Special Functions/Alternate Select */
    switch (Regs->H.BL) {
    case 0x10:  /* Get Current Display Configuration */
      Regs->H.BH = 0x0; /* color */
      Regs->H.BL = 0x3; /* 256k */
      Regs->H.CH = 0x0;
      Regs->H.CL = 0x0;
      break;
    case 0x20:  /* Select Alternate Print Screen Handler */
      break;
    case 0x34:  /* Cursor Emulation */
      mBdaPtr->VideoModeOptions &= 0x1;
      mBdaPtr->VideoModeOptions |= (Regs->H.AL & 0x1);
      break;
    default:
      DPRINTF (DBG_WARN, ("XXX video (Special functions/Alternate select) unhandled\n"));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10()\n"));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AL=0%x\n", Regs->H.AL));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AH=0%x\n", Regs->H.AH));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->X.AX=0%x\n", Regs->X.AX));
      DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.BL=0%x\n", Regs->H.BL));
      Regs->H.BH = 0;
      Regs->H.BL = 0x03;
      Regs->X.CX = 0;
      //for (;;) ; // Windows
      break;
    }
    break;
  case 0x1a:    /* Video Display Combination Code (DCC) */
    switch (Regs->H.AL) {
    case 0x0:	/* Get Display Combination Code (DCC) */
      Regs->H.AL = 0x1a;
      Regs->H.BH = 0x0;
      break;
    case 0x1:	/* Set Display Combination Code (DCC) */
      break;
    }
    break;
  default:
    DPRINTF (DBG_WARN, ("XXX video unhandled\n"));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10()\n"));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AL=0%x\n", Regs->H.AL));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->H.AH=0%x\n", Regs->H.AH));
    DPRINTF (DBG_WARN, ("XXX InterruptVector0x10() Regs->X.AX=0%x\n", Regs->X.AX));
    //for (;;) ; // Windows
    break;
  }
}

VOID
VGAInitialize(VOID)
{
  DPRINTF (DBG_INFO, ("XXX VGAInitialize()\n"));

  mBdaPtr->VideoModeOptions = 0x60;     /* 256k, active, color */
  mBdaPtr->VideoDisplayDataArea = 0x01; /* VGA is active */
  mBdaPtr->VideoDCC = 0x08;		/* VGA with analog color monitor */

  VGASetVideoMode(0x3, FALSE);

#if 0
  {
    UINT16 Val16;
    UINT32 Val32;
    UINT64 Val64;

    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 0) = 'X';
    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 0 + 1) = 0x7;

    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 2) = 'Y';
    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 2 + 1) = 0x7;

    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 4) = 'Z';
    *(UINT8 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 4 + 1) = 0x7;

    Val16 = *(UINT16 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 0);
    DEBUG(("XXX Val16 = 0x%x\n", Val16));
    Val32 = *(UINT32 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 0);
    DEBUG(("XXX Val32 = 0x%x\n", Val32));
    Val64 = *(UINT64 *)(0xB8000 + 0 * mBdaPtr->TextColumns + 0);
    DEBUG(("XXX Val64 = 0x%lx\n", Val64));

    DEBUG(("XXX spinning \n"));
    for (;;) ;
  }
#endif
}
