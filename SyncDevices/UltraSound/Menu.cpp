#include <iostream>

using namespace std;

extern void addNewPatient();
extern void editPatientInfo();
extern void startProcedure();
extern void printPatientInformation();

void menuPage() {
	int choice;
	cout << "Select one of the following menu items!" << endl;
	cout << "1. Add new Patient" << endl;
	cout << "2. Edit patient info" << endl;
	cout << "3. Start Procedure" << endl;
	cout << "4. Print Patient Data" << endl;
	cout << "Your choice (1/2/3/4)? ";
	cin >> choice;
	switch (choice) {
	case 1:
		addNewPatient();
		break;
	case 2:
		editPatientInfo();
		break;
	case 3:
		startProcedure();
		break;
	case 4:
		printPatientInformation();
		break;
	}
}

void mainMenu() {
	char choice;

	cout << "Warm greetings! Welcome to Philips UltraSound_v1 system.. " << endl;

	do {
		cout << "Select 'm' for Menu Page and 'q' to exit the application: ";
		cin >> choice;
		if (choice == 'm') {
			menuPage();
		}
	} while (choice != 'q');
	
	// write code to clear sessions, expty required things.. and have a graceful exit..

}