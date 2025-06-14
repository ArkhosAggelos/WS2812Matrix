#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);
const char* texto = " WS2812Matrix ";
int brilho = 50, velocidade = 100;

void setup() {
  painel.begin();
  painel.setBrightness(brilho);
}

void loop() {
  uint32_t cor = painel.textColor(255, 0, 255); // Magenta
  int len = strlen(texto);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;

  for (int px = WIDTH; px > -pix; px--) {
    painel.clear();
    painel.drawText6x4(texto, row, px, cor);
    painel.show();
    delay(velocidade);
  }
}