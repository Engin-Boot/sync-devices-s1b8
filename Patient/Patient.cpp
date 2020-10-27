#include "Patient.hpp"

    int id;
    string name;
    string gender;
    int age;
    string procedureName;
    string consumables;
    string reportIds;
    int busy;

Patient :: Patient()
    :id(0), name(""), gender(""), age(0), procedureName(""), consumables(""), reportIds(""), busy(0) {}

Patient::Patient(const string& Name, const string& Gender, int Age, const string& ProcedureName) 
    : id(0),name(Name), gender(Gender), age(Age), procedureName(ProcedureName), consumables(""), reportIds(""),busy(0) {}

Patient& Patient::operator=(const Patient& p) {
    this->id = p.id;
    this->name = p.name;
    this->gender = p.gender;
    this->age = p.age;
    this->procedureName = p.procedureName;
    this->consumables = p.consumables;
    this->reportIds = p.reportIds;
    this->busy = p.busy;
    return *this;
}

int Patient::getId(){
    return id;
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

int Patient :: getBusyStatus(){
    return busy;
}

void Patient :: setId(int newId){
    id = newId;
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

void Patient::setBusyStatus(int newStatus)
{
    busy = newStatus;
}

string Patient::toString() {
    string result = to_string(id) + ";" + name + ";" + gender + ";" + to_string(age) + ";" + procedureName + ";" + consumables + ";" + reportIds + ";" + to_string(busy);
    return result;
}