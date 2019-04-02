//-----------------------------------------------------------------------------
// Name: Jonathan Wolfe
// Email: jawhf4@mail.umkc.edu
// Due: 3/31/19
// Project: Program 4 - Rec Center Desk
// Class: CS 201
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <fstream>

// Manages student item check out information
class Student
{
public:
    //Needed to initialize members to nulls
    Student();

    Student(const unsigned int studentID, const std::string firstName, const std::string lastName);

    // Copy Constructor
    Student(const Student& student);

    // Needed to delete itemsCheckedOut
    ~Student();

    inline const unsigned int GetID() { return studentID; }

    inline const std::string GetFirstName() { return firstName; }

    inline const std::string GetLastName() { return lastName; }

    inline const unsigned int CheckoutCount() { return numItemsCheckedOut; }

    inline void SetFirstName(const std::string firstName) { this->firstName = firstName; }

    inline void SetLastName(const std::string lastName) { this->lastName = lastName; }

    // Sets the student ID to ID as long as the ID is 5 digits long and 
    // returns whether the setting was successful
    //
    // Changed the check to 5 digit check from 1000 and 10,000 due to
    // every student ID being greater than 10,000
    //
    // Returns false and warns of an invalid ID if it is not a 5 digit number
    bool SetID(const unsigned int& ID);

    // Returns whether item was added to the check out item array
    //
    // Adds item to the check out item list for the student if the item is
    // not present
    //
    // item is the item to be added to the checked out item array
    bool CheckOut(const std::string& item);

    // Removes item from the checked out item array and returns whether the
    // removal was successful
    //
    // Deletes the array if there are no longer any items
    //
    // item is the item to be removed from the checked out item array
    bool CheckIn(const std::string& item);

    // Returns whether the item is in the checked out item array
    //
    // item is the item to check for in the array
    bool HasCheckedOut(const std::string& item);

    // Sets all member variables to zero or empty strings and 
    // deletes checked out items array.
    void Clear();

    // Read the student info from the in stream
    //
    // in is the istream to read from to get the student info
    // student is the destination of the student info
    //
    // A failed reading returns a failed stream and does not add the student
    //
    // Invalid student ids stop the student info from being added and
    // moves the stream to the next student
    friend std::istream& operator>>(std::istream& in, Student& student);

    // Prints the student info to the out stream
    //
    // Prints the student's id, first name and last name to a line separated
    // by spaces, then the amount of checked out items to a line and
    // finally each checked out item to a line separated by spaces to out stream.
    //
    // out is ostream to print onto the student info
    // student is the source of the info
    friend std::ostream& operator<<(std::ostream& out, const Student& student);

    // Checks out the item to the student
    //
    // item is the item that will be checked out
    //
    // Throws runtime error if the item could not be checked out
    Student operator+(const std::string& item);

    // Assigns the student info from student to this instance
    void operator=(const Student& student);

    // Checks out the item to the student and returns if the checkout was successful
    //
    // item is the item that will be checked out
    bool operator+=(const std::string& item);

    // Compares the student instance ID to the studentID
    bool operator==(const int& studentID);

    // Compares the student instance ID to the studentID
    bool operator!=(const int& studentID);

private:
    std::string firstName; // Student's first name
    std::string lastName; // Student's last name

    // Student's ID, must be 5 digits
    // Instructions indicated a limit of 1000-10000 which is not consistent with the data
    int studentID; 

    // Count of items in the dynamic array of checked out items
    // This is the count of items and not the actual size of the array
    int numItemsCheckedOut;

    // Size of the dynamic array itemsCheckedOut
    // This should alway be the size of or greater than the count of items
    int arraySize;

    // Dynamic array of items checked out by the student
    // This gets initialized to nullptr in the constructor
    std::string* itemsCheckedOut;
};