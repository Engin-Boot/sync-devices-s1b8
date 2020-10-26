import time
import settings
from MenuCLI import MenuCLI
from pubsub_util import PubSubUtil


def main_application(client):
    while not settings.exit_application:
        client.published = False
        MenuCLI.displayMainMenu()
        choice = settings.get_user_choice()
        settings.functions_map[choice]()
    

if __name__ == '__main__':

    settings.init_globals()

    settings.create_and_init_client()

    client = settings.client

    PubSubUtil.set_callbacks(client)

    client.subscribed = False

    client.published = False

    PubSubUtil.connect_client(client, settings.host, settings.port)

    settings.client.loop_start()

    PubSubUtil.wait_for_connection(client)

    client.subscribe(settings.topic)

    PubSubUtil.wait_for_subscription(client)

    main_application(client)

    client.loop_stop()

    client.disconnect()
