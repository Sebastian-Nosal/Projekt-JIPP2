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

public:
    Student();
    Student(int id, std::string fname, std::string lname, double avg, int sem);

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
