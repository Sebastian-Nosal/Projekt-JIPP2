#include "handler.h"
#include <string>

Handler::Handler() {
}
 
void Handler::add(std::string firstname,std::string lastname, std::string average, std::string semester) {
    int sem = std::stoi(semester);
    double avg1 = std::stod(average);
    Student s(firstname,lastname,avg1,sem);
    this->data.pushBack(s);
}

Student* Handler::list() {
    int size = this->data.size();
    Student* students = new Student[size];
    for(int i=0;i<size;i++) {
        students[i] = this->data[i];
    }
    return students;
}

int Handler::getSize() {
    return this->data.size();
}