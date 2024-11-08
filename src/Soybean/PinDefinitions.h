/*
* This is the header file that houses all of the pin definitions for the bot
* Owner: Cameron Schwartzberg (BigBroccoli)
* Contributors: Marco Caliendo (MCal88), Joshua Greuel, Andrew Barnes (abarnes6) and Mitchell Wettig
* Date Created: 2/18/2024
*/

#ifndef PinDefinitions_h
#define PinDefinitions_h

// Include standard integer library for uint8_t type
#include <stdint.h>

// Define a namespace 'pin' to encapsulate all pin definitions
namespace pin{
    constexpr uint8_t I2C_ADDRESS = 0x04;
    constexpr uint8_t I2C_SDA = 21;
    // constexpr uint8_t I2C_SCL = 22;
    /*
    * Pin definitions for the motor controllers and other components
    * connected to the output pins of the microcontroller
    *
    * IMPORTANT: PINS MUST BE UPDATED AS PIN LAYOUT CHANGES!!
    * IF NOT CHANGED, NOTHING WILL WORK!!
    */

    // Drive motor pins
    constexpr uint8_t LEFT_MOTOR = 4;           // Pin for the left motor
    constexpr uint8_t RIGHT_MOTOR = 11;         // Pin for the right motor

   // Arm Motor
   constexpr uint8_t ARM_MOTOR = 12;

    // Encoder pins
    // Note: These are placeholder values and should be updated with the actual pin numbers
    constexpr uint8_t RIGHT_WHEEL_ENCODER_PIN1 = 2;
    constexpr uint8_t RIGHT_WHEEL_ENCODER_PIN2 = 3;
}

#endif //PinDefinitions_h
