#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void incrementPatientCounter() {
    string currentCounter;
    ifstream patientCountTrackerFile("patientCountTrackerFile.txt");
    if (!patientCountTrackerFile) {
        ofstream patientCountTrackerFile("patientCountTrackerFile.txt");
        patientCountTrackerFile << "1";
        patientCountTrackerFile.close();
    }
    else {
        getline(patientCountTrackerFile, currentCounter);
        patientCountTrackerFile.close();
        int incrementedValue = stoi(currentCounter);
        incrementedValue++;
        fstream temp("patientCountTrackerFile.txt", ios::trunc | ios::out);
        temp << to_string(incrementedValue);
        temp.close();
    }
}