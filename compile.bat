@echo off
g++ src/main.cpp src/circle.cpp src/rect.cpp src/point.cpp src/line.cpp -o main.exe -lgdi32 -mwindows
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b
)
echo Compilation successful.