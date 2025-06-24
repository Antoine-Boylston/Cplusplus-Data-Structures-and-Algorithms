//============================================================================
// Name        : Advising Assistance Program
// Author      : Antoine Boylston
// Version     : 1.0
// Description : Program for course planning at ABCU. It loads course data form
//               a CSV file into a Hash Table for fast searching and allows 
//               users to: 1) load data, 2) print a sorted list of all courses,
//               and 3) display detailed information about a specific course, 
//               including prerequisites. It includes input validation, follows
//               industry-standard best practices, and provides a user-friendly
//               menu interface.
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Struct to hold course data
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Hash table to store courses
unordered_map<string, Course> courseTable;

// Function to convert string to uppercase (for consistent searching)
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Function to load courses from file
void loadCourses(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid course entry." << endl;
            continue;
        }

        Course course;
        course.courseNumber = toUpper(tokens[0]); // store as uppercase
        course.courseTitle = tokens[1];

        // Add any prerequisites
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(toUpper(tokens[i]));
        }

        // Insert course into hash table
        courseTable[course.courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Function to print course list in alphanumeric order
void printCourseList() {
    if (courseTable.empty()) {
        cout << "Error: No course data loaded. Please load data first." << endl;
        return;
    }

    // Copy courses to vector
    vector<Course> courseList;
    for (const auto& pair : courseTable) {
        courseList.push_back(pair.second);
    }

    // Sort courses by course number
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });

    // Print sorted courses
    cout << "\nHere is a sample schedule:\n";
    for (const Course& course : courseList) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print course details
void printCourseDetails(const string& inputCourseNumber) {
    string courseNumber = toUpper(inputCourseNumber);
    auto it = courseTable.find(courseNumber);
    if (it != courseTable.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseTitle << endl;
        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites:";
            for (const string& prereq : course.prerequisites) {
                cout << " " << prereq;
            }
            cout << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}

// Main program
int main() {
    string fileName;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (true) {
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit\n";

    cout << "What would you like to do? ";
    if (!(cin >> choice)) {
        // If user did not enter an integer
        cout << "Invalid input. Please enter a number." << endl;

        // Clear the error flag on cin
        cin.clear();

        // Ignore invalid input left in buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        continue; // Skip to next iteration
    }

    // Clear newline character left in input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1) {
        cout << "Enter file name to load: ";
        getline(cin, fileName);
        loadCourses(fileName);
    } else if (choice == 2) {
        printCourseList();
    } else if (choice == 3) {
        cout << "What course do you want to know about? ";
        string courseNum;
        getline(cin, courseNum);
        printCourseDetails(courseNum);
    } else if (choice == 9) {
        cout << "Thank you for using the course planner!" << endl;
        break;
    } else {
        cout << choice << " is not a valid option." << endl;
    }
}

    return 0;
}
