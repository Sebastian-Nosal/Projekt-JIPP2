#include "data.h"

Student::Student(std::string fname,std::string lname, double avg,int sem) {
    this->id = next_id;
    next_id++;
    this->firstname = fname;
    this->lastname = lname;
    this->average = avg;
    this->semester = sem;
}

Student::Student() {
    this->id = next_id;
    next_id++;
    this->firstname = "";
    this->lastname = "";
    this->average = 0.0;
    this->semester = 0;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "ID: " << s.id
       << ", Name: " << s.firstname << " " << s.lastname
       << ", Avg: " << s.average
       << ", Semester: " << s.semester;
    return os;
}

std::string Student::getFirstName() {
    return this->firstname;
}

std::string Student::getLastName() {
    return this->lastname;
}

int Student::getSemester() {
    return this->semester;
}

double Student::getAverage() {
    return this->average;
}

int Student::getId() {
    return this->id;
}