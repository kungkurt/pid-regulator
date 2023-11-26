@echo off & setlocal enabledelayedexpansion

:: Author       Robin Riis
:: Company      AGSTU AB
:: Description 
::   This little shell script is used for compiling with HLS under windows operating system
::   it supports to set standard flags and you can also send flags as arguments
::
::   any argument that starts with "-" will be added as a compiler flag
::   no specific order is necessary except that the first argument that do not start with "-"
::   will be used as RUN_ARG
::   arguments like "--simulator none" will need to be added to FLAGS since support for space in CLI arguments do not exist for now.
::
::   a table of available RUN_ARG is shown below
::      - simulation
::          -- this mode will create simulation with modelsim
::      - fpga
::          -- this will do a quartus compile to implement design on a FPGA
::      - all
::          -- This will build simulation, fpga and host
::      - <empty or anything else>
::          -- This will compile native on a x86-64 arch for a quick test.
::
::   with this you can for example run ".\make.bat --fp-relaced simulation --fpc" and it will build simulation with  

GOTO init_compiler

:init_compiler
set "CC=i++"
set "TARGET=10M50DAF484C7G"
set "HOST=x86-64"
set "FLAGS=--clock 50MHz --fpc --fp-relaxed --simulator none" 
set "SOURCE_FILES=pid_input.c proportional.c integral.c derivative.c pid_output.c testbench.c"
set "APPLICATION_NAME=pid-controller"
set "RUN_ARG=unset"
GOTO set_flags

::set extra flags which is every argument that starts with "-"
::and set RUN_ARG to the first argument that do not start with "-"
:set_flags
set argc=0
set current=%0
for %%x in (%*) do (
    set current=%%x
    set /A argc+=1
    if "!current:~0,1!" equ "-"  (
        set FLAGS=!FLAGS! %%x
    ) else (
        if "%RUN_ARG%" equ "unset" ( set RUN_ARG=%%x ) else echo "ignored argument %%x"
    )
)
GOTO Check_RUN_ARG

:Check_RUN_ARG
set RUN_ARG=%RUN_ARG: =%
if "%RUN_ARG%" equ "simulation" (
    :: compile for simulation in modelsim
    GOTO Compile_Simulation
) else if "%RUN_ARG%" equ "fpga" (
    :: do a quartus compile
    GOTO Compile_FPGA
) else if "%RUN_ARG%" equ "all" (
    :: compile all three
    GOTO Compile_ALL
) else (
    :: do not cross compile
    GOTO Compile_Host
)

:Compile_ALL
if defined IS_RUN_ALL (
    set /A IS_RUN_ALL+=1
) else (
    set IS_RUN_ALL=1
)
if "!IS_RUN_ALL!" equ "1" (
    echo compiling for host..
    GOTO Compile_Host
) else if "!IS_RUN_ALL!" equ "2" (
    echo compiling for simulation..
    GOTO Compile_Simulation
) else if "!IS_RUN_ALL!" equ "3" (
    echo compiling for fpga..
    GOTO Compile_FPGA
) else (
    GOTO Graceful_Exit
)


:Compile_Simulation
set ARCH=%TARGET%
set APPNAME=%APPLICATION_NAME%-simulation
set FLAGS=%FLAGS% -ghdl
GOTO Do_Compile

:Compile_FPGA
set ARCH=%TARGET%
set APPNAME=%APPLICATION_NAME%
set FLAGS=%FLAGS% --quartus-compile
GOTO Do_Compile

:Compile_Host
set ARCH=%HOST%
set FLAGS=
set APPNAME=%APPLICATION_NAME%-host-test
GOTO Do_Compile 

:Do_Compile
:: run compilation 
echo %CC% %SOURCE_FILES% -march=%ARCH% %FLAGS% -o %APPNAME%
echo:
%CC% %SOURCE_FILES% -march=%ARCH% %FLAGS% -o %APPNAME%
if defined IS_RUN_ALL ( GOTO init_compiler ) else GOTO Graceful_Exit

:Graceful_Exit
set CC=
set FLAGS=
set ARCH=
set APPLICATION_NAME=
set APPNAME=
set SOURCE_FILES=
set argc=
set current=
set IS_RUN_ALL=
set RUN_ARG=
exit /B 0