HLTDriver 16-Bit

This driver is intended to keep systems cooler by calling HLT without having to patch the kernel.

Original Author       : Andy Willis
Modified for OS/2 1.x : Tobias Karnat

############################
Compiled with OpenWatcom 1.9

wmake

############################
Tested with OS/2 1.2 and 1.3

Copy IDLEHLT.{EXE,SYS} to C:\OS2

Add to CONFIG.SYS:
DEVICE=C:\OS2\IDLEHLT.SYS

Add to STARTUP.CMD:
DETACH IDLEHLT
