#include "handler.h"
#include <string>
#include <fstream>

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
    std::ofstream file("students.txt");
    if (!file.is_open()) return false;

    for (unsigned i = 0; i < data.size(); ++i) {
        const Student& s = data[i];
        file << s.getId() << ","
             << s.getFirstName() << ","
             << s.getLastName() << ","
             << s.getAverage() << ","
             << s.getSemester() << "\n";
    }
    return true;
}

bool Handler::loadFromFile() {
    std::ifstream file("students.txt");
    if (!file.is_open()) return false;

    data.clear();
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string token;
        pos = line.find(',');
        token = line.substr(0, pos);
        int id = std::stoi(token);
        line.erase(0, pos + 1);
        pos = line.find(',');
        std::string fname = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        std::string lname = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        token = line.substr(0, pos);
        double avg = std::stod(token);
        line.erase(0, pos + 1);
        int sem = std::stoi(line);
        Student s(id, fname, lname, avg, sem);
        data.pushBack(s);
    }

    return true;
}

bool Handler::saveToBinary() {
    std::ofstream file("students.bin", std::ios::binary);
    if (!file.is_open()) return false;

    int count = data.size();
    file.write(reinterpret_cast<char*>(&count), sizeof(count));

    for (unsigned i = 0; i < data.size(); ++i) {
        const Student& s = data[i];

        int id = s.getId();
        double avg = s.getAverage();
        int sem = s.getSemester();

        std::string fname = s.getFirstName();
        std::string lname = s.getLastName();

        int fnameLen = fname.length();
        int lnameLen = lname.length();

        file.write(reinterpret_cast<char*>(&id), sizeof(id));
        file.write(reinterpret_cast<char*>(&avg), sizeof(avg));
        file.write(reinterpret_cast<char*>(&sem), sizeof(sem));

        file.write(reinterpret_cast<char*>(&fnameLen), sizeof(fnameLen));
        file.write(fname.c_str(), fnameLen);

        file.write(reinterpret_cast<char*>(&lnameLen), sizeof(lnameLen));
        file.write(lname.c_str(), lnameLen);
    }

    return true;
}

bool Handler::loadFromBinary() {
    std::ifstream file("students.bin", std::ios::binary);
    if (!file.is_open()) return false;

    data.clear();
    int count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; ++i) {
        int id, sem;
        double avg;
        int fnameLen, lnameLen;

        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        file.read(reinterpret_cast<char*>(&avg), sizeof(avg));
        file.read(reinterpret_cast<char*>(&sem), sizeof(sem));

        file.read(reinterpret_cast<char*>(&fnameLen), sizeof(fnameLen));
        std::string fname(fnameLen, ' ');
        file.read(&fname[0], fnameLen);

        file.read(reinterpret_cast<char*>(&lnameLen), sizeof(lnameLen));
        std::string lname(lnameLen, ' ');
        file.read(&lname[0], lnameLen);

        Student s(id, fname, lname, avg, sem);
        data.pushBack(s);
    }

    return true;
}

double Handler::getAverageOfSemester(int semester) {
    double sum =0;
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

Student Handler::getByIdx(int idx) {
    if(idx<0||idx>=this->data.size()) {
        Student s(-1,"Index Out Of Range","Noone",0,0);
        return s;
    }
    else return this->data[idx];
}

Student* Handler::getFromNtoK(int n, int k,int& output_length) {
    int start, end, size;
    if(n<0 || k<0 || n>=this->data.size() || k>=this->data.size()) {
        Student* s = new Student[1];
        s[0] = Student(-1,"Index Out Of Range","Noone",0,0);
        return s;
    }
    else if(n<=k) {
        start = n;
        end = k;
    }
    else {
        start = k;
        end = n;
    }
    int j=0;
    output_length = end - start + 1;
    Student* s = new Student[output_length];
    for(int i=start;i<=end;i++) {
        s[j] = this->data[i];
        j++;
    }
    return s;

}

double Handler::getOverallAverage() {
    double sum;
    for(int i=0;i<this->data.size();i++) {
        sum+=this->data[i].getAverage();
    }
    return sum/this->data.size();
}