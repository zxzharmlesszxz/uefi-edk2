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

#ifndef _BHYVECSM16_DEBUG_H_
#define _BHYVECSM16_DEBUG_H_

#define DBG_VERB  3
#define DBG_INFO  2
#define DBG_WARN  1
#define DBG_CRIT  0

#ifdef DEBUG_PORT
#define DEBUG(Expression)       \
  do {                          \
    DebugPrint Expression;      \
  } while (FALSE)

extern UINTN DebugLevel;
#define DPRINTF(Level, Expression) \
  if (Level <= DebugLevel)         \
    DebugPrint Expression


#else
#define DEBUG(Expression)       \
  do {                          \
  } while (FALSE);

#define DPRINTF(Level, Expression) \
  do {
  } while (FALSE);
#endif

#endif
