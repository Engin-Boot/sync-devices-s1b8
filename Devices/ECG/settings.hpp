#pragma once

#include "PatientWrapper.hpp"
#include "pubsub_opts.hpp"
#include "MQTTAsync.h"

Patient original_patient;
Patient temporary_patient;
pubsub_opts opts;
MQTTAsync client;

int finished;
int subscribed;
int published;
int disconnected;
int exit_application;
string serialized_data;
bool publishable;
char* client_id;
char* topic;

void set_client_id(char* id);
void set_topic(char* t);
void InitGlobals();

MQTTAsync_createOptions create_opts;
MQTTAsync_responseOptions pub_opts;
MQTTAsync_disconnectOptions disc_opts;