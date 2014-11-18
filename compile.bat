@ECHO OFF
@call SET BAT_PATH=%~dp0
if "%1"=="debug" SET DEBUG="true"
@call "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"


@call SET SRCFILES="%BAT_PATH%src/client/*.cpp" "%BAT_PATH%src/client/components/*.cpp" "%BAT_PATH%src/client/components/graphics/*.cpp"
@call SET LIBFILES= "glew32.lib" "SDL2_image.lib" "SDL2_ttf.lib" "SDL2main.lib" "SDL2.lib" "GLu32.lib" "OpenGL32.lib" "kernel32.lib" "user32.lib" "gdi32.lib"
@call SET SDL_INC=%BAT_PATH%other\sdl\include
@call SET SDL_LIB=%BAT_PATH%other\sdl\lib32
@call SET OUTFILE=%BAT_PATH%teeworlds3d.exe


call :run
exit errorlevel

:run
@call color 07
@call mkdir "%BAT_PATH%obj"
@call cd "%BAT_PATH%obj"
@call echo --------------------------COMPILING--------------------------
if "%DEBUG%"=="" (
@call cl /c /O2 /Gm /MD /MP /DPLATFORM_WIN -D WIN32 -I%SDL_INC% /analyze /fp:precise /EHsc %SRCFILES%
) else (
@call mkdir debug
@call cd debug
@call echo --------------------------DEBUG--------------------------
@call cl /c /Od /ZI /Gm /MD /MP /DPLATFORM_WIN -D WIN32 -I%SDL_INC% /analyze /fp:precise /EHsc %SRCFILES%
)
if errorlevel 1 GOTO err
@call echo --------------------------LINKING--------------------------
if "%DEBUG%"=="" (
@call link /OPT:REF /verbose:lib /OUT:"%OUTFILE%" /SUBSYSTEM:CONSOLE /MACHINE:X86 /NOLOGO /LIBPATH:"%SDL_LIB%" "*.obj" %LIBFILES%
) else (
@call link /DEBUG /verbose:lib /OUT:"%OUTFILE%" /SUBSYSTEM:CONSOLE /MACHINE:X86 /NOLOGO /LIBPATH:"%SDL_LIB%" "*.obj" %LIBFILES%
)
if errorlevel 1 GOTO err
@call cd "%BAT_PATH%"
@call color 0A
@call echo ALL RIGHT
@call pause
exit /b 0

:err
@call color 0C
@call echo ERROR! STOPPING!
@call pause
exit /b 1