#pragma once
#include "data.h"
#include "SmartArray.h"
#include <iostream>
#include <functional>

class Handler {
    private:
    SmartArray<Student> data;
    public:
    Handler();
    bool add(std::string firstname,
        std::string lastname, 
        std::string average, 
        std::string semester);
    bool remove(std::string id);
    Student* list();
    int getSize();
    bool update(std::string searchId,
        std::string firstname,
        std::string lastname, 
        std::string average, 
        std::string semester);
        Student* listByCriteria(std::function<bool(const Student&)> predicate, int& outSize);
    bool loadFromBinary();
    bool saveToBinary();
    bool loadFromFile();
    bool saveToFile();
    double getAverageOfSemester(int semester);
    Student* getBestStudents(int& amount); 
};