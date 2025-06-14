#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);

void setup() {
  panel.begin();
  panel.setBrightness(50);
  panel.clear();
  uint32_t color = panel.textColor(0, 255, 0); // Green
  panel.drawText6x4("HELLO!", 1, 3, color);
  panel.show();
}

void loop() {}