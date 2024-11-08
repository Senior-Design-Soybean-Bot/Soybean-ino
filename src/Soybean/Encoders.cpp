/*
* This file is connected to "Encoders.cpp"
* Owner: Marco Caliendo (MCal88)
* Contributors: Cameron Schwartzberg (BigBroccoli), and Andrew Barnes (abarnes6)
*/


#include "Encoders.h"
#include "PinDefinitions.h"

namespace encoders {
    int readEncoder(Encoder &enc){
        return enc.read();
    }

    float getRPM(Encoder &e){
        int counts = readEncoder(e);
        return ((counts / static_cast<float>(PPR)) * 60.0) / CV;
    }

    
}
