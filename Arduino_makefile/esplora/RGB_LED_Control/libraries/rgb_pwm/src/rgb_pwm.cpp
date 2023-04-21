#include "Arduino.h"
#include "rgb_pwm.h"


rgb_pwm::rgb_pwm()  {
    for (int pin_no = 0; pin_no < 3; pin_no++)  {
        cols_rgb[pin_no] = 0;
    }
}


void rgb_pwm::begin( const uint8_t rgbpins[], const uint8_t pincount) {
    for (int pin_no=0; pin_no < pincount; pin_no++ )   {
        pins_rgb[pin_no] = rgbpins[pin_no];
        pinMode(rgbpins[pin_no], OUTPUT);
        analogWrite(rgbpins[pin_no], 0);
    }
}

void rgb_pwm::show( int r, int g, int b)    {
    cols_rgb[0] = uint8_t(r % 256);
    cols_rgb[1] = uint8_t(g % 256);
    cols_rgb[2] = uint8_t(b % 256);

    for (int pin_no = 0; pin_no < 3; pin_no++)  {
        analogWrite(pins_rgb[pin_no], cols_rgb[pin_no]);
    }

}