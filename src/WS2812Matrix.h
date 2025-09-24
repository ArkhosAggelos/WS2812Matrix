#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class WS2812Matrix {
public:
  // zigzag=false = progressivo (cada linha da esquerda→direita)
  // zigzag=true  = serpentina (linhas ímpares da direita→esquerda)
  WS2812Matrix(uint8_t pin, uint16_t width, uint16_t height, bool zigzag = false)
  : _w(width), _h(height), _zigzag(zigzag),
    _strip(width * height, pin, NEO_GRB + NEO_KHZ800) {}

  void begin()                 { _strip.begin(); _strip.show(); }
  void setBrightness(uint8_t b){ _strip.setBrightness(b); }
  void clear()                 { _strip.clear(); }
  void show()                  { _strip.show(); }

  uint16_t width()  const { return _w; }
  uint16_t height() const { return _h; }

  // Helpers de cor
  static uint32_t textColor(uint8_t r, uint8_t g, uint8_t b) {
    // Apenas empacota RGB no formato do strip (NEO_GRB é tratado internamente)
    return Adafruit_NeoPixel::Color(r, g, b);
  }
  static uint32_t textColor(const uint8_t rgb[3]) {
    return Adafruit_NeoPixel::Color(rgb[0], rgb[1], rgb[2]);
  }

  // Desenha 1 pixel (ignora se fora dos limites)
  void drawPixel(int16_t x, int16_t y, uint32_t color) {
    if (x < 0 || y < 0 || x >= (int16_t)_w || y >= (int16_t)_h) return;
    _strip.setPixelColor(indexFromXY((uint16_t)x, (uint16_t)y), color);
  }

  // Desenha um caractere 6x4 (6 linhas x 4 colunas)
  // 'row' = linha Y (topo=0), 'col' = coluna X (esquerda=0)
  void drawChar6x4(char c, int16_t row, int16_t col, uint32_t color);

  // Desenha string com espaçamento de 1 coluna entre caracteres
  void drawText6x4(const char* s, int16_t row, int16_t col, uint32_t color);

private:
  uint16_t _w, _h;
  bool _zigzag;
  Adafruit_NeoPixel _strip;

  uint16_t indexFromXY(uint16_t x, uint16_t y) const {
    // mapeamento por linhas
    if (_zigzag && (y & 1)) {
      // linha ímpar (0-based): direita->esquerda
      return y * _w + (_w - 1 - x);
    }
    // linha par: esquerda->direita
    return y * _w + x;
  }

  // Renderiza um glifo 6x4 a partir de 6 linhas de 4 bits (LSB=coluna 0)
  void drawGlyph6x4(const uint8_t rows[6], int16_t row, int16_t col, uint32_t color);
};
