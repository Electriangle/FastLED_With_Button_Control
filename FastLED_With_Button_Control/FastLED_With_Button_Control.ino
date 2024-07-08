/*
 * Title: FastLED_With_Button_Control
 * 
 * Description:
 *      - This sketch was created for controlling a WS2812B LED light strip (or similar) using the FastLED library and using an input button 
 *        to switch between different animations. 
 *      - NOTE: Button pin has been set to use internal pull-up resistor. (If selected pin does not have an internal pull-up available,
 *        connect an external pull-up resistor). The button should be connected across the input pin to ground. 
 *      
 * Author: Electriangle
 *      - Channel: https://www.youtube.com/@Electriangle
 *      
 * License: MIT License
 *      - Copyright (c) 2024 Electriangle
 *
 * Date Created: 7/6/2024
*/

#include "FastLED.h"

#define NUM_LEDS          150    // Enter the total number of LEDs on the strip
#define LED_PIN           4      // The pin connected to DATA line to control the LEDs
#define INPUT_BUTTON_PIN  2      // The pin of the input button
#define NUM_ANIMATIONS    3      // The total number of animations listed below to cycle through; An "OFF" state is included by default

int input_state = HIGH;          // The current state of the output pin
int animation_state;             // The current state of animation
int button_state;                // The current reading from the input pin
int last_button_state = LOW;     // The previous reading from the input pin
unsigned long last_debounce_time = 0;  // The last time the output pin was toggled
unsigned long debounce_delay = 50;     // The debounce time; increase if the output flickers

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(INPUT_BUTTON_PIN, INPUT_PULLUP);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);    // Set power limit of LED strip to 5V, 1500mA
  FastLED.clear();                                    // Initialize all LEDs to "OFF"
}

void loop() {
  // ********** READ INPUT BUTTON (WITH DEBOUNCE) **********
  // Read the state of the switch into a local variable:
  int input_reading = digitalRead(INPUT_BUTTON_PIN);

  // If the switch changed, due to noise or pressing:
  if (input_reading != last_button_state) {
    // reset the debouncing timer
    last_debounce_time = millis();
  }

  if ((millis() - last_debounce_time) > debounce_delay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (input_reading != button_state) {
      button_state = input_reading;

      // Only toggle the color state if the new button state is LOW:
      if (input_reading == LOW) {
        animation_state = (animation_state + 1) % (NUM_ANIMATIONS + 1);
      }
    }
  }

  // Save the reading. Next time through the loop, it'll be the last_button_state:
  last_button_state = input_reading;

  // ********** SWITCH BETWEEN ANIMATIONS **********
  switch (animation_state) {
    case 1:
      // Put 1st animation function here

      break;
    case 2:
      // Put 2nd animation function here

      break;
    case 3:
      // Put 3rd animation function here

      break;

    // Add more cases as desired and update the NUM_ANIMATIONS value above...

    default:
      // Turn OFF all the LEDs
      fadeToBlackBy(leds, NUM_LEDS, 3);
      FastLED.show();
      break;
  }
}
