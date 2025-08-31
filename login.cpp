#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Hash password using a simple method
string simpleHash(const string& password) {
    int hash = 0;
    for (char c : password)
        hash += (int)c;
    return to_string(hash);
}

// Check if username exists in the file or not
bool userExists(const string& username) {
    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string user, pass;
        getline(iss, user, ',');
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Register new user
void RegisterUser() {
    string username, password;
    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username.empty() || password.empty()) {
        cout << "Username or password cannot be empty.\n";
        return;
    }

    if (userExists(username)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    ofstream outfile("users.txt", ios::app);
    outfile << username << "," << simpleHash(password) << "\n";
    outfile.close();
    cout << "Registration successful!\n";
}

// Login user
void LoginUser() {
    string username, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream infile("users.txt");
    string line;
    bool success = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        string storedUser, storedPass;
        getline(iss, storedUser, ',');
        getline(iss, storedPass);

        if (storedUser == username && storedPass == simpleHash(password)) {
            success = true;
            break;
        }
    }

    if (success) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n=== Login & Registration System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: RegisterUser(); break;
            case 2: LoginUser(); break;
            case 3: cout << "Thank!..\n"; return 0;
            default: cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
