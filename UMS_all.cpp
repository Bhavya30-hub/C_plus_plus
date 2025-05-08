//  University Management System

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <limits>

using namespace std;

// Custom Exceptions
class UniSystemError : public exception {
    string err_msg;
public:
    UniSystemError(string msg) : err_msg(std::move(msg)) {}
    const char* what() const noexcept override { return err_msg.c_str(); }
};

class EnrollIssue : public UniSystemError {
public:
    EnrollIssue(string m) : UniSystemError(std::move(m)) {}
};

class GradeProblem : public UniSystemError {
public:
    GradeProblem(string m) : UniSystemError(std::move(m)) {}
};

class PaymentProblem : public UniSystemError {
public:
    PaymentProblem(string m) : UniSystemError(std::move(m)) {}
};

class Person {
protected:
    string name;
    string uniqueID;
    string contactNum;
    int ageYears;

public:
    Person(string n, int age, string id, string contact) {
        setName(n);
        setAge(age);
        setID(id);
        setContact(contact);
    }
    virtual ~Person() = default;

    void setName(const string& n) {
        if (n.empty()) throw UniSystemError("Name cannot be empty!");
        name = n;
    }
    void setAge(int a) {
        if (a <= 0 || a > 120) throw UniSystemError("Invalid age provided.");
        ageYears = a;
    }
    void setID(const string& i) { uniqueID = i; }
    void setContact(const string& c) { contactNum = c; }

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << ageYears << ", ID: " << uniqueID << ", Contact: " << contactNum << endl;
    }
    virtual double calculateFees() const { return 0.0; }
};

class Student : public Person {
protected:
    string programme;
    float currentGPA;
    string admissionDate;
    vector<string> coursesEnrolled;

public:
    Student(string n, int a, string i, string c, string prog, float gpa, string admDate)
        : Person(n, a, i, c), programme(prog), admissionDate(admDate) {
        setGPA(gpa);
    }
    void setGPA(float gpa) {
        if (gpa < 0.0 || gpa > 4.0) throw GradeProblem("GPA should be between 0.0 and 4.0.");
        currentGPA = gpa;
    }
    void displayDetails() const override {
        Person::displayDetails();
        cout << "Programme: " << programme << ", GPA: " << currentGPA << ", Admitted on: " << admissionDate << endl;
    }
};

class UndergradStudent : public Student {
    string majorSubject, minorSubject, expectedGradDate;
public:
    UndergradStudent(string n, int a, string i, string c, string prog, float g, string adm,
                     string major, string minor, string gradDate)
        : Student(n, a, i, c, prog, g, adm), majorSubject(major), minorSubject(minor), expectedGradDate(gradDate) {}
    void displayDetails() const override {
        Student::displayDetails();
        cout << "Major: " << majorSubject << ", Minor (if any): " << minorSubject << ", Expected Graduation: " << expectedGradDate << endl;
    }
};

class GradStudent : public Student {
    string researchArea, guideName, thesisTitle;
public:
    GradStudent(string n, int a, string i, string c, string prog, float g, string adm,
                string research, string guide, string thesis)
        : Student(n, a, i, c, prog, g, adm), researchArea(research), guideName(guide), thesisTitle(thesis) {}
    void displayDetails() const override {
        Student::displayDetails();
        cout << "Research Area: " << researchArea << ", Guide: " << guideName << ", Thesis: " << thesisTitle << endl;
    }
};
class Professor {
    friend class Department;  //  Use with caution
protected:
    string uniqueID;
public:
    string name;
};

class Professor : public Person {
protected:
    string deptName, specializationArea, joiningDate;
public:
    Professor(string n, int a, string i, string c, string dept, string spec, string joinDate)
        : Person(n, a, i, c), deptName(dept), specializationArea(spec), joiningDate(joinDate) {}
    void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << deptName << ", Specialization: " << specializationArea << endl;
    }
};

class AsstProfessor : public Professor {
public:
    AsstProfessor(string n, int a, string i, string c, string d, string s, string j)
        : Professor(n, a, i, c, d, s, j) {}
    double calculateFees() const override { return 50000.0; }
};

class Course {
    string courseCode, courseTitle, description;
    int creditsOffered;
    Professor* instructorInCharge;

public:
    Course(string code, string title, int credits, string desc = "")
        : courseCode(code), courseTitle(title), description(desc), creditsOffered(credits), instructorInCharge(nullptr) {
        if (credits <= 0) throw UniSystemError("Course must have at least 1 credit.");
    }
    void assignInstructor(Professor* p) { instructorInCharge = p; }
    void displayDetails() const {
        cout << "Course Code: " << courseCode << ", Title: " << courseTitle << ", Credits: " << creditsOffered;
        if (instructorInCharge) cout << ", Instructor: " << instructorInCharge->name;
        cout << endl;
    }
};

