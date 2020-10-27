#include "pubsub.hpp"

void mysleep(int ms)
{
    usleep(ms * 1000);
}

void create_client_object(MQTTAsync &client, MQTTAsync_createOptions &create_opts, const char *url)
{
    int rc = 0;
    printf("URL is %s\n", url);
    create_opts.sendWhileDisconnected = 1;
    rc = MQTTAsync_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL, &create_opts);
    if (rc != MQTTASYNC_SUCCESS)
    {
        fprintf(stderr, "Failed to create client, return code: %s\n", MQTTAsync_strerror(rc));
        exit(EXIT_FAILURE);
    }
}

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{   
    handle_incoming_messages(context, topicName, topicLen, message);
    return 1;
}

void set_callbacks(MQTTAsync &client)
{
    int rc = 0;
    rc = MQTTAsync_setCallbacks(client, client, NULL, messageArrived, NULL);
    if (rc != MQTTASYNC_SUCCESS)
    {
        fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
        exit(EXIT_FAILURE);
    }
}


int myconnect(MQTTAsync client)
{
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    int rc = 0;
    printf("Connecting...\n");
    conn_opts.onSuccess = onConnect;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.cleansession = 1;
    conn_opts.keepAliveInterval = opts.keepalive;
    conn_opts.MQTTVersion = opts.MQTTVersion;
    conn_opts.context = client;
    conn_opts.automaticReconnect = 1;

    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
        exit(EXIT_FAILURE);
    }
    return rc;
}

void onDisconnect(void *context, MQTTAsync_successData *response)
{
    printf("Client Disconnected...\n");
    disconnected = 1;
}

void onPublishFailure(void *context, MQTTAsync_failureData *response)
{
    fprintf(stderr, "Publish failed, rc %s\n", MQTTAsync_strerror(response->code));
}

void onPublish(void *context, MQTTAsync_successData *response)
{
    printf("Published...\n");
    published = 1;
}

void onSubscribe(void *context, MQTTAsync_successData *response)
{
    printf("Subscribed Succesfully\n");
    subscribed = 1;
}

void onSubscribeFailure(void *context, MQTTAsync_failureData *response)
{
    fprintf(stderr, "Subscribe failed, rc %s\n",
            MQTTAsync_strerror(response->code));
    finished = 1;
}

void onConnectFailure(void *context, MQTTAsync_failureData *response)
{
    fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
    finished = 1;
}

void onConnect(void *context, MQTTAsync_successData *response)
{
    MQTTAsync client = (MQTTAsync)context;
    MQTTAsync_responseOptions ropts = MQTTAsync_responseOptions_initializer;
    int rc;

    printf("Subscribing to topic %s with client %s at QoS %d\n", opts.topic, opts.clientid, opts.qos);

    ropts.onSuccess = onSubscribe;
    ropts.onFailure = onSubscribeFailure;
    ropts.context = client;
    if ((rc = MQTTAsync_subscribe(client, opts.topic, opts.qos, &ropts)) != MQTTASYNC_SUCCESS)
    {
        fprintf(stderr, "Failed to start subscribe, return code %s\n", MQTTAsync_strerror(rc));
        finished = 1;
    }
}

void disconnect_client(MQTTAsync &client, MQTTAsync_disconnectOptions &disc_opts)
{
    int rc = 0;
    disc_opts.onSuccess = onDisconnect;
    if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS)
    {
        fprintf(stderr, "Failed to start disconnect, return code: %s\n", MQTTAsync_strerror(rc));
        exit(EXIT_FAILURE);
    }
}

int mypublish(MQTTAsync client, int datalen, std::string &data, MQTTAsync_responseOptions &pub_opts)
{
    int rc;
    printf("Publishing data of length %d\n", datalen);

    rc = MQTTAsync_send(client, opts.topic, datalen, data.c_str(), opts.qos, opts.retained, &pub_opts);
    if (rc != MQTTASYNC_SUCCESS)
        fprintf(stderr, "Error from MQTTAsync_send: %s\n", MQTTAsync_strerror(rc));

    return rc;
}

void publish(MQTTAsync &client, MQTTAsync_responseOptions &pub_opts, string &data)
{
    int rc = 0;
    rc = mypublish(client, data.length(), data, pub_opts);
    if (rc != MQTTASYNC_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
}

void wait_for_disconnection(MQTTAsync &client, MQTTAsync_disconnectOptions &disc_opts)
{
    disconnect_client(client, disc_opts);
    while (!disconnected)
        mysleep(100);
}

