//-----------------------------------------------------------------------------
// Name: Jonathan Wolfe
// Email: jawhf4@mail.umkc.edu
// Due: 3/31/19
// Project: Program 4 - Rec Center Desk
// Class: CS 201
//-----------------------------------------------------------------------------
#pragma once
#include "Student.h"
#include <fstream>
#include <string>

// Returns the count of the students from the inFS file stream
// 
// inFS is the file stream for Students.txt with the position 
// at the start and no flags and leaves it in the same condition
// fileName is the name of the file to read
// 
// Throws a runtime error if the file cannot be read in the expected manner
int GetStudentCount(std::ifstream& inFS, const std::string fileName);

// Reads the contents of the file fileName and copies the info to the and
// created students array returns the size of the created array
//
// The file should be formatted with id, first name, last name, checked 
// out items count and list of checked out items separated by white spaces
//
// students is an array of Student that should be a nullptr
// fileName of the file to be read
//
// Throws a runtime error if the file cannot be read in the expected manner
int ReadStudentFile(Student* &students, const std::string fileName);

// Reads the contents of the file fileName to the array students by checking out items
// within the array if the student matches the associated student with the item
//
// The file must be in the format of student id and checked out item separated by 
// spaces and each entry on a new line
//
// students is an array of Student instances to be altered
// studentCount is the size of the students array
// fileName is the name of the file of checked out items
//
// Warns if a checked out item has already been checked out by the student
// Warns if the associated student with a checked out item cannot be found in the array
// Throws runtime error if the file is not found or cannot be opened
void ReadCheckOuts(Student* &students, const int& studentCount, const std::string fileName);

// Reads the contents of the file fileName to the array students by checking in items
// within the array for the first student in the array with the item checked out
//
// The file must be in the format of one item per line
//
// students is an array of Student instances to be altered
// studentCount is the size of the students array
// fileName is the name of the file of checked in items
//
// Throws runtime error if the file is not found or cannot be opened
void ReadCheckIns(Student* &students, const int& studentCount, const std::string fileName);

// Copies the info from students array to the fileName file
// 
// students is an array of Student instances
// studentCount is the size of the students array
// fileName is the name of the file to create/override
// 
// Throws a runtime error if the file cannot be created/overridden
void SaveUpdatedStudentList(Student* &students, const int& studentCount, const std::string fileName);