class Department {
    string deptName, location;
    float annualBudget;
    vector<Professor*> faculty;
    vector<Course> offeredCourses;

public:
    Department(string name, string loc, float budget)
        : deptName(name), location(loc), annualBudget(budget) {}
    void addProfessor(Professor* p) { faculty.push_back(p); }
    void addCourse(const Course& c) { offeredCourses.push_back(c); }
    void displayDetails() const {
        cout << "Department Name: " << deptName << ", Location: " << location << ", Budget: " << annualBudget << endl;
        cout << "Faculty: " << endl;
        for (const auto& prof : faculty) {
            cout << "- " << prof->name << " (" << prof->uniqueID << ")" << endl;
        }
        cout << "Courses Offered: " << endl;
        for (const auto& course : offeredCourses) {
            course.displayDetails();
        }
    }
};

class GradeBook {
    map<string, float> studentMarks;
public:
    void recordMarks(const string& studentID, float marks) {
        if (marks < 0.0 || marks > 100.0) throw GradeProblem("Marks should be between 0 and 100.");
        studentMarks[studentID] = marks;
    }
    float calculateAvgMarks(const string& studentID) const {
        auto it = studentMarks.find(studentID);
        if (it == studentMarks.end()) throw GradeProblem("Student ID not found in grade book.");
        return it->second;
    }
};

class EnrollmentManager {
    map<string, vector<string>> courseWiseEnrollment;
public:
    void enrollStudent(const string& courseCode, const string& studentID) {
        courseWiseEnrollment[courseCode].push_back(studentID);
        cout << "Student " << studentID << " enrolled in course " << courseCode << endl;
    }
    void displayCourseEnrollment(const string& courseCode) const {
        cout << "Students enrolled in " << courseCode << ":" << endl;
        if (auto it = courseWiseEnrollment.find(courseCode); it != courseWiseEnrollment.end()) {
            for (const auto& studentID : it->second) cout << "- " << studentID << endl;
        } else {
            cout << "No students enrolled in this course yet." << endl;
        }
    }
};
// The main University system
class University {
    vector<Department> departmentsList;
    vector<Student*> studentsList;
    vector<Professor*> professorsList;
    vector<Course> coursesList;
    EnrollmentManager enrollmentMgr;
    GradeBook gradeBook;

public:
    void addDepartment(const Department& d) {
        departmentsList.push_back(d);
    }
    void addStudent(Student* s) {
        studentsList.push_back(s);
    }
    void addProfessor(Professor* p) {
        professorsList.push_back(p);
    }
    void addCourse(const Course& c) {
        coursesList.push_back(c);
    }

    void displayAllStudents() {
        cout << "\n--- All Students ---" << endl;
        if (studentsList.empty()) {
            cout << "No students in the system yet." << endl;
            return;
        }
        for (const auto& student : studentsList) {
            student->displayDetails();
            cout << "----------------------" << endl;
        }
    }

    void displayAllProfessors() {
        cout << "\n--- All Professors ---" << endl;
        if (professorsList.empty()) {
            cout << "No professors in the system yet." << endl;
            return;
        }
        for (const auto& professor : professorsList) {
            professor->displayDetails();
            cout << "------------------------" << endl;
        }
    }

    void displayAllCourses() {
        cout << "\n--- All Courses ---" << endl;
        if (coursesList.empty()) {
            cout << "No courses in the system yet." << endl;
            return;
        }
        for (const auto& course : coursesList) {
            course.displayDetails();
            cout << "--------------------" << endl;
        }
    }

    void enrollStudentInCourse(string studentID, string courseCode) {
        enrollmentMgr.enrollStudent(courseCode, studentID);
    }

    void showCourseEnrollment(string courseCode) {
        enrollmentMgr.displayCourseEnrollment(courseCode);
    }

    void recordStudentMarks(string studentID, float marks) {
        gradeBook.recordMarks(studentID, marks);
    }

    void showStudentAverageMarks(string studentID) {
        try {
            cout << "Average Marks for Student " << studentID << ": " << gradeBook.calculateAvgMarks(studentID) << endl;
        } catch (const GradeProblem& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    ~University() {
        for (auto& student : studentsList) {
            delete student;
        }
        for (auto& professor : professorsList) {
            delete professor;
        }
    }
};

// Function to get valid integer input
int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    while (cin.fail()) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> value;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline
    return value;
}

// Function to get valid float input
float getFloatInput(const string& prompt) {
    float value;
    cout << prompt;
    cin >> value;
    while (cin.fail()) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> value;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline
    return value;
}

// Function to get string input
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin >> ws, value); // Read with leading whitespace discarded
    return value;
}

