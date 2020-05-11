#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "config.h"

void setupWebserver();
void webserverHandleWebRequests();
void webserverHandleRoot();
bool webserverLoadFromSpiffs(String path);


#endif