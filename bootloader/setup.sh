#!/bin/bash

echo "--- M4 Bootloader Toolkit: Host Setup ---"

# 1. Update system packages
sudo apt update && sudo apt upgrade -y

# 2. Install core Python tools and GUI support (Tkinter)
echo "Installing system dependencies..."
sudo apt install -y python3-pip python3-tk python3-dev libusb-1.0-0-dev

# 3. Install Python libraries from your requirements.txt
if [ -f requirements.txt ]; then
    echo "Installing Python modules..."
    pip3 install -r requirements.txt
else
    echo "Error: requirements.txt not found!"
    exit 1
fi

echo "--- Setup Complete! You are ready to boot. ---"
