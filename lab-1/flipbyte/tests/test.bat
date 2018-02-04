flipbyte.exe
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe 11 22
IF NOT ERRORLEVEL 1 GOTO err

flipbyte.exe notANumber
IF NOT ERRORLEVEL 2 GOTO err

flipbyte.exe ""
IF NOT ERRORLEVEL 2 GOTO err

flipbyte.exe -67
IF NOT ERRORLEVEL 3 GOTO err

flipbyte.exe 456
IF NOT ERRORLEVEL 3 GOTO err

flipbyte.exe 0 > output.txt
FC /B output.txt expectedOutputFor0.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 15 > output.txt
FC /B output.txt expectedOutputFor15.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 121 > output.txt
FC /B output.txt expectedOutputFor121.txt
IF ERRORLEVEL 1 GOTO err

flipbyte.exe 255 > output.txt
FC /B output.txt expectedOutputFor255.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT