#pragma once

#include <iostream>

using namespace std;

class Patient 
{
private:
    int id; 
    string name;
    string gender;
    int age;
    string procedureName;
    string consumables;
    string reportIds;
    int busy;

public:
    Patient();
    Patient(const string& Name, const string& Gender, int Age, const string& ProcedureName);

    Patient& operator=(const Patient& p);
    int getId();
    string getName();
    string getGender();
    int getAge();
    string getProcedureName();
    string getConsumables();
    string getReportIds();
    int getBusyStatus();
    void setId(int newId);
    void setName(const string& newName);
    void setGender(const string& newGender);
    void setAge(int newAge);
    void setProcedureName(const string& newProcedureName);
    void setConsumables(const string& newConsumables);
    void setReportIds(const string& newReportIds);
    void setBusyStatus(int newStatus);
    void addConsumable(const string& newConsumable);
    void addReportId(const string& newReportId);
    string toString();
    bool isEmpty();
};
