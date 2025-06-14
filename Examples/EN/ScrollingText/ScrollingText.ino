#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);
const char* text = " WS2812Matrix ";
int brightness = 50, speed = 100;

void setup() {
  panel.begin();
  panel.setBrightness(brightness);
}

void loop() {
  uint32_t color = panel.textColor(255, 0, 255); // Magenta
  int len = strlen(text);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;

  for (int px = WIDTH; px > -pix; px--) {
    panel.clear();
    panel.drawText6x4(text, row, px, color);
    panel.show();
    delay(speed);
  }
}