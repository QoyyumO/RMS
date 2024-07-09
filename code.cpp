#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>   // Include for numeric_limits
#include <iomanip>  // Include for setprecision
#include <algorithm> // Include for sort

using namespace std;

struct User {
    string username;
    string password;
};

struct Student {
    string name;
    string matricNo; 
    int MTH201; 
    int CSC201;
    int INS204;
    int CSC211; 
    double gpa = 0.0;  // Default GPA to 0.0

    void computeGPA() {
        int totalCredits = 55; 
        double totalPoints = MTH201 + CSC201 + INS204 + CSC211;
        gpa = totalPoints / totalCredits * 5;
    }

    bool operator<(const Student& other) const {
        return matricNo < other.matricNo;
    }
};

class AuthenticationSystem {
private:
    vector<User> users;

public:
    AuthenticationSystem() {
        loadUsersFromTXT("users.txt");
    }

    void loadUsersFromTXT(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password, ',');

            users.push_back({username, password});
        }

        file.close();
    }

    bool authenticateUser(const string& username, const string& password) {
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                return true; // Authentication successful
            }
        }
        return false; // Authentication failed
    }
};

class Records {
private:
    vector<Student> students;

public:
    Records() {
        loadRecordsFromTXT("students_records.txt");
    }

    void loadRecordsFromTXT(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        students.clear(); // Clear existing records

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Student student;
            string gpaStr;

            getline(ss, student.name, ',');
            getline(ss, student.matricNo, ',');
            ss >> student.MTH201;
            ss.ignore(numeric_limits<streamsize>::max(), ','); // Ignore the comma
            ss >> student.CSC201;
            ss.ignore(numeric_limits<streamsize>::max(), ','); // Ignore the comma
            ss >> student.INS204;
            ss.ignore(numeric_limits<streamsize>::max(), ','); // Ignore the comma
            ss >> student.CSC211;
            ss.ignore(numeric_limits<streamsize>::max(), ','); // Ignore the comma
            getline(ss, gpaStr);

            // If GPA is not provided or is empty, compute it
            if (gpaStr.empty()) {
                student.computeGPA();
            } else {
                student.gpa = stod(gpaStr);
            }

            students.push_back(student);
        }

        file.close();
    }

    void saveRecordsToTXT(const string& filename) {
        // Sort students by matriculation number
        sort(students.begin(), students.end());

        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& student : students) {
            file << student.name << ',' << student.matricNo << ','
                 << student.MTH201 << ',' << student.CSC201 << ',' << student.INS204 << ',' << student.CSC211 << ','
                 << fixed << setprecision(2) << student.gpa << '\n';
        }

        file.close();
    }

    void updateStudentScores() {
        string matricNo;
        cout << "Enter matriculation number of the student: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
        getline(cin, matricNo);

        cout << "Searching for student with Matric No: " << matricNo << endl; // Debug print

        Student* student = findStudentByMatricNo(matricNo);

        if (student != nullptr) {
            cout << "Student found: " << student->name << endl; // Debug print
            cout << "Enter new scores for MTH201, CSC201, INS204, CSC211: ";
            cin >> student->MTH201 >> student->CSC201 >> student->INS204 >> student->CSC211;

            if (cin.fail()) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
                cout << "Invalid input. Please enter numeric values for the scores.\n";
                return;
            }

            student->computeGPA();

            saveRecordsToTXT("students_records.txt");

            cout << "Scores updated successfully.\n";
        } else {
            cout << "Student not found.\n";
        }
    }

    void displayAllResults() {
        if (students.empty()) {
            cout << "No student records available.\n";
        } else {
            for (const auto& student : students) {
                cout << "Name: " << student.name << "\n"
                     << "Matriculation Number: " << student.matricNo << "\n"
                     << "MTH201: " << student.MTH201 << "\n"
                     << "CSC201: " << student.CSC201 << "\n"
                     << "INS204: " << student.INS204 << "\n"
                     << "CSC211: " << student.CSC211 << "\n"
                     << "GPA: " << fixed << setprecision(2) << student.gpa << "\n\n";
            }
        }
    }

    void searchIndividualRecord() {
        string matricNo;
        cout << "Enter matriculation number of the student: ";
        cin >> matricNo;

        Student* student = findStudentByMatricNo(matricNo);

        if (student != nullptr) {
            cout << "Name: " << student->name << "\n"
                 << "Matriculation Number: " << student->matricNo << "\n"
                 << "MTH201: " << student->MTH201 << "\n"
                 << "CSC201: " << student->CSC201 << "\n"
                 << "INS204: " << student->INS204 << "\n"
                 << "CSC211: " << student->CSC211 << "\n"
                 << "GPA: " << fixed << setprecision(2) << student->gpa << "\n";
        } else {
            cout << "Student not found.\n";
        }
    }

    void storeIndividualRecord() {
        Student newStudent;

        cout << "Enter name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
        getline(cin, newStudent.name);

        cout << "Enter matriculation number: ";
        getline(cin, newStudent.matricNo); // Read matriculation number as a string

        // Check if matriculation number is unique
        if (findStudentByMatricNo(newStudent.matricNo) != nullptr) {
            cout << "Matriculation number already exists. Please enter a unique matriculation number.\n";
            return;
        }

        cout << "Enter scores for MTH201, CSC201, INS204, CSC211: ";
        cin >> newStudent.MTH201 >> newStudent.CSC201 >> newStudent.INS204 >> newStudent.CSC211;

        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            cout << "Invalid input. Please enter numeric values for the scores.\n";
            return;
        }

        newStudent.computeGPA();  // Compute GPA

        students.push_back(newStudent);

        saveRecordsToTXT("students_records.txt");

        cout << "Record stored successfully.\n";
    }

    Student* findStudentByMatricNo(const string& matricNo) {
        for (auto& student : students) {
            if (student.matricNo == matricNo) {
                return &student;
            }
        }
        return nullptr;
    }
};

int main() {
    AuthenticationSystem authSystem;
    Records records;

    char startQuizChoice;
    cout << "Welcome to Result Management System!\n";
    while (true) {
        cout << "Do you want to view results? (Y/N): ";
        cin >> startQuizChoice;

        startQuizChoice = tolower(startQuizChoice);

        if (startQuizChoice == 'n') {
            cout << "Aborted. Goodbye!!\n";
            return 0;  // End the application
        } else if (startQuizChoice == 'y') {
            break;
        } else {
            cout << "Invalid choice. Please enter 'Y' or 'N'.\n";
        }
    }

    bool authenticated = false;
    string username, password;

    while (!authenticated) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        authenticated = authSystem.authenticateUser(username, password);

        if (!authenticated) {
            cout << "Authentication failed. Invalid username or password.\n";
            cout << "Please re-enter your login details.\n";
        }
    }

    cout << "Authentication successful. Welcome, " << username << "!\n";
    char userChoice;

    do {
        cout << "Choose an option:\n"
             << "1. Update student scores\n"
             << "2. Display all results\n"
             << "3. Search for individual record\n"
             << "4. Store individual record\n"
             << "5. Exit\n";
        cin >> userChoice;

        switch (userChoice) {
            case '1':
                records.updateStudentScores();
                break;
            case '2':
                records.displayAllResults();
                break;
            case '3':
                records.searchIndividualRecord();
                break;
            case '4':
                records.storeIndividualRecord();
                break;
            case '5':
                cout << "Exiting. Goodbye!!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (userChoice != '5');

    cout << "Exiting. Goodbye!!\n";
    return 0;
}
