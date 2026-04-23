// --- Main Entry Point ---

// EFI Applications must use Microsoft ABI calling conventions
extern "C" EFI_STATUS efi_main(EFI_HANDLE ImageHandle, void* SystemTable) {
    // In a real environment, SystemTable provides access to BootServices
    // which gives you gGOP and gInput. We assume they are initialized here.
    
    Graphics gfx(gGOP);
    BootManager bootMenu(&gfx);
    MiniShell shell(&gfx);

    SystemState currentState = STATE_BOOT_MENU;
    EFI_INPUT_KEY key;
    EFI_STATUS status;

    // Main GUI Loop
    while (currentState != STATE_BOOTING) {
        
        // 1. Render Current State
        if (currentState == STATE_BOOT_MENU) {
            bootMenu.Render();
        } else if (currentState == STATE_SHELL) {
            // Re-render menu in background, shell on top
            bootMenu.Render(); 
            shell.Render();
        }

        // 2. Poll for Input
        // Note: UEFI ReadKeyStroke is non-blocking. It returns an error if no key.
        status = gInput->ReadKeyStroke(gInput, &key);
        
        if (status == 0) { // Success, key was pressed
            
            // Check for Command/Ctrl + K
            // UEFI doesn't always map modifiers natively via ReadKeyStroke.
            // Often 'Ctrl+K' results in a specific ASCII control code (0x0B).
            // Alternatively, using EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL allows checking Shift/Ctrl states.
            // For simplicity here, we assume unicode 'k' + checking a mock modifier state,
            // or the ASCII vertical tab (Ctrl+K).
            if (key.UnicodeChar == 0x0B || key.UnicodeChar == 'k') { 
                // Toggle shell
                if (currentState == STATE_BOOT_MENU) {
                    currentState = STATE_SHELL;
                } else {
                    currentState = STATE_BOOT_MENU;
                }
                continue; 
            }

            // Route input to the active component
            if (currentState == STATE_BOOT_MENU) {
                bootMenu.HandleInput(key, currentState);
            } else if (currentState == STATE_SHELL) {
                shell.HandleInput(key, currentState);
            }
        } else {
            // 3. Power Saving
            // If no key is pressed, halt the CPU until the next hardware interrupt
            // to prevent the bootloader from pinning the CPU at 100% usage.
            cpu_halt();
        }
    }

    // --- Booting Phase ---
    gfx.ClearScreen(0x000000);
    gfx.DrawString(800, 500, "Loading Operating System...", 0xFFFFFF);
    
    // Here you would call UEFI LoadImage and StartImage using the 
    // DevicePath associated with the selected drive.

    return 0; // EFI_SUCCESS
}
