#include <iostream>
#include <gtest/gtest.h>
#include "../../Devices/ECG/pubsub.cpp"
#include <unistd.h>

#define LATENCY 2
#define TOPIC "MedicalDevice"
#define CLIENT_ID "CT_CLIENT_1"
#define BROKER_URL "tcp://mqtt.eclipse.org:1883"

using namespace std;

pubsub_opts opts;
MQTTAsync client;
int finished;
int subscribed;
int published;
int disconnected;

MQTTAsync_createOptions create_opts;
MQTTAsync_responseOptions pub_opts;
MQTTAsync_disconnectOptions disc_opts;

string payload;

void InitGlobals()
{
    opts =
    {
	    NULL, MQTTVERSION_DEFAULT, (char*)TOPIC, (char*)CLIENT_ID, 0, 0, 20, /* MQTT options */
    };

    create_opts = MQTTAsync_createOptions_initializer;
    pub_opts = MQTTAsync_responseOptions_initializer;
    disc_opts = MQTTAsync_disconnectOptions_initializer;
    finished = 0;
    subscribed = 0;
    published = 0;
    disconnected = 0;
}

void handle_incoming_messages(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    payload = (char*)message->payload;
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
}

TEST(pubsub_unittest, test_connect_and_subscribe)
{
    EXPECT_EQ(subscribed,0);
    myconnect(client);
    sleep(LATENCY);
    EXPECT_EQ(subscribed,1);
}

TEST(pubsub_unittest, test_publish)
{
    string message = "Hello";
    EXPECT_EQ(published,0);
    publish(client, pub_opts, message );
    sleep(LATENCY);
    EXPECT_EQ(published,1);
    EXPECT_EQ(payload, "Hello");
}


int main(int argc, char **argv) {
    const char *broker_url = (const char *)BROKER_URL;
    InitGlobals();
    create_client_object(client, create_opts, broker_url);
    set_callbacks(client);
    pub_opts.onSuccess = onPublish;
    pub_opts.onFailure = onPublishFailure;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
