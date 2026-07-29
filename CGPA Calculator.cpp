#include <iostream>
#include <string>

using namespace std;

int main() {
    // Show a welcome message
    cout << "Welcome to the GPA Calculator!" << endl;
    cout << "---------------------------------" << endl;

    int totalCourses;
    cout << "How many classes did you take? ";
    cin >> totalCourses;

    // We need variables to hold the total math scores
    double totalCredits = 0;
    double totalGradePoints = 0;

    // Loops through each class one by one
    for (int i = 1; i <= totalCourses; i++) {
        cout << endl;
        cout << "--- Class Number " << i << " ---" << endl;

        string grade;
        cout << "Enter your letter grade (A, B, C, D, or F): ";
        cin >> grade;

        double credits;
        cout << "Enter the credit hours for this class: ";
        cin >> credits;

        // Change the letter grade into a number score
        double pointValue = 0;
        
        if (grade == "A" || grade == "a") {
            pointValue = 4.0;
        }
        if (grade == "B" || grade == "b") {
            pointValue = 3.0;
        }
        if (grade == "C" || grade == "c") {
            pointValue = 2.0;
        }
        if (grade == "D" || grade == "d") {
            pointValue = 1.0;
        }
        if (grade == "F" || grade == "f") {
            pointValue = 0.0;
        }

        // Grade points = grade number multiplied by credit hours
        double classPoints = pointValue * credits;

        // Add this class to the grand total
        totalCredits = totalCredits + credits;
        totalGradePoints = totalGradePoints + classPoints;
    }

    // Calculate the final GPA score
    double finalGpa = totalGradePoints / totalCredits;

    // Show the results
    cout << endl;
    cout << "===========================" << endl;
    cout << "RESULTS:" << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Your Final GPA: " << finalGpa << endl;
    cout << "===========================" << endl;

    return 0;
}
