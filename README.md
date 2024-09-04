# MathTestsApp
Math Tests app is desktop windows app to check your skills in math!

## How to setup project?
App is developed under qt6.4.0 version in Qt Creator
1. Open using qt creator file `Math_Operations_Tester.pro`
2. Setup compiler *Desktop Qt 6.4.0 MinGW 64-bit*
3. Build and run.

## How to deploy app?
App is deployed in qt6 (v6.4.0)
1. Compile app in qt6 Creator IDE in release mode. (It is in the left-bttom side)
2. Delete all files in release folder except .exe file.
3. Go to Your Qt installation folder and go to next folder with name 6.4.0. Click into bin folder.
4. Open in `bin` folder cmd and run command `.\windeployqt.exe file_path`. In *file_path* paste path to your release .exe file from compilation.
5. Paste from `bin` folder required files: `libwinpthread-1.dll`, `libstdc++-6.dll`, `libgcc_s_seh-1.dll` to your release folder.
6. It is ready and should work:)
