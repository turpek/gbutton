## GButton

Uma biblioteca simples para tratar eventos de botões do tipo *push button* no arduino, onde também resolve o problema de *bounce* via software, com essa biblioteca é possível detectar os seguintes eventos;

- Botão foi pressionado (borda de descida)

- Botão foi solto (borda de subida)

- Botão está pressionado

- Um clique

- Dois cliques

- Multiplos cliques

- Botão pressionado

### Como usar

Essa biblioteca conta com a classe **`GButton`**, classe essa que expõem o estado do botão. Ela tem dois construtores o prímeiro tem a seguinte assinatura

```cpp
GButton(uint8_t pin, uint8_t mode, unsigned long interval)
```

| Parâmetro                  | Descrição                                   |
| -------------------------- | ------------------------------------------- |
| *`uint8_t pin`*            | Número do pino do botão                     |
| *`uint8_t mode`*           | Modo do botão ("*pull up*" ou "pull down" ) |
| *`unsigned long interval`* | Intervalo de debounce                       |

já o segundo construtor não tem parâmetros e a configuração é feita através do método `begin` que aceita os mesmo argumentos do construtor descrito acima, ídeal para ser usado com objeto global, com isso é possível configurar o mesmo na função `setup`, da seguinte forma

```cpp
GButton button;


void setup() {
    // ...
    button.begin(pin, INPUT_PULLUP, 50);
    button.update();
}
```

o método **`update()`** atualiza o estado do botão, é aconselhavel chama-lo uma vez no setup, para atualizar os atributos que dependem do tempo corretamente.  Para a leitura do estado do botão é fornecido os seguintes métodos

| Método                            | Descrição                                                                                                                             |
| --------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| *`void update()`*                 | Atualiza o estado do botão.                                                                                                           |
| *`bool justPressed()`*            | Retorna verdadeiro na borda de descida, ou seja, identifica o momento que o botão foi pressionado.                                    |
| *`bool justReleased()`*           | Retorna verdadeiro na borda de subida, ou seja, determina o momento em que o botão foi solto.                                         |
| *`isClick()`*                     | Retorna verdadeiro se o botão foi clicado uma vez dentro do intervalo definido como clique.                                           |
| *`isDoubleClick()`*               | Retorna verdadeiro para o caso em que o botão foi clicado duas vezes dentro do intervalo definido como clique.                        |
| *`isMultiClick()`*                | Retorna verdadeiro para o caso em que o botão foi clicado ***N*** vezes, onde *`N > 2`*.                                              |
  | *`bool isLongPressed()`*          | Retorna verdadeiro se um botão foi pressionado durante o intervalo de tempo necessário para ser considerado um "pressionamento longo". |
| *`unsigned getCountMultiClick()`* | Retorna o número de vezes em que o  botão foi clicado, no caso se  *`isMultiClick()`* for verdadeiro.                                 |

também é possível definir alguns valores para tornar o objeto mais dinâmico, sendo eles

| Método                                              | Descrição                                                                                                                                                 |
| --------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `void setInterval(unsigned long msecs)`             | Define o tempo de **debounce**                                                                                                                            |
| *`void setLongPressedTime(unsigned long msecs);`*   | Define a quantidade de tempo para a ação ser considerada um *pressionamento longo*                                                                        |
| *`void setClickTime(unsigned long msecs)`*          | Define o intervalo de tempo máximo para uma  ação ser considerada um clique (clique duplo e multiplos são considerados um clique que repetiram *N* vezes) |
| *`void setMultiClickInterval(unsigned long msecs)`* | Tempo máximo  para ocorrer o clique *`N+1`*, caso não ocorra a ação é considerada como um clique *`N`*.                                                   |
| `void setPressedState(uint8_t state)`               | Define se a ação de pressionar o botão é `LOW` ou `HIGH`.                                                                                                 |

### Exemplo rápido

Configura o botão no pino 4 com INPUT_PULLUP e debounce de 50 ms, e um LED no pino 5 como saída.  No loop, chama botao.update() e pisca o LED por 150 ms sempre que um clique simples é detectado.

```cpp
#include <Arduino.h>
#include "GButton.h"

GButton botao;              // objeto global, debounce padrão = 50 ms
const uint8_t LED_PIN = 5;  // LED no pino 5
const uint8_t BTN_PIN = 4;  // botão no pino 4

void setup() {
  pinMode(LED_PIN, OUTPUT);
  botao.begin(BTN_PIN, INPUT_PULLUP, 50);
}

void loop() {
  botao.update();

  // Quando detectar um clique simples, pisca o LED
  if (botao.isClick()) {
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
  }
}
```

### Exemplo didático

Considere um  botão no modo *pull up*  conectado ao pino 4 e dois LEDS, um *LED* conectado no pino 5 do arduino no modo *pull up* e outro LED conectado no pino 6, também no mesmo modo, vamos usar o LED do pino 5 para contar a quantidade de vezes que o botão foi clicado (no caso do botão ser pressionado por um longo tempo o LED deve ficar asceso até o mesmo ser liberado), já o LED do pino 6, deve ascender na borda de descida, e apagar na borda de descida, na borda de descida devemos apagar o LED do pino 5 também, para tratar o caso do botão pressionado.

```cpp
#include "GButton.h"


#define PIN_BUTTON 4
#define PIN_LED_1  5 // Led que pisca N vezes, onde N representa o número de cliques
#define PIN_LED_2  6 // Led controlada pela borda de descida e subida

GButton botao;


// Função para piscar o LED 1
void blink_led() {
    digitalWrite(PIN_LED_1, HIGH);
    delay(200);
    digitalWrite(PIN_LED_1, LOW);
    delay(200);
}

void setup() {

  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);

  botao.begin(PIN_BUTTON, INPUT_PULLUP, 50);

  // Define o intervalo de tempo máximo para identificar um clique.
  botao.setClickTime(200);

  // Define o tempo de espera para identificar um proximo clique
  // Caso falhe o estado atual é consolidado.
  botao.setMultiClickInterval(300);

  // Define o tempo mínimo para o pressionamento longo.
  botao.setLongPressedTime(600);
}

void loop() {
  // Atualiza o estado do botão.
  botao.update();

  if (botao.isClick()) {
    blink_led();
  }
  else if (botao.isDoubleClick()) {
    blink_led();
    blink_led();
  }
  else if (botao.isMultiClick()) {
    int nCliques = botao.getCountMultiClick();
    for (int i = 0; i < nCliques; i++) {
      blink_led();
    }
  }

  if(botao.justPressed()){
    // Borda de descida, ou seja o botão foi prossionado
    // então ascendemos o LED 2
    digitalWrite(PIN_LED_2, HIGH);

  }
  else if(botao.justReleased()) {
    // Borda de subida, ou seja, o botão foi solto portanto
    // apagamos o LED 2, também apagamos o LED 1, para o caso
    // de o botão ser pressionado por um longo tempo
    delay(50);
    digitalWrite(PIN_LED_2, LOW);
    digitalWrite(PIN_LED_1, LOW);
  }

  if (botao.isLongPressed()) {
    // Ascendemos o LED 1 durante o tempo em que o botão ficar
    // pressionado no estado de "pressionamento longo"
    digitalWrite(PIN_LED_1, HIGH);
  }
}
```
