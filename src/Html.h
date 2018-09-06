#ifndef Html_h
#define Html_h
#include <ESP8266WebServer.h>

const char HTML_HEAD[] PROGMEM = "<!DOCTYPE html><html><head>"
                                 "<meta charset=\"utf-8\">"
                                 "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">"
                                 "<link rel=\"stylesheet\" href=\"https:/stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\" integrity=\"sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO\" crossorigin=\"anonymous\">"
                                 "<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.3.1/css/all.css\" integrity=\"sha384-mzrmE5qonljUremFsqc01SB46JvROS7bZs3IO2EmfFsd15uHvIt+Y8vEf7N7fWAU\" crossorigin=\"anonymous\">"
                                 "</head><body>"
                                 "<nav class=\"navbar navbar-dark bg-dark mb-3\">"
                                 "<a class=\"navbar-brand\" href=\"/\">ClockClock</a>"
                                 "</nav>"
                                 "<div class=\"container\">";
const char HTML_FOOT[] PROGMEM = "</div>"
                                 "<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>"
                                 "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\" integrity=\"sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49\" crossorigin=\"anonymous\"></script>"
                                 "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\" integrity=\"sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy\" crossorigin=\"anonymous\"></script>"
                                 "</body></html>";
const char HTML_INDEX[] PROGMEM = "<a href=\"/add\" class=\"btn btn-success mb-3\"><i class=\"fas fa-plus\"></i> New Alarm</a>"
                                  "<ul class=\"list-group\">"
                                  "{alarms}"
                                  "</ul>";
const char HTML_ALARM[] PROGMEM = "<li class=\"list-group-item\">"
                                  "<a class=\"btn btn-secondary btn-sm mr-3\" href=\"/toggle?alarm={index}\">{invertedStatus}</a>"
                                  "<span class=\"day\">{day}</span> at <span class=\"hour\">{hour}</span>:<span class=\"minute\">{minute}</span><a class=\"btn btn-danger btn-sm float-right\" href=\"/delete?alarm={index}\"><i class=\"fas fa-trash\"></i></a></li>";
const char HTML_FORM[] PROGMEM = "<form method=\"post\" action=\"/save\">"
                                 "<div class=\"form-group\">"
                                 "<label for=\"day\">Day</label>"
                                 "<select name=\"day\" class=\"form-control mb-2\">"
                                 "<option value=\"1\">Sunday</option>"
                                 "<option value=\"2\">Monday</option>"
                                 "<option value=\"3\">Tuesday</option>"
                                 "<option value=\"4\">Wednesday</option>"
                                 "<option value=\"5\">Thursday</option>"
                                 "<option value=\"6\">Friday</option>"
                                 "<option value=\"7\">Saturday</option>"
                                 "</select>"
                                 "</div>"
                                 "<div class=\"row\">"
                                 "<div class=\"col-12 col-sm-6\">"
                                 "<div class=\"form-group\">"
                                 "<label for=\"hour\">Hour</label>"
                                 "<input type=\"number\" name=\"hour\" min=\"0\" max=\"23\" class=\"form-control mb-2\" />"
                                 "</div>"
                                 "</div>"
                                 "<div class=\"col-12 col-sm-6\">"
                                 "<div class=\"form-group\">"
                                 "<label for=\"minute\">Minute</label>"
                                 "<input type=\"number\" name=\"minute\" min=\"0\" max=\"59\" class=\"form-control mb-2\" />"
                                 "</div>"
                                 "</div>"
                                 "</div>"
                                 "<button class=\"btn btn-success btn-block\">Save</button>"
                                 "</form>";

class Html
{
public:
  Html();
  void setup();
  void loop();

private:
  ESP8266WebServer *server = nullptr;
  byte _eepromByte;
  String wrapHtml(String body);
  void handleIndex();
  void handleForm();
  void handleSave();
  void handleDelete();
  void handleToggle();
  void redirectToIndex();
};
#endif