# -ms     small memory model (small code/small data)
# -5      optimize for Pentium
# -omi
#     o   control optimization
#     m   generate inline code for math functions
#     i   expand intrinsic functions inline
# -s      remove stack overflow checks
# -zdp    DS is pegged to DGROUP
# -zff    FS floats i.e. not fixed to a segment
# -zgf    GS floats i.e. not fixed to a segment
# -zu     SS != DGROUP (i.e., don't assume stack is in your data segment)
# -zl     remove default library information
# -zq     operate quietly (equivalent to -q)
# -wx     set warning level to maximum setting

OS21_H    = $(%WATCOM)\h;$(%WATCOM)\h\os21x
INCLUDE16 = $(OS21_H);.\include
C16FLAGS  = -i=$(INCLUDE16) -bt=os2 -ms -5 -omi -s -zdp -zff -zgf -zu -zl -zq -wx
WC16      = wcc $(C16FLAGS)
LD16FLAG  = op prot,map,st=0

ASM       = wasm
LD        = wlink

.c.obj:   .AUTODEPEND
  $(WC16) $*.c

.asm.obj: .AUTODEPEND
  $(ASM) $*.asm

OBJS = devsegs.obj header.obj init.obj strategy.obj ioctl.obj

SEGS = seg type DATA SHARED PRELOAD, '_TEXT' PRELOAD IOPL, '_INITCODE' PRELOAD IOPL

all: idlehlt.sys idlehlt.exe .SYMBOLIC

idlehlt.sys: $(OBJS)
  $(LD) name idlehlt.sys sys os2_dll initg $(LD16FLAG) lib os2 $(SEGS) FILE {$(OBJS)}

idlehlt.exe:
  wcl -i=$(OS21_H) -bcl=os2 idlehlt.c

clean:    .SYMBOLIC
CLEANEXT = sys exe obj err lnk sym lst map lib
  @for %a in ($(CLEANEXT)) do -@rm *.%a
