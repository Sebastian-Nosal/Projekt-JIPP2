#include "data.h"

Student::Student(int id,std::string fname,std::string lname, double avg,int sem) {
    this->id = id;
    this->firstname = fname;
    this->lastname = lname;
    this->average = avg;
    this->semester = sem;
}

Student::Student() {
    id = 0;
    firstname = "";
    lastname = "";
    average = 0.0;
    semester = 0;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "ID: " << s.id
       << ", Name: " << s.firstname << " " << s.lastname
       << ", Avg: " << s.average
       << ", Semester: " << s.semester;
    return os;
}