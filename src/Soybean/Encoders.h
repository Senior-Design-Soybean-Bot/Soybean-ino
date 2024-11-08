/*
* Owner: Marco Caliendo (MCal88)
* Contributors: Cameron Schwartzberg (BigBroccoli), and Andrew Barnes (abarnes6)
*/

#ifndef Encoders_h
#define Encoders_h

#include <Encoder.h>
#include <Arduino.h>

namespace encoders {
    int readEncoder(Encoder &enc);
    float getRPM(Encoder &e);

    constexpr int PPR = 600;
    constexpr uint8_t CV = 4;
}

#endif // Encoders_h
