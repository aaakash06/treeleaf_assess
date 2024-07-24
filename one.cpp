#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std; 

struct Student {
    int id;
    string name;
    string date_birth;
    int roll_no;
    string department;
    string address;
    int age;
};

tm parseDate(const string& date) {
    tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    return tm;
}

int calculateAge(const string& date_birth) {
    tm birth = parseDate(date_birth);
    time_t now = time(nullptr);
    tm* now_tm = localtime(&now);
    int age = now_tm->tm_year + 1900 - (birth.tm_year + 1900);
    if ((birth.tm_mon > now_tm->tm_mon) || 
        (birth.tm_mon == now_tm->tm_mon && birth.tm_mday > now_tm->tm_mday)) {
        age--;
    }
    return age;
}

vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        istringstream ss(line);
        string token;
        Student student;

        getline(ss, token, ',');
        student.id = stoi(token);

        getline(ss, student.name, ',');

        getline(ss, student.date_birth, ',');
        student.age = calculateAge(student.date_birth);

        getline(ss, token, ',');
        student.roll_no = stoi(token);

        getline(ss, student.department, ',');

        getline(ss, student.address, ',');

        students.push_back(student);
    }
    return students;
}

void writeCSV(const string& filename, const vector<Student>& students) {
    ofstream file(filename);
    file << "id,name,date_birth,roll_no,department,address,age\n";
    for (const auto& student : students) {
        file << student.id << "," << student.name << "," << student.date_birth << ","
             << student.roll_no << "," << student.department << "," << student.address << ","
             << student.age << "\n";
    }
}

int main() {
    vector<Student> students = readCSV("students.csv");

    // Sort by name
    vector<Student> students_sorted_by_name = students;
    sort(students_sorted_by_name.begin(), students_sorted_by_name.end(), [](const Student& a, const Student& b) {
        return a.name < b.name;
    });
    writeCSV("students_sorted_by_name.csv", students_sorted_by_name);

    // Sort by age
    vector<Student> students_sorted_by_age = students;
    sort(students_sorted_by_age.begin(), students_sorted_by_age.end(), [](const Student& a, const Student& b) {
        return a.age < b.age;
    });
    writeCSV("students_sorted_by_age.csv", students_sorted_by_age);

    return 0;
}
