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
 * Jul 13, 14  Tobias Karnat  HLT16 version
 */

#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#define INCL_DOSFILEMGR
#define INCL_DOSPROCESS
#define INCL_DOSSIGNALS

#include <os2.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

static volatile int ExitWhile;

static void pascal far BrkHandler(USHORT sig_arg, USHORT sig_num)
{
    ExitWhile = TRUE;
}

void main( )
{
    USHORT rc, Action;
    HFILE FileHandle;

    DosSetSigHandler(BrkHandler, NULL, NULL, SIGA_ACCEPT, SIG_CTRLC);
    DosSetSigHandler(BrkHandler, NULL, NULL, SIGA_ACCEPT, SIG_KILLPROCESS);
    DosSetSigHandler(BrkHandler, NULL, NULL, SIGA_ACCEPT, SIG_CTRLBREAK);

    DosSetPrty(PRTYS_PROCESS, PRTYC_IDLETIME, 0, 0);

    rc = DosOpen("Idlehlt$", &FileHandle, &Action, 0L,
                 FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, 0L);

    if(!rc) {
        while(!ExitWhile)
            DosDevIOCtl(NULL, NULL, 0x01, 0x91, FileHandle);
        DosClose(FileHandle);
    } else {
        char buf[6];
        char Message[35] = "HLT Driver not installed? rc=";
        const char Newline[2] = {'\r', '\n'};

        utoa(rc, buf, 10);
        strcat(Message, buf);

        DosWrite(STDERR_FILENO, &Message, strlen(Message), &Action);
        DosWrite(STDERR_FILENO, &Newline, 2, &Action);
    }
}
