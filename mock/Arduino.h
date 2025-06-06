#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H


#include <stdint.h>

// Modos de pino
#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define INPUT_PULLDOWN  3
#define A0             -1
#define A1             -2

// Estados lógicos
#define LOW  0
#define HIGH 1

// Estados do joystick
#define JOYSTICK_LEFT   200
#define JOYSTICK_CENTER 512
#define JOYSTICK_RIGHT  800
#define JOYSTICK_NOISE  510
#define JOYSTICK_UP     200
#define JOYSTICK_DOWN   800

#define MSBFIRST 1  // Só um valor qualquer para a constante


// Número máximo de pinos simulados
const int MAX_PINS = 20;

inline int pin_modes[MAX_PINS]  = {INPUT};
inline int pin_values[MAX_PINS] = {LOW};
inline unsigned int current_time = 0;
inline int mock_analog_x = 512;
inline int mock_analog_y = 512;


inline void pinMode(int pin, int mode) {
    if (pin < 0 || pin >= MAX_PINS) return;
    pin_modes[pin] = mode;
    // Ajusta valor padrão conforme o modo pull
    if (mode == INPUT_PULLUP) {
        pin_values[pin] = HIGH;
    }
    else if (mode == INPUT_PULLDOWN) {
        pin_values[pin] = LOW;
    }
}


inline void digitalWrite(int pin, int value) {
    if (pin < 0 || pin >= MAX_PINS) return;
    if (pin_modes[pin] != OUTPUT) return;
    pin_values[pin] = (value == HIGH ? HIGH : LOW);
}


inline int digitalRead(int pin) {
    if (pin < 0 || pin >= MAX_PINS) return LOW;
    int mode = pin_modes[pin];
    if (mode == INPUT_PULLUP || mode == INPUT_PULLDOWN || mode == INPUT) {
        return (pin_values[pin] == HIGH ? HIGH : LOW);
    }
    return LOW;
}


inline int analogRead(int pin) {
    if (pin == A0) return mock_analog_x;
    if (pin == A1) return mock_analog_y;
    return 0;
}

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


inline unsigned long millis() {
    return current_time;
}

inline  unsigned long mock_random_seed_value;

inline void randomSeed(unsigned long seed) {
    mock_random_seed_value = seed;
}

inline long mock_random_return_value;
inline long random(long max) {
    return mock_random_return_value % max;
}

inline long random(long min, long max) {
    return min + (mock_random_return_value % (max - min));
}

inline void delay(long time) {};

// Protótipo da função shiftOut para compilar
inline void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
  // Mock vazio - não faz nada
  (void)dataPin;
  (void)clockPin;
  (void)bitOrder;
  (void)val;
}


#endif
