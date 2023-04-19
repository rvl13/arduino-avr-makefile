#include "Arduino.h"
#include "rgb_pwm.h"

void color_wheel_8bit(rgb_pwm *LED, uint8_t Pos)  {
    uint8_t Pos_Temp = 0;
    
    if (Pos < 85)   {
        Pos_Temp = Pos;
        LED->show( Pos_Temp * 3, 255 - (Pos_Temp * 3), 0 );
    }
    else if (Pos < 170)  {
        Pos_Temp = Pos - 85;
        LED->show( 255 - (Pos_Temp * 3), 0, Pos_Temp * 3 );
    }
    else    {
        Pos_Temp = Pos - 170;
        LED->show( 0, Pos_Temp * 3, 255 - (Pos_Temp * 3) );
    }

}