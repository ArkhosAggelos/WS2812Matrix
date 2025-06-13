# WS2812Matrix
- English: Easy WS2812b 8x8 matrix control for Arduino, fixed or scrolling text with 6x4 font. 
- Português: Controle simples de matriz WS2812b 8x8 no Arduino, texto fixo ou rolante com fonte 6x4.

## English

**Easy-to-use Arduino library for controlling WS2812b (NeoPixel) LED matrices derived from the 8x8 format.**

This library allows you to display fixed or scrolling text using a built-in 6x4 font, making it simple and educational—ideal for school projects, science fairs, and fast prototyping.

### Features

- Supports any matrix size composed of 8x8 blocks (such as 8x8, 8x32, 16x16, etc)
- Fixed or scrolling text display
- Simple and efficient 6x4 pixel font
- Color, brightness, and text speed configurable
- Easy to use and ideal for educational use



## Português

**Biblioteca Arduino fácil para controle de matrizes de LEDs WS2812b (NeoPixel) derivadas do formato 8x8.**

Esta biblioteca permite exibir texto fixo ou rolante usando uma fonte embutida 6x4, tornando o uso simples e didático—ideal para projetos educacionais, feiras de ciências e prototipagem rápida.

### Recursos

- Suporta qualquer tamanho de matriz composta por blocos 8x8 (ex: 8x8, 8x32, 16x16, etc)
- Exibição de texto fixo ou rolante
- Fonte simples e eficiente com 6x4 pixels
- Configuração de cor, brilho e velocidade do texto
- Fácil de usar e ideal para uso educacional

### Como usar

```cpp
#include <WS2812Matrix.h>
WS2812Matrix painel(6, 32, 8); // pino, largura, altura
void setup() {
  painel.begin();
  painel.setBrightness(40);
  painel.drawText6x4("Ola!", 1, 3, painel.getStrip()->Color(255,255,0));
  painel.show();
}

