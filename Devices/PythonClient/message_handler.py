import settings
import copy


class MessageHandler:
    @staticmethod
    def handle_edit():
        condition = settings.temporary_patient.getId() != settings.original_patient.getId()        
        if condition:
            settings.update_patient_count()
            settings.update_inventory(settings.original_patient.getProcedureName().lower().strip())
            settings.send_mail_if_stock_low()
            
        
    @staticmethod
    def handle_message(message):
        contents = list(message.strip().split(";"))
        settings.original_patient.setId(contents[0])
        settings.original_patient.setName(contents[1])
        settings.original_patient.setGender(contents[2])
        settings.original_patient.setAge(int(contents[3]))
        settings.original_patient.setProcedureName(contents[4])
        settings.original_patient.setConsumables(contents[5])
        settings.original_patient.setReportIds(contents[6])
        settings.original_patient.setBusyStatus(int(contents[7]))

        MessageHandler.handle_edit()

        settings.temporary_patient = copy.deepcopy(settings.original_patient)


        
