/*
* This the microcontroller code is for Sandstorm the 2024 Lunabotics bot.
* This code is for esp-wrover-kit based ESP32 microcontrollers.
* This main file holds the setup, loop functions, and string parsing for the bot.
* Owner: Cameron Schwartzberg (BigBroccoli)
* Contributors: Marco Caliendo (MCal88), Andrew Barnes (abarnes6), Mitchell Wettig, Jared Hillyer, and Joshua Greuel
* Date Created: 2/18/2024
*/

// Include all necessary libraries
#include <Servo.h>
#include <Arduino.h>
#include <Encoder.h>

// Include custom header files
#include "PinDefinitions.h" // Holds all of the pin definitions for output signals
#include "Motors.h"         // Contains motor-related functions
#include "Encoders.h"       // Contains functions for reading encoder values
#include "Communication.h"  // Contains function for parsing commands from the RPi

// Define constants
constexpr uint8_t STOP = 90;                // Stop value for the motors
constexpr uint8_t MAX_ARRAY_SIZE = 10;      // Maximum size for token array
constexpr uint8_t MAX_INPUT_LENGTH = 50;    // Maxium length for input string

// Variable for keeping track of elapsed time (used for calculating motor RPM)
unsigned long millisBefore = 0;

// Create instances of the motor and encoder containers
motors::Container motorContainer{};

Encoder frontLeftEncoder(pin::FRONT_LEFT_WHEEL_ENCODER_PIN1, pin::FRONT_LEFT_WHEEL_ENCODER_PIN2);
Encoder frontRightEncoder(pin::FRONT_RIGHT_WHEEL_ENCODER_PIN1, pin::FRONT_RIGHT_WHEEL_ENCODER_PIN2);
Encoder rearLeftEncoder(pin::REAR_LEFT_ENCODER_PIN1, pin::REAR_LEFT_ENCODER_PIN2);
Encoder rearRightEncoder(pin::REAR_RIGHT_ENCODER_PIN1, pin::REAR_RIGHT_ENCODER_PIN2);

void setup() {
    // For the serial communication from RPi to Arduino
    comm::i2cSetup(motorContainer);
    
    // Set up motors using pin definitions from PinDefinitions.h
    // All motors are initialized to the STOP (90) value as a safety measure
    motors::Setup(pin::DIGGING_MOTOR, motorContainer.digMotor, STOP);
    motors::Setup(pin::DIGGING_ACTUATOR, motorContainer.actuator, STOP);
    motors::Setup(pin::DEPOSIT_MOTOR, motorContainer.auger, STOP);
    motors::Setup(pin::DEPOSIT_VIBRATOR, motorContainer.vibrator, STOP);
    motors::Setup(pin::LEFT_MOTOR, motorContainer.driveMotor1, STOP);
    motors::Setup(pin::RIGHT_MOTOR, motorContainer.driveMotor2, STOP);

    // Set up camera servos
    // Note: These are initializaed to sepcific positions other than STOP
    motors::Setup(pin::HORIZONTAL_SERVO, motorContainer.horizontalServo, 180);
    motors::Setup(pin::VERTICAL_SERVO, motorContainer.verticalServo, 90);
    motors::Setup(pin::ARM_SERVO, motorContainer.armServo, 0);
}

void loop() {
    // Check if data is available from the RPi
    if (Serial.available() > 0) {
        char inputBuffer[MAX_INPUT_LENGTH + 1] = {0}; // +1 for null terminator

        // RRead bytes into the buffer until a newline character is received
        int bytesRead = Serial.readBytesUntil('\n', inputBuffer, MAX_INPUT_LENGTH);
        inputBuffer[bytesRead] = '\0';  // Add null terminator

        // Tokenize the input string
        char* tokens[MAX_ARRAY_SIZE] = {nullptr};
        int numCount = 0;
        char *token = strtok(inputBuffer, ",");

        // Store tokens in the array
        while (token != NULL && numCount < MAX_ARRAY_SIZE) {
            tokens[numCount++] = token;
            token = strtok(NULL, ",");
        }

        // Process the received commands
        // This uses the comm::Process function to interpret and execute commands
        // Commands are single characters followed by parameters:
        // 'm' - Movement, 'b' - Digging Belt, 'g' - Digging Actuator, 
        // 'd' - Deposit Auger, 'v' - Deposit Vibrator,
        // 'h' - Horizontal Camera Servo, 'e' - Vertical Camera Servo, 'a' - Arm Servo
        comm::Process(tokens, motorContainer);
    }
    
    // if (millis() - millisBefore > 1000){
    //     float fl_rpm = encoders::getRPM(frontLeftEncoder);
    //     float fr_rpm = encoders::getRPM(frontRightEncoder);
    //     float rl_rpm = encoders::getRPM(rearLeftEncoder);
    //     float rr_rpm = encoders::getRPM(rearRightEncoder);
    //     millisBefore = millis();
    // }
}


