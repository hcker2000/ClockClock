#include "Display.h"
#include "PadDigit.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>              //https://github.com/PaulStoffregen/Time

Display::Display()
{
    Adafruit_SSD1306 display(OLED_RESET);
    localTime = 0;
    lastUpdate = 0;
}

void Display::setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48);
  delay(250);
  display.clearDisplay();
}

void Display::loop(time_t &t)
{
    localTime = t;
    
    if (second(localTime) != second(lastUpdate)) {
        lastUpdate = localTime;
        updateDisplay();
    }
}

void Display::updateDisplay()
{
    String sHourMinute = PadDigit::format(hourFormat12(localTime)) + ":" + PadDigit::format(minute(localTime));
    
    String amPm = "";

    if (isAM(localTime))
    {
        amPm = "AM";
    }
    else
    {
        amPm = "PM";
    }

    Serial.println(sHourMinute);

    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(5, 0);
    display.clearDisplay();
    display.println(sHourMinute);

    display.setCursor(51, 32);
    display.setTextSize(2);
    display.println(amPm);
    
    display.setCursor(0, 55);
    display.setTextSize(0);
    display.println((String) ntpChar + " " + (String) ip);

    display.display();
}

void Display::ntpStatus(bool status)
{
    if(status){
        ntpChar = (char)24;
        return;
    }

    ntpChar = (char)25;
}

void Display::showWifiInstructions(String apName)
{   
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("WiFi Setup");
    display.setTextSize(0);
    display.println("");
    display.println("AP: " + apName);
    display.println("PWD: password");
    display.println("");
    display.println("Connect and configure your Wifi setting");
    display.display();
}