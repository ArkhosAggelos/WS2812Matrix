
# WS2812Matrix

**Easy-to-use Arduino library for controlling WS2812b (NeoPixel) LED matrices derived from the 8x8 format.**

This library allows you to display fixed or scrolling text using a built-in 6x4 font, making it simple and educational—ideal for school projects, science fairs, and fast prototyping.

## Features

- Supports any matrix size composed of 8x8 blocks (such as 8x8, 8x32, 16x16, etc)
- Fixed or scrolling text display
- Simple and efficient 6x4 pixel font
- Color, brightness, and text speed configurable
- Easy to use and ideal for educational use
- **Utility functions for color: `textColor(r, g, b)` and `textColor(byte arr[3])`**

## Example: Fixed Text (with RGB values)

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);

void setup() {
  panel.begin();
  panel.setBrightness(40);

  uint32_t textColor = panel.textColor(255, 0, 255); // Magenta

  panel.clear();
  panel.drawText6x4("Hello!", 1, 3, textColor);
  panel.show();
}

void loop() {
  // Nothing to do, the text remains displayed
}
```

## Example: Fixed Text (with array)

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);

void setup() {
  panel.begin();
  panel.setBrightness(40);

  byte colorArray[3] = {0, 255, 0}; // Green
  uint32_t textColor = panel.textColor(colorArray);

  panel.clear();
  panel.drawText6x4("WS2812", 1, 3, textColor);
  panel.show();
}

void loop() {
  // Nothing to do, the text remains displayed
}
```

## Example: Scrolling Text

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix panel(PIN, WIDTH, HEIGHT);

const char* text = " Welcome to WS2812Matrix! ";
int brightness = 40;
int speed = 100;

void setup() {
  panel.begin();
  panel.setBrightness(brightness);
}

void loop() {
  byte colorArray[3] = {255, 128, 0}; // Orange
  uint32_t textColor = panel.textColor(colorArray);

  int len = strlen(text);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;
  for (int px = WIDTH; px > -pix; px--) {
    panel.clear();
    panel.drawText6x4(text, row, px, textColor);
    panel.show();
    delay(speed);
  }
}
```

## License

This library is licensed under the MIT License.

## Author

&copy;2025 Claudio Roberto da Silva

---

# WS2812Matrix (em Português)

**Biblioteca Arduino fácil para controle de matrizes de LEDs WS2812b (NeoPixel) derivadas do formato 8x8.**

Esta biblioteca permite exibir texto fixo ou rolante usando uma fonte embutida 6x4, tornando o uso simples e didático—ideal para projetos educacionais, feiras de ciências e prototipagem rápida.

## Recursos

- Suporta qualquer tamanho de matriz composta por blocos 8x8 (ex: 8x8, 8x32, 16x16, etc)
- Exibição de texto fixo ou rolante
- Fonte simples e eficiente com 6x4 pixels
- Configuração de cor, brilho e velocidade do texto
- Fácil de usar e ideal para uso educacional
- **Funções utilitárias para cor: `textColor(r, g, b)` e `textColor(byte arr[3])`**

## Exemplo: Texto Fixo (com valores RGB)

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);

void setup() {
  painel.begin();
  painel.setBrightness(40);

  uint32_t corTexto = painel.textColor(255, 0, 255); // Magenta

  painel.clear();
  painel.drawText6x4("Olá!", 1, 3, corTexto);
  painel.show();
}

void loop() {
  // Nada a fazer, o texto permanece exibido
}
```

## Exemplo: Texto Fixo (com array)

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);

void setup() {
  painel.begin();
  painel.setBrightness(40);

  byte corArray[3] = {0, 255, 0}; // Verde
  uint32_t corTexto = painel.textColor(corArray);

  painel.clear();
  painel.drawText6x4("WS2812", 1, 3, corTexto);
  painel.show();
}

void loop() {
  // Nada a fazer, o texto permanece exibido
}
```

## Exemplo: Texto Rolante

```cpp
#include <WS2812Matrix.h>
#define PIN    6
#define WIDTH  32
#define HEIGHT 8

WS2812Matrix painel(PIN, WIDTH, HEIGHT);

const char* texto = " Bem-vindo ao WS2812Matrix! ";
int brilho = 40;
int velocidade = 100;

void setup() {
  painel.begin();
  painel.setBrightness(brilho);
}

void loop() {
  byte corArray[3] = {255, 128, 0}; // Laranja
  uint32_t corTexto = painel.textColor(corArray);

  int len = strlen(texto);
  int pix = len * 5;
  int row = (HEIGHT - 6) / 2;
  for (int px = WIDTH; px > -pix; px--) {
    painel.clear();
    painel.drawText6x4(texto, row, px, corTexto);
    painel.show();
    delay(velocidade);
  }
}
```

## Licença

Esta biblioteca está licenciada sob a licença MIT.

## Autor

&copy;2025 Claudio Roberto da Silva
