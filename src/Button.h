#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

#define LONG_PRESS_TIME 400
#define CLICK_TIME 150
#define MULTI_CLICK_INTERVAL 250
#define DEBOUCING_DELAY 50

class BaseButton {

  private:
    bool lastState = false;
    bool singleClick = false;
    bool doubleClick = false;
    bool multiClick = false;
    bool justPress = false;
    bool pressed = false;
    bool longPressed = false;
    bool released = false;
    unsigned int countClick = 0;
    unsigned int countMultiClick = 0;
    unsigned long interval = DEBOUCING_DELAY;
    unsigned long multiClickInterval = MULTI_CLICK_INTERVAL;
    unsigned long lastTime = 0;
    unsigned long pressedTime = 0;
    unsigned long lastReleaseTime = 0;
    unsigned long longPressTime = LONG_PRESS_TIME;
    unsigned long clickTime = CLICK_TIME;

  public:

    BaseButton();
    BaseButton(unsigned long interval);
    void setLongPressedTime(unsigned long longPressTime);
    void setInterval(unsigned long interval);
    bool justPressed();
    bool isClick();
    bool isDoubleClick();
    bool isMultiClick();
    bool isPressed();
    bool isLongPressed();
    bool justReleased();
    unsigned int getCountMultiClick();

  protected:
    void updateState(bool state);

};


class Button: public BaseButton {
  private:
    uint8_t pin;
    uint8_t mode;
    int pressedLevel = LOW;

  public:
    Button();
    Button(uint8_t pin, uint8_t mode, unsigned long interval);
    void begin(uint8_t pin, uint8_t mode, unsigned long interval);
    void setPressedState(uint8_t state);
    void update();
};


#endif
