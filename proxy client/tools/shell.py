#!/usr/bin/env python3
import os, sys

# Ensure the script can find your local m1n1 python modules
sys.path.append(os.path.dirname(os.path.dirname(__file__)))

from m1n1.setup import *
from m1n1.shell import IPythonShell

def setup_m3_m4(p):
    """
    Custom initialization for M3/M4 chips during the shell boot-up.
    """
    # Detect the chip ID (T8122 = M3, T8132 = M4)
    chip_id = p.get_chip_id()
    
    if chip_id in [0x8122, 0x8132]:
        print(f"--- M-Series Bringup: Detected SoC ID 0x{chip_id:x} ---")
        # Add any early register pokes needed for M3/M4 here
    else:
        print(f"Connected to known SoC: 0x{chip_id:x}")

# Initialize the proxy connection (usually over /dev/ttyACM0)
# This uses the environment variable M1N1DEVICE
p = Tweaker()
u = p.u
if_addr = p.if_addr

# Run our custom M3/M4 detection
setup_m3_m4(p)

print("Entering interactive shell...")
# Launch the IPython shell so you can run 'p.read32(address)' manually
shell = IPythonShell(p)
shell.run()
