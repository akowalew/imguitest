@echo off
set WFLAGS=/W4 /WX /wd4101 /wd4065 /wd4100
cl /nologo win32_app.cpp /Fe:app.exe /Iimgui /Oi /O1 /EHa- /EHs- /EHc- /GA /Gm- /GR- /GS- /Gw /Gy /Zi /MT /fastfail %WFLAGS% /link /DEBUG:FULL /OPT:REF /OPT:ICF user32.lib opengl32.lib
upx --ultra-brute app.exe
