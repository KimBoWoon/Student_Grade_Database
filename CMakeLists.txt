cmake_minimum_required(VERSION 3.3)
project(Student_Grade_Database)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    StudentGradeDatabase/Student_Grade_Database/Student_Grade_Database.c
    StudentGradeDatabase/Student_Grade_Database/Student_Grade_Database.h)

add_executable(Student_Grade_Database ${SOURCE_FILES})