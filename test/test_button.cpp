#include "Arduino.h"
#include "unity.h"
#include "Button.h"
#include "unity_internals.h"
#include <climits>

#define DEBOUCING_DELAY 50
#define PIN 5

void setUp(void){
  pin_values[PIN] = HIGH;
  current_time = 0;
}

void tearDown(void){}

void test_button_pressed_false(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  button.update();
  TEST_ASSERT_FALSE(button.isPressed());
}

void test_button_pressed_false_deboucing_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  button.update();
  TEST_ASSERT_FALSE(button.isPressed());
}

void test_button_pressed_false_no_deboucing_elapsed_with_digitalRead_LOW(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY - 1;
  button.update();
  TEST_ASSERT_FALSE(button.isPressed());
}

void test_button_pressed_true(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  TEST_ASSERT_TRUE(button.isPressed());
}

void test_button_longpressed_false_digitalRead_HIGH(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  pin_values[PIN] = HIGH;
  current_time += LONG_PRESS_TIME;
  button.update();
  TEST_ASSERT_FALSE(button.isLongPressed());
}

void test_button_longpressed_false_digitalRead_HIGH_longtime_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  pin_values[PIN] = HIGH;
  current_time += LONG_PRESS_TIME;
  button.update();
  TEST_ASSERT_FALSE(button.isLongPressed());
}

void test_button_longpressed_false_digitalRead_LOW_longtime_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME - 1;
  button.update();
  TEST_ASSERT_FALSE(button.isLongPressed());
}

void test_button_longpressed_true_digitalRead_LOW(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME;
  button.update();
  TEST_ASSERT_TRUE(button.isLongPressed());
}

void test_button_released_false_digitalRead_HIGH_time_deboucing_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY - 1;
  button.update();
  TEST_ASSERT_FALSE(button.justReleased());
}

void test_button_released_false_digitalRead_HIGH_time_deboucing_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  button.update();
  TEST_ASSERT_FALSE(button.justReleased());
}


void test_button_released_false_digitalRead_LOW_time_deboucing_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  TEST_ASSERT_FALSE(button.justReleased());
}

void test_button_released_true_after_pressed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();
  TEST_ASSERT_TRUE_MESSAGE(button.justReleased(), "Release is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(button.isPressed(), "Pressed is FALSE");
}

void test_button_released_true_after_longPressed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();
  TEST_ASSERT_TRUE_MESSAGE(button.justReleased(), "Release is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(button.isLongPressed(), "LongPressed is FALSE");
}

void test_button_released_true_after_click_case_1(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  TEST_ASSERT_TRUE_MESSAGE(button.justReleased(), "Release is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(button.justPressed(), "Click is FALSE");

}

void test_button_released_true_after_click_case_2(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();
  TEST_ASSERT_TRUE_MESSAGE(button.justReleased(), "Release is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(button.justPressed(), "Click is FALSE");

}

void test_button_released_false_after_released_digitalRead_HIGH_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();

  TEST_ASSERT_FALSE(button.justReleased());
}

void test_button_released_false_after_released_digitalRead_HIGH_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  pin_values[PIN] = LOW;
  current_time = DEBOUCING_DELAY;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += 1;
  pin_values[PIN] = HIGH;
  button.update();

  TEST_ASSERT_FALSE(button.justReleased());
}

void test_button_justPressed_false_digitalRead_HIGH_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY - 1;
  button.update();
  TEST_ASSERT_FALSE(button.justPressed());
}


void test_button_justPressed_false_digitalRead_HIGH_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  button.update();
  TEST_ASSERT_FALSE(button.justPressed());
}

void test_button_justPressed_false_digitalRead_LOW_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY - 1;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_FALSE(button.justPressed());
}

void test_button_justPressed_true_digitalRead_LOW_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_TRUE(button.justPressed());
}

void test_button_justPressed_false_digitalRead_LOW_after_click_true_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_FALSE(button.justPressed());
}

void test_button_justPressed_false_digitalRead_LOW_after_click_true_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += 1;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_FALSE(button.justPressed());
}

void test_button_click_false_digitalRead_HIGH_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY - 1;
  pin_values[PIN] = HIGH;
  button.update();
  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_false_digitalRead_LOW_time_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY - 1;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_false_digitalRead_HIGH_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = HIGH;
  button.update();
  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_false_digitalRead_LOW_time_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();
  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_false_after_release_ClickTime_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME + 1;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_false_after_release_multiClickInterval_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_click_true_after_release_multiClickInterval_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_TRUE(button.isClick());
}

void test_button_click_false_after_singleClick(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  TEST_ASSERT_FALSE(button.isClick());
}

void test_button_doubleClick_false_after_click_clickTime_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Tentativa do segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME + 1;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_FALSE_MESSAGE(button.isDoubleClick(), "Toque duplo deve falhar!");
  TEST_ASSERT_TRUE_MESSAGE(button.isClick(), "Eh um toque simples");

}

void test_button_doubleClick_false_after_click_multiClickInterval_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Tentativa do segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  TEST_ASSERT_FALSE(button.isDoubleClick());
}


void test_button_doubleClick_true(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Tentativa do segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_TRUE(button.isDoubleClick());
}


