// bootloader_gui.cpp
#include <stdint.h>
#include <stddef.h>

// --- Minimal UEFI Definitions (Usually provided by efi.h) ---
typedef unsigned long long EFI_STATUS;
typedef void* EFI_HANDLE;

struct EFI_INPUT_KEY {
    uint16_t ScanCode;
    uint16_t UnicodeChar;
};

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (*ReadKeyStroke)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This, EFI_INPUT_KEY* Key);
    void* WaitForKey;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
    uint32_t MaxMode;
    uint32_t Mode;
    void* Info;
    uintN_t SizeOfInfo;
    uint64_t FrameBufferBase;
    uintN_t FrameBufferSize;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode;
    void* SetMode;
    void* Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* Mode;
};

// --- Global Pointers to UEFI Protocols ---
EFI_GRAPHICS_OUTPUT_PROTOCOL* gGOP = nullptr;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL* gInput = nullptr;

// --- Graphics Engine ---
class Graphics {
private:
    uint32_t* framebuffer;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;

public:
    Graphics(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop) {
        // Cast framebuffer base to a 32-bit pixel pointer (ARGB)
        framebuffer = reinterpret_cast<uint32_t*>(gop->Mode->FrameBufferBase);
        // In a real implementation, query gop->Mode->Info for width/height
        width = 1920; 
        height = 1080;
        pitch = 1920; 
    }

    void DrawPixel(uint32_t x, uint32_t y, uint32_t color) {
        if (x >= width || y >= height) return;
        framebuffer[y * pitch + x] = color;
    }

    void DrawRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
        for (uint32_t i = 0; i < w; ++i) {
            for (uint32_t j = 0; j < h; ++j) {
                DrawPixel(x + i, y + j, color);
            }
        }
    }

    void ClearScreen(uint32_t color = 0x000000) {
        DrawRect(0, 0, width, height, color);
    }

    // Draws a simple bitmap. 
    // In your full code, you'd have a massive array of hex values for the penguin.
    void DrawBitmap(uint32_t startX, uint32_t startY, uint32_t w, uint32_t h, const uint32_t* bitmap) {
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                uint32_t color = bitmap[y * w + x];
                if (color != 0x00000000) { // Assuming 0x00 is transparent alpha
                    DrawPixel(startX + x, startY + y, color);
                }
            }
        }
    }
    
    // Stub for text rendering (requires a baked-in font array)
    void DrawChar(uint32_t x, uint32_t y, char c, uint32_t color) {
        // Implementation requires reading an 8x16 font array and calling DrawPixel
    }

    void DrawString(uint32_t x, uint32_t y, const char* str, uint32_t color) {
        int i = 0;
        while (str[i] != '\0') {
            DrawChar(x + (i * 8), y, str[i], color);
            i++;
        }
    }
};
