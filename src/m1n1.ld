/* m1n1 Linker Script */
OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

/* The entry point is at offset 0x800 for the XNU boot protocol */
ENTRY(_start)

SECTIONS
{
    /* Apple Silicon bootloaders are typically loaded at address 0x0 */
    . = 0x0;

    .text : {
        /* Ensure the entry point is at the correct 0x800 offset */
        . = 0x800;
        KEEP(*(.text.start))  /* Your Assembly entry code from start.S */
        *(.text .text.*)      /* All other code */
    }

    .rodata : {
        . = ALIGN(8);
        *(.rodata .rodata.*)  /* Read-only data like your boot logo path */
    }

    .data : {
        . = ALIGN(8);
        *(.data .data.*)      /* Initialized variables */
    }

    .bss : {
        . = ALIGN(8);
        __bss_start = .;
        *(.bss .bss.*)        /* Uninitialized data (cleared at boot) */
        *(COMMON)
        __bss_end = .;
    }

    /* Payload section: where your linuxbucket and dtbucket files append */
    .payload : {
        . = ALIGN(16384);     /* Align to 16K for Apple page sizes */
        __payload_start = .;
        *(.payload)
        __payload_end = .;
    }

    /DISCARD/ : { *(.comment) *(.note*) }
}
