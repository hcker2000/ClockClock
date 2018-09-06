#ifndef PadDigit_h
#define PadDigit_h
#include "Arduino.h"
class PadDigit{
    public:
        PadDigit();
        static String format(int digit);
};
#endif