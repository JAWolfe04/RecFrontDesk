//-----------------------------------------------------------------------------
// Name: Jonathan Wolfe
// Email: jawhf4@mail.umkc.edu
// Due: 3/31/19
// Project: Program 4 - Rec Center Desk
// Class: CS 201
//-----------------------------------------------------------------------------
#include "Student.h"
#include "FileHelper.h"
#include <iostream>
#include <stdexcept>

int main()
{
    // Dynamic array of Student type containing all students' data
    // Initialized to nullptr and populated while reading file
    // A vector would be better than a dynamic array but the instuctions
    // indicate a dynamic array must be use
    Student* students = nullptr;

    // Amount of students in the students dynamic array
    // It is important to keep track of the length of a dynamic array
    int studentCount = 0;


    try 
    {
        // All of these functions can throw runtime exceptions
        // No need to explain this part since thats what function 
        // comments are for
        studentCount = ReadStudentFile(students, "Students.txt");

        ReadCheckOuts(students, studentCount, "checkouts.txt");

        ReadCheckIns(students, studentCount, "checkins.txt");

        SaveUpdatedStudentList(students, studentCount, "Updated_Students.txt");
    }
    // Using runtime error handling to avoid doing returns and ifs that would be harder
    // to implement but faster in runtime. Still not a fan of error handling.
    catch (std::runtime_error e)
    {
        std::cout << e.what();
    }

    // Freeing the memory is good practice, even though it is not really needed 
    // since the program is about to end and it would be freed anyway
    delete[] students;

    // Good practice to indicate the end of the program
    return 0;
}