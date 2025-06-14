#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);

void setup() {
  painel.begin();
  painel.setBrightness(50);
  painel.clear();
  uint32_t cor = painel.textColor(0, 255, 0); // Verde
  painel.drawText6x4("OLA!", 1, 3, cor);
  painel.show();
}

void loop() {}