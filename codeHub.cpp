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

void Exam_Informatoion(string sub, string nameDoc, int numQues, int numroom, int timelimit)
{

    cout << "\t \t \t \t \t    ===>>EXAM DATA<<=== \n \n \n";
    cout << " THE NAME OF SUBJECT:: \n  ==>>";
    cin >> sub;
    cout << "\n";
    cout << " DOCTOR Name:: \n =>> ";
    cin >> nameDoc;
    cout << "\n";
    cout << " NUMBERS OF QUESTIONS:: \n   =>> ";
    cin >> numQues;
    cout << "\n";
    cout << "Enter NUMBER OF ROOM:: \n  =>> ";
    cin >> numroom;
    cout << "\n";
    cout << "TIME LIMIT:: \n   =>> ";
    cin >> timelimit;
    cout << "\n";
    cout << "\t  \t \t $$##=====================================================##$$ \n \n \n\n";
}

void Student_Data(string name, int ID)
{
    cout << "\t \t \t \t \t ===>>STUDENT DATA<<===\t \n \n";
    cout << "Enter your Name:: \n =>> ";
    cin >> name;
    cout << "\n";
    cout << "Enter your ID:: \n =>> ";
    cin >> ID;
}

// Add Questions

void addQ()
{
    int x;
    cout << "How many questions would you like to add?" << endl;
    cin >> x;
    int numberOfQuestions = x;
    string questions[numberOfQuestions];
    string choices[numberOfQuestions][4];
    int correctAnswers[numberOfQuestions];
    for (int i = 0; i < numberOfQuestions; i++)
    {
        cout << "Question " << i + 1 << ": ";
        cin >> questions[i];
        getline(cin, questions[i]);
        for (int j = 0; j < 4; j++)
        {
            cout << "Choice " << j + 1 << " : ";
            getline(cin, choices[i][j]);
        }

        cout << "Enter the correct answer (1 to 4): ";
        cin >> correctAnswers[i];
    }

    int score = 0;
    for (int i = 0; i < numberOfQuestions; i++)
    {
        cout << questions[i] << endl;
        for (int j = 0; j < 4; j++)
        {
            cout << j + 1 << ". " << choices[i][j] << endl;
        }

        int userChoice;
        cout << "Choose the correct answer (1-4): ";
        cin >> userChoice;

        if (userChoice == correctAnswers[i])
        {
            cout << "Correct answer!" << endl;
            score++;
        }
        else
        {
            cout << "Wrong answer!" << endl;
        }
    }

    cout << "You answered correctly " << score << " out of " << numberOfQuestions << " questions." << endl;
}

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

void addStudentData()
{
    ofstream file("students.txt", ios::app);

    if (!file)
    {

        return;
    }

    int id;
    float grade;
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Grade: ";
    cin >> grade;

    file << id << " " << grade << endl;
    file.close();
    cout << "Data saved successfully!" << endl;
}

void displayStudentData()
{
    ifstream file("students.txt");
    if (!file)
    {
        return;
    }

    int id;
    float grade;
    cout << "Students Data:" << endl;
    cout << "ID\tGrade" << endl;
    while (file >> id >> grade)
    {
        cout << id << "\t" << grade << endl;
    }
    file.close();
}

// Display Results

int main()
{

    int choices;
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
    cin >> choices;

    switch (choices)
    {
    }

    // Manage User Data

    string subject, doctorname, namestudent;

    int num, id, questionnums, roomnum, limittime;

    Exam_Informatoion(subject, doctorname, questionnums, roomnum, limittime);

    Student_Data(namestudent, num);

    // Add Questions

    addQ();

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

    int choice;

    do
    {
        cout << "\nChoice an operation to perform" << endl;
        cout << "1. Add student data " << endl;
        cout << "2. display student data" << endl;
        cout << "3. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudentData();
            break;
        case 2:
            displayStudentData();
            break;
        case 3:
            cout << "program terminated." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);

    // Display Results

    return 0;
}