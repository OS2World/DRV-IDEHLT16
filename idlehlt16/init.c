/************************************************************************\
**                                                                      **
**               OS/2(r) Physical Device Driver Libraries               **
**                         for Watcom C/C++ 10                          **
**                                                                      **
**  COPYRIGHT:                                                          **
**                                                                      **
**    (C) Copyright Advanced Gravis Computer Technology Ltd 1994.       **
**        All Rights Reserved.                                          **
**                                                                      **
**  DISCLAIMER OF WARRANTIES:                                           **
**                                                                      **
**    The following [enclosed] code is provided to you "AS IS",         **
**    without warranty of any kind.  You have a royalty-free right to   **
**    use, modify, reproduce and distribute the following code (and/or  **
**    any modified version) provided that you agree that Advanced       **
**    Gravis has no warranty obligations and shall not be liable for    **
**    any damages arising out of your use of this code, even if they    **
**    have been advised of the possibility of such damages.  This       **
**    Copyright statement and Disclaimer of Warranties may not be       **
**    removed.                                                          **
**                                                                      **
\************************************************************************/

/* Init.c
 *
 * Device driver initialization
 *
 * History:
 *
 * Sep 30, 94  David Bollo    Initial version
 * Jul 02, 07  Mike Greene    Modified for Open Watcom
 * Sep 13, 11  Andy Willis    HLT version
 * Jul 13, 14  Tobias Karnat  HLT16 version
 */

#include <os2.h>
#include <i86.h>
#include <stdint.h>
#include <devtypes.h>
#include <devhdr.h>
#include <devreqp.h>
#include <devaux.h>

#pragma code_seg ( "_INITCODE" ) ;
#pragma data_seg ( "_INITDATA", "INITDATA" ) ;

extern USHORT  OffFinalCS;
extern USHORT  OffFinalDS;

extern ULONG  DevHlp;  // DevHelp Interface Address

// Sign on and installation messages
static const char WELCOME[] =
    "\r\n"
    "HLT Driver installed.\r\n";
const int WELCOME_LENGTH = sizeof(WELCOME) - 1;

// Initialize device driver
uint16_t StratInit( REQP_INIT FAR *rp )
{
    USHORT ret;

    DevHlp = rp->in.devhlp;    // save far pointer to DevHlp

    // Signal that we've installed successfully by setting the size of
    // our code and data segments.
    rp->out.finalcs = FP_OFF( &OffFinalCS );    // set pointers to
    rp->out.finalds = FP_OFF( &OffFinalDS );    //discardable code/data

    DosWrite( 1, WELCOME, WELCOME_LENGTH, &ret );

    //user code
    return RPDONE;
}
