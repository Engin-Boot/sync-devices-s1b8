from Patient import Patient
from PatientWrapper import PatientWrapper
import paho.mqtt.client as mqtt
import json

def exitApplication():
    global exit_application
    print("Exiting application...")
    exit_application = True

def create_and_init_client():
    global client
    global client_id
    client_id = "client_1"
    client = mqtt.Client(client_id)

def init_globals():
    global exit_application
    global topic
    global original_patient
    global temporary_patient
    global host
    global port
    global functions_map
    global edit_functions_map

    functions_map = {
        "1" : PatientWrapper.addNewPatient,
        "2" : PatientWrapper.editPatient,
        "3" : PatientWrapper.startProcedure,
        "4" : PatientWrapper.printPatientInformation,
        "5" : PatientWrapper.printPatientCount,
        "6" : exitApplication
    }

    edit_functions_map = {
        "1" : PatientWrapper.EditName,
        "2" : PatientWrapper.EditAge,
        "3" : PatientWrapper.EditGender,
        "4" : PatientWrapper.EditProcedureName,
        "5" : PatientWrapper.EditAll
    }

    exit_application = False
    host = "localhost"
    port = 1883
    topic = "topic_1"
    original_patient = Patient()
    temporary_patient = Patient()


def get_patient_count():
    filepath = 'json_data/patient_count.json'
    with open(filepath, 'r') as file:
        data = json.load(file)
    return int(data["patient_count"])


def update_patient_count():
    filepath = 'json_data/patient_count.json'
    patient_count  = get_patient_count()
    patient_count += 1
    data = {"patient_count" : patient_count}

    with open(filepath, 'w') as file:
        json.dump(data, file)
    
def get_user_choice():
    choice = input()
    return choice