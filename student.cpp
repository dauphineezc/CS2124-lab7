#include "course.h"
#include "student.h"
#include "registrar.h"
using namespace std;

namespace BrooklynPoly {
    // Student constructor
    Student::Student(const std::string& name) : name(name) {}

    // Student name getter
    const std::string& Student::getName() const { return name; }

    // bool addCourse to Student's Course vector
    bool Student::addCourse(Course* new_course) {
        bool already_enrolled = false;
        for (std::size_t index = 0; index < courses.size(); ++index) {
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
        for (std::size_t index = 0; index < courses.size(); ++index) {
            if (courses[index] == course) {
                if (index == courses.size() - 1) {
                    courses.pop_back();
                }
                else {
                    for (std::size_t index2 = index; index2 < courses.size() - 1; ++index2) {
                        courses[index2] = courses[index2 + 1];
                    }
                    courses.pop_back();
                    break;
                }
            }
        }
    }

    // output operator for Student
    std::ostream& operator<<(std::ostream& os, const Student& rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0) {
            os << "No Courses";
        }
        else {
            for (std::size_t index = 0; index < rhs.courses.size(); ++index)
                os << rhs.courses[index]->getName() << " ";
        }
        return os;
    }
}