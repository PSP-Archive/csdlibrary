PROJECT = csdlibrary
TITLE = csd library sample
OBJECTS = startup.o main.o process.o pg.o font.o
LIBRARYS = -lcsd -l_c

all: $(PROJECT)

rebuild: distclean all

clean:
	@if exist *.o del *.o
	@if exist *.map del *.map
	@if exist out del out
	@if exist outp del outp

distclean: clean
	@if exist ..\bin\EBOOT.PBP del ..\bin\EBOOT.PBP

include ..\Makefile.global

