set PROGRAM="%~1"

echo not enough arguments
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

echo so many arguments
%PROGRAM% input.txt output.txt abc
IF NOT ERRORLEVEL 1 GOTO err

echo nonexistent input
%PROGRAM% nonexistentInput.txt output.txt
IF NOT ERRORLEVEL 2 GOTO err

echo manyStartPositions.txt
%PROGRAM% manyStartPositions.txt output.txt
IF NOT ERRORLEVEL 4 GOTO err

echo labyrinth3x2
%PROGRAM% 3x4Labyrinth.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC 3x4Labyrinth.txt output.txt
IF ERRORLEVEL 1 GOTO err

echo labyrinth-1.txt
%PROGRAM% labyrinth-1.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC labyrinth-1_result.txt output.txt
IF ERRORLEVEL 1 GOTO err

echo labyrinth-1_locked.txt
%PROGRAM% labyrinth-1_locked.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC labyrinth-1_locked.txt output.txt
IF ERRORLEVEL 1 GOTO err

echo labyrinth-3.txt
%PROGRAM% labyrinth-3.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC labyrinth-3_result.txt output.txt
IF ERRORLEVEL 1 GOTO err

echo labyrinth30x30.txt
%PROGRAM% 30x30labyrinth.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC 30x30labyrinth_result.txt output.txt
IF ERRORLEVEL 1 GOTO err

echo labyrinth100x100.txt
%PROGRAM% 100x100labyrinth.txt output.txt
IF ERRORLEVEL 1 GOTO err
FC 100x100labyrinth_result.txt output.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT
