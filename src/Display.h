#ifndef Display_h
#define Display_h

#include <Adafruit_SSD1306.h>

#define OLED_RESET 0 // GPIO0

class Display
{
public:
  Display();
  void setup();
  void loop(time_t &t);
  void ntpStatus(bool status);
  void showWifiInstructions(String apName);
  String ip;
  bool inverted;

private:
  time_t localTime;
  time_t lastUpdate;
  Adafruit_SSD1306 display;
  void updateDisplay();
  char ntpChar;
};
#endif