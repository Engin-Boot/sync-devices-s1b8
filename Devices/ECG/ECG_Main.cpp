#include "PatientWrapper.hpp"
#include "ECG.hpp"
#include "MQTTAsync.h"
#include "pubsub.hpp"
#include "MenuCLI.hpp"

#define TOPIC "MedicalDevice"
#define CLIENT_ID "CT_CLIENT_1"
#define BROKER_URL "tcp://localhost:1883"

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

    finished = 0;
    subscribed = 0;
    published = 0;
    disconnected = 0;
    exit_application = 0;
    serialized_data = "";
    publishable = false;
}

void MainMenu()
{
    int choice;
    DisplayChoices();
    choice = getUserChoice();
    ExecuteMainMenuChoice(choice);
    PublishToSynchronize();
}

void MainApplication()
{
    char choice;
    cout << "Warm greetings! Welcome to Philips ECG_v1 system.. " << endl;
    cout << "Enter 'm' for Menu Page and 'q' to exit the application: ";
    cin >> choice;
    if(choice == 'm')
    {
        MainMenu();
    }
    else if(choice == 'q')
    {
        DisconnectAndWaitForDisconnection();
        DestroyClient();
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    const char *broker_url = (const char *)BROKER_URL;

    InitGlobals();

    CreateClient(broker_url);

    SetInitalCallbacks();

    ConnectClientToBrokerAndSubscribe();

    SetOnPublishCallbacks();

    InitializeMainApplication();

    while (!exit_application)
    {
        MainApplication();
    }

    DisconnectAndWaitForDisconnection();

    DestroyClient();
    
    return EXIT_SUCCESS;
}