#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// Manage User Data

// Add Questions

// Display Exam Data

// Create Exam
void createExam()
{
    srand(time(0));
    int numofQuestions, Questions;
    cout << "How many questions do you want to add? ";
    cin >> numofQuestions;
    ofstream file("exam.Q");
    if (numofQuestions <= 5)
    {
        cout << "start the exam " << endl;
    }
    else
    {
        cout << "Not enough questions available";
    }
    file << "Question,Ans A,Ans B,Ans C,Ans D,Correct Answer\n";
    for (int i = 1; i <= numofQuestions; ++i)
    {
        string question, ansA, ansB, ansC, ansD;
        char correctAnswer;
        cout << "Enter Question " << i << ": ";
        cin >> question;
        cout << "Ans A: ";
        cin >> ansA;
        cout << "Ans B: ";
        cin >> ansB;
        cout << "Ans C: ";
        cin >> ansC;
        cout << "Ans D: ";
        cin >> ansD;
        correctAnswer = 'A' + (rand() % 4);
        file << question << "," << ansA << "," << ansB << "," << ansC << "," << ansD << "," << correctAnswer << "\n";
        cout << "Correct answer for this question: " << correctAnswer << endl;
    }

    file.close();
    cout << "Exam saved to 'exam.Q'!" << endl;
}

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