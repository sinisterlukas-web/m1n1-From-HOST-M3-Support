    .text : {
        . = 0x800;
        KEEP(*(.text.start))
        *(.text .text.*)
        *(.init .init.*) /* Needed for C++ Global Constructors */
    }
