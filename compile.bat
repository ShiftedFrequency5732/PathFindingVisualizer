:: Tell the user that the compilation has been started, and run the MakeFile.
echo "Starting the compilation process..."
mingw32-make -f MakeFile

:: In case there was an error durring the compilation process, exit the batch file.
if %ERRORLEVEL% NEQ 0 exit %ERRORLEVEL%

:: Otherwise, tell the user that compilation has been successful, start the compiled program.
echo "Compilation successful! Starting the program."
program.exe

