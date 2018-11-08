#ifndef Alarm_h
#define Alarm_h

#include <Arduino.h>

class Alarm
{
public:
  Alarm();
  void setup();
  void loop(time_t &t);
  bool running();

private:
  time_t localTime;
  time_t lastUpdate;
  time_t ledStartTime;
  time_t vibeStartTime;
  time_t buzzerStartTime;
  time_t alarmEndTime;
  bool alarmRunning = false;
  void check();
  void process();
  void clear();
  void interruptHandler();
  byte eepromByte = 0;
  unsigned int ledLevel = 0;
};
#endif