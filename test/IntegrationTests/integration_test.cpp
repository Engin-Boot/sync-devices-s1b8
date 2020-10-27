#include <iostream>
#include <gtest/gtest.h>
#include "../../Devices/ECG/settings.cpp"
#include "../../Devices/ECG/PatientWrapper.cpp"
#include "../../Devices/ECG/ECG.cpp"
#include "../../Devices/ECG/Procedure.cpp"
#include "../../Devices/ECG/MenuCLI.cpp"
#include "../../Devices/ECG/message_handler.cpp"
#include "../../Devices/ECG/pubsub.cpp"

void connect_and_subscribe()
{
    const char *broker_url = (const char *)"tcp://localhost:1883";
    char* topic = (char*)"TEST_TOPIC";
    char* client_id = (char*)"ECG_CLIENT_TEST";

    set_client_id(client_id);
    set_topic(topic);
    InitGlobals();
    CreateClient(broker_url);
    SetInitalCallbacks();
    ConnectClientToBrokerAndSubscribe();
    SetOnPublishCallbacks();
}


TEST(ECG_CLIENT_INTEGRATION_TEST, TEST_SUBSCRIBE_ADD_AND_PUBLISH)
{
    // connect and subscribe
    connect_and_subscribe();

    // add patient details
	temporary_patient.setName("ABC");
	temporary_patient.setGender("Male");
	temporary_patient.setAge(30);
	temporary_patient.setProcedureName("HeartByPassSurgery");

    // serialize and publish
    serialized_data = temporary_patient.toString();
    publishable = true;
	PublishToSynchronize();
    publishable = false;

	EXPECT_EQ(temporary_patient.getName(), original_patient.getName());
	EXPECT_EQ(temporary_patient.getAge(), original_patient.getAge());
	EXPECT_EQ(temporary_patient.getGender(), original_patient.getGender());
	EXPECT_EQ(temporary_patient.getProcedureName(), original_patient.getProcedureName());

    // disconnect and free memory
    DisconnectAndWaitForDisconnection();
    DestroyClient();
}


TEST(ECG_CLIENT_INTEGRATION_TEST, TEST_SUBSCRIBE_EDIT_AND_PUBLISH)
{
    // connect and subscribe
    connect_and_subscribe();

    // add patient details
	temporary_patient.setName("ABC");
	temporary_patient.setGender("Male");
	temporary_patient.setAge(30);
	temporary_patient.setProcedureName("HeartByPassSurgery");

    // serialize and publish
    serialized_data = temporary_patient.toString();
    publishable = true;
	PublishToSynchronize();
    publishable = false;

    // edit
    setName("XYZ");
    setAge(25);
    setGender("Female");
    setProcedureName("Cardiac");

    serialized_data = temporary_patient.toString();
    publishable = true;
	PublishToSynchronize();
    publishable = false;

    EXPECT_EQ("XYZ", original_patient.getName());
	EXPECT_EQ(25, original_patient.getAge());
	EXPECT_EQ("Female", original_patient.getGender());
	EXPECT_EQ("Cardiac", original_patient.getProcedureName());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}