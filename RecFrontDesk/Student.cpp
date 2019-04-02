//-----------------------------------------------------------------------------
// Name: Jonathan Wolfe
// Email: jawhf4@mail.umkc.edu
// Due: 3/31/19
// Project: Program 4 - Rec Center Desk
// Class: CS 201
//-----------------------------------------------------------------------------
#include "Student.h"
#include <iostream>
#include <stdexcept>

Student::Student()
{
    studentID = 0;
    numItemsCheckedOut = 0;
    arraySize = 0;
    firstName = "";
    lastName = "";
    itemsCheckedOut = nullptr; // Must initialize to nullptr before it can be used
}

Student::Student(const unsigned int studentID, const std::string firstName, const std::string lastName)
{
    this->studentID = 0;
    this->numItemsCheckedOut = 0;
    this->arraySize = 0;
    this->studentID = studentID;
    this->firstName = firstName;
    this->lastName = lastName;
}

Student::Student(const Student & student)
{
    numItemsCheckedOut = student.numItemsCheckedOut;
    arraySize = student.arraySize;
    studentID = student.studentID;
    firstName = student.firstName;
    lastName = student.lastName;
    itemsCheckedOut = nullptr;

    if (arraySize > 0)
    {
        itemsCheckedOut = new std::string[arraySize];

        for (int i = 0; i < arraySize; ++i)
            itemsCheckedOut[i] = student.itemsCheckedOut[i];
    }
}

Student::~Student()
{
    Clear();
}

bool Student::SetID(const unsigned int& ID)
{
    if (ID >= 10000 && ID <= 99999) // Verify the ID is a 5 digit number
    {
        studentID = ID;
        return true;
    }
    else
    {
        std::cout << "Student id: " << ID << " is out of range 10000 and 99999" << std::endl;
        return false;
    }
}

bool Student::CheckOut(const std::string& item)
{
    if (HasCheckedOut(item))
        return false;

    if (!itemsCheckedOut) // It will be a nullptr if it is empty
    {
        arraySize = 5; // Instructions say to make the initial size 5
        itemsCheckedOut = new std::string[arraySize];
    }
    else
    {
        // No need to check earlier because the array must exist 
        // for it to be checked and this is the first point where
        // it is established that already exists

        // Items already checked out should not checked out again
        if (HasCheckedOut(item))
            return false;

        // Once the array is full, expand it by reallocating a new memory set
        if (numItemsCheckedOut == arraySize)
        {
            // Doubling the array size should reduce the amount of times it is
            // expanded which should be more efficient
            std::string *tempArray = new std::string[arraySize * 2];

            for (int i = 0; i < arraySize; ++i)
                tempArray[i] = itemsCheckedOut[i];

            delete[] itemsCheckedOut;
            itemsCheckedOut = tempArray;
            arraySize *= 2;
        }
    }

    // Add the item to the end of the list
    itemsCheckedOut[numItemsCheckedOut] = item;
    ++numItemsCheckedOut;

    return true;
}

bool Student::CheckIn(const std::string& item)
{
    for (int i = 0; i < numItemsCheckedOut; ++i)
    {
        if (itemsCheckedOut[i] == item)
        {
            // Shifting each item down one from the found item
            // and setting the last entry to an empty string
            // makes handling the output easier
            for (i; i < numItemsCheckedOut - 1; ++i)
                itemsCheckedOut[i] = itemsCheckedOut[i + 1];

            itemsCheckedOut[i] = "";
            --numItemsCheckedOut;

            // Deleting the empty checkout array provides
            // better memory utilization
            if (numItemsCheckedOut == 0)
            {
                delete[] itemsCheckedOut;
                itemsCheckedOut = nullptr;
                arraySize = 0;
            }

            return true;
        }
    }

    return false;
}

bool Student::HasCheckedOut(const std::string& item)
{
    for (int i = 0; i < numItemsCheckedOut; ++i)
    {
        if (itemsCheckedOut[i] == item)
            return true;
    }

    return false;
}

void Student::Clear()
{
    studentID = 0;
    numItemsCheckedOut = 0;
    arraySize = 0;
    firstName = "";
    lastName = "";
    delete[] itemsCheckedOut;
    itemsCheckedOut = nullptr;
}

Student Student::operator+(const std::string& item)
{
    Student student(*this);

    // Handle items that cannot be checked out
    if (!student.CheckOut(item))
    {
        throw std::runtime_error("The item " + item + " has already been checked out by "
            + std::to_string(student.studentID) + '\n');
    }

    return student;
}

void Student::operator=(const Student& student)
{
    studentID = 0;
    numItemsCheckedOut = 0;
    arraySize = 0;
    studentID = student.studentID;
    firstName = student.firstName;
    lastName = student.lastName;

    numItemsCheckedOut = student.numItemsCheckedOut;
    arraySize = student.arraySize;

    if (arraySize > 0)
    {
        itemsCheckedOut = new std::string[arraySize];

        for (int i = 0; i < arraySize; ++i)
            itemsCheckedOut[i] = student.itemsCheckedOut[i];
    }
}

bool Student::operator+=(const std::string& item)
{
    return CheckOut(item);
}

bool Student::operator==(const int& studentID)
{
    return this->studentID == studentID;
}

bool Student::operator!=(const int& studentID)
{
    return this->studentID != studentID;
}

std::istream& operator>>(std::istream& in, Student& student)
{
    student.Clear();

    // Need temp variables to check the id and if it is valid
    // then remaining values can be set
    int id, items;
    std::string firstName, lastName;

    in >> id >> firstName >> lastName >> items;

    // Return a failed stream and let the user determine what to do
    if (in.fail())
        return in;
    
    // Don't add a student with invalid id, move on to the next student
    if (!student.SetID(id))
    {
        std::cout << "Omitting student id: " << id << std::endl;

        // Skip list of checked out items
        for (int i = 0; i < items; ++i)
            in.ignore(256, '\n');

        return in;
    }

    student.firstName = firstName;
    student.lastName = lastName;

    for (int i = 0; i < items; ++i)
    {
        std::string item;
        in >> item;
        student.CheckOut(item);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& student)
{
    out << student.studentID << " " << student.firstName << " " << student.lastName << '\n';
    out << student.numItemsCheckedOut << '\n';

    for (int i = 0; i < student.numItemsCheckedOut; ++i)
    {
        out << student.itemsCheckedOut[i] << ' ';
    }

    // Need to end the line of checked out items
    if (student.numItemsCheckedOut > 0)
        out << '\n';

    return out;
}