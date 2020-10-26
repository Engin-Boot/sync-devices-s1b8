#pragma once 

#include "../../Patient/Patient.hpp"
#include "MenuCLI.hpp"

#include <iostream>
using namespace std;

extern Patient original_patient;
extern Patient temporary_patient;
extern string serialized_data;
extern bool publishable;

void addConsumable(const string& consumable);
void addReportId(const string& report_id);
void addNewPatient();
void editPatientInfo();
void editName();
void editAge();
void editGender();
void editProcedure();
void editAll();
void startProcedure();
void printPatientInformation();
