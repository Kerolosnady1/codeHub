#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

struct Question_
{
    string text;
    string options[4];
    int correctOption;
};

Question_ questions[100];
int userScores[100][100];

// Manage User Data

// Add Questions

// Display Exam Data

struct Question
{
    string text;
    vector<string> choices;
};
void displayQuestions(const vector<Question> &questions)
{
    for (size_t i = 0; i < questions.size(); ++i)
    {
        cout << "Question " << i + 1 << ": " << questions[i].text << "\n";
        for (size_t j = 0; j < questions[i].choices.size(); ++j)
        {
            cout << "  " << char('A' + j) << ". " << questions[i].choices[j] << "\n";
        }
        cout << "\n";
    }
}

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
void takeExam(const Question_ examQuestions[], int totalExamQuestions, int userId)
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

void Exam_Grade(int answer[], int correctanswer[], int numofquestions)
{
    int sizeofanswer = sizeof(answer) / sizeof(answer[0]);
    int sizeofcorrectanswer = sizeof(correctanswer) / sizeof(correctanswer[0]);
    if (sizeofanswer != sizeofcorrectanswer)
    {
        cout << "You forgot to answer some questions!" << endl;
        return;
    }

    int grade = 0;

    for (int i = 0; i < numofquestions; i++)
    {
        if (answer[i] == correctanswer[i])
        {
            grade++;
        }
    }

    double percentage = ((double)grade / numofquestions) * 100;

    cout << "Number of questions answered correctly: " << grade << endl;
    cout << "Percentage: " << percentage << "%" << endl;

    if (percentage >= 90)
    {
        cout << "Your grade is: A" << endl;
    }
    else if (percentage >= 80)
    {
        cout << "Your grade is: B" << endl;
    }
    else if (percentage >= 70)
    {
        cout << "Your grade is: C" << endl;
    }
    else if (percentage >= 60)
    {
        cout << "Your grade is: D" << endl;
    }
    else
    {
        cout << "Your grade is: F" << endl;
    }
}

// Save and Load Data

// Display Results

int main()
{

    int choice;
    Question_ examQuestions[100];
    int totalExamQuestions = 0;

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
    cin >> choice;

    switch (choice)
    {
    }

    // Manage User Data

    // Add Questions

    // Display Exam Data

    vector<Question> questions;

    int numQuestions;
    cout << "Enter the number of questions: ";
    cin >> numQuestions;
    cin.ignore();

    for (int i = 0; i < numQuestions; ++i)
    {
        Question q;
        cout << "Enter the text for question " << i + 1 << ": ";
        getline(cin, q.text);

        int numChoices;
        cout << "Enter the number of choices for this question: ";
        cin >> numChoices;
        cin.ignore();

        q.choices.resize(numChoices);
        for (int j = 0; j < numChoices; ++j)
        {
            cout << "Enter choice " << j + 1 << ": ";
            getline(cin, q.choices[j]);
        }

        questions.push_back(q);
    }

    cout << "\nDisplaying Questions:\n";
    displayQuestions(questions);

    // Create Exam

    createExam();

    // Take Exam

    // Grade Exam

    // Save and Load Data

    // Display Results

    return 0;
}