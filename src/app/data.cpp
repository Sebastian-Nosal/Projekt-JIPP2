#include "data.h"

int Student::next_id = 0; 
Student::Student(std::string fname,std::string lname, double avg,int sem) {
    this->id = next_id;
    next_id++;
    this->firstname = fname;
    this->lastname = lname;
    if(avg<2.0) avg=2.0;
    if(avg>5.0) avg=5.0;
    this->average = avg;
    if(sem<1) sem=1;
    if(sem>8) sem=8;
    this->semester = sem;
}

Student::Student(int id,std::string fname, std::string lname, double avg, int sem) {
    this->id = id;
    this->firstname = fname;
    this->lastname = lname;
    if(avg<2.0) avg=2.0;
    if(avg>5.0) avg=5.0;
    this->average = avg;
    if(sem<1) sem=1;
    if(sem>8) sem=8;
    this->semester = sem;
}

Student::Student() {
    this->id = 0;
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

std::string Student::getFirstName() const {
    return this->firstname;
}

std::string Student::getLastName() const {
    return this->lastname;
}

int Student::getSemester() const {
    return this->semester;
}

double Student::getAverage() const {
    return this->average;
}

int Student::getId() const {
    return this->id;
}