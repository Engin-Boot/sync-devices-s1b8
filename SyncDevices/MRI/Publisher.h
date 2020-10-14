#pragma once

#include <iostream>
#include <windows.h>
#include <signal.h>
#include <cstdio>
#include <stdlib.h>
#include <string>

#include "inc/MQTTAsync.h"
#include "inc/pubsub_opts.h"

using namespace std;

MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
static int disconnected_pub = 0;
static int connected_pub = 0;
static int published_pub = 0;
MQTTAsync client_pub;

struct pubsub_opts opts =
{
	1, 0, 0, MQTTASYNC_TRACE_MAXIMUM, "\n", 100,  	/* debug/app options */
	MQTTVERSION_DEFAULT, NULL, "MRI_v1_pub", 2, 0, "localhost", "1883", NULL, 10, /* MQTT options */
};

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m);
void onDisconnect(void* context, MQTTAsync_successData* response);
void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onConnect(void* context, MQTTAsync_successData* response);
void onPublishFailure(void* context, MQTTAsync_failureData* response);
void onPublish(void* context, MQTTAsync_successData* response);
void myconnect(MQTTAsync client_pub);
void connectPublisher();
int publish(string topicName, string message);