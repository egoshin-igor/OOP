set PROGRAM="%~1"

%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 11 22
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% notANumber
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% ""
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% -1
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% -67
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 456
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 0 > tests\output.txt
FC /B tests\output.txt tests\expectedOutputFor0.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 15 > tests\output.txt
FC /B tests\output.txt tests\expectedOutputFor15.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 121 > tests\output.txt
FC /B tests\output.txt tests\expectedOutputFor121.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% 255 > tests\output.txt
FC /B tests\output.txt tests\expectedOutputFor255.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT