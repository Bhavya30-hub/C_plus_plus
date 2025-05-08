#include <iostream>
#include <string>
using namespace std;

// Base class Person
class Person 
{
public:
    virtual void displayDetails() = 0;  // (virtual function) for polymorphism
    virtual ~Person() {}
};

class Student : public Person
{
private:
    string name;
    int rollNumber;
    float cgpa;
    string courses[10];
    int courseCount;

public:
    Student() : name(""), rollNumber(0), cgpa(0.0), courseCount(0) {}  // Default constructor
    Student(string n, int roll, float c) 
    {
        name = n;
        rollNumber = roll;
        cgpa = (c >= 0.0 && c <= 10.0) ? c : 0.0;
        courseCount = 0;
    }
    string getName() { return name; }
    void setName(string n) { name = n; }

    int getRollNumber() { return rollNumber; }
    void setRollNumber(int roll) { rollNumber = roll; }

    float getCgpa() { return cgpa; }
    void setCgpa(float c) { cgpa = (c >= 0.0 && c <= 10.0) ? c : 0.0; }

    void addCourse(string course) 
    {
        for (int i = 0; i < courseCount; ++i) {
            if (courses[i] == course) return;
        }
        if (courseCount < 10) courses[courseCount++] = course;
    }

    void displayDetails() override 
    {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "CGPA: " << cgpa << endl;
        cout << "Courses: ";
        for (int i = 0; i < courseCount; ++i) cout << courses[i] << " ";
        cout << endl;
    }
};

// Class to manage student grades for a course
class GradeBook
{
private:
    int studentRollNumbers[100];
    float studentGrades[100];
    int count;

public:
    GradeBook() { count = 0; }

    void addGrade(int rollNumber, float grade) {
        if (count < 100) {
            studentRollNumbers[count] = rollNumber;
            studentGrades[count] = grade;
            count++;
        }
    }

    float calculateAverageGrade() {
        if (count == 0) return 0.0;
        float total = 0;
        for (int i = 0; i < count; ++i) {
            total += studentGrades[i];
        }
        return total / count;
    }

    void getHighestGrade() {
        float highest = studentGrades[0];
        for (int i = 1; i < count; ++i) {
            if (studentGrades[i] > highest) {
                highest = studentGrades[i];
            }
        }
        cout << "Highest Grade: " << highest << endl;
    }
};

//  to manage student enrollment in courses
class EnrollmentManager {
private:
    int studentRollNumbers[100];
    string courseCodes[100];
    int enrollCount;

public:
    EnrollmentManager() { enrollCount = 0; }

    void enrollStudent(int rollNumber, string courseCode) {
        if (enrollCount < 100) {
            studentRollNumbers[enrollCount] = rollNumber;
            courseCodes[enrollCount] = courseCode;
            enrollCount++;
        }
    }

    void displayEnrollments() {
        for (int i = 0; i < enrollCount; ++i) {
            cout << "Roll Number: " << studentRollNumbers[i] << " is enrolled in course " << courseCodes[i] << endl;
        }
    }
};

// UniversityManagementSystem class 
class UniversityManagementSystem {
private:
    Student students[100];
    int studentCount;

public:
    UniversityManagementSystem() { studentCount = 0; }

    void addStudent(Student s) {
        if (studentCount < 100) students[studentCount++] = s;
    }

    Student* searchStudent(int roll) {
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].getRollNumber() == roll) return &students[i];
        }
        return nullptr;
    }

    void displayAll() {
        for (int i = 0; i < studentCount; ++i) {
            students[i].displayDetails();
            cout << "-------------------------\n";
        }
    }
};

int main() {
    //  UniversityManagementSystem
    UniversityManagementSystem ums;

    //  Student objects
    Student s1("Alice", 101, 8.5);
    s1.addCourse("Math");
    s1.addCourse("Physics");

    Student s2("Tom", 102, 7.8);
    s2.addCourse("Chemistry");

    ums.addStudent(s1);
    ums.addStudent(s2);

    // Display all students
    ums.displayAll();

    // Search for a student by roll number
    int roll = 101;
    Student* found = ums.searchStudent(roll);
    if (found) {
        cout << "\nDetails of student with roll number " << roll << ":\n";
        found->displayDetails();
    } else {
        cout << "\nStudent not found.\n";
    }

    // GradeBook Example
    GradeBook gradeBook;
    gradeBook.addGrade(101, 8.5);
    gradeBook.addGrade(102, 7.8);
    gradeBook.getHighestGrade();
    cout << "Average Grade: " << gradeBook.calculateAverageGrade() << endl;

    // EnrollmentManager Example
    EnrollmentManager enrollmentManager;
    enrollmentManager.enrollStudent(101, "CS101");
    enrollmentManager.enrollStudent(102, "Math102");
    enrollmentManager.displayEnrollments();

    return 0;
}
