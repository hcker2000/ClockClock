#ifndef Config_h
#define Config_h
// NTP Servers:
//static const char ntpServerName[] = "us.pool.ntp.org";
static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

const int timeZone = 0; // This will be handled by the TimeZone lib so we need to supply that with UTC

static const char *stringDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const unsigned int ALARM_TOTAL = 14;
const unsigned int DISABLED_STATE = 0;
const unsigned int ENABLED_STATE = 1;
const unsigned int DELETED_STATE = 2;
const unsigned int START_FADE = 15;                                       // Controlls how long before the alarm that the leds will start fading in. This is in minutes
const unsigned long TIME_BETWEEN_LED_STEPS = (START_FADE * 60000) / 1024; // Milliseconds between led levels
static const uint8_t OFF_PIN = D3;
static const uint8_t LED_PIN = D5;
static const uint8_t VIBE_PIN = D6;
static const uint8_t BUZZER_PIN = D7;

#endif