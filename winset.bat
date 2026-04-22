@echo off
echo --- M4 Bootloader Toolkit: Windows Host Setup ---

:: 1. Install Python and Git
echo Installing Python and Git...
winget install -e --id Python.Python.3
winget install -e --id Git.Git

:: 2. Install Python Dependencies
echo Installing Python modules...
pip install pyserial construct requests pillow

:: 3. Check for the DTB compiler
echo Note: For DTB compilation on Windows, please install 'dtc' via WSL2 or MSYS2.
pause
