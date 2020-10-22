#include "Patient.hpp"

Patient& Patient::operator=(const Patient& p) {
    this->name = p.name;
    this->gender = p.gender;
    this->age = p.age;
    this->procedureName = p.procedureName;
    this->consumables = p.consumables;
    this->reportIds = p.reportIds;
    this->busy = p.busy;
    return *this;
}

string Patient::getName() {
    return name;
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

bool Patient::getBusyStatus() {
    return busy;
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

void Patient::setBusyStatus(bool newStatus) {
    busy = newStatus;
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

bool Patient::isEmpty() {
    if (name.empty()) {
        return true;
    }
    return false;
}

bool Patient::isFree() {
    if (busy) {
        return false;
    }
    return true;
}

string Patient::toString() {
    string result = name + ";" + gender + ";" + to_string(age) + ";" + procedureName + ";" + consumables + ";" + reportIds + ";" + to_string(busy);
    return result;
}