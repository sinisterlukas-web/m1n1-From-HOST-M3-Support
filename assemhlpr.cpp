// Add this to your assembly helpers for m1n1
extern "C" void flush_cache(void* ptr, size_t size) {
    uintptr_t line_size = 64; // Standard for Apple Silicon
    uintptr_t start = (uintptr_t)ptr & ~(line_size - 1);
    uintptr_t end = (uintptr_t)ptr + size;
    
    for (uintptr_t addr = start; addr < end; addr += line_size) {
        __asm__ volatile("dc cvau, %0" : : "r"(addr) : "memory");
    }
    __asm__ volatile("dsb ish; isb" : : : "memory");
}
