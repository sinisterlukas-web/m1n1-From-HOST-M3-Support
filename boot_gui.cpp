// cpu_utils.h
#pragma once

extern "C" {
    // Halts the CPU until the next interrupt (saves power in the GUI loop)
    inline void cpu_halt() {
        __asm__ volatile("hlt" : : : "memory");
    }

    // Read a byte from a CPU port (useful if falling back to legacy PS/2 keyboard)
    inline unsigned char inb(unsigned short port) {
        unsigned char ret;
        __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }
}
