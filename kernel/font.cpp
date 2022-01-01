#include "font.hpp"

const uint8_t kFontA[16] = {
    0b00000000,  //
    0b00011000,  //    xx
    0b00011000,  //    xx
    0b00011000,  //    xx
    0b00011000,  //    xx
    0b00100100,  //   x  x
    0b00100100,  //   x  x
    0b00100100,  //   x  x
    0b00100100,  //   x  x
    0b01111110,  //  xxxxxx
    0b01000010,  //  x    x
    0b01000010,  //  x    x
    0b01000010,  //  x    x
    0b11100111,  // xxx  xxx
    0b00000000,  //
    0b00000000,  //
};

void WriteAscii(PixelWriter& writer, int x, int y, char c,
                const PixelColor& color) {
    if (c != 'A') return;
    for (int dy = 0; dy < 16; ++dy) {
        for (int dx = 0; dx < 8; ++dx) {
            if (kFontA[dy] & (0b10000000 >> dx)) {
                writer.Write(x + dx, y + dy, color);
            }
        }
    }
}
