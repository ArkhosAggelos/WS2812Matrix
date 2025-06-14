#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);
const char* texto = " CORES ";
uint32_t cores[] = {
  painel.textColor(255, 0, 0),
  painel.textColor(0, 255, 0),
  painel.textColor(0, 0, 255)
};
int brilho = 50, velocidade = 150;

void setup() {
  painel.begin();
  painel.setBrightness(brilho);
}

void loop() {
  int len = strlen(texto);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;

  for (int px = WIDTH; px > -pix; px--) {
    painel.clear();
    painel.drawText6x4(texto, row, px, cores[px % 3]);
    painel.show();
    delay(velocidade);
  }
}