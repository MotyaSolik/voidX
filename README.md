# VoidX OS

My hobby x86 32-bit Operating System written in C and Assembly from scratch.

## Features
- Custom bootstrapper via GRUB & Multiboot specification
- Custom VGA framework with line break support (`\n`)
- Disabled hardware text cursor via direct VGA port I/O

## Structure
- `vnl/` — Source code, drivers and linker script
- `build/` — Compiled kernel output (`voidx.bin`)
