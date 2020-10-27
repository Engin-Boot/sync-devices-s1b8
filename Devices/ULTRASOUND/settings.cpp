#include "settings.hpp"

void set_client_id(char* id)
{
    client_id = id;
}

void set_topic(char* t)
{
    topic = t;
}

void InitGlobals()
{
    opts =
    {
	    NULL, MQTTVERSION_DEFAULT, topic, client_id, 0, 0, 20, /* MQTT options */
    };

    create_opts = MQTTAsync_createOptions_initializer;
    pub_opts = MQTTAsync_responseOptions_initializer;
    disc_opts = MQTTAsync_disconnectOptions_initializer;

    finished = 0;
    subscribed = 0;
    published = 0;
    disconnected = 0;
    exit_application = 0;
    serialized_data = "";
    publishable = false;
}

