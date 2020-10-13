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

int messageArrived_sub(void* context, char* topic, int topicLen, MQTTAsync_message* message)
{
	string topicName(topic);

	if (topicName == "Patient/Details") {
		cout << "Subscription end: " << (char*)message->payload << endl;
		setPatientDetails((char*)message->payload);
	}

	fflush(stdout);
	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topic);
	return 1;
}

void onDisconnect_sub(void* context, MQTTAsync_successData* response)
{
	disconnected = 1;
}

void onSubscribe_sub(void* context, MQTTAsync_successData* response)
{
	subscribed = 1;
}

void onSubscribeFailure_sub(void* context, MQTTAsync_failureData* response)
{
	if (!sub_opts.quiet)
		fprintf(stderr, "Subscribe failed, rc %s\n",
			MQTTAsync_strerror(response->code));
	finished = 1;
}

void onConnectFailure_sub(void* context, MQTTAsync_failureData* response)
{
	if (!sub_opts.quiet)
		fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
	finished = 1;
}


void onConnect_sub(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions ropts = MQTTAsync_responseOptions_initializer;
	int rc;

	ropts.onSuccess = onSubscribe_sub;
	ropts.onFailure = onSubscribeFailure_sub;
	ropts.context = client;
	if ((rc = MQTTAsync_subscribe(client, sub_opts.topic, sub_opts.qos, &ropts)) != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to start subscribe, return code %s\n", MQTTAsync_strerror(rc));
		finished = 1;
	}
}

void createClient_sub(MQTTAsync* client, string url, MQTTAsync_createOptions* create_opts) {
	int rc = MQTTAsync_createWithOptions(client, url.c_str(), sub_opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL, create_opts);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to create client, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}

void setCallbacks_sub(MQTTAsync* client) {
	int rc = MQTTAsync_setCallbacks(*client, *client, NULL, messageArrived_sub, NULL);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}

void connectToBroker_sub(MQTTAsync* client) {
	int rc;
	if ((rc = MQTTAsync_connect(*client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}

int subscribe() {
	MQTTAsync client;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	int rc = 0;
	const char* url = "localhost:1883";

	createClient_sub(&client, url, &create_opts);

	setCallbacks_sub(&client);

	conn_opts.onSuccess = onConnect_sub;
	conn_opts.onFailure = onConnectFailure_sub;
	conn_opts.cleansession = 1;
	conn_opts.keepAliveInterval = sub_opts.keepalive;
	conn_opts.MQTTVersion = sub_opts.MQTTVersion;
	conn_opts.context = client;
	conn_opts.automaticReconnect = 1;

	connectToBroker_sub(&client);

	while (!subscribed) {
		sleep(100);
	}

	cout << "Subscription to the topic was successful" << endl;
	return 0;
}