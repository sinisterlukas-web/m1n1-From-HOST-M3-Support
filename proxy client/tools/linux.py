#!/usr/bin/env python3
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(__file__)))

from m1n1.setup import *
from m1n1.utils import *

p = Tweaker()

# Setup memory locations
# We offset them to avoid overlapping
KERNEL_ADDR = 0x801000000
DTB_ADDR    = 0x800000000
INITRD_ADDR = 0x810000000 # Higher up for the ramdisk

def boot_linux(kernel, dtb, initrd=None, bootargs="console=tty0 console=ttySAC0,115200 earlycon=apple-uart,0x235200000"):
    # 1. Load the DIY Bucket files
    print(f"--- Loading M-Series Linux Base ---")
    p.load_image(KERNEL_ADDR, kernel)
    p.load_image(DTB_ADDR, dtb)
    
    if initrd:
        p.load_image(INITRD_ADDR, initrd)
        # We tell the DTB where the initrd is (optional but recommended)
        print(f"Initrd loaded at 0x{INITRD_ADDR:x}")

    # 2. Patch the Boot Arguments (The "Command Line")
    # This tells Linux where to send logs (the M4 UART address)
    print(f"Setting bootargs: {bootargs}")
    p.set_bootargs(DTB_ADDR, bootargs)

    # 3. Final Handoff
    print("Preparing CPU for Linux...")
    p.proxy.set_reg(0, DTB_ADDR) # x0 = DTB Address
    
    print(f"Starting Kernel at 0x{KERNEL_ADDR:x}...")
    p.proxy.jump(KERNEL_ADDR)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: linux.py <kernel> <dtb> [initrd]")
        sys.exit(1)

    k = sys.argv[1]
    d = sys.argv[2]
    i = sys.argv[3] if len(sys.argv) > 3 else None
    
    boot_linux(k, d, i)
