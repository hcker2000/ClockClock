#include "Arduino.h"
#include "PadDigit.h"

PadDigit::PadDigit(){

}

String PadDigit::format(int digit){
  String r = (String) digit;
  if (digit < 10) {
    r = "0" + r;
  }

  return r;
}