int main() {
    University uni;

    int choice;
    do {
        cout << "\n--- University Management System ---" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. Add New Professor" << endl;
        cout << "3. Add New Course" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Display All Professors" << endl;
        cout << "6. Display All Courses" << endl;
        cout << "7. Enroll Student in Course" << endl;
        cout << "8. Show Course Enrollment" << endl;
        cout << "9. Record Student Marks" << endl;
        cout << "10. Show Student Average Marks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline from previous input

            switch (choice) {
                case 1: {
                    cout << "\n--- Adding New Student ---" << endl;
                    string name = getStringInput("Enter name: ");
                    int age = getIntInput("Enter age: ");
                    string id = getStringInput("Enter ID: ");
                    string contact = getStringInput("Enter contact number: ");
                    string programme = getStringInput("Enter programme: ");
                    float gpa = getFloatInput("Enter GPA: ");
                    string admissionDate = getStringInput("Enter admission date: ");
                    string studentType = getStringInput("Enter student type (undergrad/grad): ");
                    if (studentType == "undergrad") {
                        string major = getStringInput("Enter major subject: ");
                        string minor = getStringInput("Enter minor subject (or type 'none'): ");
                        string gradDate = getStringInput("Enter expected graduation date: ");
                        uni.addStudent(new UndergradStudent(name, age, id, contact, programme, gpa, admissionDate, major, minor, gradDate));
                    } else if (studentType == "grad") {
                        string research = getStringInput("Enter research area: ");
                        string guide = getStringInput("Enter guide's name: ");
                        string thesis = getStringInput("Enter thesis title: ");
                        uni.addStudent(new GradStudent(name, age, id, contact, programme, gpa, admissionDate, research, guide, thesis));
                    } else {
                        cout << "Invalid student type." << endl;
                    }
                    cout << "Student added successfully!" << endl;
                    break;
                }
                case 2: {
                    cout << "\n--- Adding New Professor ---" << endl;
                    string name = getStringInput("Enter name: ");
                    int age = getIntInput("Enter age: ");
                    string id = getStringInput("Enter ID: ");
                    string contact = getStringInput("Enter contact number: ");
                    string dept = getStringInput("Enter department name: ");
                    string specialization = getStringInput("Enter specialization area: ");
                    string joiningDate = getStringInput("Enter joining date: ");
                    uni.addProfessor(new AsstProfessor(name, age, id, contact, dept, specialization, joiningDate));
                    cout << "Professor added successfully!" << endl;
                    break;
                }
                case 3: {
                    cout << "\n--- Adding New Course ---" << endl;
                    string code = getStringInput("Enter course code: ");
                    string title = getStringInput("Enter course title: ");
                    int credits = getIntInput("Enter course credits: ");
                    string description = getStringInput("Enter course description (optional): ");
                    uni.addCourse(Course(code, title, credits, description));
                    cout << "Course added successfully!" << endl;
                    break;
                }
                case 4:
                    uni.displayAllStudents();
                    break;
                case 5:
                    uni.displayAllProfessors();
                    break;
                case 6:
                    uni.displayAllCourses();
                    break;
                case 7: {
                    cout << "\n--- Enroll Student in Course ---" << endl;
                    string studentID = getStringInput("Enter student ID to enroll: ");
                    string courseCode = getStringInput("Enter course code to enroll in: ");
                    uni.enrollStudentInCourse(studentID, courseCode);
                    break;
                    }
                    case 8: {
                    cout << "\n--- Show Course Enrollment ---" << endl;
                    string courseCode = getStringInput("Enter course code to view enrollment: ");
                    uni.showCourseEnrollment(courseCode);
                    break;
                    }
                    case 9: {
                    cout << "\n--- Record Student Marks ---" << endl;
                    string studentID = getStringInput("Enter student ID to record marks for: ");
                    float marks = getFloatInput("Enter marks obtained: ");
uni.recordStudentMarks(studentID, marks);
cout << "Marks recorded successfully!" << endl;
break;
}
case 10: {
cout << "\n--- Show Student Average Marks ---" << endl;
string studentID = getStringInput("Enter student ID to view average marks: ");
uni.showStudentAverageMarks(studentID);
break;
}
case 0:
cout << "Exiting the University Management System. Dhanyawad! 🙏" << endl;
break;
default:
cout << "Invalid choice. Please try again." << endl;
}
} catch (const UniSystemError& e) {
cerr << "Error Encountered: " << e.what() << endl;
}
} while (choice != 0);

return 0;
}