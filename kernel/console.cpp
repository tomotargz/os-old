#include "console.hpp"

#include <cstring>

#include "font.hpp"

Console::Console(PixelWriter& writer, const PixelColor& fg_color,
                 const PixelColor& bg_color)
    : writer_(writer),
      fg_color_(fg_color),
      bg_color_(bg_color),
      buffer_(),
      buf_begin_(0),
      buf_wp_row_(0),
      buf_wp_col_(0) {}

void Console::PutString(const char* s) {
  while (*s) {
    if (*s == '\n') {
      Newline();
    } else if (buf_wp_col_ < kColumns - 1) {
      WriteAscii(writer_, 8 * buf_wp_col_,
                 16 * ((buf_wp_row_ - buf_begin_) % kRows), *s, fg_color_);
      buffer_[buf_wp_row_][buf_wp_col_] = *s;
      ++buf_wp_col_;
    }
    ++s;
  }
}

void Console::Clear() {
  for (int y = 0; y < 16 * kRows; ++y) {
    for (int x = 0; x < 8 * kColumns; ++x) {
      writer_.Write(x, y, bg_color_);
    }
  }
}

void Console::Newline() {
  buf_wp_row_ = (buf_wp_row_ + 1) % kRows;
  buf_wp_col_ = 0;
  if (buf_wp_row_ == buf_begin_) {
    memset(buffer_[buf_wp_row_], 0, kRows);
    buf_begin_ = (buf_begin_ + 1) % kRows;
    Clear();
    ShowBuffer();
  }
}

void Console::ShowBuffer() {
  for (int r = 0; r < kRows; ++r) {
    WriteString(writer_, 0, 16 * r, buffer_[(buf_begin_ + r) % kRows],
                fg_color_);
  }
}
