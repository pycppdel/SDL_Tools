@echo off
curr=%CD%
cp test.cpp ..\SDL_ALL\SDL_ALL
cd ..\SDL_ALL\SDL_ALL
cl /Fe test test.cpp -I . -I ..\..\SDL_Tools
test.exe
cd ..\..\SDL_Tools
