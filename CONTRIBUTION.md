# Contributing to the M4 Bring-up Project 🍎🚀

First off, thanks for taking an interest in the M4 project! Bringing Linux to the newest Apple Silicon is a massive community effort. Whether you are a reverse-engineering wizard or just good at testing, we need your help.

## ⚠️ Important Note
This project involves low-level hardware interaction. By contributing or using this code, you acknowledge that you are working with experimental software that could potentially lead to data loss or hardware instability. Always have a backup!

## How You Can Help

### 1. Register Hunting (High Priority)
We are currently mapping the M4 (T8132) SoC. If you find the base addresses for the following, please open an Issue or Pull Request:
* **UART (Serial)** - Need the physical base address for console logs.
* **AIC (Interrupt Controller)** - Mapping the new M4 interrupt offsets.
* **GPIO / SPMI** - Power management and hardware signal pins.

### 2. Testing the "Buckets"
If you have successfully chainloaded a specific kernel version or DTB using the `linuxbucket/` and `dtbucket/` system, let us know! 
* Share your `.config` files or `dts` snippets.
* Report any "Early Boot" panics (photos of serial logs are great).

### 3. Improving the Host Tools
* GUI enhancements for the Pi 4/5 interface.
* Updates to the `setup.sh` to support more Linux distros.
* Python scripts for automated register fuzzing.

## Pull Request Process
1. **Fork the repo** and create your branch from `main`.
2. If you are adding a new SoC file, place it in `src/soc/tXXXX.c`.
3. Ensure your Assembly code follows the **XNU 0x800 offset** rule.
4. Update the `README.md` if you’ve added new "DIY" steps.

## Community & Credits
This fork is built on the incredible foundation laid by the **Asahi Linux** team. We uphold their standards of open-source collaboration and technical excellence.

**Let's get Linux running on the M4!**
