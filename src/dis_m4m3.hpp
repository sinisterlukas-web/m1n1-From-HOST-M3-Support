#ifndef DISPLAY_M4_HPP
#define DISPLAY_M4_HPP

#include <stdint.h>

/** 
 * M4 High-Performance Framebuffer Manager 
 * Handles the Laser Penguin UI Scaling
 */
namespace M4UI {
    const uint32_t SCREEN_WIDTH  = 2560; // Standard High-Res M4 Target
    const uint32_t SCREEN_HEIGHT = 1600;
    const uint32_t PENGUIN_SIZE  = 512;  // Making it BIG as requested

    struct Color {
        uint8_t r, g, b, a;
        uint32_t to_hex() const { return (a << 24) | (r << 16) | (g << 8) | b; }
    };

    class Framebuffer {
    public:
        void set_pixel(uint32_t x, uint32_t y, Color c);
        void fill_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Color c);
        void draw_large_penguin(uint32_t x_offset);
    };
}

#endif
