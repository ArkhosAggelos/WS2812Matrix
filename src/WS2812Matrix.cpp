#include "WS2812Matrix.h"

// ---- Font 6x4 minimalista ---------------------------------------------
// Cada caractere: 6 linhas; cada linha usa 4 bits (bits 0..3 = colunas 0..3)
// 1 = pixel aceso, 0 = apagado
// Conjunto: A–Z, 0–9 e espaço. Caracteres não suportados são renderizados como espaço.

static const uint8_t GLYPH_SPACE[6] = {0,0,0,0,0,0};

// Letras (A-Z)
static const uint8_t GLYPH_A[6] = {0b0110,0b1001,0b1111,0b1001,0b1001,0b1001};
static const uint8_t GLYPH_B[6] = {0b1110,0b1001,0b1110,0b1001,0b1001,0b1110};
static const uint8_t GLYPH_C[6] = {0b0111,0b1000,0b1000,0b1000,0b1000,0b0111};
static const uint8_t GLYPH_D[6] = {0b1110,0b1001,0b1001,0b1001,0b1001,0b1110};
static const uint8_t GLYPH_E[6] = {0b1111,0b1000,0b1110,0b1000,0b1000,0b1111};
static const uint8_t GLYPH_F[6] = {0b1111,0b1000,0b1110,0b1000,0b1000,0b1000};
static const uint8_t GLYPH_G[6] = {0b0111,0b1000,0b1011,0b1001,0b1001,0b0111};
static const uint8_t GLYPH_H[6] = {0b1001,0b1001,0b1111,0b1001,0b1001,0b1001};
static const uint8_t GLYPH_I[6] = {0b0111,0b0010,0b0010,0b0010,0b0010,0b0111};
static const uint8_t GLYPH_J[6] = {0b0011,0b0001,0b0001,0b0001,0b1001,0b0110};
static const uint8_t GLYPH_K[6] = {0b1001,0b1010,0b1100,0b1010,0b1010,0b1001};
static const uint8_t GLYPH_L[6] = {0b1000,0b1000,0b1000,0b1000,0b1000,0b1111};
static const uint8_t GLYPH_M[6] = {0b1001,0b1111,0b1111,0b1001,0b1001,0b1001};
static const uint8_t GLYPH_N[6] = {0b1001,0b1101,0b1101,0b1011,0b1011,0b1001};
static const uint8_t GLYPH_O[6] = {0b0110,0b1001,0b1001,0b1001,0b1001,0b0110};
static const uint8_t GLYPH_P[6] = {0b1110,0b1001,0b1001,0b1110,0b1000,0b1000};
static const uint8_t GLYPH_Q[6] = {0b0110,0b1001,0b1001,0b1011,0b1010,0b0101};
static const uint8_t GLYPH_R[6] = {0b1110,0b1001,0b1001,0b1110,0b1010,0b1001};
static const uint8_t GLYPH_S[6] = {0b0111,0b1000,0b0110,0b0001,0b0001,0b1110};
static const uint8_t GLYPH_T[6] = {0b1111,0b0010,0b0010,0b0010,0b0010,0b0010};
static const uint8_t GLYPH_U[6] = {0b1001,0b1001,0b1001,0b1001,0b1001,0b0110};
static const uint8_t GLYPH_V[6] = {0b1001,0b1001,0b1001,0b1001,0b0110,0b0110};
static const uint8_t GLYPH_W[6] = {0b1001,0b1001,0b1001,0b1111,0b1111,0b1001};
static const uint8_t GLYPH_X[6] = {0b1001,0b1001,0b0110,0b0110,0b1001,0b1001};
static const uint8_t GLYPH_Y[6] = {0b1001,0b1001,0b0110,0b0010,0b0010,0b0010};
static const uint8_t GLYPH_Z[6] = {0b1111,0b0001,0b0010,0b0100,0b1000,0b1111};

