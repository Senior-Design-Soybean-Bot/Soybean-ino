/*
* Owner: Marco Caliendo (MCal88)
* Contributors: Cameron Schwartzberg (BigBroccoli), and Andrew Barnes (abarnes6)
*/

#ifndef Encoders_h
#define Encoders_h

#include <Encoder.h>
#include <Arduino.h>

namespace encoders {
    struct Container {
        Encoder encoder1;
    };

    void setupEncoder(uint8_t pin_1, uint8_t pin_2, Encoder& encoder);
    long readEncoder(Encoder& enc);
    float getRPM(Encoder& enc);
}

#endif // Encoders_h
