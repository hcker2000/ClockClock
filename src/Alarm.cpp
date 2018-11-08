#include "Alarm.h"
#include "Config.h"
#include "PadDigit.h"
#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <EEPROM.h>
#include <TimeLib.h> //https://github.com/PaulStoffregen/Time

Alarm::Alarm()
{
}

void Alarm::setup()
{
    EEPROM.begin(56);

    // Setup EEPROM values if need be
    for (unsigned int i = 0; i < ALARM_TOTAL; i++)
    {
        int alarmEnabledIndex = i * 4;
        eepromByte = EEPROM.read(alarmEnabledIndex);
        if (eepromByte != 0 && eepromByte != 1 && eepromByte != DELETED_STATE)
        {
            Serial.println("Setting up Alarm: " + (String)i);
            EEPROM.write(alarmEnabledIndex, DELETED_STATE);
            EEPROM.commit();
        }
    }

    // Setup output pins
    pinMode(LED_PIN, OUTPUT);
    pinMode(VIBE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Setup input pins
    pinMode(OFF_PIN, INPUT_PULLUP);

    analogWrite(LED_PIN, 0);
    digitalWrite(VIBE_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    attachInterrupt(OFF_PIN, std::bind(&Alarm::interruptHandler, this), FALLING);
}

void Alarm::loop(time_t &t)
{
    localTime = t;

    if (minute(localTime) != minute(lastUpdate))
    {
        lastUpdate = localTime;
        check();
    }

    process();
}

void Alarm::check()
{
    if (alarmRunning == false)
    {
        for (unsigned int i = 0; i < ALARM_TOTAL; i++)
        {
            int alarmEnabledIndex = i * 4;
            eepromByte = EEPROM.read(alarmEnabledIndex); // I am keeping the enabled byte at the head of each "page". A page being four bytes consisting of enabled, day, hour, minute
            if (eepromByte == ENABLED_STATE)
            {
                byte aDay = EEPROM.read(alarmEnabledIndex + 1);
                byte aHour = EEPROM.read(alarmEnabledIndex + 2);
                byte aMinute = EEPROM.read(alarmEnabledIndex + 3);

                // Check to see if we need to handle wraping back to the last minute
                int i = (aMinute - START_FADE);
                if (i < 0)
                {
                    aMinute = 60 + i; // adding a negative number

                    // Roll back the hour
                    if ((aHour - 1) < 0)
                    {
                        aHour = 23;

                        // Rollback Day
                        // Day is stored 1-7 rather than 0-6
                        if (aDay - 1 <= 0)
                        {
                            aDay = 7;
                        }
                    }
                }

                if (aDay == weekday(localTime))
                {
                    if (aHour == hour(localTime))
                    {
                        unsigned int startFadeSeconds = (START_FADE * 60);
                        if (aMinute == minute(localTime + startFadeSeconds))
                        {
                            Serial.println(PadDigit::format(hourFormat12(localTime)) + ":" + PadDigit::format(minute(localTime)));
                            Serial.println("Alarm Started!");
                            alarmRunning = true;
                            ledStartTime = localTime;
                            vibeStartTime = localTime + (startFadeSeconds - 60);
                            buzzerStartTime = vibeStartTime + 60;
                            alarmEndTime = buzzerStartTime + 60;
                        }
                    }
                }
            }
        }
    }
}

void Alarm::process()
{
    static unsigned long lastStepTime = millis();
    static unsigned long lastDigitalTime = millis();
    static bool isDigitalOn = false;

    if (alarmRunning == true)
    {
        if (localTime >= ledStartTime && ledLevel < 1024)
        {
            // Update leds
            if (millis() >= lastStepTime + TIME_BETWEEN_LED_STEPS)
            {
                lastStepTime = millis();
                ledLevel += 1;
                Serial.println("LED Level:" + (String)ledLevel);
                analogWrite(LED_PIN, ledLevel);
            }
        }

        if (localTime >= vibeStartTime || localTime >= buzzerStartTime)
        {
            if (millis() > (lastDigitalTime + 500))
            {
                lastDigitalTime += 500;

                if (isDigitalOn == true)
                {
                    isDigitalOn = false;

                    if (localTime >= vibeStartTime)
                    {
                        digitalWrite(VIBE_PIN, LOW);
                    }

                    if (localTime >= buzzerStartTime)
                    {
                        digitalWrite(BUZZER_PIN, LOW);
                    }
                }
                else
                {
                    isDigitalOn = true;

                    if (localTime >= vibeStartTime)
                    {
                        digitalWrite(VIBE_PIN, HIGH);
                    }

                    if (localTime >= buzzerStartTime)
                    {
                        digitalWrite(BUZZER_PIN, HIGH);
                    }
                }
            }
        }

        if (localTime >= alarmEndTime)
        {
            clear();
        }
    }
}

void Alarm::interruptHandler()
{
    static unsigned long last_interupt_time = 0;
    unsigned long now = millis();

    if (now - last_interupt_time > 100)
    {
        Serial.println("Alarm Off");
        clear();
    }

    last_interupt_time = now;
}

void Alarm::clear()
{
    alarmRunning = false;
    ledLevel = 0;
    analogWrite(LED_PIN, 0);
    digitalWrite(VIBE_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}

bool Alarm::running()
{
    return alarmRunning;
}