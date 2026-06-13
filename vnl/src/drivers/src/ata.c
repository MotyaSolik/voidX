#include <ata.h>
#include <ports.h>

void ata_read_sector(uint32_t lba, uint8_t *buffer) {
    outb(0x1F6, (uint8_t)((lba >> 24) & 0x0F) | 0xE0);

    // скока секторов
    outb(0x1F2, 1);

    outb(0x1F3, (uint8_t)lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));

    outb(0x1F7, 0x20);

    while (1) {
        uint8_t status = inb(0x1F7);
        if ((status & 0x80) == 0 && (status & 0x08) != 0) {
            break;
        }
    }
    
    uint16_t *buf16 = (uint16_t *)buffer;
    for (int i = 0; i < 256; i++) {
        buf16[i] = inw(0x1F0);
    }
}