// Dígitos (0–9)
static const uint8_t GLYPH_0[6] = {0b0110,0b1001,0b1001,0b1001,0b1001,0b0110};
static const uint8_t GLYPH_1[6] = {0b0010,0b0110,0b0010,0b0010,0b0010,0b0111};
static const uint8_t GLYPH_2[6] = {0b1110,0b0001,0b0010,0b0100,0b1000,0b1111};
static const uint8_t GLYPH_3[6] = {0b1110,0b0001,0b0110,0b0001,0b0001,0b1110};
static const uint8_t GLYPH_4[6] = {0b1001,0b1001,0b1111,0b0001,0b0001,0b0001};
static const uint8_t GLYPH_5[6] = {0b1111,0b1000,0b1110,0b0001,0b0001,0b1110};
static const uint8_t GLYPH_6[6] = {0b0110,0b1000,0b1110,0b1001,0b1001,0b0110};
static const uint8_t GLYPH_7[6] = {0b1111,0b0001,0b0010,0b0100,0b0100,0b0100};
static const uint8_t GLYPH_8[6] = {0b0110,0b1001,0b0110,0b1001,0b1001,0b0110};
static const uint8_t GLYPH_9[6] = {0b0110,0b1001,0b1001,0b0111,0b0001,0b0110};

void WS2812Matrix::drawGlyph6x4(const uint8_t rows[6], int16_t row, int16_t col, uint32_t color) {
  for (int8_t r = 0; r < 6; r++) {
    uint8_t line = rows[r] & 0x0F;             // só 4 bits
    for (int8_t c = 0; c < 4; c++) {
      if (line & (1 << c)) {                   // bit 0 = coluna 0 (mais à esquerda)
        drawPixel(col + c, row + r, color);
      }
    }
  }
}

void WS2812Matrix::drawChar6x4(char ch, int16_t row, int16_t col, uint32_t color) {
  const uint8_t* g = nullptr;

  if      (ch == ' ') g = GLYPH_SPACE;
  else if (ch >= 'A' && ch <= 'Z') {
    static const uint8_t* const LUT_AZ[26] = {
      GLYPH_A,GLYPH_B,GLYPH_C,GLYPH_D,GLYPH_E,GLYPH_F,GLYPH_G,GLYPH_H,GLYPH_I,GLYPH_J,
      GLYPH_K,GLYPH_L,GLYPH_M,GLYPH_N,GLYPH_O,GLYPH_P,GLYPH_Q,GLYPH_R,GLYPH_S,GLYPH_T,
      GLYPH_U,GLYPH_V,GLYPH_W,GLYPH_X,GLYPH_Y,GLYPH_Z
    };
    g = LUT_AZ[ch - 'A'];
  }
  else if (ch >= 'a' && ch <= 'z') {
    static const uint8_t* const LUT_AZ[26] = {
      GLYPH_A,GLYPH_B,GLYPH_C,GLYPH_D,GLYPH_E,GLYPH_F,GLYPH_G,GLYPH_H,GLYPH_I,GLYPH_J,
      GLYPH_K,GLYPH_L,GLYPH_M,GLYPH_N,GLYPH_O,GLYPH_P,GLYPH_Q,GLYPH_R,GLYPH_S,GLYPH_T,
      GLYPH_U,GLYPH_V,GLYPH_W,GLYPH_X,GLYPH_Y,GLYPH_Z
    };
    g = LUT_AZ[ch - 'a'];
  }
  else if (ch >= '0' && ch <= '9') {
    static const uint8_t* const LUT_09[10] = {
      GLYPH_0,GLYPH_1,GLYPH_2,GLYPH_3,GLYPH_4,GLYPH_5,GLYPH_6,GLYPH_7,GLYPH_8,GLYPH_9
    };
    g = LUT_09[ch - '0'];
  }
  else {
    g = GLYPH_SPACE;
  }

  drawGlyph6x4(g, row, col, color);
}

void WS2812Matrix::drawText6x4(const char* s, int16_t row, int16_t col, uint32_t color) {
  // largura 4 + 1 coluna de espaço
  int16_t x = col;
  for (const char* p = s; *p; ++p) {
    drawChar6x4(*p, row, x, color);
    x += 5;
  }
}
