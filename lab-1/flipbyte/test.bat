set PROGRAM="%~1"

echo not enough arguments
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

echo so many arguments
%PROGRAM% 11 22
IF NOT ERRORLEVEL 1 GOTO err

echo Arguments not a number
%PROGRAM% notANumber
IF NOT ERRORLEVEL 2 GOTO err

echo empty Argument
%PROGRAM% ""
IF NOT ERRORLEVEL 2 GOTO err

echo out of range - -1
%PROGRAM% -1
IF NOT ERRORLEVEL 3 GOTO err

echo out of range - 256
%PROGRAM% 256
IF NOT ERRORLEVEL 3 GOTO err

echo out of range - -67
%PROGRAM% -67
IF NOT ERRORLEVEL 3 GOTO err

echo out of range - 456
%PROGRAM% 456
IF NOT ERRORLEVEL 3 GOTO err

%PROGRAM% 0 > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\expectedOutputFor0.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 15 > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\expectedOutputFor15.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 121 > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\expectedOutputFor121.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 255 > tests\output.txt
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\expectedOutputFor255.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT