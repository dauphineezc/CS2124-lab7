#include "course.h"
#include "student.h"
#include "registrar.h"
using namespace std;

namespace BrooklynPoly {
    // Course constructor
    Course::Course(const std::string& courseName) : name(courseName) {}

    // Course name getter
    const string& Course::getName() const { return name; }

    // bool addStudent to Course
    bool Course::addStudent(Student* new_student) {
        bool already_enrolled = false;
        for (std::size_t index = 0; index < students.size(); ++index) {
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
        for (std::size_t index = 0; index < students.size(); ++index) {
            students[index]->removedFromCourse(this);
        }
        while (!students.empty()) {
            students.pop_back();
        }
    } 

    // output operator for Course
    std::ostream& operator<<(std::ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() == 0) {
            os << " No Students";
        }
        else {
            for (std::size_t index = 0; index < rhs.students.size(); ++index)
                os << rhs.students[index]->getName() << " ";
        }
        return os;
    }
}