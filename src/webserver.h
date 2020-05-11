#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "config.h"
//#include "ESPAsyncWebServer.h"

void setupWebserver();
void webserverHandleWebRequests();
void webserverHandleRoot();
bool webserverLoadFromSpiffs(String path);


#endif