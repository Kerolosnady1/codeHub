#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Struct Definitions
struct Question_
{
    string text;
    string options[4];
    int correctOption;
};

struct Student
{
    int id;
    float grade;
};

// Global Variables
Question_ examQuestions[100];
int userScores[100][100];
vector<Student> students;

// Function to Display Exam Information
void Exam_Information(string &sub, string &nameDoc, int &numQues, int &numRoom, int &timeLimit)
{
    cout << "\t\t\t===>> EXAM DATA <<===\n\n";
    cout << "Subject Name: ";
    cin.ignore(); // To handle leftover newline
    getline(cin, sub);
    cout << "Doctor Name: ";
    getline(cin, nameDoc);
    cout << "Number of Questions: ";
    cin >> numQues;
    cout << "Number of Rooms: ";
    cin >> numRoom;
    cout << "Time Limit (minutes): ";
    cin >> timeLimit;
    cout << "\t\t\t=========================\n";
}

// Function to Collect Student Data
void Student_Data(string &name, int &ID)
{
    cout << "\t\t\t===>> STUDENT DATA <<===\n";
    cout << "Enter your Name: ";
    cin.ignore(); // Handle leftover newline
    getline(cin, name);
    cout << "Enter your ID: ";
    cin >> ID;
}

// Function to Add Questions
void addQ()
{
    int numQuestions;
    cout << "How many questions would you like to add? ";
    cin >> numQuestions;

    for (int i = 0; i < numQuestions; i++)
    {
        cout << "Enter text for question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, examQuestions[i].text);

        for (int j = 0; j < 4; j++)
        {
            cout << "Enter choice " << j + 1 << ": ";
            getline(cin, examQuestions[i].options[j]);
        }

        cout << "Enter the correct answer (1-4): ";
        cin >> examQuestions[i].correctOption;
    }
    cout << "Questions added successfully!\n";
}

// Function to Create an Exam File
void createExam()
{
    srand(time(0));
    int numQuestions;
    cout << "How many questions do you want to add? ";
    cin >> numQuestions;

    if (numQuestions <= 0)
    {
        cout << "Invalid number of questions. Aborting.\n";
        return;
    }

    ofstream file("exam.Q");
    file << "Question,Ans A,Ans B,Ans C,Ans D,Correct Answer\n";
    for (int i = 0; i < numQuestions; i++)
    {
        string question, ansA, ansB, ansC, ansD;
        cout << "Enter Question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, question);
        cout << "Ans A: ";
        getline(cin, ansA);
        cout << "Ans B: ";
        getline(cin, ansB);
        cout << "Ans C: ";
        getline(cin, ansC);
        cout << "Ans D: ";
        getline(cin, ansD);

        char correctAnswer = 'A' + (rand() % 4);
        file << question << "," << ansA << "," << ansB << "," << ansC << "," << ansD << "," << correctAnswer << "\n";
        cout << "Correct answer for this question: " << correctAnswer << endl;
    }

    file.close();
    cout << "Exam saved to 'exam.Q'!\n";
}

// Function to Take an Exam
void takeExam(int totalExamQuestions)
{
    if (totalExamQuestions == 0)
    {
        cout << "No exam available. Create an exam first.\n";
        return;
    }

    cout << "Starting the exam...\n";
    for (int i = 0; i < totalExamQuestions; i++)
    {
        cout << "Question " << (i + 1) << ": " << examQuestions[i].text << "\n";
        for (int j = 0; j < 4; j++)
        {
            cout << "\tOption " << (j + 1) << ": " << examQuestions[i].options[j] << "\n";
        }

        int answer;
        cout << "Enter your answer (1-4): ";
        cin >> answer;
        userScores[0][i] = answer; // Storing answers for a single user
    }
    cout << "Exam completed!\n";
}

// Function to Save Student Data
void addStudentData()
{
    ofstream file("students.txt", ios::app);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    Student student;
    cout << "Enter Student ID: ";
    cin >> student.id;
    cout << "Enter Grade: ";
    cin >> student.grade;

    students.push_back(student);
    file << student.id << " " << student.grade << "\n";
    file.close();
    cout << "Data saved successfully!\n";
}

// Function to Display Student Data
void displayStudentData()
{
    ifstream file("students.txt");
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    int id;
    float grade;
    cout << "Students Data:\nID\tGrade\n";
    while (file >> id >> grade)
    {
        cout << id << "\t" << grade << endl;
    }
    file.close();
}

// Function to Sort and Display Results in Ascending Order
void displayResultsInAscendingOrder()
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.grade < b.grade; });

    cout << "\nResults in Ascending Order:\nID\tGrade\n";
    for (const auto &student : students)
    {
        cout << student.id << "\t" << student.grade << endl;
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n======= Exam Management System ========\n";
        cout << "1. Manage Exam Information\n";
        cout << "2. Manage Student Data\n";
        cout << "3. Add Questions\n";
        cout << "4. Create Exam\n";
        cout << "5. Take Exam\n";
        cout << "6. Display Student Data\n";
        cout << "7. Display Results in Ascending Order\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string subject, doctorName;
            int numQuestions, numRooms, timeLimit;
            Exam_Information(subject, doctorName, numQuestions, numRooms, timeLimit);
            break;
        }
        case 2:
        {
            addStudentData();
            break;
        }
        case 3:
        {
            addQ();
            break;
        }
        case 4:
        {
            createExam();
            break;
        }
        case 5:
        {
            takeExam(5); // Example with 5 questions
            break;
        }
        case 6:
        {
            displayStudentData();
            break;
        }
        case 7:
        {
            displayResultsInAscendingOrder();
            break;
        }
        case 8:
        {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}