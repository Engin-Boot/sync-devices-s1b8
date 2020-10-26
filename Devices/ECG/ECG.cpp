#include "ECG.hpp"
#include "pubsub.hpp"

void CreateClient(const char* url)
{
    create_client_object(client, create_opts, url);
}

void SetInitalCallbacks()
{
    set_callbacks(client);
}

void WaitForConnection()
{
    while(!finished)
    {
        sleep(1);
        if(subscribed) break;
    }
}

void HandleBadConnectionIfAny()
{
    if(finished)
    {
        cout << "Connect failed..." << endl;
        DestroyClient();
        exit(EXIT_FAILURE);
    }
}

void ConnectClientToBrokerAndSubscribe()
{
    myconnect(client);
    WaitForConnection();
    HandleBadConnectionIfAny();
}

void SetOnPublishCallbacks()
{
    pub_opts.onSuccess = onPublish;
    pub_opts.onFailure = onPublishFailure;
}

void wait_for_publish()
{
    while(!published) sleep(1);
}

void PublishToSynchronize()
{
    if(publishable)
    {
        publish(client, pub_opts, serialized_data);
        wait_for_publish();
        published = 0;
        publishable = false;
    }
}


void DisconnectAndWaitForDisconnection()
{
    wait_for_disconnection(client, disc_opts);
}

void DestroyClient()
{
    MQTTAsync_destroy(&client);
}