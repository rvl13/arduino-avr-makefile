#include <Arduino.h>
#include "rgb_pwm.h"
#include "rainbow.h"

const byte RED_PIN    = 5;
const byte BLUE_PIN   = 9;
const byte GREEN_PIN  = 10;
int i = 0;

rgb_pwm LED1;


void setup();

void loop();

void setup() {
    // put your setup code here, to run once:
    byte rgb_pins[] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    LED1.begin(rgb_pins, 3);
}

void loop() {
    // put your main code here, to run repeatedly:
    //LED1.show(i, i / 5, i / 10);
    color_wheel_8bit(&LED1, i);

    i = (i + 5) % 256;

    delay(50);
}