void test_button_multiClick_false_clickTime_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Gerando o segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Tentativa de gerar o terceiro click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME + 1;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_FALSE_MESSAGE(button.isMultiClick(), "O multiClick deve falhar!");
  TEST_ASSERT_TRUE_MESSAGE(button.isDoubleClick(), "Eh um doubleclick!");
}

void test_button_multiClick_false_multiClickInterval_no_elapsed(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Gerando o segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Tentativa de gerar o terceiro click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  TEST_ASSERT_FALSE(button.isMultiClick());
}

void test_button_multiClick_true(){
  int expect_count_click = 3;
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Gerando o segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Tentativa de gerar o terceiro click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_TRUE_MESSAGE(button.isMultiClick(), "Eh um multiClick");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_count_click, button.getCountMultiClick(), "Eh esperado 3 clicks!");
}


void test_button_multiClick_true_4_clicks(){
  int expect_count_click = 4;
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Gerando o segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Gerando o terceiro click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Tentativa de gerar o quarto click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL;
  button.update();

  TEST_ASSERT_TRUE_MESSAGE(button.isMultiClick(), "Eh um multiClick");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_count_click, button.getCountMultiClick(), "Eh esperado 4 clicks!");
}



void test_button_multiClick_false_before_longPress(){
  Button button = Button(PIN, INPUT_PULLUP, DEBOUCING_DELAY);

  // Gerando um click
  current_time = DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += DEBOUCING_DELAY;
  button.update();

  // Tentativa do segundo click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  // Tentativa de um terceiro click
  current_time += DEBOUCING_DELAY;
  pin_values[PIN] = LOW;
  button.update();

  current_time += CLICK_TIME;
  pin_values[PIN] = HIGH;
  button.update();

  current_time += MULTI_CLICK_INTERVAL - 1;
  button.update();

  pin_values[PIN] = LOW;
  current_time += DEBOUCING_DELAY;
  button.update();
  current_time += LONG_PRESS_TIME;
  button.update();

  TEST_ASSERT_FALSE(button.isMultiClick());
}


int main(){
  UNITY_BEGIN();
  RUN_TEST(test_button_pressed_false);
  RUN_TEST(test_button_pressed_false_deboucing_elapsed);
  RUN_TEST(test_button_pressed_false_no_deboucing_elapsed_with_digitalRead_LOW);
  RUN_TEST(test_button_pressed_true);

  RUN_TEST(test_button_longpressed_false_digitalRead_HIGH);
  RUN_TEST(test_button_longpressed_false_digitalRead_HIGH_longtime_no_elapsed);
  RUN_TEST(test_button_longpressed_false_digitalRead_LOW_longtime_no_elapsed);
  RUN_TEST(test_button_longpressed_true_digitalRead_LOW);

  RUN_TEST(test_button_released_false_digitalRead_HIGH_time_deboucing_no_elapsed);
  RUN_TEST(test_button_released_false_digitalRead_HIGH_time_deboucing_elapsed);
  RUN_TEST(test_button_released_false_digitalRead_LOW_time_deboucing_elapsed);
  RUN_TEST(test_button_released_true_after_pressed);
  RUN_TEST(test_button_released_true_after_longPressed);
  RUN_TEST(test_button_released_true_after_click_case_1);
  RUN_TEST(test_button_released_true_after_click_case_2);
  RUN_TEST(test_button_released_false_after_released_digitalRead_HIGH_time_elapsed);
  RUN_TEST(test_button_released_false_after_released_digitalRead_HIGH_time_no_elapsed);

  RUN_TEST(test_button_justPressed_false_digitalRead_HIGH_time_no_elapsed);
  RUN_TEST(test_button_justPressed_false_digitalRead_HIGH_time_elapsed);
  RUN_TEST(test_button_justPressed_false_digitalRead_LOW_time_no_elapsed);
  RUN_TEST(test_button_justPressed_true_digitalRead_LOW_time_elapsed);
  RUN_TEST(test_button_justPressed_false_digitalRead_LOW_after_click_true_time_elapsed);
  RUN_TEST(test_button_justPressed_false_digitalRead_LOW_after_click_true_time_no_elapsed);

  RUN_TEST(test_button_click_false_digitalRead_HIGH_time_no_elapsed);
  RUN_TEST(test_button_click_false_digitalRead_LOW_time_no_elapsed);
  RUN_TEST(test_button_click_false_digitalRead_HIGH_time_elapsed);
  RUN_TEST(test_button_click_false_digitalRead_LOW_time_elapsed);
  RUN_TEST(test_button_click_false_after_release_ClickTime_elapsed);
  RUN_TEST(test_button_click_false_after_release_multiClickInterval_no_elapsed);
  RUN_TEST(test_button_click_true_after_release_multiClickInterval_elapsed);
  RUN_TEST(test_button_click_false_after_singleClick);
  RUN_TEST(test_button_doubleClick_false_after_click_clickTime_elapsed);
  RUN_TEST(test_button_doubleClick_false_after_click_multiClickInterval_no_elapsed);
  RUN_TEST(test_button_doubleClick_true);
  RUN_TEST(test_button_multiClick_false_clickTime_elapsed);
  RUN_TEST(test_button_multiClick_false_multiClickInterval_no_elapsed);
  RUN_TEST(test_button_multiClick_true);
  RUN_TEST(test_button_multiClick_true_4_clicks);

  RUN_TEST(test_button_multiClick_false_before_longPress);

  return UNITY_END();
}
