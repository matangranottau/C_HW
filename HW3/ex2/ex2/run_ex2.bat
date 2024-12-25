
REM Batch script to compile and execute ex2.c

REM Set variables
set source=ex2.c
set output=ex2.exe
set inputFolder=inputs
set outputFolder=outputs

REM Ensure GCC is available
where gcc >nul 2>&1
if errorlevel 1 (
    echo GCC compiler not found! Please install GCC and add it to your PATH.
    pause
    exit /b 1
)

REM Compile the C code
echo Compiling %source%...
gcc %source% -o %output%
if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

REM Ensure input and output folders exist
if not exist %inputFolder% (
    echo Input folder "%inputFolder%" does not exist!
    pause
    exit /b 1
)

if not exist %outputFolder% (
    echo Output folder "%outputFolder%" not found, creating it...
    mkdir %outputFolder%
)

REM Process each input file in the inputs folder
echo Running %output% for each input file in %inputFolder%...
for %%f in (%inputFolder%\*.txt) do (
    set inputFile=%%f
    set outputFile=%outputFolder%\%%~nf_output.txt

    echo Processing %%f...
    %output% < %%f > %outputFile%

    if errorlevel 1 (
        echo Error running %%f! Check your program for issues.
        pause
        exit /b 1
    )
)

REM Notify the user
echo All input files processed. Check the %outputFolder% folder for results.
pause
