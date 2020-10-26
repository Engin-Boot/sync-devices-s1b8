import settings
import time
import random
from MenuCLI import MenuCLI

class PatientWrapper:
    @staticmethod
    def setAndPublishBusyStatus(client, busyStatus):
        settings.temporary_patient.setBusyStatus(busyStatus)
        msg = settings.temporary_patient.toString()
        client.publish(settings.topic, msg)


    @staticmethod
    def isPatientBusy():
        return settings.original_patient.getBusyStatus()


    @staticmethod
    def isPatientDataAvailable():
        return settings.original_patient.getId != 0


    @staticmethod
    def EditName():
        name = input("Enter corrected name: ")
        settings.temporary_patient.setName(name)


    @staticmethod
    def EditAge():
        age = int(input("Enter corrected age: "))
        settings.temporary_patient.setAge(age)

    @staticmethod
    def EditGender():
        gender = input("Enter corrected gender: ")
        settings.temporary_patient.setGender(gender)

    @staticmethod
    def EditProcedureName():
        procedureName = input("Enter procedure name: ")
        settings.temporary_patient.setProcedureName(procedureName)

    @staticmethod
    def EditAll():
        PatientWrapper.EditName()
        PatientWrapper.EditAge()
        PatientWrapper.EditGender()
        PatientWrapper.EditProcedureName()

    @staticmethod
    def isPatientDataAvailableAndFree():
        if not PatientWrapper.isPatientDataAvailable():
            print("No patient details entered.. Please try after entering the patient details!")
            return False
        
        if PatientWrapper.isPatientBusy():
            print("Sorry! some procedure is already in progress with the current patient.. please try again in sometime..") 
            return False
        
        return True
    
    @staticmethod 
    def procedure(repeat_count):
        count = 0
        while count < repeat_count:
            time.sleep(1)
            strInput = input("Enter any consumable used till now: (if nothing, type none) ")
            if strInput != "none":
                settings.temporary_patient.addConsumables(strInput)
            count += 1

    @staticmethod
    def startProcedure():
        client = settings.client

        if not PatientWrapper.isPatientDataAvailableAndFree:
            return
        
        PatientWrapper.setAndPublishBusyStatus(client, 1)

        PatientWrapper.procedure(repeat_count = 3)
        reportId = "MRI " + str(random.randint(100, 3000))
        settings.temporary_patient.addReportIds(reportId)

    
        settings.temporary_patient.setBusyStatus(0)
        msg = settings.temporary_patient.toString()
        client.publish(settings.topic, msg)


    @staticmethod
    def get_serialized_patient_info():
        name = input("Enter patient name: ")
        age = int(input("Enter age: "))
        gender = input("Enter gender: ")
        procedure_name = input("Enter procedure name: ")

        settings.temporary_patient.setId(settings.get_patient_count())
        settings.temporary_patient.setName(name)
        settings.temporary_patient.setAge(age)
        settings.temporary_patient.setGender(gender)
        settings.temporary_patient.setProcedureName(procedure_name)

        return settings.temporary_patient.toString()

    @staticmethod
    def addNewPatient():
        client = settings.client
        settings.update_patient_count()
        msg = PatientWrapper.get_serialized_patient_info()
        client.publish(settings.topic, msg)
        while not client.published:
            time.sleep(1)


    @staticmethod
    def editPatient():
        client = settings.client
        if not PatientWrapper.isPatientDataAvailableAndFree():
            return

        PatientWrapper.setAndPublishBusyStatus(client, 1)

        MenuCLI.displayEditMenu()
        
        print("Enter your choice: ")
        choice = settings.get_user_choice()

        settings.edit_functions_map[choice]()

        settings.temporary_patient.setBusyStatus(0)
        msg = settings.temporary_patient.toString()
        client.publish(settings.topic, msg)


    @staticmethod
    def printPatientInformation():
        print("Name: ", settings.original_patient.getName())
        print("Age: ", settings.original_patient.getAge())
        print("Gender:", settings.original_patient.getGender())
        print("Procedure Name: ", settings.original_patient.getProcedureName())
        print("Consumables: ", settings.original_patient.getConsumables())
        print("Report IDs", settings.original_patient.getReportIds())


    @staticmethod
    def printPatientCount():
        patient_count = settings.get_patient_count()
        print("Patient Count: ", patient_count)