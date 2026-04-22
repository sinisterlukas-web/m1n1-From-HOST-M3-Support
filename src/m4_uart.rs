// m4_uart.rs - Modern Rust driver for the M4 Serial Console
#![no_std]

pub struct M4Uart {
    base_addr: usize,
}

impl M4Uart {
    pub const fn new(addr: usize) -> Self {
        M4Uart { base_addr: addr }
    }

    pub fn putc(&self, c: u8) {
        let ptr = self.base_addr as *mut u32;
        unsafe {
            // Wait for the TX buffer to be ready, then write
            while core::ptr::read_volatile(ptr.add(4)) & 0x10 != 0 {}
            core::ptr::write_volatile(ptr, c as u32);
        }
    }

    pub fn write_str(&self, s: &str) {
        for b in s.bytes() {
            self.putc(b);
        }
    }
}
