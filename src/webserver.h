#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "userconfig.h"

void setupWebserver();
String webserverProcessHtmlTemplate(const String& var);
void webserverNotFound(AsyncWebServerRequest *request);

#endif