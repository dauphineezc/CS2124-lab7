#include "course.h"
#include "student.h"
#include "registrar.h"

namespace BrooklynPoly {
    // Registrar constructor
    Registrar::Registrar() {}

    // bool addCourse to Registrar
    bool Registrar::addCourse(const std::string& course_name) {
        bool already_exists = false;
        std::size_t course_index = findCourse(course_name);
        if (course_index != courses.size()) {
            already_exists = true;
            return already_exists;
        }
        courses.push_back(new Course(course_name));
        return already_exists;
    }

    // bool addStudent to Registrar
    bool Registrar::addStudent(const std::string& student_name) {
        bool already_exists = false;
        std::size_t student_index = findStudent(student_name);
        if (student_index != students.size()) {
            already_exists = true;
            return already_exists;
        }
        students.push_back(new Student(student_name));
        return already_exists;
    }

    // bool enrollStudentInCourse
    bool Registrar::enrollStudentInCourse(const std::string& studentName, const std::string& courseName) {
        bool successful_enrollment = false;
        std::size_t student_index = findStudent(studentName);
        std::size_t course_index = findCourse(courseName);

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
    bool Registrar::cancelCourse(const std::string& courseName) {
        bool course_canceled = false;
        std::size_t course_index = findCourse(courseName);
        Course* specified_course = courses[course_index];

        if (course_index == courses.size()) {
            return course_canceled;
        }

        specified_course->removeStudentsFromCourse();
        if (course_index == courses.size() - 1) {
            courses.pop_back();
        }
        else {
            for (std::size_t index = course_index; index < courses.size() - 1; ++index) {
                courses[index] = courses[index + 1];
            }
            courses.pop_back();
        }
        course_canceled = true;
        return course_canceled;
    }

    // bool purge
    void Registrar::purge() {
        for (std::size_t index = 0; index < students.size(); ++index) {
            delete students[index];
        }
        students.clear();
        for (std::size_t index = 0; index < courses.size(); ++index) {
            delete courses[index];
        }
        courses.clear();
    }

    // size_t findStudent
    std::size_t Registrar::findStudent(const std::string& student_name) const {
        for (std::size_t index = 0; index < students.size(); ++index) {
            if (students[index]->getName() == student_name) {
                return index;
            }
        }
        return students.size();
    }

    // size_t findCourse
    std::size_t Registrar::findCourse(const std::string& course_name) const {
        for (std::size_t index = 0; index < courses.size(); ++index) {
            if (courses[index]->getName() == course_name) {
                return index;
            }
        }
        return courses.size();
    }

    // output operator for Registrar
    std::ostream& operator<<(std::ostream& os, const Registrar& rhs) {
        os << "Registrar's Report\n";
        os << "Courses:\n";
        if (rhs.courses.size() != 0) {
            for (std::size_t index = 0; index < rhs.courses.size(); ++index) {
                os << *rhs.courses[index] << endl;
            }
        }

        os << "Students:\n";
        if (rhs.students.size() != 0) {
            for (std::size_t index = 0; index < rhs.students.size(); ++index) {
                os << *rhs.students[index] << endl;
            }
        }
        return os;
    }
}