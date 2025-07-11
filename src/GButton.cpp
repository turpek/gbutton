#include "GButton.h"


BaseButton::BaseButton(){};

BaseButton::BaseButton(unsigned long interval){
  setInterval(interval);
}

void BaseButton::setLongPressedTime(unsigned long msecs){
  this->longPressTime = msecs;
}

void BaseButton::setInterval(unsigned long msecs){
  this->interval = msecs;
}

void BaseButton::setClickTime(unsigned long msecs) {
  this->clickTime = msecs;
}

void BaseButton::setMultiClickInterval(unsigned long msecs) {
  this->multiClickInterval = msecs;
}

bool BaseButton::justPressed(){
  return justPress;
}

bool BaseButton::isClick(){
  return singleClick;
}

bool BaseButton::isDoubleClick(){
  return doubleClick;
}

bool BaseButton::isMultiClick(){
  return multiClick;
}

bool BaseButton::isPressed(){
  return pressed;
}

bool BaseButton::isLongPressed(){
  return longPressed;
}

bool BaseButton::justReleased(){
  return released;
}

unsigned int BaseButton::getCountMultiClick(){
  return countMultiClick;
}

void BaseButton::updateState(bool state){
  unsigned long currentTime = millis();
  singleClick = false;
  doubleClick = false;
  multiClick = false;
  released = false;
  justPress = false;
  countMultiClick = 0;

  if((currentTime - lastTime) >= interval){
    lastTime = currentTime;
    if(state == true && state != lastState){
      pressed = true;
      justPress = true;
      pressedTime = currentTime;
    }
    else if(state == false && state != lastState){
      released = true;
      pressed = false;
      longPressed = false;
      lastReleaseTime = currentTime;
    }
    lastState = state;
  }

  if(isPressed() && (currentTime - pressedTime) >= longPressTime){
    longPressed = true;
    countClick = 0;
  }
  else if(justReleased() && (currentTime - pressedTime) <= clickTime){
    countClick += 1;
  }

  if(!isPressed() && countClick > 0 && (currentTime - lastReleaseTime) >= multiClickInterval){
    if(countClick == 1){
      singleClick = true;
    }
    else if(countClick == 2){
      doubleClick = true;
    }
    else{
      multiClick = true;
      countMultiClick = countClick;
    }
    countClick = 0;
  }
}


GButton::GButton(){
  setInterval(DEBOUCING_DELAY);
};

GButton::GButton(uint8_t pin, uint8_t mode, unsigned long interval)
  : BaseButton::BaseButton() {
    begin(pin, mode, interval);
}

void GButton::begin(uint8_t pin, uint8_t mode, unsigned long interval){
  this->pin = pin;
  this->mode = mode;
  pinMode(pin, mode);
  setInterval(interval);
}

void GButton::setPressedState(uint8_t state){
  pressedLevel = state;
}

void GButton::update(){
  updateState(digitalRead(this->pin) == pressedLevel);
}
