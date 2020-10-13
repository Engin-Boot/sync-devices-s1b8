#include <iostream>
#include <windows.h>
#include <signal.h>
#include <cstdio>
#include <stdlib.h>
#include <string>

#include "inc/MQTTAsync.h"
#include "inc/pubsub_opts.h"

using namespace std;

#define sleep Sleep

MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
static int disconnected = 0;
static int connected = 0;
static int published = 0;
MQTTAsync client;

struct pubsub_opts opts =
{
	1, 0, 0, MQTTASYNC_TRACE_MAXIMUM, "\n", 100,  	/* debug/app options */
	MQTTVERSION_DEFAULT, NULL, "MRI_v1_pub", 0, 0, "localhost", "1883", NULL, 10, /* MQTT options */
};

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m)
{
	return 1;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	disconnected = 1;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
	connected = -1;

	MQTTAsync client = (MQTTAsync)context;
}

void myconnect(MQTTAsync client);
int mypublish(MQTTAsync client, int datalen, const char* data);

void onConnect(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	int rc = 0;

	if (opts.verbose)
		printf("Connected\n");
	connected = 1;
}

void onPublishFailure(void* context, MQTTAsync_failureData* response)
{
	if (opts.verbose)
		fprintf(stderr, "Publish failed, rc %s\n", MQTTAsync_strerror(response->code));
	published = -1;
}

void onPublish(void* context, MQTTAsync_successData* response)
{
	if (opts.verbose)
		printf("Publish succeeded\n");

	published = 1;
}

void myconnect(MQTTAsync client)
{
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc = 0;

	if (opts.verbose)
		printf("Connecting\n");

	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.cleansession = 1;
	conn_opts.keepAliveInterval = opts.keepalive;
	conn_opts.MQTTVersion = opts.MQTTVersion;
	conn_opts.context = client;
	conn_opts.automaticReconnect = 1;

	connected = 0;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}


void connectPublisher() {
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	int rc = 0;
	const char* url = "localhost:1883";

	create_opts.sendWhileDisconnected = 1;

	rc = MQTTAsync_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL, &create_opts);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to create client, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

	rc = MQTTAsync_setCallbacks(client, client, NULL, messageArrived, NULL);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

	pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;

	myconnect(client);
}

int publish(string topicName, string message) {
	int rc;
	int datalen = (int)message.length();

	rc = MQTTAsync_send(client, topicName.c_str(), datalen, message.c_str(), opts.qos, opts.retained, &pub_opts);
	if (rc != MQTTASYNC_SUCCESS)
		fprintf(stderr, "Error from MQTTAsync_send: %s\n", MQTTAsync_strerror(rc));
	return rc;
}
