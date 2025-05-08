#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
using namespace std;

// Custom Exceptions
class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(string msg) : UniversitySystemException("Payment Error: " + msg) {}
};

// Abstract Base Class
class Person 
{
public:
    int getId() const { return id; }
protected:
    string name;
    int id;
public:
    Person(string n, int i) : name(n), id(i) {
        if (i <= 0) throw UniversitySystemException("Invalid ID assigned.");
    }
    virtual void displayDetails() = 0;
    virtual ~Person() {}
};

class Professor : public Person {
protected:
    int yearsOfService;
    float baseSalary;
public:
    Professor(string n, int i, int years, float salary) : Person(n, i), yearsOfService(years), baseSalary(salary) {}
    virtual float calculatePayment() = 0;
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string n, int i, int y, float s) : Professor(n, i, y, s) {}
    float calculatePayment() override {
        return baseSalary + (yearsOfService * 1000);
    }
    void displayDetails() override {
        cout << "Assistant Professor: " << name << ", ID: " << id << ", Salary: " << calculatePayment() << endl;
    }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string n, int i, int y, float s) : Professor(n, i, y, s) {}
    float calculatePayment() override {
        return baseSalary + (yearsOfService * 1500);
    }
    void displayDetails() override {
        cout << "Associate Professor: " << name << ", ID: " << id << ", Salary: " << calculatePayment() << endl;
    }
};

class FullProfessor : public Professor {
public:
    FullProfessor(string n, int i, int y, float s) : Professor(n, i, y, s) {}
    float calculatePayment() override {
        return baseSalary + (yearsOfService * 2000);
    }
    void displayDetails() override {
        cout << "Full Professor: " << name << ", ID: " << id << ", Salary: " << calculatePayment() << endl;
    }
};

class Student : public Person {
public:
int getId() const { return id; }
protected:
    float cgpa;
public:
    Student(string n, int i, float c) : Person(n, i), cgpa(c) {
        if (c < 0.0 || c > 10.0) throw UniversitySystemException("Invalid CGPA.");
    }
    virtual void displayDetails() override {
        cout << "Student: " << name << ", ID: " << id << ", CGPA: " << cgpa << endl;
    }
};

class UndergraduateStudent : public Student {
    string major, minor, graduationDate;
public:
    UndergraduateStudent(string n, int i, float c, string maj, string min, string grad)
        : Student(n, i, c), major(maj), minor(min), graduationDate(grad) {}
    void displayDetails() override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor << ", Graduation: " << graduationDate << endl;
    }
};

class GraduateStudent : public Student {
    string researchTopic, thesisTitle;
    Professor* advisor;
public:
    GraduateStudent(string n, int i, float c, string topic, string thesis, Professor* adv)
        : Student(n, i, c), researchTopic(topic), thesisTitle(thesis), advisor(adv) {}

    void displayDetails() override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << ", Thesis: " << thesisTitle << endl;
        cout << "Advisor: "; advisor->displayDetails();
    }
};

class Course {
    string code, title;
    Professor* instructor;
    vector<Student*> enrolled;
    int maxSeats = 3;

public:
    Course(string c, string t, Professor* p) : code(c), title(t), instructor(p) {}

    void enroll(Student* s) {
        if (enrolled.size() >= maxSeats) throw EnrollmentException("Course is full.");
        enrolled.push_back(s);
    }

    void displayCourse() {
        cout << "Course: " << title << " by "; instructor->displayDetails();
        for (Student* s : enrolled) s->displayDetails();
    }
};

class GradeBook {
    map<int, float> grades;
public:
    void addGrade(int studentId, float grade) {
        if (grade < 0.0 || grade > 10.0) throw GradeException("Invalid grade entry.");
        grades[studentId] = grade;
    }

    float calculateAverage() {
        float sum = 0;
        for (auto& pair : grades) sum += pair.second;
        return grades.empty() ? 0 : sum / grades.size();
    }
};

class Department {
    string name;
    vector<Professor*> professors;
public:
    Department(string n) : name(n) {}
    void addProfessor(Professor* p) { professors.push_back(p); }
    void listProfessors() {
        for (Professor* p : professors) p->displayDetails();
    }
};

class UniversitySystem {
    vector<Department> departments;
    vector<Course*> courses;
    vector<Student*> students;

public:
    void addDepartment(Department d) { departments.push_back(d); }
    void addCourse(Course* c) { courses.push_back(c); }
    void addStudent(Student* s) { students.push_back(s); }

    void enrollStudentInCourse(Student* s, Course* c) {
        try {
            c->enroll(s);
        } catch (const EnrollmentException& e) {
            cerr << e.what() << endl;
        }
    }

    void showAll() {
        for (auto c : courses) c->displayCourse();
    }
};

int main() {
    try {
        AssistantProfessor prof1("Dr. Smith", 1, 5, 50000);
        UndergraduateStudent ugs("Alice", 101, 8.5, "CSE", "Math", "2026");

        Course course1("CS101", "Intro to C++", &prof1);
        UniversitySystem uni;

        uni.addCourse(&course1);
        uni.addStudent(&ugs);
        uni.enrollStudentInCourse(&ugs, &course1);

        GradeBook grades;
        grades.addGrade(ugs.getId(), 9.0);

        cout << "Average grade: " << grades.calculateAverage() << endl;

        uni.showAll();

    } catch (const UniversitySystemException& e) {
        cerr << "System Exception: " << e.what() << endl;
    }
    return 0;
}
