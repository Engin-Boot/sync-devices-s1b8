#include <iostream>
#include <string>
#include <unistd.h>
#include <ctime>

#define PROCEDURE_RUN_TIME 3

#include "../../Patient/Patient.hpp"

using namespace std;

extern bool isPatientDataAvailable();
extern void printPatientInformation();
extern void addConsumable(const string& consumable);
extern void addReportId(const string& report_id);
extern bool publishable;
extern string serialized_data;
extern Patient temporary_patient;

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

	cout << "Procedure has started on the patient with below mentioned details! " << endl;
	printPatientInformation();

	procedure();

	int randomNumber = randomNoGeneration();

	string reportId = "ECG" + to_string(randomNumber);

	addReportId(reportId);

	cout << "Procedure has completed successfully!" << endl;
	
	publishable = true;
	serialized_data = temporary_patient.toString();
}