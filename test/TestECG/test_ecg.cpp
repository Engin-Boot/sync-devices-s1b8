#include <iostream>
#include <gtest/gtest.h>
#include "MQTTAsync.h"
#include "../../Devices/ECG/PatientWrapper.cpp"
#include "../../Devices/ECG/ECG.cpp"
#include "../../Devices/ECG/Procedure.cpp"
#include "../../Devices/ECG/MenuCLI.cpp"
#include "../../Devices/ECG/message_handler.cpp"
#include "../../Devices/ECG/pubsub.cpp"
#include "../../Patient/Patient.cpp"
#include<unistd.h>
#define TOPIC "MedicalDevice"
#define CLIENT_ID "CT_CLIENT_1"
#define BROKER_URL "tcp://localhost:1883"

Patient original_patient;
Patient temporary_patient;
pubsub_opts opts;
MQTTAsync client;
int exit_application;
int finished;
int subscribed;
int published;
int disconnected;
string serialized_data;
bool publishable;

MQTTAsync_createOptions create_opts;
MQTTAsync_responseOptions pub_opts;
MQTTAsync_disconnectOptions disc_opts;

void InitGlobals()
{
    opts =
    {
	    NULL, MQTTVERSION_DEFAULT, (char*)TOPIC, (char*)CLIENT_ID, 0, 0, 20, /* MQTT options */
    };

    create_opts = MQTTAsync_createOptions_initializer;
    pub_opts = MQTTAsync_responseOptions_initializer;
    disc_opts = MQTTAsync_disconnectOptions_initializer;
    exit_application=0;
    finished = 0;
    subscribed = 0;
    published = 0;
    disconnected = 0;
    serialized_data = "";
    publishable = false;
}

TEST(ECG_PublishAndSetPatientDetails, TestPatientDetails)
{
   
	temporary_patient.setName("ABC");
	temporary_patient.setGender("Male");
	temporary_patient.setAge(30);
	temporary_patient.setProcedureName("HeartByPassSurgery");

    serialized_data = temporary_patient.toString();
    publishable = true;
	PublishToSynchronize();
    publishable = false;

	EXPECT_EQ(temporary_patient.getName(), original_patient.getName());
	EXPECT_EQ(temporary_patient.getAge(), original_patient.getAge());
	EXPECT_EQ(temporary_patient.getGender(), original_patient.getGender());
	EXPECT_EQ(temporary_patient.getProcedureName(), original_patient.getProcedureName());

    DisconnectAndWaitForDisconnection();
    DestroyClient();
}

int main(int argc, char **argv) {
    const char *broker_url = (const char *)BROKER_URL;
    InitGlobals();
    CreateClient(broker_url);
    SetInitalCallbacks();
    ConnectClientToBrokerAndSubscribe();
    SetOnPublishCallbacks();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}