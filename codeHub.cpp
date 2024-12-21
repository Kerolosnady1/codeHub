#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Manage User Data

// Add Questions

// Display Exam Data

// Create Exam

// Take Exam
void takeExam(const Question examQuestions[], int totalExamQuestions, int userId)
{
    if (totalExamQuestions == 0)
    {
        cout << "No exam available. Create an exam first.\n";
        return;
    }

    cout << "Starting the exam...\n";
    for (int i = 0; i < totalExamQuestions; ++i)
    {
        cout << "Question " << (i + 1) << ": " << examQuestions[i].text << "\n";
        for (int j = 0; j < 4; ++j)
        {
            cout << "\tOption " << (j + 1) << ": " << examQuestions[i].options[j] << "\n";
        }
        int answer;
        cout << "Enter your answer (1-4): ";
        cin >> answer;
        userScores[userId][i] = answer - 1;
    }
    cout << "Exam completed!\n";
}

// Grade Exam

// Save and Load Data

// Display Results
int main()
{
    cout << "=======================================";
    cout << "\n======= Exam Management System ========\n";
    cout << "=======================================\n";
    cout << "1. Manage User Data\n";
    cout << "2. Add Questions\n";
    cout << "3. Display Exam Data\n";
    cout << "4. Create Exam\n";
    cout << "5. Take Exam\n";
    cout << "6. Grade Exam\n";
    cout << "7. Save Data\n";
    cout << "8. Load Data\n";
    cout << "9. Display Results\n";
    cout << "10. Exit\n";
    cout << "Choose an option: ";
}