set PROGRAM="%~1"

%PROGRAM% > tests\output.txt
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% tests\input.txt tests\output.txt abc cb qwer
IF NOT ERRORLEVEL 1 GOTO err

%PROGRAM% tests\nonexistentInput.txt tests\output.txt abc wb
IF NOT ERRORLEVEL 2 GOTO err

rem Убрал проверку на закрытый output, потому что после клонирования с гита файл locedOuput снимается с режима только для чтения
rem %PROGRAM% tests\input.txt tests\lockedOutput.txt abc cab
rem IF NOT ERRORLEVEL 3 GOTO err

%PROGRAM% tests\empty.txt tests\output.txt abc cab
IF ERRORLEVEL 1 GOTO err
FC tests\empty.txt tests\output.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\notFound.txt tests\output.txt "If search string not found" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC  tests\output.txt tests\notFound.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\mama.txt tests\output.txt ma mama
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\mamaResult.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\digit.txt tests\output.txt 1231234 "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\digitResult.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\oneString.txt tests\output.txt all "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\oneStringResultWithPartReplace.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\oneString.txt tests\output.txt "This is all string" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\oneStringResultWithFullReplace.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\longString.txt tests\output.txt "qwerty" "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\longStringResult.txt
IF ERRORLEVEL 1 GOTO err

%PROGRAM% tests\threeLines.txt tests\output.txt qwerty "Replacement completed"
IF ERRORLEVEL 1 GOTO err
FC tests\output.txt tests\threeLinesResult.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT