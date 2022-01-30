@echo off
curr=%CD%
copy test.cpp ..\SDL_ALL\SDL_ALL
cd ..\SDL_ALL\SDL_ALL
cl /Fe test test.cpp -I . -I ..\..\SDL_Tools -I C:\Users\paulT\AppData\Local\Programs\Python\Python39\include
test.exe
cd ..\..\SDL_Tools
