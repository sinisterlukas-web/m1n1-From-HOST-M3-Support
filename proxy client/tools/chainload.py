#!/usr/bin/env python3
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(__file__)))

from m1n1.setup import *
from m1n1.utils import *

p = Tweaker()

# --- M3/M4 MEMORY OFFSETS ---
# Apple Silicon RAM usually starts at 0x800000000 (32GB mark)
# We place the kernel and DTB safely inside that range.
KERNEL_ADDR = 0x801000000  # Kernel start
DTB_ADDR    = 0x800000000  # Device Tree start

def load_payload(path, addr):
    if not os.path.exists(path):
        print(f"Error: {path} not found in bucket!")
        sys.exit(1)
    data = open(path, "rb").read()
    print(f"Loading {path} ({len(data)} bytes) to 0x{addr:x}...")
    p.proxy.write(addr, data)

# 1. Load the "Manual DIY" files from your buckets
# Usage: python3 chainload.py linuxbucket/Image dtbucket/m4.dtb
if len(sys.argv) < 3:
    print("Usage: chainload.py <kernel_path> <dtb_path>")
    sys.exit(1)

kernel_path = sys.argv[1]
dtb_path = sys.argv[2]

load_payload(kernel_path, KERNEL_ADDR)
load_payload(dtb_path, DTB_ADDR)

# 2. Set the "Handoff" Registers (x0 = DTB address)
print("Setting registers for Linux handoff...")
p.proxy.set_reg(0, DTB_ADDR)  # x0 -> DTB
p.proxy.set_reg(1, 0)         # x1 -> 0
p.proxy.set_reg(2, 0)         # x2 -> 0
p.proxy.set_reg(3, 0)         # x3 -> 0

# 3. The Big Jump
print(f"Jumping to Kernel at 0x{KERNEL_ADDR:x}!")
p.proxy.jump(KERNEL_ADDR)
