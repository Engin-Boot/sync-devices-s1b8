#pragma once

#include <iostream>

using namespace std;

class Patient {
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
    Patient(const string& Name, const string& Gender, int Age, const string& ProcedureName) : name(Name), gender(Gender), age(Age), procedureName(ProcedureName), busy(false) {}

    Patient& operator=(const Patient& p) {
        this->name = p.name;
        this->gender = p.gender;
        this->age = p.age;
        this->procedureName = p.procedureName;
        this->consumables = p.consumables;
        this->reportIds = p.reportIds;
        this->busy = p.busy;
        return *this;
    }

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    int getAge() {
        return age;
    }

    string getProcedureName() {
        return procedureName;
    }

    string getConsumables() {
        return consumables;
    }

    string getReportIds() {
        return reportIds;
    }

    bool getBusyStatus() {
        return busy;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setGender(const string& newGender) {
        gender = newGender;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    void setProcedureName(const string& newProcedureName) {
        procedureName = newProcedureName;
    }

    void setConsumables(const string& newConsumables) {
        consumables = newConsumables;
    }

    void setReportIds(const string& newReportIds) {
        reportIds = newReportIds;
    }

    void setBusyStatus(bool newStatus) {
        busy = newStatus;
    }

    void addConsumable(const string& newConsumable) {
        if (consumables.empty()) {
            consumables = newConsumable;
        }
        else {
            consumables = consumables + "," + newConsumable;
        }
    }

    void addReportId(const string& newReportId) {
        if (reportIds.empty()) {
            reportIds = newReportId;
        }
        else {
            reportIds = reportIds + "," + newReportId;
        }
    }

    bool isEmpty() {
        if (name.empty()) {
            return true;
        }
        return false;
    }

    bool isFree() {
        if (busy) {
            return false;
        }
        return true;
    }

    string toString() {
        string result = name + ";" + gender + ";" + to_string(age) + ";" + procedureName + ";" + consumables + ";" + reportIds + ";" + to_string(busy);
        return result;
    }
};