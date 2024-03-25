:: Delete the Build folders
rmdir /q /s Bin
rmdir /q /s Obj

:: Delete the Visual Studio solution
del *.sln

:: Delete Visual Studio files for the Engine folder
del Engine\*.vcxproj Engine\*.vcxproj.user Engine\*.vcxproj.filters

:: Delete Visual Studio files for the Libs folder
for /d %%d in (Libs\*) do (
    del "%%d\*.vcxproj"
    del "%%d\*.vcxproj.user"
    del "%%d\*.vcxproj.filters"
)

:: Delete the Visual Studio files for the Games folder
for /d %%d in (Games\*) do (
    del "%%d\*.vcxproj"
    del "%%d\*.vcxproj.user"
    del "%%d\*.vcxproj.filters"
)

:: Build and open the Visual Studio solution
.\Premake\premake5.exe vs2022
START /B TrianGL.sln
