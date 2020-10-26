import settings

class MessageHandler:
    @staticmethod 
    def handle_message(message):
        contents = list(message.strip().split(";"))
      
        if settings.temporary_patient.getId() != int(contents[0]):
            settings.update_patient_count()
          
        settings.original_patient.setId(int(contents[0]))
        settings.original_patient.setName(contents[1])
        settings.original_patient.setGender(contents[2])
        settings.original_patient.setAge(int(contents[3]))
        settings.original_patient.setProcedureName(contents[4])
        settings.original_patient.setConsumables(contents[5])
        settings.original_patient.setReportIds(contents[6])
        settings.original_patient.setBusyStatus(int(contents[7]))
        settings.temporary_patient = settings.original_patient