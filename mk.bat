@echo off
SET PS2DEV=D:\Program Files\PS2Dev
SET PS2GCC=D:\Program Files\PS2Dev\gcc
SET PS2LIB=D:\Program Files\PS2Dev\ps2lib
PATH %PATH%;%PS2DEV%\share;%PS2GCC%\ee\bin;%PS2GCC%\iop\bin;%PS2GCC%\dvp\bin;%PS2DEV%\tool

if not "%1"=="" goto MAKE

make
goto END

:MAKE
make %1

:END
