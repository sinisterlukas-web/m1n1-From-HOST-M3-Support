// --- Constants and Mock Data ---
// In a 1000-line file, this would be thousands of hex values.
const uint32_t PENGUIN_WIDTH = 64;
const uint32_t PENGUIN_HEIGHT = 64;
extern const uint32_t NORMAL_PENGUIN_BMP[];   // Standard Tux
extern const uint32_t GLOWING_PENGUIN_BMP[]; // Glowing neon Tux

enum SystemState {
    STATE_BOOT_MENU,
    STATE_SHELL,
    STATE_BOOTING
};

struct BootDrive {
    char name[32];
    bool isLinux;
    void* efiDevicePath; // Path to the actual bootx64.efi
};

// --- The Embedded Shell ---
class MiniShell {
private:
    char inputBuffer[256];
    int cursorIdx;
    Graphics* gfx;

public:
    MiniShell(Graphics* graphics) : cursorIdx(0), gfx(graphics) {
        for(int i=0; i<256; ++i) inputBuffer[i] = '\0';
    }

    void Render() {
        gfx->DrawRect(100, 100, 800, 600, 0x222222); // Dark grey terminal window
        gfx->DrawRect(100, 100, 800, 20, 0x444444);  // Title bar
        gfx->DrawString(110, 104, "Bootloader Shell (Type 'exit' to return)", 0xFFFFFF);
        
        gfx->DrawString(110, 140, "root@bootloader:~#", 0x00FF00);
        gfx->DrawString(260, 140, inputBuffer, 0xFFFFFF);
        
        // Draw cursor
        gfx->DrawRect(260 + (cursorIdx * 8), 140, 8, 16, 0x00FF00);
    }

    void HandleInput(EFI_INPUT_KEY key, SystemState& state) {
        if (key.UnicodeChar == '\r') { // Enter key
            ExecuteCommand(state);
            cursorIdx = 0;
            for(int i=0; i<256; ++i) inputBuffer[i] = '\0';
        } 
        else if (key.UnicodeChar == '\b') { // Backspace
            if (cursorIdx > 0) {
                cursorIdx--;
                inputBuffer[cursorIdx] = '\0';
            }
        } 
        else if (key.UnicodeChar >= 32 && key.UnicodeChar <= 126) {
            if (cursorIdx < 254) {
                inputBuffer[cursorIdx] = (char)key.UnicodeChar;
                cursorIdx++;
            }
        }
    }

    void ExecuteCommand(SystemState& state) {
        // String comparison without stdlib
        bool isExit = true;
        const char* exitStr = "exit";
        for(int i=0; i<4; i++) { if(inputBuffer[i] != exitStr[i]) isExit = false; }
        
        if (isExit) {
            state = STATE_BOOT_MENU;
        }
        // Add more commands: 'ls', 'boot', 'memmap'
    }
};

// --- Boot Manager ---
class BootManager {
private:
    BootDrive drives[5];
    int driveCount;
    int selectedIndex;
    Graphics* gfx;

public:
    BootManager(Graphics* graphics) : driveCount(3), selectedIndex(0), gfx(graphics) {
        // Mock data. In reality, you probe UEFI for SimpleFileSystemProtocols
        drives[0] = {"Arch Linux", true, nullptr};
        drives[1] = {"Windows 11", false, nullptr};
        drives[2] = {"Ubuntu 24.04", true, nullptr};
    }

    void Render() {
        gfx->ClearScreen(0x111122); // Deep blue background
        gfx->DrawString(850, 100, "Select OS to Boot", 0xFFFFFF);
        gfx->DrawString(800, 900, "Press Cmd/Ctrl+K for Shell", 0x888888);

        int startX = 600;
        int y = 400;

        for (int i = 0; i < driveCount; ++i) {
            int x = startX + (i * 250);
            
            // Draw the penguin
            if (i == selectedIndex) {
                gfx->DrawBitmap(x, y, PENGUIN_WIDTH, PENGUIN_HEIGHT, GLOWING_PENGUIN_BMP);
                // Highlight text
                gfx->DrawString(x - 10, y + 80, drives[i].name, 0x00FFFF); 
            } else {
                gfx->DrawBitmap(x, y, PENGUIN_WIDTH, PENGUIN_HEIGHT, NORMAL_PENGUIN_BMP);
                gfx->DrawString(x - 10, y + 80, drives[i].name, 0xAAAAAA);
            }
        }
    }

    void HandleInput(EFI_INPUT_KEY key, SystemState& state) {
        // ScanCode 0x03 is Left Arrow, 0x04 is Right Arrow in UEFI
        if (key.ScanCode == 0x03) {
            if (selectedIndex > 0) selectedIndex--;
        } else if (key.ScanCode == 0x04) {
            if (selectedIndex < driveCount - 1) selectedIndex++;
        } else if (key.UnicodeChar == '\r') {
            state = STATE_BOOTING;
        }
    }
};
