#include <iostream>
#include <sstream>
#include "PatientWrapper.hpp"
#include "message_handler.hpp"

extern Patient original_patient;
extern Patient temporary_patient;

vector<string> split(const char* data)
{
    vector<string> contents;
    stringstream ss(data);
    string token;
    while (getline(ss, token, ';')) {
        contents.push_back(token);
    }
    return contents;
}

void handle_incoming_messages(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    vector<string> contents = split((char*)message->payload);
    original_patient.setName(contents[0]);
    original_patient.setGender(contents[1]);
    original_patient.setAge(stoi(contents[2]));
    original_patient.setProcedureName(contents[3]);
    original_patient.setConsumables(contents[4]);
    original_patient.setReportIds(contents[5]);
    temporary_patient = original_patient;
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
}