#include "Publisher.h"

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m)
{
	return 1;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	disconnected_pub = 1;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
	connected_pub = -1;
}

void onConnect(void* context, MQTTAsync_successData* response)
{
	if (opts.verbose)
		printf("connected_pub\n");
	connected_pub = 1;
}

void onPublishFailure(void* context, MQTTAsync_failureData* response)
{
	if (opts.verbose)
		fprintf(stderr, "Publish failed, rc %s\n", MQTTAsync_strerror(response->code));
	published_pub = -1;
}

void onPublish(void* context, MQTTAsync_successData* response)
{
	if (opts.verbose)
		printf("Publish succeeded\n");

	published_pub = 1;
}

void myconnect(MQTTAsync client_pub)
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
	conn_opts.context = client_pub;
	conn_opts.automaticReconnect = 1;

	connected_pub = 0;
	if ((rc = MQTTAsync_connect(client_pub, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}


void connectPublisher() {
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	int rc = 0;
	const char* url = "localhost:1883";

	create_opts.sendWhileDisconnected = 1;

	rc = MQTTAsync_createWithOptions(&client_pub, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL, &create_opts);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to create client_pub, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

	rc = MQTTAsync_setCallbacks(client_pub, client_pub, NULL, messageArrived, NULL);
	if (rc != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

	pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;

	myconnect(client_pub);
}

int publish(string topicName, string message) {
	int rc;
	int datalen = (int)message.length();

	rc = MQTTAsync_send(client_pub, topicName.c_str(), datalen, message.c_str(), opts.qos, opts.retained, &pub_opts);
	if (rc != MQTTASYNC_SUCCESS)
		fprintf(stderr, "Error from MQTTAsync_send: %s\n", MQTTAsync_strerror(rc));
	return rc;
}
