from patient import Patient
from patient_wrapper import PatientWrapper
from inventory_manager import InventoryManager
import paho.mqtt.client as mqtt
import json
import os
from mailer import Mailer

def get_formated_message(scracity_details):
    msg_prefix = "Items List:\n\n\t"
    return msg_prefix + '\n\t'.join(item for item in scracity_details)


def send_mail_if_stock_low():
    global inv_manager
    sender_email_id = os.getenv('EMAIL_ID_SENDER')
    receiver_email_id = os.getenv('EMAIL_ID_RECEIVER')
    password = os.getenv('SENDER_PASSWORD')
    mail = Mailer(email=sender_email_id, password=password)
    scracity_details = inv_manager.getScarcityDetails()
    if len(scracity_details) != 0:
        message = get_formated_message(scracity_details)
        mail.send(receiver=receiver_email_id,
                  subject='LOW STOCK', message=message)

def update_inventory(procedure):
    global inv_manager
    inv_manager.updateInventory(procedure.lower().strip())


def exitApplication():
    global exit_application
    print("Exiting application...")
    exit_application = True


def init_mail_params():
    global sender_email_id
    global receiver_email_id
    global password
    sender_email_id = os.getenv('EMAIL_ID_SENDER')
    receiver_email_id = os.getenv('EMAIL_ID_RECEIVER')
    password = os.getenv('SENDER_PASSWORD')

def create_and_init_client():
    global client
    global client_id
    client_id = "Python_Client"
    client = mqtt.Client(client_id)


def init_globals():
    global exit_application
    global topic
    global original_patient
    global temporary_patient
    global host
    global port
    global main_menu_functions_map
    global edit_menu_functions_map
    global inv_manager

    main_menu_functions_map = {
        "1": PatientWrapper.addNewPatient,
        "2": PatientWrapper.editPatient,
        "3": PatientWrapper.startProcedure,
        "4": PatientWrapper.printPatientInformation,
        "5": PatientWrapper.printPatientCount,
        "6": exitApplication
    }

    edit_menu_functions_map = {
        "1": PatientWrapper.editName,
        "2": PatientWrapper.editAge,
        "3": PatientWrapper.editGender,
        "4": PatientWrapper.editProcedureName,
        "5": PatientWrapper.editAll
    }

    inventory_filepath = "json_data/inventory.json"
    inv_manager = InventoryManager(inventory_filepath)

    exit_application = False
    host = "localhost"
    port = 1883
    topic = "MedicalDevice"
    original_patient = Patient()
    temporary_patient = Patient()


def get_patient_count():
    filepath = 'json_data/patient_count.json'
    with open(filepath, 'r') as file:
        data = json.load(file)
    return int(data["patient_count"])


def update_patient_count():
    filepath = 'json_data/patient_count.json'
    patient_count = get_patient_count()
    patient_count += 1
    data = {"patient_count": patient_count}

    with open(filepath, 'w') as file:
        json.dump(data, file)


def get_user_choice():
    choice = input()
    return choice
