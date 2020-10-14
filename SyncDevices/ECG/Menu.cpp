#include <iostream>
#include "Menu.h"

using namespace std;

void checkAndExecuteAddPatient(int choice) {
	if (choice == 1) {
		addNewPatient();
	}
}

void checkAndExecuteEditPatient(int choice) {
	if (choice == 2) {
		editPatientInfo();
	}
}

void checkAndExecuteStartProcedure(int choice) {
	if (choice == 3) {
		startProcedure();
	}
}

void checkAndExecuteDisplayPatientData(int choice) {
	if (choice == 4) {
		printPatientInformation();
	}
}

void executeChoice(int choice) {
	checkAndExecuteAddPatient(choice);
	checkAndExecuteEditPatient(choice);
	checkAndExecuteStartProcedure(choice);
	checkAndExecuteDisplayPatientData(choice);
}

void menuPage() {
	int choice;
	cout << "Select one of the following menu items!" << endl;
	cout << "1. Add new Patient" << endl;
	cout << "2. Edit patient info" << endl;
	cout << "3. Start Procedure" << endl;
	cout << "4. Print Patient Data" << endl;
	cout << "Your choice (1/2/3/4)? ";
	cin >> choice;

	executeChoice(choice);
}

void mainMenu() {
	char choice;

	cout << "Warm greetings! Welcome to Philips ECG_v1 system.. " << endl;

	do {
		cout << "Select 'm' for Menu Page and 'q' to exit the application: ";
		cin >> choice;
		if (choice == 'm') {
			menuPage();
		}
	} while (choice != 'q');

	// write code to clear sessions, expty required things.. and have a graceful exit..
}