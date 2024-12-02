/*
* This file is connected to "Encoders.cpp"
* Owner: Marco Caliendo (MCal88)
* Contributors: Cameron Schwartzberg (BigBroccoli), and Andrew Barnes (abarnes6)
*/


#include "Encoders.h"
#include "PinDefinitions.h"

namespace encoders {
    //unsigned long millisBefore = 0;
    constexpr int PULSES_PER_REV = 600;
    constexpr float RPM_SCALING = 4.0f;

    // Constant Variable for tuning the rpm function
    constexpr uint8_t cv = 4;

    void setupEncoder(uint8_t pin_1, uint8_t pin_2, Encoder& encoder) {
        encoder = Encoder(pin_1, pin_2);
    }


    /*
    * Function must be called as often as possible in the main file
    * How we handle this may change if we decide to go with full interrupts for all encoders
    */
    long readEncoder(Encoder& enc) {
        return enc.read();
    }

    /* 
    * For whatever reason there was a miss match between pulses per revolution 
    * read on the arduino vs. pulses per revolution labeled on the encoder.
    * This resulted in this function returning an rpm 4 times higher than in reality.
    * The variable cv in this function fixes the issue but may need to change to a 
    * different value if different encoders are used in the future.
    */
    float getRPM(Encoder& enc) {
        long counts = readEncoder(enc);
        return (((float)counts / PULSES_PER_REV) * 60.0f) / RPM_SCALING;
    }
}
