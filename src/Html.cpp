#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <EEPROM.h>
#include "Config.h"
#include "Html.h"
#include "PadDigit.h"


byte _eepromByte = 0;

String Html::wrapHtml(String body)
{
    String header = FPSTR(HTML_HEAD);
    String footer = FPSTR(HTML_FOOT);

    return header + body + footer;
}

void Html::redirectToIndex()
{
    server->sendHeader("Location", String("/"), true);
    server->send(302, "text/plain", "");
}

void Html::handleIndex()
{
    if (server != nullptr)
    {
        String html = FPSTR(HTML_INDEX);

        // Build the html for the saved alarms
        String alarmsHtml = "";
        for (unsigned int i = 0; i < ALARM_TOTAL; i++)
        {
            int alarmEnabledIndex = i * 4;
            _eepromByte = EEPROM.read(alarmEnabledIndex);

            if (_eepromByte != DELETED_STATE)
            {
                String alarmHtml = FPSTR(HTML_ALARM);

                alarmHtml.replace("{index}", (String)alarmEnabledIndex);
                String invertedState = "Disable";
                if (_eepromByte == 0)
                {
                    invertedState = "Enable";
                }
                alarmHtml.replace("{invertedStatus}", invertedState);
                alarmHtml.replace("{day}", stringDays[EEPROM.read(alarmEnabledIndex + 1) - 1]); // The day is stored as 1-7 per the Time lib and our day names are of course base 0;
                alarmHtml.replace("{hour}", PadDigit::format(EEPROM.read(alarmEnabledIndex + 2)));
                alarmHtml.replace("{minute}", PadDigit::format(EEPROM.read(alarmEnabledIndex + 3)));

                alarmsHtml += alarmHtml;
            }
        }

        html.replace("{alarms}", alarmsHtml);
        server->send(200, "text/html", wrapHtml(html));
    }
}

void Html::handleForm()
{
    String html = FPSTR(HTML_FORM);
    server->send(200, "text/html", wrapHtml(html));
}

void Html::handleSave()
{
    for (unsigned int i = 0; i < ALARM_TOTAL; i++)
    {
        int alarmEnabledIndex = i * 4;
        _eepromByte = EEPROM.read(alarmEnabledIndex); // I am keeping the enabled byte at the head of each "page". A page beeing four bytes consisting of enabled, day, hour, minute
        if (_eepromByte == DELETED_STATE)
        { // Find the first available slot
            // Do save
            EEPROM.write(alarmEnabledIndex, 1);
            EEPROM.write(alarmEnabledIndex + 1, server->arg("day").toInt());
            EEPROM.write(alarmEnabledIndex + 2, server->arg("hour").toInt());
            EEPROM.write(alarmEnabledIndex + 3, server->arg("minute").toInt());
            EEPROM.commit();

            redirectToIndex();
            break;
        }
    }
    server->send(200, "text/html", "You have reached the max number of alarms"); // Send out the error page if we have hit the max alarms
}

void Html::handleDelete()
{
    if (server->hasArg("alarm"))
    {
        EEPROM.write(server->arg("alarm").toInt(), 2);
        EEPROM.commit();
    }

    redirectToIndex();
}

void Html::handleToggle()
{
    if (server->hasArg("alarm"))
    {
        int i = server->arg("alarm").toInt();
        _eepromByte = EEPROM.read(i);

        if (_eepromByte == 0)
        {
            EEPROM.write(i, 1);
        }
        else
        {
            EEPROM.write(i, 0);
        }
        EEPROM.commit();
    }

    redirectToIndex();
}

Html::Html()
{
    ESP8266WebServer server(80);
    this->server = &server;
}

void Html::setup()
{
    this->server->on("/", std::bind(&Html::handleIndex, this));
    this->server->on("/add", std::bind(&Html::handleForm, this));
    this->server->on("/save", std::bind(&Html::handleSave, this));
    this->server->on("/delete", std::bind(&Html::handleDelete, this));
    this->server->on("/toggle", std::bind(&Html::handleToggle, this));
    this->server->begin();
}

void Html::loop()
{
    this->server->handleClient();
}