#include "PatientWrapper.hpp"
#include <vector>
#include <ctime>

void addConsumable(const string& consumable)
{
	temporary_patient.addConsumable(consumable);
}


void addReportId(const string& report_id)
{
	temporary_patient.addReportId(report_id);
}

int isPatientFree()
{
	return !original_patient.getBusyStatus();
}

bool isPatientDataAvailable() {
	if (original_patient.isEmpty()) {
		return false;
	}
	return true;
}

string generate_patient_id(const string& name)
{
	srand((unsigned)time(0));
	int num = rand() % 2000;
	return name + to_string(num);
}


PatientInfo getPatientInfo()
{
	string name;
	int age;
	string gender;
	string procedureName;

	PatientInfo p_info;

	cout << "Enter patient name: ";
	cin >> p_info.name;
	
	cout << "Enter patient gender (Male/Female): ";
	cin >> p_info.gender;
	
	cout << "Enter patient age: ";
	cin >> p_info.age;

	cout << "Enter Procedure name: ";
	cin >> p_info.procedureName;
	
	return p_info;
}

void generateAndsetPatientId()
{
	string name = temporary_patient.getName();
	string patient_id = generate_patient_id(name);
	temporary_patient.setId(patient_id);
}

void setPatientInfo(PatientInfo& p_info)
{
	temporary_patient.setName(p_info.name);
	temporary_patient.setAge(p_info.age);
	temporary_patient.setGender(p_info.gender);
	temporary_patient.setProcedureName(p_info.procedureName);
	generateAndsetPatientId();
}

void addNewPatient()
{
    string strInput;
    string verified = "no";
	int intInput;
	PatientInfo p_info;
	do {
		p_info = getPatientInfo();
		cout << "Verified your details (yes/no)? ";
		cin >> verified;
	} while (verified == "no");

	setPatientInfo(p_info);

    serialized_data = temporary_patient.toString();
	publishable = true;
}

void setName(const string& name)
{
	temporary_patient.setName(name);
}

void setAge(int intInput)
{
	temporary_patient.setAge(intInput);
}

void setGender(const string& strInput)
{
	temporary_patient.setGender(strInput);
}

void setProcedureName(const string& strInput)
{
	temporary_patient.setProcedureName(strInput);
}

void editName()
{
	string strInput;
	cout << "Enter new Name: ";
	cin >> strInput;
	setName(strInput);
}

void editAge()
{
	int intInput;
	cout << "Enter new age: ";
	cin >> intInput;
	setAge(intInput);
}

void editGender()
{
	string strInput;
	cout << "Enter new gender: ";
	cin >> strInput;
	setGender(strInput);	
}

void editProcedure()
{
	string strInput;
	cout << "Enter new procedure name: ";
	cin >> strInput;
	setProcedureName(strInput);
}


void editAll()
{
	editName();
	editAge();
	editGender();
	editProcedure();
}

void setAndPublishPatientBusy()
{
	temporary_patient.setBusyStatus(1);
	serialized_data = temporary_patient.toString();
	publishable = true;
	PublishToSynchronize();
}

void unsetPatientBusyStatus()
{
	temporary_patient.setBusyStatus(0);
}

void editPatientInfo()
{
	if (!isPatientDataAvailable()) {
		cout << "Sorry.. no patient data is available. Kindly add patient info before editing..." << endl;
		return;
	}

	if(!isPatientFree()) {
		cout << "The patient data is being used by some other device. Try again after sometime..." << endl;
		return;
	}


	setAndPublishPatientBusy();


	cout << "The following are the entered patient information: " << endl;
	printPatientInformation();

	displayEditMenu();
	
	int choice = getUserChoice();
	ExecuteEditMenuChoice(choice);

	unsetPatientBusyStatus();
	
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