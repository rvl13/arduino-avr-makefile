#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 500

int main (void) {
    /*Set to one the seventh bit of DDRB to one
    **Set digital pin 13 to output mode */
    DDRB |= _BV(DDB7);

    while(1) {
        /*Set to one the seventh bit of PORTB to one
        **Set to HIGH the pin 13 */
        PORTB |= _BV(PORTB7);

        /*Wait 3000 ms */
        _delay_ms(MS_DELAY);

        /*Set to zero the seventh bit of PORTB
        **Set to LOW the pin 13 */
        PORTB &= ~_BV(PORTB7);

        /*Wait 3000 ms */
        _delay_ms(MS_DELAY);
    }
}
