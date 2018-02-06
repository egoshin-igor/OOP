invert.exe
IF NOT ERRORLEVEL 1 GOTO err

invert.exe nonexistentInput.txt
IF NOT ERRORLEVEL 2 GOTO err

invert.exe incorrectFileContent.txt
IF NOT ERRORLEVEL 3 GOTO err

invert.exe determinateZero.txt
IF NOT ERRORLEVEL 4 GOTO err

invert.exe unitMatrix.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt unitMatrixResult.txt
IF ERRORLEVEL 1 GOTO err

invert.exe example1.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt example1Result.txt
IF ERRORLEVEL 1 GOTO err

invert.exe example2.txt > output.txt
IF ERRORLEVEL 1 GOTO err
FC /B output.txt example2Result.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT