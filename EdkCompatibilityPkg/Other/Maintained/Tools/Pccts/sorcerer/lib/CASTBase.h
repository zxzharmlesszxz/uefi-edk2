#ifndef CASTBase_h
#define CASTBase_h

/*
 * CASTBase.h
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to SORCERER -- SORCERER is in the public
 * domain.  An individual or company may do whatever they wish with
 * source code distributed with SORCERER or the code generated by
 * SORCERER, including the incorporation of SORCERER, or its output, into
 * commerical software.
 *
 * We encourage users to develop software with SORCERER.  However, we do
 * ask that credit is given to us for developing SORCERER.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like SORCERER and have developed a nice tool with the
 * output, please mention that you developed it using SORCERER.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * SORCERER 1.00B
 * Terence Parr
 * AHPCRC, University of Minnesota
 * 1992-1994
 */

/* ONLY USED TO C COMPILE LIBRARY FUNCTIONS; YOU CAN FORCE THEM TO COMPILE WITH
 * YOUR SORAST DEF IF YOU WANT (THAT WAY, ORDER OF FIELD DEFINITION IS IRRELEVANT)
 */

/* Typically, this file is not used / seen by the programmer */

/* Used as "super-class" for compiling C library routines */
typedef struct _nodebase {
            struct _nodebase *right, *down;
            int token;
        } SORAST;

#endif