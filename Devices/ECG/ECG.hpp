#pragma once

#include <iostream>
#include "MQTTAsync.h"
using namespace std;

extern MQTTAsync client;
extern MQTTAsync_createOptions create_opts;
extern MQTTAsync_responseOptions pub_opts;
extern MQTTAsync_disconnectOptions disc_opts;

extern string serialized_data;
extern bool publishable;

void CreateClient(const char* url);
void SetInitalCallbacks();
void ConnectClientToBrokerAndSubscribe();
void SetOnPublishCallbacks();
void PublishToSynchronize();
void DisconnectAndWaitForDisconnection();
void DestroyClient();


