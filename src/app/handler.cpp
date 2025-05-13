#include "handler.h"
#include <string>

Handler::Handler() {
}
 
bool Handler::add(std::string firstname,std::string lastname, std::string average, std::string semester) {
    int sem;
    double avg1; 
    try {
        sem = std::stoi(semester);
        avg1 = std::stod(average);
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }
    Student s(firstname,lastname,avg1,sem);
    this->data.pushBack(s);
    return true;
}

Student* Handler::list() {
    int size = this->data.size();
    Student* students = new Student[size];
    for(int i=0;i<size;i++) {
        students[i] = this->data[i];
    }
    return students;
}

bool Handler::remove(std::string id) {
    int int_id;
    try {
        int_id = stoi(id);
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }
  
    int size = this->data.size();
    bool flag = false;
    if(size<=0) return false;
    for(int i=0; i<size; i++) {
        if(this->data[i].getId() == int_id) {
            this->data.erase(i);
            flag = true;
            break;
        } 
    }
    return flag;
}

bool Handler::update(std::string searchId,std::string firstname,std::string lastname, std::string average, std::string semester) {
    int sem,id;
    double avg1; 
    try {
        id = std::stoi(searchId);
        sem = std::stoi(semester);
        avg1 = std::stod(average);
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    catch (const std::out_of_range&) {
        return false;
    }

    Student s(id,firstname,lastname,avg1,sem);
    int size = this->data.size();
    bool flag = true;
    for(int i=0; i<size; i++) {
        if(this->data[i].getId() == id) {
            this->data.erase(i);
            this->data.insert(i,s);
            flag = false;
            break;
        } 
    }
    if(flag) this->data.pushBack(s);
    return true;
}

int Handler::getSize() {
    return this->data.size();
}

Student* Handler::listByCriteria(std::function<bool(const Student&)> predicate, int& outSize) {
    std::vector<Student> matches;
    for (int i = 0; i < this->data.size(); ++i) {
        if (predicate(this->data[i])) {
            matches.push_back(this->data[i]);
        }
    }

    outSize = matches.size();
    if (outSize == 0) return nullptr;

    Student* result = new Student[outSize];
    for (int i = 0; i < outSize; ++i) {
        result[i] = matches[i];
    }

    return result;
}

bool Handler::saveToFile() {
    return true;
}

bool Handler::loadFromFile() {
    return true;
}

bool Handler::saveToBinary() {
    return true;
}

bool Handler::loadFromBinary() {
    return true;
}

double Handler::getAverageOfSemester(int semester) {
    int sum =0;
    int count = 0;
    int size = this->data.size();
    for(int i=0;i<size;i++) {
        if(this->data[i].getSemester()==semester) {
            count++;
            sum+=this->data[i].getAverage();
        }
    }
    if(count==0) return 0;
    return sum/count;
}

Student* Handler::getBestStudents(int& amount) {
    int size = this->data.size();
    double max = 0;
    int count = 0;
    for(int i=0; i<size;i++) {
        if(this->data[i].getAverage()>max){
            max = this->data[i].getAverage();
            count = 1;
        } 
        else if(this->data[i].getAverage() == max) count++;
    }
    
    Student* result = new Student[count];
    int j=0;
    for(int i=0; i<size;i++) {
        if(this->data[i].getAverage() == max) {
            result[j] = this->data[i];
            j++;
        }
    }
    amount = count;
    return result;

} 