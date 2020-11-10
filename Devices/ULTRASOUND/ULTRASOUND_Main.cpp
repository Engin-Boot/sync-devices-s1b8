#include "ULTRASOUND.hpp"
#include "MenuCLI.hpp"
#include "pubsub.hpp"

#define TOPIC "MedicalDevice"
#define CLIENT_ID "ULTRASOUND_CLIENT_1"
#define BROKER_URL "tcp://localhost:1883"

extern void set_client_id(char* id);
extern void set_topic(char* t);
extern void InitGlobals();

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
    cout << "\nWarm greetings! Welcome to Philips ULTRASOUND_v1 system.. " << endl;
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

    char* client_id = (char*)CLIENT_ID;
    
    char* topic = (char*)TOPIC;

    set_client_id(client_id);

    set_topic(topic);

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