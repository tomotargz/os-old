#pragma once

#include "graphics.hpp"

class Console {
 public:
  static const int kRows = 25, kColumns = 80;

  Console(PixelWriter& writer, const PixelColor& fg_color,
          const PixelColor& bg_color);
  void PutString(const char* s);

 private:
  void Clear();
  void Newline();
  void ShowBuffer();

  PixelWriter& writer_;
  const PixelColor fg_color_, bg_color_;
  char buffer_[kRows][kColumns + 1];
  int buf_begin_, buf_wp_row_, buf_wp_col_;
};
