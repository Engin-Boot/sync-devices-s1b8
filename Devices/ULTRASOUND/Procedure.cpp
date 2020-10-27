#include "Procedure.hpp"

int randomNoGeneration()
{
	srand((unsigned)time(0));
	int randomNumber;
	randomNumber = (rand() % 3000);
	return randomNumber;
}

void procedure() {
	string strInput;
	int count = 0;
	while (count < PROCEDURE_RUN_TIME) {
		sleep(3);
		cout << "Enter any consumable used till now: (If more than one, add comma seperated/ if nothing, type none)" << endl;
		cin >> strInput;
		if (strInput != "none") {
			addConsumable(strInput);
		}
		count++;
	}
}


void startProcedure() {
	if (!isPatientDataAvailable()) {
		cout << "No patient details entered.. Please try after entering the patient details! " << endl;
		return;
	}

	if(!isPatientFree()) {
		cout << "The patient data is being used by some other device. Try again after sometime..." << endl;
		return;
	}

	setAndPublishPatientBusy();

	cout << "Procedure has started on the patient with below mentioned details! " << endl;
	printPatientInformation();

	procedure();

	int randomNumber = randomNoGeneration();

	string reportId = "ULTRASOUND" + to_string(randomNumber);

	addReportId(reportId);

	cout << "Procedure has completed successfully!" << endl;

	unsetPatientBusyStatus();
	serialized_data = temporary_patient.toString();
	publishable = true;
}