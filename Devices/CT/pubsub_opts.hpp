#pragma once

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