@echo off
chcp 65001 >nul
title ELE411 Calisma Sitesi
cd /d "%~dp0"

where python >nul 2>nul
if errorlevel 1 (
    echo [HATA] Python bulunamadi. Python 3 kurulu ve PATH'te olmali.
    pause
    exit /b 1
)

where g++ >nul 2>nul
if errorlevel 1 (
    if exist "C:\msys64\ucrt64\bin\g++.exe" (
        set "PATH=C:\msys64\ucrt64\bin;%PATH%"
    ) else (
        echo [HATA] g++ bulunamadi. MSYS2 UCRT64 ile g++ kurun:
        echo        pacman -S mingw-w64-ucrt-x86_64-gcc
        pause
        exit /b 1
    )
)

echo ELE411 calisma sitesi baslatiliyor...
echo Tarayici otomatik acilacak: http://localhost:8000
echo Kapatmak icin bu pencereyi kapatin.
echo.
python server.py
pause
