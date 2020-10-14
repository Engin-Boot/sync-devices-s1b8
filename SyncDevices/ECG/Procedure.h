#pragma once
#include <iostream>
#include <string>
#include <signal.h>
#include <Windows.h>
#include <ctime>

using namespace std;

extern bool isPatientDataAvailable();
extern bool isPatientFree();
extern void publishAndSetPatientBusyStatus(bool);
extern void printPatientInformation();
extern void addConsumable(string);
extern void addReportId(string);

int randomNoGeneration();
void procedure();
void startProcedure();