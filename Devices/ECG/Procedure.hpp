#include <iostream>
#include <string>
#include <unistd.h>
#include <ctime>

#define PROCEDURE_RUN_TIME 3

#include "../../Patient/Patient.hpp"

using namespace std;

extern bool isPatientDataAvailable();
extern int isPatientFree();
extern void printPatientInformation();
extern void addConsumable(const string& consumable);
extern void addReportId(const string& report_id);
extern void PublishToSynchronize();

extern bool publishable;
extern string serialized_data;
extern Patient temporary_patient;

extern void setAndPublishPatientBusy();
extern void unsetPatientBusyStatus();
