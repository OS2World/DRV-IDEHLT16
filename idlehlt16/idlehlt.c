/*************************************************************************
 *
 * idlehlt.exe
 *
 * A program to communicate with the HLT driver.
 *
 */

#define INCL_DOSFILEMGR          /* File Manager values */
#define INCL_DOSPROCESS
#define INCL_DOSERRORS           /* DOS Error values    */
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#include <os2.h>
#include <stdio.h>
#include <string.h>


int main( )
{
    USHORT rc;
    USHORT ulAction    = 0;
    HFILE hfFileHandle = 0;

    DosSetPrty(PRTYS_PROCESS, PRTYC_IDLETIME, 0, 0);
    rc = DosOpen( "Idlehlt$",
              &hfFileHandle,
              &ulAction,
              0,
              FILE_NORMAL, FILE_OPEN, OPEN_SHARE_DENYNONE, 0 );

    if( rc == 0 )
    {
        while (1)
        {
            rc = DosDevIOCtl(0,NULL,0x01,0x91,hfFileHandle);
        }
    }

    rc = DosClose(hfFileHandle);
    return rc;
}
