#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "config.h"

void setupWebserver();
String webserverProcessHtmlTemplate(const String& var);
void webserverNotFound(AsyncWebServerRequest *request);

#endif