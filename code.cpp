#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
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
            // Handle the error gracefully, e.g., throw an exception
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
int main() {
    AuthenticationSystem authSystem;

    char startQuizChoice;
    cout << "Welcome to Result Management System!\n";
    while (true) {
        cout << "Do you want to view results? (Y/N): ";
        cin >> startQuizChoice;

        startQuizChoice = tolower(startQuizChoice);

        if (startQuizChoice == 'y' || startQuizChoice == 'n') {
            break;
        } else {
            cout << "Invalid choice. Please enter 'Y' or 'N'.\n";
        }
    }

    if (startQuizChoice == 'n') {
        cout << "Aborted. Goodbye!!\n";
        return 0;  // End the application
    }

    if (startQuizChoice == 'y') {
        // Get username and password from the user
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        // Authenticate user
        if (authSystem.authenticateUser(username, password)) {
            cout << "Authentication successful. Welcome, " << username << "!\n";
            // Add code for the rest of your application here
        } else {
            cout << "Authentication failed. Invalid username or password.\n";
        }
    }

    return 0;
}
