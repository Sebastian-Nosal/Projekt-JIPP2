#pragma once
#include <iostream>
#include <string>

class Student {
private:
    int id;
    std::string firstname;
    std::string lastname;
    double average;
    int semester;
    static int next_id;

public:
    Student();
    Student(std::string fname, std::string lname, double avg, int sem);
    std::string getFirstName();
    std::string getLastName();
    int getSemester();
    double getAverage();
    int getId();

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
