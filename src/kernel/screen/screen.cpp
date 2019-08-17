#include "vga.cpp"

uint8_t ttyColor;
uint16_t *ttyBuffer;

void clearScreen(void) {
  ttyColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  ttyBuffer = (uint16_t *)0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      ttyBuffer[index] = vgaEntry(' ', ttyColor);
    }
  }
}

void setScreenColor(uint8_t color) { ttyColor = color; }

size_t screenIndex(size_t x, size_t y) { return y * VGA_WIDTH + x; }

void updateCursor(int x, int y) {
  uint16_t pos = y * VGA_WIDTH + x;

  writePort(0x3D4, 0x0F);
  writePort(0x3D5, (uint8_t)(pos & 0xFF));
  writePort(0x3D4, 0x0E);
  writePort(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void setScreenEntry(char c, uint8_t color, size_t x, size_t y) {
  ttyBuffer[screenIndex(x, y)] = vgaEntry(c, color);
  updateCursor(x, y);
}
