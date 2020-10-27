import time
import settings
from menu_cli import MenuCLI
from pubsub_util import PubSubUtil
from mailer import Mailer
from inventory_manager import InventoryManager


def get_formated_message(scracity_details):
    msg_prefix = "Items List:\n\n\t"
    return msg_prefix + '\n\t'.join(item for item in scracity_details)


def send_mail_if_stock_low(mail):
    scracity_details = settings.inv_manager.getScarcityDetails()
    if len(scracity_details) != 0:
        message = get_formated_message(scracity_details)
        mail.send(receiver=settings.receiver_email_id,
                  subject='LOW STOCK', message=message)


def main_application(client):
    mail = Mailer(email=settings.sender_email_id, password=settings.password)

    while not settings.exit_application:
        client.published = False
        MenuCLI.displayMainMenu()
        choice = settings.get_user_choice()
        settings.main_menu_functions_map[choice]()
        send_mail_if_stock_low(mail)


if __name__ == '__main__':

    settings.init_globals()

    settings.init_mail_params()

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
