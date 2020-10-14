#include "Procedure.h"

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
	while (count < 6) {
		Sleep(10000);
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
	if (!isPatientFree()) {
		cout << "Sorry! some procedure is already in progress with the current patient.. please try again in sometime.." << endl;
		return;
	}

	cout << "Procedure has started on the patient with below mentioned details! " << endl;
	printPatientInformation();

	publishAndSetPatientBusyStatus(true);

	procedure();

	int randomNumber = randomNoGeneration();

	string reportId = "MRI" + to_string(randomNumber);

	addReportId(reportId);

	publishAndSetPatientBusyStatus(false);

	cout << "Procedure has completed successfully!" << endl;
	cout << "Patient details are!.." << endl;
	printPatientInformation();
}