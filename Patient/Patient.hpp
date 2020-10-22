#pragma once

#include <iostream>

using namespace std;

class Patient 
{
private:
    string name;
    string gender;
    int age;
    string procedureName;
    string consumables;
    string reportIds;
    bool busy;

public:
    Patient() {}
    Patient(const string& Name, const string& Gender, int Age, const string& ProcedureName) 
    : name(Name), gender(Gender), age(Age), procedureName(ProcedureName), busy(false) {}

    Patient& operator=(const Patient& p);
    string getName();
    string getGender();
    int getAge();
    string getProcedureName();
    string getConsumables();
    string getReportIds();
    bool getBusyStatus();
    void setName(const string& newName);
    void setGender(const string& newGender);
    void setAge(int newAge);
    void setProcedureName(const string& newProcedureName);
    void setConsumables(const string& newConsumables);
    void setReportIds(const string& newReportIds);
    void setBusyStatus(bool newStatus);
    void addConsumable(const string& newConsumable);
    void addReportId(const string& newReportId);
    bool isEmpty();
    bool isFree();
    string toString();
};
