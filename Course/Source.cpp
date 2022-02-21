//============================================================================
// Name        : Source.cpp
// Author      : Craig A Nelson
// Version     : 1.0
// Copyright   : Copyright © 2022 SNHU //CS-300-T3671 DSA: Analysis and Design 22EW3
// Description : Project Two in C++, Reads CSV and prints required info
//============================================================================



#include <iostream>
#include <fstream>

#include "CSVparser.hpp"

using namespace std;

//==============================================================================//
// Global definitions visible to all methods and classes                                                
//==============================================================================//

/*
  Each course contains an Id, Name, and a Vector to 
  hold as many prereqs as the course has
 */
struct Course {
    string courseNum;
    string courseName;
    vector<string> preReqs;

    Course() {}
};

/*
 Each node in the Binary Search Tree contains the course info and left and right children
  Multiple constructors allow a node with or without a defined course
 */
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};


//==============================================================================//
// CourseBST Class Definition                                                                                                   
//==============================================================================//

class CourseBST {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void printSampleSchedule(Node* node);
    void printCourseInformation(Node* node, string courseNum);


public:
    CourseBST();
    virtual ~CourseBST();
    void DeleteRecursive(Node* node);
    void Insert(Course course);
    int NumPrerequisiteCourses(Course course);
    void PrintSampleSchedule();
    void PrintCourseInformation(string courseNum);

};

/*
Construct the Binary Search Tree and initialize the root
*/
CourseBST::CourseBST() {
    root = nullptr;
}

/*
 Deconstruct the Binary Search Tree by passing the root
 to the function that recursively deletes each node
 */
CourseBST::~CourseBST() {
    DeleteRecursive(root);
}

/*
Delete the Binary Search Tree nodes recursively 
this is used by the deconstructor
 */
void CourseBST::DeleteRecursive(Node* node) {
    if (node) {
        DeleteRecursive(node->left);
        DeleteRecursive(node->right);
        delete node;
    }
}

/*
 Insert a node into the Binary Search Tree
 */
void CourseBST::Insert(Course course) {
    //If the root is not initialized
    if (root == nullptr)
        //initialize it with the current course info
        root = new Node(course);
    //Else, send the node to the addNode method 
    //to be added to the Binary Search Tree
    else
        
        this->addNode(root, course);
}

/*
 Returns the number of prereqs the passed course has
 */
int CourseBST::NumPrerequisiteCourses(Course course) {
    int count = 0;
    for (unsigned int i = 0; i < course.preReqs.size(); i++) {
        if (course.preReqs.at(i).length() > 0)
            count++;
    }
    return count;
}

/*
 Passes the Binary Search Tree root to the private method
 */
void CourseBST::PrintSampleSchedule() {
    this->printSampleSchedule(root);
}

/*
 Passes the Binary Search Tree root and the course Id 
 to be searched for and displayed if found
 */
void CourseBST::PrintCourseInformation(string courseNum) {
    this->printCourseInformation(root, courseNum);
}

/*
Utilizes the public Insert method
  Determines and sets correct alphanumeric location 
  and if the current child is a nullptr,
  adds the node to the Binary Search Tree, 
  else keeps traversing Binary Search Tree until a nullptr is found
 */
void CourseBST::addNode(Node* node, Course course) {

    // Current courseNum is less than the current node's courseNum
    if (node->course.courseNum.compare(course.courseNum) > 0) {
        if (node->left == nullptr)
            node->left = new Node(course);
        else
            this->addNode(node->left, course);
    }
    // Current courseNum is equal or greater than the current node's courseNum
    else {
        if (node->right == nullptr)
            node->right = new Node(course);
        else
            this->addNode(node->right, course);
    }
}

/*
Recursively prints the loaded courses IN ORDER
 */
void CourseBST::printSampleSchedule(Node* node) {

    if (node != nullptr) {
        printSampleSchedule(node->left);
        cout << node->course.courseNum << ", " << node->course.courseName << endl;
        printSampleSchedule(node->right);
    }
    return;
}

/*
 Displays a single courses information including its prereqs
 */
void CourseBST::printCourseInformation(Node* curr, string courseNum) {

    // Traverse Binary Search Tree until bottom reached or matching courseNum found
    while (curr != nullptr) {

        // Passed courseNum matches the current courseNum
        if (curr->course.courseNum.compare(courseNum) == 0) {

            // Display course and get num prereqs
            cout << endl << curr->course.courseNum << ", " << curr->course.courseName << endl;
            unsigned int size = NumPrerequisiteCourses(curr->course);
            cout << "Prerequisite(s): ";

            // If prereqs exist, display each prereq with proper formatting
            unsigned int i = 0;
            for (i = 0; i < size; i++) {
                cout << curr->course.preReqs.at(i);
                if (i != size - 1)
                    cout << ", ";
            }
            // If no prereqs, inform user and return to stop the search
            if (i == 0)
                cout << "No prerequisites required.";
            cout << endl;
            return;
        }

        // Passed courseNum is smaller than the current courseNum so traverse left
        else if (courseNum.compare(curr->course.courseNum) < 0)
            curr = curr->left;

        // Passed courseNum is larger than the current courseNum so traverse right
        else
            curr = curr->right;
    }
    // nullptr has been reached but course hasn't been found/ printed, so inform user
    cout << "Course " << courseNum << " not found." << endl;
}


