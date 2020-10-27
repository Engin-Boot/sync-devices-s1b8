#pragma once 

#include "../../Patient/Patient.hpp"
#include "MenuCLI.hpp"

#include <iostream>
using namespace std;

struct PatientInfo
{
    string name;
    int age;
    string gender;
    string procedureName;
};

extern Patient original_patient;
extern Patient temporary_patient;
extern string serialized_data;
extern bool publishable;

extern void PublishToSynchronize();
void addConsumable(const string& consumable);
void addReportId(const string& report_id);
void addNewPatient();
void editPatientInfo();
void editName();
void editAge();
void editGender();
void editProcedure();
void editAll();
int isPatientFree();
bool isPatientDataAvailable();
string generate_patient_id(const string& name);
void startProcedure();
void printPatientInformation();
