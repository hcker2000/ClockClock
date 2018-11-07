#include "Config.h"
#include "Html.h"
#include <TimeLib.h>  //https://github.com/PaulStoffregen/Time
#include <Timezone.h> //https://github.com/JChristensen/Timezone
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <DNSServer.h>   //Local DNS Server used for redirecting all requests to the configuration portal
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include "Display.h"
#include "Alarm.h"

Display oledDisplay;
Alarm alarm;
Html htmlLib;

WiFiUDP Udp;
unsigned int localPort = 8888; // local port to listen for UDP packets

TimeChangeRule dstStart = {"EDT", Second, Sun, Mar, 2, -240}; //UTC - 4 hours
TimeChangeRule dstEnd = {"EST", First, Sun, Nov, 2, -300};    //UTC - 5 hours
Timezone localTimeZone(dstStart, dstEnd);

time_t getNtpTime();

void sendNTPpacket(IPAddress &address);

void configModeCallback(WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  oledDisplay.showWifiInstructions(myWiFiManager->getConfigPortalSSID());
}

void setup()
{
  Serial.begin(9600);
  oledDisplay.setup();
  alarm.setup();
  delay(250);
  Serial.println("ClockClock the alarm clock");

  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);

  // This will block untell the wifi connection has been configured and/or connected
  if (!wifiManager.autoConnect("ClockClock", "password"))
  {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(5); // update from ntp every 5 seconds

  htmlLib.setup();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    IPAddress myIP = WiFi.localIP();
    String ipStr = String(myIP[0]) + "." + String(myIP[1]) + "." + String(myIP[2]) + "." + String(myIP[3]);
    oledDisplay.ip = ipStr;
  }
  else
  {
    oledDisplay.ip = "";
  }

  htmlLib.loop();

  if (timeStatus() != timeNotSet)
  {
    time_t localTime = localTimeZone.toLocal(now());
    oledDisplay.inverted = alarm.running();
    oledDisplay.loop(localTime);
    alarm.loop(localTime);
  }
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48;     // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0)
    ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500)
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE)
    {
      oledDisplay.ntpStatus(true);
      Udp.read(packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 = (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];

      setSyncInterval(300); // update from ntp every 5 minutes
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  oledDisplay.ntpStatus(false);

  setSyncInterval(5); // update from ntp every 5 seconds
  return 0;           // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0;          // Stratum, or type of clock
  packetBuffer[2] = 6;          // Polling Interval
  packetBuffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
