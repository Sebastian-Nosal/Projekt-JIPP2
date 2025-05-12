#pragma once
#include "data.h"
#include "SmartArray.h"
#include <iostream>

class Handler {
    private:
    SmartArray<Student> data;
    public:
    Handler();
    void add(std::string firstname,
        std::string lastname, 
        std::string average, 
        std::string semester);
    void remove(std::string id);
    

};