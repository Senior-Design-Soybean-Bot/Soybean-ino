/*
* Communication.cpp - Implementation file for handling communication between the RPi and the microcontroller
* for the Sandstorm 2024 Lunabotics bot.
* 
* This file implements the communication protocol and preocession functions.
*
* Owner: Cameron Schwartzberg (BigBroccoli)
* Contributors: Andrew Barnes (abarnes6)
* Date Created: 10/9/2024
*/

#include "Communication.h"

namespace comm {
    // Command character definitions for various functions
    constexpr char MOVEMENT = 'm';
    constexpr char ARM = 'a';

    /*
    * Process function implementation
    *
    * This function interprets commands sent the RPi and executes the corresponding functions.
    * Using a switch statement to determine which function to call based on the command character.
    * 
    * @param tokens An array of char pointers containing the parsed command tokens
    * @param motorContainer A struct containing all of the motor objects
    */
    void Process(char* tokens[], motors::Container motorContainer) {
        // Check if at least two tokens are present
        if (tokens[0] == nullptr || tokens[1] == nullptr) {
            return;
        }

        char cmd = tokens[0][0];
        int param1 = atoi(tokens[1]);
        int param2;

        // Parse param2 if it exists
        if (tokens[2] != nullptr) {
            if (cmd == MOVEMENT) {
                param2 = atoi(tokens[2]);
            }
            else {
                param2 = (int)tokens[2][0];
            }
        }

        // Process the command
        switch (cmd) {
            case MOVEMENT:
                motors::drive(param1, param2, motorContainer.driveMotor1, motorContainer.driveMotor2);
                break;
            case ARM:
                if (param1) {
                    if (param2 == 'u')
                    {
                        motors::Forward(motorContainer.armMotor);
                    }
                    else if (param2 == 'd')
                    {
                        motors::Backward(motorContainer.armMotor);
                    }                
                }
                else {
                    motors::Stop(motorContainer.armMotor);
                }
                break;
            default:
                break;
        }
    }
}