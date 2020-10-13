#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "inc/Patient.h"

using namespace std;

extern int publish(string topicName, string message);

Patient originalPatientDetails;
Patient temporaryPatientDetails;

void publishPatientDetails() {
	publish("Patient/Details", temporaryPatientDetails.toString());
}

void publishAndSetPatientName(string newName) {
	temporaryPatientDetails.setName(newName);
	publishPatientDetails();
}

void publishAndSetPatientGender(string newGender) {
	temporaryPatientDetails.setGender(newGender);
	publishPatientDetails();
}

void publishAndSetPatientAge(int newAge) {
	temporaryPatientDetails.setAge(newAge);
	publishPatientDetails();
}

void publishAndSetProcedureName(string newProcedureName) {
	temporaryPatientDetails.setProcedureName(newProcedureName);
	publishPatientDetails();
}

void publishAndSetPatientBusyStatus(bool newStatus) {
	temporaryPatientDetails.setBusyStatus(newStatus);
	publishPatientDetails();
}

void addConsumable(string newConsumable) {
	temporaryPatientDetails.addConsumable(newConsumable);
	publishPatientDetails();
}

void addReportId(string newReportId) {
	temporaryPatientDetails.addReportId(newReportId);
	publishPatientDetails();
}

bool isPatientDataAvailable() {
	if (originalPatientDetails.isEmpty()) {
		return false;
	}
	return true;
}

bool isPatientFree() {
	if (originalPatientDetails.isFree()) {
		return true;
	}
	return false;
}

void printPatientInformation() {
	cout << "Patient Name: " << originalPatientDetails.getName() << endl;
	cout << "Patent Gender: " << originalPatientDetails.getGender() << endl;
	cout << "Patient Age: " << originalPatientDetails.getAge() << endl;
	cout << "Procedure Name: " << originalPatientDetails.getProcedureName() << endl;
	cout << "Consumables: " << originalPatientDetails.getConsumables() << endl;
	cout << "ReportIds: " << originalPatientDetails.getReportIds() << endl;
	cout << "Busy state: " << originalPatientDetails.getBusyStatus() << endl;
}

void addNewPatient() {
	string strInput, verified;
	int intInput;
	if (isPatientDataAvailable()) {
		cout << "Bullshit buffalo! you already have patient data... do you want to remove that information and add new patient (yes/no)? " << endl;
		cin >> strInput;
		if (strInput == "no") {
			return;
		}
		
		// check whether the patient is free or not.. if not free.. then ask him to try again later.. 
		if (!isPatientFree()) {
			cout << "Some procedure is in progress with the current patient. Please try again in sometime..." << endl;
			return;
		}
	}
	
	publishAndSetPatientBusyStatus(true);

	do {
		cout << "Enter patient name: ";
		cin >> strInput;
		publishAndSetPatientName(strInput);

		cout << "Enter patient gender (Male/Female): ";
		cin >> strInput;
		publishAndSetPatientGender(strInput);

		cout << "Enter patient age: ";
		cin >> intInput;
		publishAndSetPatientAge(intInput);

		cout << "Enter Procedure name: ";
		cin >> strInput;
		publishAndSetProcedureName(strInput);

		cout << "Verified your details (yes/no)? ";
		cin >> verified;
	} while (verified == "no");

	publishAndSetPatientBusyStatus(false);
}

void editPatientInfo() {
	// show entered data first...
	// give option to select what he wants to edit...
	char choice;
	string strInput;
	int intInput;

	if (!isPatientDataAvailable()) {
		cout << "Sorry.. no patient data is available. Kindly add patient info before editing..." << endl;
		return;
	}

	if (!isPatientFree()) {
		cout << "Some procedure is in progress with the patient.. Try again in sometime.. " << endl;
		return;
	}

	publishAndSetPatientBusyStatus(true);
	
	cout << "The following are the entered patient information: " << endl;
	printPatientInformation();

	cout << "What do you want to edit (n for name/ a for age/ g for gender/ p for procedurename/ q to quit edit mode)? ";
	cin >> choice;
	switch (choice)
	{
	case 'n':
		cout << "Enter new Name: ";
		cin >> strInput;
		publishAndSetPatientName(strInput);
		break;
	case 'a':
		cout << "Enter new age: ";
		cin >> intInput;
		publishAndSetPatientAge(intInput);
		break;
	case 'g':
		cout << "Enter new gender: ";
		cin >> strInput;
		publishAndSetPatientGender(strInput);
		break;
	case 'p':
		cout << "Enter new procedure name: ";
		cin >> strInput;
		publishAndSetProcedureName(strInput);
		break;
	case 'q':
		break;
	default:
		cout << "Invalid option selected.." << endl;
		break;
	}
	
	publishAndSetPatientBusyStatus(false);
}

void setPatientDetails(string details) {
	string param;
	stringstream ss(details);
	vector<string>params;
	while (getline(ss, param, ';')) {
		params.push_back(param);
	}

	originalPatientDetails.setName(params[0]);
	originalPatientDetails.setGender(params[1]);
	originalPatientDetails.setAge(stoi(params[2]));
	originalPatientDetails.setProcedureName(params[3]);
	originalPatientDetails.setConsumables(params[4]);
	originalPatientDetails.setReportIds(params[5]);
	bool val = params[6] == "1";
	originalPatientDetails.setBusyStatus(val);
	
	temporaryPatientDetails = originalPatientDetails;
}