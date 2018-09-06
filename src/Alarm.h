#ifndef Alarm_h
#define Alarm_h

#include <Arduino.h>

class Alarm
{
  public:
    Alarm();
    void setup();
    void loop(time_t &t);
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
    byte eepromByte = 0;
};
#endif