//==============================================================================//
// Static methods used for testing                                                                                              
//==============================================================================//

//Load Courses from cin choice for csv file
bool loadCourses(string csvPath, CourseBST* coursesBST) {

    // Open course file, get/ separate each line & insert into BST
    try {
        ifstream courseFile(csvPath);

        if (courseFile.is_open()) {
            while (!courseFile.eof()) {

                // A vector will hold each csv that a course contains
                vector<string> courseInfo;
                string courseData;

                getline(courseFile, courseData);
                while (courseData.length() > 0) {

                    // Get substring of each course data, add to vector & delete from str
                    unsigned int comma = courseData.find(',');
                    if (comma < 100) {  // Any data field is allowed 99 chars or less
                        courseInfo.push_back(courseData.substr(0, comma));
                        courseData.erase(0, comma + 1);
                    }
                    // Add the last course after the final comma
                    else {
                        courseInfo.push_back(courseData.substr(0, courseData.length()));
                        courseData = "";
                    }
                }

                // Load the separated values into a course, 
                //insert into Binary Search Tree and close file
                Course course;
                course.courseNum = courseInfo[0];
                course.courseName = courseInfo[1];

                for (unsigned int i = 2; i < courseInfo.size(); i++) {
                    course.preReqs.push_back(courseInfo[i]);
                }
                coursesBST->Insert(course);
            }
            courseFile.close();
            return true;
        }
    }
    catch (csv::Error& e) {
        cerr << e.what() << endl;
    }
    return false;
}


//==============================================================================//
// Main method                                                                                                                                  
//==============================================================================//

int main(int argc, char* argv[]) {

    // Process command line argument
    string csvPath, courseId;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseId = argv[2];
        break;
    default:
        csvPath = "";
        break;
    }

    // Define Binary Search Tree and  Welcome User
    CourseBST* coursesBST = nullptr;
    cout << "\nWelcome to the course planner!\n" << endl;

    // Making user choice a string and converting first char to int prevents invalid data
    string choice = "0";
    int userChoice = choice[0] - '0';

    //if not 9 or exit
    while (userChoice != 9) {

        cout << "   1. Load Data Structure" << endl;
        cout << "   2. Print Course List" << endl;
        cout << "   3. Print Course" << endl;
        cout << "   9. Exit" << endl;
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        // Check if user choice is a double digit
        if (choice.length() == 1)
            userChoice = choice[0] - '0';
        else
            userChoice = 0;

        bool success = 1;

        // Handle users choice from menu
        switch (userChoice) {

            // Instantiate Binary Search Tree
            // get file path name 
            //and load courses into Binary Search Tree 
        case 1:

            if (coursesBST == nullptr)
                coursesBST = new CourseBST();
            if (csvPath.length() == 0) {
                cout << "Enter the file name that contains the course data: ";
                cin >> csvPath;
            }
            // Determine if the file was opened- load successful
            success = loadCourses(csvPath, coursesBST);
            if (success)
                cout << "Courses have been loaded.\n" << endl;
            else
                cout << "File not found.\n" << endl;
            csvPath = "";
            break;

            // Validate that a Binary Search Tree  exists
            //and print a sample schedule
        case 2:

            if (coursesBST != nullptr && success) {
                cout << "Here is a sample schedule:\n" << endl;
                coursesBST->PrintSampleSchedule();
                cout << endl;
            }
            else
                cout << "Load courses first - option 1\n" << endl;
            break;

            // Validate that a Binary Search Tree  exists
            //and search/ display course info
        case 3:

            if (coursesBST != nullptr && success) {
                if (courseId.length() == 0) {
                    cout << "What course do you want to know about? ";
                    cin >> courseId;
                    for (auto& userChoice : courseId) userChoice = toupper(userChoice);
                }
                coursesBST->PrintCourseInformation(courseId);
                cout << endl;
            }
            else
                cout << "Load courses first - option 1\n" << endl;
            courseId = "";
            break;

            // User entered invalid data or exited the program
        default:

            if (userChoice != 9)
                cout << choice << " is not a valid option\n" << endl;
            break;
        }
    }
    cout << "\nThank you for using the course planner!" << endl;

    return 0;
}