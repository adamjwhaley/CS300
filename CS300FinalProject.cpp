//============================================================================
// Name        : HashTable.cpp
// Author      : Jake Whaley
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

string toUpperCase(const string& str);


//Define course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

//Loading data from the file
void loadCourses(vector<Course>& courses) {
    string fileName;
    cout << "Please enter the file name, including  '.xxx' for file type." << endl;
    cin >> fileName;

    ifstream file(fileName);
    if (file.is_open() != true) {
        cout << "Error: Unable to open file. File named '" << fileName << "' could not be found." << endl;
        return;
    }

    courses.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream fileLines(line);
        string courseNumber;
        string title;
        string prereq;
        vector<string> prereqs;

        getline(fileLines, courseNumber, ',');
        getline(fileLines, title, ',');

        while (getline(fileLines, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        courses.push_back({courseNumber, title, prereqs});

    }

    file.close();
    cout << courses.size() << " courses have been loaded successfully." << endl;
}

//Printing a sorted list
void printSortedList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;

    sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    cout << "Sorted list of CS courses, including math courses: " << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

//Printing specific course information
void printAnyCourse(const vector <Course>& courses) {
    string findCourse;
    cout << "Please enter a course number: " << endl;
    cin >> findCourse;
    findCourse = toUpperCase(findCourse);

    for (const auto& course : courses) {
        if (toUpperCase(course.courseNumber) == findCourse) {
            cout << course.courseNumber << "- " << course.courseTitle << endl;
            if (course.prerequisites.empty() != true) {
                cout << "Prerequisites: " << endl;
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            else {
                cout << "No prerequisites exist." << endl;
            }
            return;
        }
    }
    cout << "Unable to find that course." << endl;
}

//Converting string to Uppercase
string toUpperCase(const string& str) {
    string upperStr = str;
    for (auto& letter : upperStr) {
        letter = toupper(letter);
    }
    return upperStr;
}

//Main Function
int main()
{
    vector<Course> courses;
    int userInput = 0;

    while (true) {
        cout << "Advising Assistance Program" << endl;
        cout << " " << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cin >> userInput;

        //Input validation
        if (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 9) {
            cout << "You entered " << userInput << ". Please enter a valid input." << endl;
            continue;
        }

        switch (userInput) {
        case 1:
            loadCourses(courses);
            break;
        case 2:
            if (courses.empty() == true) {
                cout << "You must load data before attempting to print the Course list." << endl;
            }
            else {
                printSortedList(courses);
            }
            break;
        case 3:
            if (courses.empty() == true) {
                cout << "You must load data before attempting to print a course." << endl;
            }
            else {
                printAnyCourse(courses);
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        }
    }
    return 0;
}
