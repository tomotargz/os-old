#include "mouse.hpp"

#include "graphics.hpp"

namespace {

const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    "@              ",  //
    "@@             ",  //
    "@.@            ",  //
    "@..@           ",  //
    "@...@          ",  //
    "@....@         ",  //
    "@.....@        ",  //
    "@......@       ",  //
    "@.......@      ",  //
    "@........@     ",  //
    "@.........@    ",  //
    "@..........@   ",  //
    "@...........@  ",  //
    "@............@ ",  //
    "@......@@@@@@@@",  //
    "@......@       ",  //
    "@....@@.@      ",  //
    "@...@ @.@      ",  //
    "@..@   @.@     ",  //
    "@.@    @.@     ",  //
    "@@      @.@    ",  //
    "@       @.@    ",  //
    "         @.@   ",  //
    "         @@@   ",  //
};
}  // namespace

MouseCursor::MouseCursor(PixelWriter* writer, PixelColor erase_color,
                         Vector2D<int> initial_position)
    : pixel_writer_(writer),
      erase_color_(erase_color),
      position_(initial_position) {
  DrawMouseCursor(position_);
}

void MouseCursor::MoveRelative(Vector2D<int> displacement) {
  EraseMouseCursor();
  position_ += displacement;
  DrawMouseCursor(position_);
}

void MouseCursor::DrawMouseCursor(Vector2D<int> position) {
  for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
    for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
      if (mouse_cursor_shape[dy][dx] == '@') {
        pixel_writer_->Write(position.x + dx, position.y + dy, {0, 0, 0});
      } else if (mouse_cursor_shape[dy][dx] == '.') {
        pixel_writer_->Write(position.x + dx, position.y + dy, {255, 255, 255});
      }
    }
  }
}

void MouseCursor::EraseMouseCursor() {
  for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
    for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
      if (mouse_cursor_shape[dy][dx] != ' ') {
        pixel_writer_->Write(position_.x + dx, position_.y + dy, erase_color_);
      }
    }
  }
}
