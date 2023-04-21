#ifndef rgb_pwm_h
#define rgb_pwm_h

#include "Arduino.h"

class rgb_pwm
{
    public:
        rgb_pwm();
    
        void begin(const uint8_t rgbpins[], const uint8_t pincount);
    
        void show(int r, int g, int b);
    
    private:
        uint8_t pins_rgb[3];
        uint8_t cols_rgb[3];
};

#endif