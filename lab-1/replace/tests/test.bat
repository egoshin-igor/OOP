replace.exe
IF NOT ERRORLEVEL 1 GOTO err

replace.exe input.txt output.txt abc cb qwer
IF NOT ERRORLEVEL 2 GOTO err

replace.exe nonexistentInput.txt output.txt abc cab
IF NOT ERRORLEVEL 3 GOTO err

replace.exe input.txt lockedOutput.txt abc cab
IF NOT ERRORLEVEL 4 GOTO err

replace.exe input.txt output.txt "" cab
IF NOT ERRORLEVEL 5 GOTO err

replace.exe empty.txt output.txt abc cab
IF ERRORLEVEL 1 GOTO err
FC /B empty.txt output.txt
IF ERRORLEVEL 1 GOTO err

replace.exe notFound.txt output.txt "If search string not found" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt notFound.txt
IF ERRORLEVEL 1 GOTO err

replace.exe mama.txt output.txt ma mama
IF ERRORLEVEL 1 GOTO err
FC /B output.txt mamaResult.txt
IF ERRORLEVEL 1 GOTO err

replace.exe digit.txt output.txt 1231234 "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt digitResult.txt
IF ERRORLEVEL 1 GOTO err

replace.exe oneString.txt output.txt all "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt oneStringResultWithPartReplace.txt
IF ERRORLEVEL 1 GOTO err

replace.exe oneString.txt output.txt "This is all string" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt oneStringResultWithFullReplace.txt
IF ERRORLEVEL 1 GOTO err

replace.exe longString.txt output.txt "This is string" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt longStringResult.txt
IF ERRORLEVEL 1 GOTO err

replace.exe threeLines.txt output.txt qwerty "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt threeLinesResult.txt
IF ERRORLEVEL 1 GOTO err

replace.exe bigFile.txt output.txt qwerty "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC /B output.txt bigFileResult.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT