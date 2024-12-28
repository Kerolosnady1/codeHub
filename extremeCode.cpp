#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Struct to represent a question
struct Question
{
    string text;
    string options[4];
    int correctOption;
};

// Global variables
Question questions[100];
int totalQuestions = 0;
int userIDs[100];
string userNames[100];
int userScores[100][100] = {0}; // Initialize to 0
int totalUsers = 0;

// Find the index of a user by userId
int findUserIndex(int userId)
{
    for (int i = 0; i < totalUsers; ++i)
    {
        if (userIDs[i] == userId)
        {
            return i;
        }
    }
    return -1; // User not found
}

// Function to manage exam information data
void Exam_Informatoion(string sub, string nameDoc, int numQues, int numroom, int timelimit)
{

    cout << "\t \t \t \t \t    ===>>EXAM DATA<<=== \n \n \n";
    cout << " THE NAME OF SUBJECT:: \n  ==>> ";
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

// Function to manage user data
void Student_Data()
{
    int userId;
    string userName;

    cout << "Enter user ID: ";
    cin >> userId;
    cin.ignore();
    cout << "Enter user name: ";
    getline(cin, userName);

    userIDs[totalUsers] = userId;
    userNames[totalUsers] = userName;
    totalUsers++;
    cout << "User data saved successfully!\n";
}

// Function to add questions
void addQ()
{
    Question q;
    cout << "Enter the question text: ";
    cin.ignore();
    getline(cin, q.text);

    for (int i = 0; i < 4; ++i)
    {
        cout << "Enter option " << (i + 1) << ": ";
        getline(cin, q.options[i]);
    }

    cout << "Enter the correct option number: ";
    cin >> q.correctOption;
    --q.correctOption; // Convert to zero-based index

    questions[totalQuestions] = q;
    totalQuestions++;
    cout << "Question added successfully!\n";
}

// Function to display exam data
void displayExamData()
{
    if (totalQuestions == 0)
    {
        cout << "No questions available.\n";
        return;
    }

    for (int i = 0; i < totalQuestions; ++i)
    {
        cout << "Question " << (i + 1) << ": " << questions[i].text << "\n";
        for (int j = 0; j < 4; ++j)
        {
            cout << "\tOption " << (j + 1) << ": " << questions[i].options[j] << "\n";
        }
        cout << "\tCorrect Option: " << (questions[i].correctOption + 1) << "\n";
    }
}

// Function to create an exam
void CreateExam(Question examQuestions[], int &totalExamQuestions)
{
    totalExamQuestions = 0;
    int numQuestions;

    cout << "Enter the number of questions for the exam: ";
    cin >> numQuestions;

    if (numQuestions > totalQuestions)
    {
        cout << "Not enough questions available. Using all available questions.\n";
        numQuestions = totalQuestions;
    }

    for (int i = 0; i < numQuestions; ++i)
    {
        examQuestions[i] = questions[i];
    }
    totalExamQuestions = numQuestions;
    cout << "Exam created successfully with " << numQuestions << " questions.\n";
}

// Function to take an exam
void takeExam(const Question examQuestions[], int totalExamQuestions, int userId)
{
    if (totalExamQuestions == 0)
    {
        cout << "No exam available. Create an exam first.\n";
        return;
    }

    int userIndex = findUserIndex(userId);
    if (userIndex == -1)
    {
        cout << "Invalid user ID. Please register first.\n";
        return;
    }

    string sub, nameDoc;
    int numQues = totalExamQuestions, numroom, timelimit;
    Exam_Informatoion(sub, nameDoc, numQues, numroom, timelimit);

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

        if (answer < 1 || answer > 4)
        {
            cout << "Invalid option. Please try again.\n";
            --i; // Retry the question
        }
        else
        {
            userScores[userIndex][i] = answer - 1; // Convert to zero-based index
        }
    }
    cout << "Exam completed!\n";
}

// Function to grade an exam
void Exam_Grade(const Question examQuestions[], int totalExamQuestions, int userId)
{
    if (totalExamQuestions == 0)
    {
        cout << "No exam or answers available to grade.\n";
        return;
    }

    int userIndex = findUserIndex(userId);
    if (userIndex == -1)
    {
        cout << "Invalid user ID. Please register first.\n";
        return;
    }

    int score = 0;
    for (int i = 0; i < totalExamQuestions; ++i)
    {
        if (userScores[userIndex][i] == examQuestions[i].correctOption)
        {
            ++score;
        }
    }

    double percentage = (score * 100.0) / totalExamQuestions;
    cout << "Exam graded! Score for user ID " << userId << ": " << score << "/" << totalExamQuestions << "\n";
    cout << "Correct answers: " << score << "\n";
    cout << "Percentage: " << percentage << "%\n";
}

// Function to save or load data
void saveAndLoadData(bool save)
{
    if (save)
    {
        // Create and open a CSV file for saving the data
        ofstream outFile("ExamData.csv");

        // Write the header for the CSV file
        outFile << "UserID,UserName,UserGrade,CorrectAnswersCount\n"; // Header for User Data

        // Save data for each user
        for (int i = 0; i < totalUsers; ++i)
        {
            int correctAnswersCount = 0;
            int totalScore = 0;

            // Calculate the number of correct answers for each user
            for (int j = 0; j < totalQuestions; ++j)
            {
                if (userScores[i][j] == questions[j].correctOption)
                {
                    correctAnswersCount++; // Count correct answers
                    totalScore++;          // Increment score for correct answer
                }
            }

            // Calculate percentage grade
            double gradePercentage = (double(correctAnswersCount) / totalQuestions) * 100;

            // Write User data to CSV (Formatted percentage grade)
            outFile << userIDs[i] << ","                                  // UserID
                    << userNames[i] << ","                                // UserName
                    << fixed << setprecision(2) << gradePercentage << "," // UserGrade (Percentage)
                    << correctAnswersCount << "\n";                       // CorrectAnswersCount
        }

        outFile.close();
        cout << "Data saved successfully in CSV format!\n";
    }
    else
    {
        ifstream inFile("ExamData.csv");
        if (!inFile)
        {
            cout << "Error: Unable to open file.\n";
            return;
        }

        string line;
        totalUsers = 0;

        // Skip the header line
        getline(inFile, line);

        // Read user data from file
        while (getline(inFile, line))
        {
            size_t pos = 0;
            int userID, correctAnswersCount;
            string userName;
            double userGrade;

            // Parse each line into the respective fields
            pos = line.find(',');
            userID = stoi(line.substr(0, pos)); // Get UserID
            line.erase(0, pos + 1);

            pos = line.find(',');
            userName = line.substr(0, pos); // Get UserName
            line.erase(0, pos + 1);

            pos = line.find(',');
            userGrade = stod(line.substr(0, pos)); // Get UserGrade (Percentage)
            line.erase(0, pos + 1);

            correctAnswersCount = stoi(line); // Get CorrectAnswersCount

            // Store the loaded data into appropriate arrays (You could skip this step if not needed)
            userIDs[totalUsers] = userID;
            userNames[totalUsers] = userName;
            totalUsers++;
        }

        inFile.close();
        cout << "Data loaded successfully from CSV format!\n";
    }
}

// Function to display results in ascending order
void DisplayResult()
{
    if (totalUsers == 0)
    {
        cout << "No users available.\n";
        return;
    }

    // Sort users based on total scores
    for (int i = 0; i < totalUsers - 1; ++i)
    {
        for (int j = i + 1; j < totalUsers; ++j)
        {
            int totalScoreI = 0, totalScoreJ = 0;
            for (int k = 0; k < totalQuestions; ++k)
            {
                totalScoreI += userScores[i][k];
                totalScoreJ += userScores[j][k];
            }
            if (totalScoreI > totalScoreJ)
            {
                swap(userIDs[i], userIDs[j]);
                swap(userNames[i], userNames[j]);
                for (int k = 0; k < totalQuestions; ++k)
                {
                    swap(userScores[i][k], userScores[j][k]);
                }
            }
        }
    }

    cout << "\nResults in Ascending Order:\n";
    for (int i = 0; i < totalUsers; ++i)
    {
        int totalScore = 0;
        for (int j = 0; j < totalQuestions; ++j)
        {
            totalScore += userScores[i][j];
        }
        double percentage = (totalScore * 100.0) / totalQuestions;
        cout << "User ID: " << userIDs[i] << ", Name: " << userNames[i] << ", Total Score: " << totalScore
             << ", Percentage: " << percentage << "%\n";
    }
}

// Main Function
int main()
{
    int choice;
    Question examQuestions[100];
    int totalExamQuestions = 0;

    do
    {
        cout << "\n===== Exam Management System =====\n";
        cout << "1. Manage User Data (USER)\n";
        cout << "2. Add Questions (ADMIN)\n";
        cout << "3. Display Exam Data (ADMIN)\n";
        cout << "4. Create Exam (ADMIN)\n";
        cout << "5. Take Exam (USER)\n";
        cout << "6. Grade Exam (USER)\n";
        cout << "7. Save Data (ADMIN)\n";
        cout << "8. Load Data (ADMIN)\n";
        cout << "9. Display Results (ADMIN)\n";
        cout << "10. Exit (USER)\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            Student_Data();
            break;
        case 2:
            addQ();
            break;
        case 3:
            displayExamData();
            break;
        case 4:
            CreateExam(examQuestions, totalExamQuestions);
            break;
        case 5:
        {
            int userId;
            cout << "Enter your user ID: ";
            cin >> userId;
            takeExam(examQuestions, totalExamQuestions, userId);
            break;
        }
        case 6:
        {
            int userId;
            cout << "Enter your user ID: ";
            cin >> userId;
            Exam_Grade(examQuestions, totalExamQuestions, userId);
            break;
        }
        case 7:
            saveAndLoadData(true);
            break;
        case 8:
            saveAndLoadData(false);
            break;
        case 9:
            DisplayResult();
            break;
        case 10:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}