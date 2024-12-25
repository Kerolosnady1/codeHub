#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Struct to represent a question
struct Question {
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
int findUserIndex(int userId) {
    for (int i = 0; i < totalUsers; ++i) {
        if (userIDs[i] == userId) {
            return i;
        }
    }
    return -1; // User not found
}

// Function to manage user data
void manageUserData() {
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
void addQuestions() {
    Question q;
    cout << "Enter the question text: ";
    cin.ignore();
    getline(cin, q.text);

    for (int i = 0; i < 4; ++i) {
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
void displayExamData() {
    if (totalQuestions == 0) {
        cout << "No questions available.\n";
        return;
    }

    for (int i = 0; i < totalQuestions; ++i) {
        cout << "Question " << (i + 1) << ": " << questions[i].text << "\n";
        for (int j = 0; j < 4; ++j) {
            cout << "\tOption " << (j + 1) << ": " << questions[i].options[j] << "\n";
        }
        cout << "\tCorrect Option: " << (questions[i].correctOption + 1) << "\n";
    }
}

// Function to create an exam
void createExam(Question examQuestions[], int& totalExamQuestions) {
    totalExamQuestions = 0;
    int numQuestions;

    cout << "Enter the number of questions for the exam: ";
    cin >> numQuestions;

    if (numQuestions > totalQuestions) {
        cout << "Not enough questions available. Using all available questions.\n";
        numQuestions = totalQuestions;
    }

    for (int i = 0; i < numQuestions; ++i) {
        examQuestions[i] = questions[i];
    }
    totalExamQuestions = numQuestions;
    cout << "Exam created successfully with " << numQuestions << " questions.\n";
}

// Function to take an exam
void takeExam(const Question examQuestions[], int totalExamQuestions, int userId) {
    if (totalExamQuestions == 0) {
        cout << "No exam available. Create an exam first.\n";
        return;
    }

    int userIndex = findUserIndex(userId);
    if (userIndex == -1) {
        cout << "Invalid user ID. Please register first.\n";
        return;
    }

    cout << "Starting the exam...\n";
    for (int i = 0; i < totalExamQuestions; ++i) {
        cout << "Question " << (i + 1) << ": " << examQuestions[i].text << "\n";
        for (int j = 0; j < 4; ++j) {
            cout << "\tOption " << (j + 1) << ": " << examQuestions[i].options[j] << "\n";
        }
        int answer;
        cout << "Enter your answer (1-4): ";
        cin >> answer;

        if (answer < 1 || answer > 4) {
            cout << "Invalid option. Please try again.\n";
            --i; // Retry the question
        } else {
            userScores[userIndex][i] = answer - 1; // Convert to zero-based index
        }
    }
    cout << "Exam completed!\n";
}

// Function to grade an exam
void gradeExam(const Question examQuestions[], int totalExamQuestions, int userId) {
    if (totalExamQuestions == 0) {
        cout << "No exam or answers available to grade.\n";
        return;
    }

    int userIndex = findUserIndex(userId);
    if (userIndex == -1) {
        cout << "Invalid user ID. Please register first.\n";
        return;
    }

    int score = 0;
    for (int i = 0; i < totalExamQuestions; ++i) {
        if (userScores[userIndex][i] == examQuestions[i].correctOption) {
            ++score;
        }
    }
    cout << "Exam graded! Score for user ID " << userId << ": " << score << "/" << totalExamQuestions << "\n";
}

// Function to save or load data
void saveAndLoadData(bool save) {
    if (save) {
        ofstream outFile("data.txt");
        // Save users
        outFile << totalUsers << "\n";
        for (int i = 0; i < totalUsers; ++i) {
            outFile << userIDs[i] << " " << userNames[i] << "\n";
        }

        // Save questions
        outFile << totalQuestions << "\n";
        for (int i = 0; i < totalQuestions; ++i) {
            outFile << questions[i].text << "\n";
            for (int j = 0; j < 4; ++j) {
                outFile << questions[i].options[j] << "\n";
            }
            outFile << questions[i].correctOption << "\n";
        }

        outFile.close();
        cout << "Data saved successfully!\n";
    } else {
        ifstream inFile("data.txt");
        totalUsers = 0;
        totalQuestions = 0;

        // Load users
        int numUsers;
        inFile >> numUsers;
        for (int i = 0; i < numUsers; ++i) {
            inFile >> userIDs[i];
            inFile.ignore();
            getline(inFile, userNames[i]);
        }
        totalUsers = numUsers;

        // Load questions
        int numQuestions;
        inFile >> numQuestions;
        inFile.ignore();
        for (int i = 0; i < numQuestions; ++i) {
            getline(inFile, questions[i].text);
            for (int j = 0; j < 4; ++j) {
                getline(inFile, questions[i].options[j]);
            }
            inFile >> questions[i].correctOption;
            inFile.ignore();
        }
        totalQuestions = numQuestions;

        inFile.close();
        cout << "Data loaded successfully!\n";
    }
}


// Function to display results in ascending order
void displayResults() {
    if (totalUsers == 0) {
        cout << "No users available.\n";
        return;
    }

    // Sort users based on total scores
    for (int i = 0; i < totalUsers - 1; ++i) {
        for (int j = i + 1; j < totalUsers; ++j) {
            int totalScoreI = 0, totalScoreJ = 0;
            for (int k = 0; k < totalQuestions; ++k) {
                totalScoreI += userScores[i][k];
                totalScoreJ += userScores[j][k];
            }
            if (totalScoreI > totalScoreJ) {
                swap(userIDs[i], userIDs[j]);
                swap(userNames[i], userNames[j]);
                for (int k = 0; k < totalQuestions; ++k) {
                    swap(userScores[i][k], userScores[j][k]);
                }
            }
        }
    }

    cout << "\nResults in Ascending Order:\n";
    for (int i = 0; i < totalUsers; ++i) {
        int totalScore = 0;
        for (int j = 0; j < totalQuestions; ++j) {
            totalScore += userScores[i][j];
        }
        cout << "User ID: " << userIDs[i] << ", Name: " << userNames[i] << ", Total Score: " << totalScore << "\n";
    }
}

// Main Function
int main() {
    int choice;
    Question examQuestions[100];
    int totalExamQuestions = 0;

    do {
        cout << "\n===== Exam Management System =====\n";
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

        switch (choice) {
            case 1: manageUserData(); break;
            case 2: addQuestions(); break;
            case 3: displayExamData(); break;
            case 4: createExam(examQuestions, totalExamQuestions); break;
            case 5: {
                int userId;
                cout << "Enter your user ID: ";
                cin >> userId;
                takeExam(examQuestions, totalExamQuestions, userId);
                break;
            }
            case 6: {
                int userId;
                cout << "Enter your user ID: ";
                cin >> userId;
                gradeExam(examQuestions, totalExamQuestions, userId);
                break;
            }
            case 7: saveAndLoadData(true); break;
            case 8: saveAndLoadData(false); break;
            case 9: displayResults(); break;
            case 10: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}
