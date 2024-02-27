#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
    class Student; 
    class Course; 
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        bool addCourse(const std::string& course_name);
        bool addStudent(const std::string& student_name);
        bool enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();

    private:
        std::size_t findStudent(const std::string& student_name) const;
        std::size_t findCourse(const std::string& course_name) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };  
}

#endif