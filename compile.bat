@ECHO OFF
@call SET BAT_PATH=%~dp0
if "%1"=="debug" SET DEBUG="true"
::Edit this lines to specify your environment
@call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"
::VS>=2015 if set
@call SET ISVS15=/DVS15
::
@call SET INCLUDE=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Include;%INCLUDE%
@call SET PATH=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Bin;%PATH%
@call SET LIB=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Lib;%LIB%

@call SET INCLUDEPATH=-I"%BAT_PATH%src" -I"%BAT_PATH%other/glew/include" -I"%BAT_PATH%other/glm" -I"%BAT_PATH%other/sdl/include"
@call SET SRCFILES="%BAT_PATH%src/shared/*.cpp" "%BAT_PATH%src/shared/world/*.cpp" "%BAT_PATH%src/client/*.cpp" "%BAT_PATH%src/client/components/*.cpp" "%BAT_PATH%src/client/components/graphics/*.cpp" "%BAT_PATH%src/client/components/graphics/models/*.cpp" "%BAT_PATH%src/client/components/graphics/shaders/*.cpp"  "%BAT_PATH%src/client/components/graphics/geometry/*.cpp" "%BAT_PATH%src/client/components/ui/*.cpp"
@call SET LIBFILES= "glew32s.lib" "SDL2_image.lib" "SDL2_ttf.lib" "SDL2main.lib" "SDL2.lib" "GLu32.lib" "OpenGL32.lib" "kernel32.lib" "user32.lib" "gdi32.lib"
if not "%ISVS15%"=="" (
@call SET LIBFILES=%LIBFILES% "legacy_stdio_definitions.lib"
)
@call SET SDL_LIB=%BAT_PATH%other\sdl\lib32
@call SET GLEW_LIB=%BAT_PATH%other\glew\lib\Win32
@call SET OUTFILE=%BAT_PATH%teeworlds3d.exe


call :run
exit errorlevel

:run
@call color 07
@call mkdir "%BAT_PATH%obj"
@call cd "%BAT_PATH%obj"
@call echo --------------------------COMPILING--------------------------
if "%DEBUG%"=="" (
@call cl /analyze- /c /Ox /GL /MD /MP /DPLATFORM_WIN /DWIN32 /D_USING_V110_SDK71_ %ISVS15% %INCLUDEPATH% /fp:fast /EHsc %SRCFILES%
) else (
@call mkdir debug
@call cd debug
@call echo --------------------------DEBUG--------------------------
@call cl /analyze- /c /Od /ZI /Gm /MDd /MP /DPLATFORM_WIN /DWIN32 /D_USING_V110_SDK71_ %ISVS15% %INCLUDEPATH% /fp:precise /EHsc %SRCFILES%
)
if errorlevel 1 GOTO err
@call echo --------------------------LINKING--------------------------
if "%DEBUG%"=="" (
@call link /analyze- /NODEFAULTLIB:libcmt.lib /OPT:REF /verbose:lib /OUT:"%OUTFILE%" /SUBSYSTEM:CONSOLE,5.01 /MACHINE:X86 /NOLOGO /LIBPATH:"%SDL_LIB%" /LIBPATH:"%GLEW_LIB%" "*.obj" %LIBFILES%
) else (
@call link /analyze- /NODEFAULTLIB:libcmt.lib /DEBUG /verbose:lib /OUT:"%OUTFILE%" /SUBSYSTEM:CONSOLE,5.01 /MACHINE:X86 /NOLOGO /LIBPATH:"%SDL_LIB%" /LIBPATH:"%GLEW_LIB%" "*.obj" %LIBFILES%
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
