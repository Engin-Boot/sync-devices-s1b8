#include "Patient.hpp"

    string name;
    string gender;
    int age;
    string procedureName;
    string consumables;
    string reportIds;

Patient::Patient()
    : name(""), gender(""), age(0), procedureName(""), consumables(""), reportIds("") {}

Patient::Patient(const string& Name, const string& Gender, int Age, const string& ProcedureName) 
    : name(Name), gender(Gender), age(Age), procedureName(ProcedureName), consumables(""), reportIds("") {}

Patient& Patient::operator=(const Patient& p) {
    this->name = p.name;
    this->gender = p.gender;
    this->age = p.age;
    this->procedureName = p.procedureName;
    this->consumables = p.consumables;
    this->reportIds = p.reportIds;
    return *this;
}

string Patient::getName() {
    return name;
}

bool Patient::isEmpty() {
    if (name.empty()) {
        return true;
    }
    return false;
}

string Patient::getGender() {
    return gender;
}

int Patient::getAge() {
    return age;
}

string Patient::getProcedureName() {
    return procedureName;
}

string Patient::getConsumables() {
    return consumables;
}

string Patient::getReportIds() {
    return reportIds;
}


void Patient::setName(const string& newName) {
    name = newName;
}

void Patient::setGender(const string& newGender) {
    gender = newGender;
}

void Patient::setAge(int newAge) {
    age = newAge;
}

void Patient::setProcedureName(const string& newProcedureName) {
    procedureName = newProcedureName;
}

void Patient::addConsumable(const string& newConsumable) {
    if (consumables.empty()) {
        consumables = newConsumable;
    }
    else {
        consumables = consumables + "," + newConsumable;
    }
}

void Patient::addReportId(const string& newReportId) {
    if (reportIds.empty()) {
        reportIds = newReportId;
    }
    else {
        reportIds = reportIds + "," + newReportId;
    }
}

void Patient::setConsumables(const string& newConsumables)
{
    consumables = newConsumables;
}

void Patient::setReportIds(const string& newReportIds)
{
    reportIds = newReportIds;
}


string Patient::toString() {
    string result = name + ";" + gender + ";" + to_string(age) + ";" + procedureName + ";" + consumables + ";" + reportIds;
    return result;
}