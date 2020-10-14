#pragma once

extern void addNewPatient();
extern void editPatientInfo();
extern void startProcedure();
extern void printPatientInformation();

void checkAndExecuteAddPatient(int choice);
void checkAndExecuteEditPatient(int choice);
void checkAndExecuteStartProcedure(int choice);
void checkAndExecuteDisplayPatientData(int choice);
void executeChoice(int choice);
void menuPage();
void mainMenu();