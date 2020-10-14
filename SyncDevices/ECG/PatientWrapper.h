#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "inc/Patient.h"

using namespace std;

extern int publish(string topicName, string message);

Patient originalPatientDetails;
Patient temporaryPatientDetails;

void publishPatientDetails();
void publishAndSetPatientName(string newName);
void publishAndSetPatientGender(string newGender);
void publishAndSetPatientAge(int newAge);
void publishAndSetProcedureName(string newProcedureName);
void publishAndSetPatientBusyStatus(bool newStatus);
void addConsumable(string newConsumable);
void addReportId(string newReportId);
bool isPatientDataAvailable();
bool isPatientFree();
void printPatientInformation();
bool checkPatientBusyness();
bool userConfirmationPage();
void addNewPatient();
void checkAndPromptforName(char choice);
void checkAndPromptforAge(char choice);
void checkAndPromptforGender(char choice);
void checkAndPromptforProcedureName(char choice);
void editPatientInfo();
void setPatientDetails(string details);