#include "display_m4.hpp"
#include "assets/penguin_raw.h"

using namespace M4UI;

extern "C" void start_cpp_gui() {
    Framebuffer fb;
    Color black = {0, 0, 0, 255};
    Color glow  = {255, 0, 0, 150}; // Red laser glow

    // 1. Set the big black background
    fb.fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, black);

    // 2. Draw 3 Large Penguins (representing detected drives)
    for (int drive = 0; drive < 3; drive++) {
        uint32_t x_pos = (SCREEN_WIDTH / 4) * (drive + 1) - (PENGUIN_SIZE / 2);
        uint32_t y_pos = (SCREEN_HEIGHT / 2) - (PENGUIN_SIZE / 2);
        
        fb.draw_large_penguin(x_pos);
        
        // Add a "Laser Red" underline for the active selector
        fb.fill_rect(x_pos, y_pos + PENGUIN_SIZE + 20, PENGUIN_SIZE, 10, glow);
    }
}
