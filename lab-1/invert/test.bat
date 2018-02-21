set PROGRAM="%~1"

echo not enough arguments
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

echo so many arguments
%PROGRAM% nonexistentInput.txt
IF NOT ERRORLEVEL 2 GOTO err

echo determinantZero
%PROGRAM% tests\determinateZero.txt
IF NOT ERRORLEVEL 3 GOTO err

echo unitMatrix
%PROGRAM% tests\unitMatrix.txt > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\unitMatrixResult.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\example1.txt > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\example1Result.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\example2.txt > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\example2Result.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT