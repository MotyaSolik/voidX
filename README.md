# VoidX OS

My hobby x86 32-bit Operating System written in C and Assembly.

## Features
- Custom bootstrapper via GRUB & Multiboot specification
- Basic VGA text mode driver
- Keyboard driver
- Simple shell
- Kernel panic
- FAT32 Support(FatFs)

## Structure
- `vnl/` - Source code(`src/`), drivers(`src/drivers/`) and linker script(`linker.ld`)
- `build/` - Compiled kernel output (`voidx.bin`)
- `archive/` - Archove functions
- `files.txt` - List of files