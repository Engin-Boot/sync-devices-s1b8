#include <iostream>
#include <string>
#include <signal.h>
#include <Windows.h>
#include <ctime>

using namespace std;

extern bool isPatientDataAvailable();
extern bool isPatientFree();
extern void publishAndSetPatientBusyStatus(bool);
extern void printPatientInformation();
extern void addConsumable(string);
extern void addReportId(string);

int randomNoGeneration()
{
	srand((unsigned)time(0));
	int randomNumber;
	randomNumber = (rand() % 3000);
	return randomNumber;
}

void startProcedure() {
	int count = 0;
	string strInput;
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
	
	while (count < 6) {
		Sleep(10000);
		cout << "Enter any consumable used till now: (If more than one, add comma seperated/ if nothing, type none)" << endl;
		cin >> strInput;
		if (strInput != "none") {
			addConsumable(strInput);
		}
		count++;
	}
	
	// write function to generate random reportID..

	int randomNumber = randomNoGeneration();

	string reportId = "ECG" + to_string(randomNumber);

	addReportId(reportId);

	publishAndSetPatientBusyStatus(false);

	cout << "Procedure has completed successfully!" << endl;
	cout << "Patient details are!.." << endl;
	printPatientInformation();
}