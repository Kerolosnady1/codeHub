# Exam Management System (C++)

A console-based **Exam Management System** built using C++.  
This application allows administrators to create exams, manage questions, register students, grade exams, save results to a CSV file, and display ranked outcomes.

---

## 🚀 Features

### 👤 User Management
- Register students using unique IDs
- Store student names and exam answers
- Validate users before exam access

### 📝 Question & Exam Management
- Add multiple-choice questions (4 options each)
- Define correct answers
- Create exams using stored questions
- Display full exam content (admin only)

### 🧪 Exam Execution
- Students can take exams through an interactive console
- Input validation for answers
- Automatic answer storage

### 📊 Grading & Results
- Automatic grading based on correct answers
- Score and percentage calculation
- Sorted result display (ascending order)

### 💾 File Handling
- Save results to `ExamData.csv`
- Load stored exam results
- CSV format compatible with Excel and Google Sheets

---

## 🛠️ Technologies Used

- **Language:** C++
- **Concepts:**  
  - Structures (`struct`)
  - Arrays
  - File I/O (`fstream`)
  - Menu-driven programs
  - Sorting algorithms
- **Data Storage:** CSV file format

---

## 📂 Project Structure

Exam-Management-System/
│
├── codeHub.cpp # Main source code
├── ExamData.csv # Generated CSV file (after saving)
└── README.md # Project documentation


---

## ▶️ How to Compile and Run

### Using g++
```bash
g++ main.cpp -o exam_system
./exam_system


Using an IDE

Open the project in Code::Blocks, Visual Studio, or CLion

Compile and run codeHub.cpp

🔐 User Roles
Role	Capabilities
ADMIN	Add questions, create exams, view data, save/load files
USER	Register, take exams, view grades
📌 Notes & Limitations

Uses static arrays (maximum 100 users and 100 questions)

No authentication or password system

Data persistence is limited to CSV (no database)

Exam questions are selected sequentially (no randomization)

🌱 Future Improvements

Dynamic memory (vector)

Randomized question selection

Time-based exam enforcement

Authentication system

Database integration

GUI version

📚 References

C++ File Handling (fstream):
https://en.cppreference.com/w/cpp/io/basic_fstream

C++ Structures:
https://en.cppreference.com/w/cpp/language/struct

CSV File Format:
https://tools.ietf.org/html/rfc4180

C++ Input Validation (cin):
https://en.cppreference.com/w/cpp/io/basic_istream

📜 License

This project is provided for educational purposes.
You are free to modify and extend it for learning or academic use.


---

If you want, I can also:
- Refactor this code into **modern C++ (vectors & classes)**
- Write a **professional project report**
- Create **UML diagrams**
- Help you choose a **license (MIT, GPL, etc.)**

Just tell me 👍
