#include "PatientWrapper.h"

void publishPatientDetails(string topicName) {
	publish(topicName, temporaryPatientDetails.toString());
}

void publishAndSetPatientName(string newName) {
	temporaryPatientDetails.setName(newName);
	publishPatientDetails("Patient/Details");
}

void publishAndSetPatientGender(string newGender) {
	temporaryPatientDetails.setGender(newGender);
	publishPatientDetails("Patient/Details");
}

void publishAndSetPatientAge(int newAge) {
	temporaryPatientDetails.setAge(newAge);
	publishPatientDetails("Patient/Details");
}

void publishAndSetProcedureName(string newProcedureName) {
	temporaryPatientDetails.setProcedureName(newProcedureName);
	publishPatientDetails("Patient/Details");
}

void publishAndSetPatientBusyStatus(bool newStatus) {
	temporaryPatientDetails.setBusyStatus(newStatus);
	publishPatientDetails("Patient/Details");
}

void addConsumable(string newConsumable) {
	temporaryPatientDetails.addConsumable(newConsumable);
	publishPatientDetails("Patient/Details");
}

void addReportId(string newReportId) {
	temporaryPatientDetails.addReportId(newReportId);
	publishPatientDetails("Patient/Details");
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

bool checkPatientBusyness() {
	if (!isPatientFree()) {
		cout << "Some procedure is in progress with the current patient. Please try again in sometime..." << endl;
		return false;
	}
	return true;
}

bool userConfirmationPage() {
	string strInput;
	if (isPatientDataAvailable()) {
		cout << "Bullshit buffalo! you already have patient data... do you want to remove that information and add new patient (yes/no)? " << endl;
		cin >> strInput;
		if (strInput == "no") {
			return false;
		}
		return checkPatientBusyness();
	}
	return true;
}

void addNewPatient() {
	string strInput, verified;
	int intInput;

	if (!userConfirmationPage()) {
		return;
	}

	publishAndSetPatientBusyStatus(true);

	do {
		cout << "Enter patient name: ";
		cin >> strInput;
		temporaryPatientDetails.setName(strInput);

		cout << "Enter patient gender (Male/Female): ";
		cin >> strInput;
		temporaryPatientDetails.setGender(strInput);

		cout << "Enter patient age: ";
		cin >> intInput;
		temporaryPatientDetails.setAge(intInput);

		cout << "Enter Procedure name: ";
		cin >> strInput;
		temporaryPatientDetails.setProcedureName(strInput);

		cout << "Verified your details (yes/no)? ";
		cin >> verified;
	} while (verified == "no");

	publishPatientDetails("Patient/Add");

	publishAndSetPatientBusyStatus(false);
}

void checkAndPromptforName(char choice) {
	if (choice != 'n') {
		return;
	}
	string strInput;
	cout << "Enter new Name: ";
	cin >> strInput;
	publishAndSetPatientName(strInput);
}

void checkAndPromptforAge(char choice) {
	if (choice != 'a') {
		return;
	}
	int intInput;
	cout << "Enter new age: ";
	cin >> intInput;
	publishAndSetPatientAge(intInput);
}

void checkAndPromptforGender(char choice) {
	if (choice != 'g') {
		return;
	}
	string strInput;
	cout << "Enter new gender: ";
	cin >> strInput;
	publishAndSetPatientGender(strInput);
}

void checkAndPromptforProcedureName(char choice) {
	if (choice != 'p') {
		return;
	}
	string strInput;
	cout << "Enter new procedure name: ";
	cin >> strInput;
	publishAndSetProcedureName(strInput);
}


void editPatientInfo() {
	// show entered data first...
	// give option to select what he wants to edit...
	char choice;

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

	checkAndPromptforName(choice);
	checkAndPromptforAge(choice);
	checkAndPromptforGender(choice);
	checkAndPromptforProcedureName(choice);

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