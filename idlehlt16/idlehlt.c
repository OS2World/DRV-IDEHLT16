/***************************************************\
**                                                 **
**  idlehlt.exe                                    **
**                                                 **
**  A program to communicate with the HLT driver.  **
**                                                 **
**  License: Public Domain                         **
**                                                 **
\***************************************************/

/* History:
 *
 * Jul 02, 07  Mike Greene    Initial version
 * Sep 13, 11  Andy Willis    HLT version
 * Jul 09, 14  Tobias Karnat  HLT16 version
 */

#define INCL_DOSFILEMGR    /* File Manager values */
#define INCL_DOSPROCESS
#define INCL_DOSERRORS     /* DOS Error values    */
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSSIGNALS

#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile int exitWhile = FALSE;

void BrkHandler( int sig_num )
{
    exitWhile = TRUE;
}

void main( )
{
    USHORT rc;
    USHORT usAction     = 0;
    HFILE  hfFileHandle = 0;

    signal(SIGINT, BrkHandler);
    signal(SIGTERM, BrkHandler);
    signal(SIGBREAK, BrkHandler);

    DosSetPrty(PRTYS_PROCESS, PRTYC_IDLETIME, 0, 0);

    rc = DosOpen("Idlehlt$",
              &hfFileHandle,
              &usAction,
              0L,
              FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, 0L);

    if(!rc) {
        while(!exitWhile)
            DosDevIOCtl(NULL, NULL, 0x01, 0x91, hfFileHandle);
        DosClose(hfFileHandle);
    } else {
        printf("HLT Driver not installed? [SYS%04u]\n", rc);
    }
}
