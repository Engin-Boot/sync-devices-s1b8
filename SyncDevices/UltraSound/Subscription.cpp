#include "Subscription.h"

int messageArrived_sub(void* context, char* topic, int topicLen, MQTTAsync_message* message)
{
	string topicName(topic);

	if (topicName == "Patient/Details") {
		cout << "Subscription end: " << (char*)message->payload << endl;
		setPatientDetails((char*)message->payload);
	}
	if (topicName == "Patient/Add") {
		cout << "Adding information" << (char*) message->payload <<  endl;
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
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
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