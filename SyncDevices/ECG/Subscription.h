#pragma once

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <stdlib.h>
#include <string>

#include "inc/MQTTAsync.h"
#include "inc/MQTTClientPersistence.h"
#include "inc/pubsub_opts.h"

using namespace std;

#define sleep Sleep

extern void setPatientDetails(string);

volatile int finished = 0;
int subscribed = 0;
int disconnected = 0;

MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;

struct pubsub_opts sub_opts =
{
	0, 0, 0, MQTTASYNC_TRACE_MAXIMUM, "\n", 100,
	MQTTVERSION_DEFAULT, "Patient/Details", "ECG_v1_sub", 0, 0, "localhost", "1883", NULL, 10, /* MQTT options */
};

int messageArrived_sub(void* context, char* topic, int topicLen, MQTTAsync_message* message);
void onDisconnect_sub(void* context, MQTTAsync_successData* response);
void onSubscribe_sub(void* context, MQTTAsync_successData* response);
void onSubscribeFailure_sub(void* context, MQTTAsync_failureData* response);
void onConnectFailure_sub(void* context, MQTTAsync_failureData* response);
void onConnect_sub(void* context, MQTTAsync_successData* response);
void createClient_sub(MQTTAsync* client, string url, MQTTAsync_createOptions* create_opts);
void setCallbacks_sub(MQTTAsync* client);
void connectToBroker_sub(MQTTAsync* client);
int subscribe();