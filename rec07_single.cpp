// Zoe Dauphinee, rec 07, registrar; course; and student in a single file.

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* new_student);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* new_course);

    // Student method needed by Course
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& course_name);
    bool addStudent(const string& student_name);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string& student_name) const;
    size_t findCourse(const string& course_name) const;

    vector<Course*> courses;
    vector<Student*> students;
};


int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}


/* 
methods for Course
*/
// Course constructor
Course::Course(const string& courseName) : name(courseName) {}

// Course name getter
const string& Course::getName() const { return name; }

// bool addStudent to Course
bool Course::addStudent(Student* new_student) {
    bool already_enrolled = false;
    for (size_t index = 0; index < students.size(); ++index) {
        if (students[index] == new_student) {
            already_enrolled = true;
            return already_enrolled;
        }
    }
    students.push_back(new_student);
    return already_enrolled;
}

// void removesStudentsFromCourse
void Course::removeStudentsFromCourse() {
    for (size_t index = 0; index < students.size(); ++index) {
        students[index]->removedFromCourse(this);
    }
    while (!students.empty()) {
        students.pop_back();
    }
} 

// output operator for Course
ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if (rhs.students.size() == 0) {
        os << " No Students";
    }
    else {
        for (size_t index = 0; index < rhs.students.size(); ++index)
            os << rhs.students[index]->getName() << " ";
    }
    return os;
}


/* 
methods for Students
*/
// Student constructor
Student::Student(const string& name) : name(name) {}

// Student name getter
const string& Student::getName() const { return name; }

// bool addCourse to Student's Course vector
bool Student::addCourse(Course* new_course) {
    bool already_enrolled = false;
    for (size_t index = 0; index < courses.size(); ++index) {
        if (courses[index] == new_course) {
            already_enrolled = true;
            return already_enrolled;
        }
    }
    courses.push_back(new_course);
    return already_enrolled;
}

// void removedFromCourse
void Student::removedFromCourse(Course* course) {
    for (size_t index = 0; index < courses.size(); ++index) {
        if (courses[index] == course) {
            if (index == courses.size() - 1) {
                courses.pop_back();
            }
            else {
                for (size_t index2 = index; index2 < courses.size() - 1; ++index2) {
                    courses[index2] = courses[index2 + 1];
                }
                courses.pop_back();
                break;
            }
        }
    }
}

// output operator for Student
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() == 0) {
        os << "No Courses";
    }
    else {
        for (size_t index = 0; index < rhs.courses.size(); ++index)
            os << rhs.courses[index]->getName() << " ";
    }
    return os;
}


/* 
methods for Registrar
*/
// Registrar constructor
Registrar::Registrar() {}

// bool addCourse to Registrar
bool Registrar::addCourse(const string& course_name) {
    bool already_exists = false;
    size_t course_index = findCourse(course_name);
    if (course_index != courses.size()) {
        already_exists = true;
        return already_exists;
    }
    courses.push_back(new Course(course_name));
    return already_exists;
}

// bool addStudent to Registrar
bool Registrar::addStudent(const string& student_name) {
    bool already_exists = false;
    size_t student_index = findStudent(student_name);
    if (student_index != students.size()) {
        already_exists = true;
        return already_exists;
    }
    students.push_back(new Student(student_name));
    return already_exists;
}

// bool enrollStudentInCourse
bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    bool successful_enrollment = false;
    size_t student_index = findStudent(studentName);
    size_t course_index = findCourse(courseName);

    if (student_index == students.size()) {
        return successful_enrollment;
    }
    else if (course_index == courses.size()) {
        return successful_enrollment;
    }
    
    successful_enrollment = true;
    Student* specified_student = students[student_index];
    Course* specified_course = courses[course_index];

    specified_student->addCourse(specified_course);
    specified_course->addStudent(specified_student);
    return successful_enrollment;
}

// bool cancelCourse
bool Registrar::cancelCourse(const string& courseName) {
    bool course_canceled = false;
    size_t course_index = findCourse(courseName);
    Course* specified_course = courses[course_index];

    if (course_index == courses.size()) {
        return course_canceled;
    }

    specified_course->removeStudentsFromCourse();
    if (course_index == courses.size() - 1) {
        courses.pop_back();
    }
    else {
        for (size_t index = course_index; index < courses.size() - 1; ++index) {
            courses[index] = courses[index + 1];
        }
        courses.pop_back();
    }
    course_canceled = true;
    return course_canceled;
}

// bool purge
void Registrar::purge() {
    for (size_t index = 0; index < students.size(); ++index) {
        delete students[index];
    }
    students.clear();
    for (size_t index = 0; index < courses.size(); ++index) {
        delete courses[index];
    }
    courses.clear();
}

// size_t findStudent
size_t Registrar::findStudent(const string& student_name) const {
    for (size_t index = 0; index < students.size(); ++index) {
        if (students[index]->getName() == student_name) {
            return index;
        }
    }
    return students.size();
}

// size_t findCourse
size_t Registrar::findCourse(const string& course_name) const {
    for (size_t index = 0; index < courses.size(); ++index) {
        if (courses[index]->getName() == course_name) {
            return index;
        }
    }
    return courses.size();
}

// output operator for Registrar
ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\n";
    os << "Courses:\n";
    if (rhs.courses.size() != 0) {
        for (size_t index = 0; index < rhs.courses.size(); ++index) {
            os << *rhs.courses[index] << endl;
        }
    }

    os << "Students:\n";
    if (rhs.students.size() != 0) {
        for (size_t index = 0; index < rhs.students.size(); ++index) {
            os << *rhs.students[index] << endl;
        }
    }
    return os;
}
