@echo off
curr=%CD%
cp py_test_.cpp ..\PY
cd ..\PY
cl /Fe py_test_ py_test_.cpp -I C:\Users\paulT\AppData\Local\Programs\Python\Python39-32\include
py_test_.exe
cd ..\SDL_Tools
