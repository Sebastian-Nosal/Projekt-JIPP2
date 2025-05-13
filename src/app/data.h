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
    Student(int id,std::string fname, std::string lname, double avg, int sem);
    std::string getFirstName() const;
    std::string getLastName() const;
    int getSemester() const;
    double getAverage() const;
    int getId() const;
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
