// A little bit complex arduino sketch to set the brightness of LED based on value supplied over serial port (UART)

// The code for serial input takes care of the following :
//      -- Any of the Line Terminator : CR, LF or CRLF
//      -- local echo or loopback : whatever character user enters are echoed back to serial terminal
//              This is helpful for serial terminals like Putty, which send characters as soon as users enter it.
//      -- Backspace : User can use backspace to correct value entered over serial terminal.

// The code for serial input *** does not *** take care of the following :
//      -- Usage of arrow keys to traverse through your input and correct it
//              Always use the backspace for value correction.


#include <Arduino.h>

void setup();

void loop();


// Note that arduino Mega LED Pin 13 (built in LED) supports PWM.
// But Arduino Uno LED Pin 13 (built in LED) *** does not support PWM ***.
// So attach external LED to some other PWM capable pin

int led = 13;                   // the PWM pin to which the LED is attached to
int byteIn = 0;                 // temporary byte to store data received over UART
bool prompted = false;          // whether the user prompt has been displayed/printed or not
String RX_str = "Invalid";      // input string from user, garbage initial value
int len_str = 0;                // length of the string
char RX_char = '\0';            // temporary character to store data received over UART
bool line_ending = false;       // flag whether the line ending (CR, LF or CRLF) received or not
bool data_received = false;     // flag whether user input any data or not
int dataIn = 0;                 // raw value of brightness after converting Serial input as an integer
uint8_t brightness = 127;       // how bright the LED is, setting to 50% brightness at beginning, note that this is the final value.


// the setup routine runs once when you press reset:
void setup() {
    // initiate serial communication.   9600 Baud rate, 8 bits, n parity none, 1 stop bits, N Flow control none 
    Serial.begin(9600);
    //Serial.setTimeout(1000);  // 1 second timeout
    
    // declare LED Pin to be an output:
    pinMode(led, OUTPUT);
    
    Serial.println("setting LED to 50% brightness");
    analogWrite(led, brightness);
  
}

// the loop routine runs over and over again forever:
void loop() {

    // ask user to input a brightness value to be set.
    // Print this prompt only if not printed previously.
    // Don't print this over and over again for each iteration of loop()
    if (not prompted) {
        Serial.println("-----------------------------------");
        Serial.print("Enter the brightness value for LED : ");
        // waif for TX data to be transmitted
        Serial.flush();
        prompted = true;
    }

    // reset flags for each iteration
    len_str = 0;
    line_ending = false;
    data_received = false;
    line_ending = false;


    // Loop only if Data is avaiable to read or line ending hasn't been received yet.
    while ((Serial.available() > 0) || not line_ending)  {
        // Read the serial data byte by byte
        byteIn = Serial.read();

        // Note that Serial.read() returns -1 if no data was received.
        // Hence, only process the data if user has actually input it.
        if (byteIn != -1) {

            // convert integer value to corresponding ASCII character
            RX_char = byteIn;

            // If the line ending character is received.
            if (RX_char == '\n' || RX_char == '\r' ) {
                // set the line ending flag
                line_ending = true;
                // delay of 10 milliseconds because there will be a little delay before /n is received in case of CRLF mode
                // Under this condition, both the Serial.available() = false, also not (line_ending) = false
                // so, combined condition will be false and this loop will not run for LF
                // This will result in LF alone being processed during next iteration. 
                delay(10);
            }
            // If backspace character is received
            else if (RX_char == '\b')  {
                // Now, we also need to remove the character from the string and recduce it's length by one.
                // Do this only if length was greater than 0,
                // so that we don't make the len_str negative value,
                // otherwise it will result in accessing out of bounds array index.
                // Also, it will result in erasing any previous characters (on serial terminal) other than those entered by user
                if (len_str > 0)    {

                    // First send the same character (backspace) back to serial terminal
                    // so that cursor moves one character left
                    // Note that it still hasn't removed the character, just the cursor has moved.
                    Serial.print(RX_char);
                    
                    // Then send a null character, so it erases the character for which backspace was pressed
                    // Also, this will make cursor move one character right after the null character.
                    Serial.print('\0');
                    
                    // Send the backspace character once more to move the cursor left by one character
                    // exactly at the beginning of the null character.
                    Serial.print(RX_char);
                    
                    // set the character at current position to null character,
                    // essentially marking it as end of the string.
                    RX_str.setCharAt(len_str, '\0');
                    
                    // Also, reduce the length by one.
                    len_str -= 1;
                }
            }
            // for any other ascii character other than (CR, LF and Backspace)
            else  {
                // insert the given character into string
                RX_str.setCharAt(len_str, RX_char);
                // do a local echo on terminal (or say a loopback)
                Serial.print(RX_char);
                // increase the length by one.
                len_str += 1;
            }
        
        }

        // set the data_received flag
        data_received = true;
    }

    // set the null character at the current position, making it end of the string
    RX_str.setCharAt(len_str, '\0');

    // convert string to integer.
    // if a valid integer than conversion will be fine, otherwise 0 will be returned.
    // Note that 0 will be also returned if string was actually a zero character "0"
    // This is a conflicting case and must be taken care when making decision.
    dataIn = RX_str.toInt();


    // Change the brightness only if data was received from user and user also pressed enter after that.
    if (data_received && line_ending)  {

        // just go to new line before printing anything else.
        Serial.println();
        
        // If negative value was entered than turn off the LED.
        if (dataIn < 0) {
            // set the brightness to zero, corrected value
            brightness = 0;
            Serial.println("Negative value, turning the LED off");
        }
        // If brightness input is more that the maximum possible value (255)
        else if (dataIn > 255)  {
            // then set the brightness value to max (255), corrected value
            brightness = 255;
            Serial.println("Value greater than max possible, setting the LED to max brightness");
        }
        // IF 0 was entered or non-number value was entered
        else if (dataIn == 0)  {
            // Then maintain the current brightness, no change required.
            brightness = brightness;
            Serial.println("Either 0 value or invalid value, maintaining the current brightness");
        }
        // else a valid Integer between (0, 255]
        else  {
            // then set the brightness to the input.
            brightness = (uint8_t)dataIn;
            Serial.print("Valid value supplied, changing the brightness to : ");
            Serial.println(brightness);
        }

        Serial.print("Setting the LED to brightness : ");
        Serial.println(brightness);
        Serial.println("-----------------------------------");

        // change the brightness now.
        analogWrite(led, brightness);

        // set the prompt to false, so that it will now ask user to input the value again.
        prompted = false;
    }

    // wait atleast a second
    delay(1000);

}






