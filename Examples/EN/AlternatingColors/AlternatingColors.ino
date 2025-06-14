#include <WS2812Matrix.h>

#define PIN 6
#define WIDTH 32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);
const char* text = " COLORS ";
uint32_t colors[] = {
  panel.textColor(255, 0, 0),   // Red
  panel.textColor(0, 255, 0),   // Green
  panel.textColor(0, 0, 255)    // Blue
};
int brightness = 50, speed = 150;

void setup() {
  panel.begin();
  panel.setBrightness(brightness);
}

void loop() {
  int len = strlen(text);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;

  for (int px = WIDTH; px > -pix; px--) {
    panel.clear();
    panel.drawText6x4(text, row, px, colors[px % 3]);
    panel.show();
    delay(speed);
  }
}