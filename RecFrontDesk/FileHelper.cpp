//-----------------------------------------------------------------------------
// Name: Jonathan Wolfe
// Email: jawhf4@mail.umkc.edu
// Due: 3/31/19
// Project: Program 4 - Rec Center Desk
// Class: CS 201
//-----------------------------------------------------------------------------
#include "FileHelper.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

int GetStudentCount(std::ifstream& inFS, const std::string fileName)
{
    int studentCount = 0;
    int id, items; // Temp variables
    std::string firstName, lastName; // Temp variables

    std::cout << "Counting Students...\n";

    while (!inFS.eof())
    {
        inFS >> id >> firstName >> lastName >> items;

        // Files that do not conform to the expected format should not be read
        // Attempting to move on to the next student may create unexpected results
        if (inFS.fail())
            throw std::runtime_error("Cannot read file " + fileName);

        // At this point, the data is for a student
        ++studentCount;

        // Need to skip through the list of checkedout items since it isnt needed at this point
        for (int i = 0; i < (items + 1); ++i)
            inFS.ignore(256, '\n');
    }

    inFS.clear();
    inFS.seekg(0, inFS.beg);

    return studentCount;
}

int ReadStudentFile(Student* &students, const std::string fileName)
{
    std::ifstream inFS;

    std::cout << "Reading file: " << fileName << '\n';

    inFS.open(fileName);

    if (inFS.fail())
        throw std::runtime_error("Cannot open file " + fileName);

    // Need to know the amount of students in the file to
    // create the dynamic array
    int studentCount = GetStudentCount(inFS, fileName);

    students = new Student[studentCount];

    // Keep track of the student place in the array to
    // create new entries to the array
    int studentIndex = 0;
    while (!inFS.eof())
    {
        inFS >> students[studentIndex];

        // Not being able to read in a student may cause unexpected results
        if (inFS.fail())
            throw std::runtime_error("Cannot read file " + fileName);
        
        ++studentIndex;
    }

    inFS.close();

    return studentCount;
}

void ReadCheckOuts(Student* &students, const int& studentCount, const std::string fileName)
{
    std::ifstream inFS;

    std::cout << "Reading file: " << fileName << '\n';

    inFS.open(fileName);

    if (inFS.fail())
        throw std::runtime_error("Cannot open file " + fileName);

    while (!inFS.eof())
    {
        int studentID; // Temp variable
        std::string item; // Temp variable

        inFS >> studentID >> item;

        // Since entries are always separated by a newline,
        // skipping to the next line is acceptable
        if (inFS.fail())
        {
            // Move stream to the next entry
            inFS.clear();
            inFS.ignore(256, '\n');
            continue;
        }
        
        // Keep track of success to handle items without a proper student
        bool foundStudent = false;
        for (int i = 0; i < studentCount; ++i)
        {
            if (students[i] == studentID)
            {
                //if (!students[i].CheckOut(item))
                //    std::cout << "The item " << item << " has already been checked out by " << studentID << '\n';
                Student tempStudent = students[i];
                try
                {
                    students[i] = tempStudent + item; // + operator overload
                }
                catch (std::runtime_error e)
                {
                    std::cout << e.what();
                }

                /*bool success = students[i] += item; // += operator overload

                if(!success)
                    std::cout << "The item " << item << " has already been checked out by " << studentID << '\n';
                */

                foundStudent = true;
                break;
            }

        }

        if (!foundStudent)
            std::cout << "Student ID: " << studentID << " was not found in the student list for item checkout\n";
    }

    inFS.close();
}

void ReadCheckIns(Student* &students, const int& studentCount, const std::string fileName)
{
    std::ifstream inFS;

    std::cout << "Reading file: " << fileName << '\n';

    inFS.open(fileName);

    if (inFS.fail())
        throw std::runtime_error("Unable to open File " + fileName);

    while (!inFS.eof())
    {
        std::string item;

        // Since the item is a string, there should never be an error in reading
        inFS >> item;
        
        // Keep track of checked in items that are not on record as checked out
        bool foundItem = false;
        for (int i = 0; i < studentCount; ++i)
        {
            if (students[i].CheckIn(item))
            {
                foundItem = true;
                break;
            }
        }

        // Warn of checked in items that were not checked out
        if (!foundItem)
            std::cout << "Unable to find item " << item  << "\n";
    }

    inFS.close();
}

void SaveUpdatedStudentList(Student* &students, const int& studentCount, const std::string fileName)
{
    std::ofstream outFS;

    std::cout << "Saving to file: " << fileName << '\n';

    outFS.open(fileName);

    if (outFS.fail())
        throw std::runtime_error("Unable to create File " + fileName);

    // Record student info to fileName file
    for (int i = 0; i < studentCount; ++i)
        outFS << students[i];

    outFS.close();
}
