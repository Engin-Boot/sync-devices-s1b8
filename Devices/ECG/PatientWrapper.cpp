#include "PatientWrapper.hpp"

void addConsumable(const string& consumable)
{
	temporary_patient.addConsumable(consumable);
}


void addReportId(const string& report_id)
{
	temporary_patient.addReportId(report_id);
}

bool isPatientDataAvailable() {
	if (original_patient.isEmpty()) {
		return false;
	}
	return true;
}

void addNewPatient()
{
    string strInput;
    string verified = "no";
	int intInput;

	do {
		cout << "Enter patient name: ";
		cin >> strInput;
		temporary_patient.setName(strInput);

		cout << "Enter patient gender (Male/Female): ";
		cin >> strInput;
		temporary_patient.setGender(strInput);

		cout << "Enter patient age: ";
		cin >> intInput;
		temporary_patient.setAge(intInput);

		cout << "Enter Procedure name: ";
		cin >> strInput;
		temporary_patient.setProcedureName(strInput);

		cout << "Verified your details (yes/no)? ";
		cin >> verified;
	} while (verified == "no");
    publishable = true;
    serialized_data = temporary_patient.toString();
}


void editName()
{
	string strInput;
	cout << "Enter new Name: ";
	cin >> strInput;
	temporary_patient.setName(strInput);
}

void editAge()
{
	int intInput;
	cout << "Enter new age: ";
	cin >> intInput;
	temporary_patient.setAge(intInput);
}

void editGender()
{
	string strInput;
	cout << "Enter new gender: ";
	cin >> strInput;
	temporary_patient.setGender(strInput);
}

void editProcedure()
{
	string strInput;
	cout << "Enter new procedure name: ";
	cin >> strInput;
	temporary_patient.setProcedureName(strInput);
}


void editAll()
{
	editName();
	editAge();
	editGender();
	editProcedure();
}

void editPatientInfo()
{
	if (!isPatientDataAvailable()) {
		cout << "Sorry.. no patient data is available. Kindly add patient info before editing..." << endl;
		return;
	}

	cout << "The following are the entered patient information: " << endl;
	printPatientInformation();

	displayEditMenu();
	
	int choice = getUserChoice();
	ExecuteEditMenuChoice(choice);
	serialized_data = temporary_patient.toString();
	publishable = true;
}

void printPatientInformation()
{
    cout << "Patient Name: " << original_patient.getName() << endl;
	cout << "Patent Gender: " << original_patient.getGender() << endl;
	cout << "Patient Age: " << original_patient.getAge() << endl;
	cout << "Procedure Name: " << original_patient.getProcedureName() << endl;
	cout << "Consumables: " << original_patient.getConsumables() << endl;
	cout << "ReportIds: " << original_patient.getReportIds() << endl;
}