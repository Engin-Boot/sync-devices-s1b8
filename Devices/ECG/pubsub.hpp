#pragma once

#include <iostream>
#include "MQTTAsync.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

struct pubsub_opts
{
    /* Message options */
    char *message;
    /* MQTT options */
    int MQTTVersion;
    char *topic;
    char *clientid;
    int qos;
    int retained;
    int keepalive;
};

extern pubsub_opts opts;
extern int finished;
extern int subscribed;
extern int published;
extern int disconnected;

extern void handle_incoming_messages(void *context, char *topicName, int topicLen, MQTTAsync_message *message);

void mysleep(int ms);

void disconnect_client(MQTTAsync &client, MQTTAsync_disconnectOptions &disc_opts);

int mypublish(MQTTAsync client, int datalen, std::string &data, MQTTAsync_responseOptions &pub_opts);

void publish(MQTTAsync &client, MQTTAsync_responseOptions &pub_opts, string &data);

void wait_for_disconnection(MQTTAsync &client, MQTTAsync_disconnectOptions &disc_opts);

void create_client_object(MQTTAsync &client, MQTTAsync_createOptions &create_opts, const char *url);

void set_callbacks(MQTTAsync &client);

int myconnect(MQTTAsync client);

void onDisconnect(void *context, MQTTAsync_successData *response);

void onPublishFailure(void *context, MQTTAsync_failureData *response);

void onPublish(void *context, MQTTAsync_successData *response);

void onSubscribe(void *context, MQTTAsync_successData *response);

void onSubscribeFailure(void *context, MQTTAsync_failureData *response);

void onConnectFailure(void *context, MQTTAsync_failureData *response);

void onConnect(void *context, MQTTAsync_successData *response);

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message);
