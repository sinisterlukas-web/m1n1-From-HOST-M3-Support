#!/bin/bash
# extract_fw.sh - Pulls proprietary firmware from the local Mac partition

echo "--- M4 Firmware Extractor ---"
echo "Extracting Wi-Fi and Bluetooth blobs from macOS..."

# Standard Asahi tool location
if [ -f /usr/bin/asahi-fwextract ]; then
    sudo asahi-fwextract
    echo "Firmware extracted to /lib/firmware."
else
    echo "Error: Asahi firmware tools not found. Please install the asahi-scripts package."
fi
