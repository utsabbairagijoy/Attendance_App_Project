#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Constants for array sizes
const int MAX_USERS = 100;
const int MAX_REQUESTS = 100;
const int MAX_AVAILABILITIES = 100;
const int MAX_NOTIFICATIONS = 100;

// Structure definitions
struct User {
    string username;
    string password;
    string name;
    string role;
};

struct TuitionRequest {
    string studentUsername;
    string subject;
    string location;
    string budget;
};

struct TeacherAvailability {
    string teacherUsername;
    string subject;
    string location;
    string salary;
};

struct Notification {
    string teacherUsername;
    string studentUsername;
    string subject;
    string location;
};

// Global variables for data storage
User users[MAX_USERS];
TuitionRequest requests[MAX_REQUESTS];
TeacherAvailability availabilities[MAX_AVAILABILITIES];
Notification notifications[MAX_NOTIFICATIONS];

int userCount = 0;
int requestCount = 0;
int availabilityCount = 0;
int notificationCount = 0;

// Function prototypes
void clearScreen();
void pressEnterToContinue();
void showMainMenu();
void registerUser();
bool login(User &currentUser);
void studentMenu(const User &student);
void teacherMenu(const User &teacher);
void adminMenu();
void saveAllData();
void loadAllData();
void ensureAdminExists();

// Helper functions
void saveUsersToFile();
void loadUsersFromFile();
void saveRequestsToFile();
void loadRequestsFromFile();
void saveAvailabilitiesToFile();
void loadAvailabilitiesFromFile();
void saveNotificationsToFile();
void loadNotificationsFromFile();

int main() {
    loadAllData();
    ensureAdminExists();

    int choice;
    User currentUser;

    do {
        clearScreen();
        showMainMenu();
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: // Login
                if (login(currentUser)) {
                    clearScreen();
                    if (currentUser.role == "student") {
                        studentMenu(currentUser);
                    } else if (currentUser.role == "teacher") {
                        teacherMenu(currentUser);
                    } else if (currentUser.role == "admin") {
                        adminMenu();
                    }
                    saveAllData();
                } else {
                    cout << "Login failed. Please try again.\n";
                    pressEnterToContinue();
                }
                break;

            case 2: // Register
                registerUser();
                break;

            case 3: // Exit
                cout << "Thank you for using the Tuition Management System!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
        }
    } while (choice != 3);

    return 0;
}

// Clear the screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Wait for user to press Enter

void pressEnterToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Show the main menu
void showMainMenu() {
    cout << "===== Tuition Management System =====\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    cout << "====================================\n";
}

// Register a new user
void registerUser() {
    clearScreen();
    cout << "===== Registration =====\n";

    User newUser;

    cout << "Enter your name: ";
    getline(cin, newUser.name);

    cout << "Choose your role (student/teacher): ";
    getline(cin, newUser.role);

    // Validate role
    if (newUser.role != "student" && newUser.role != "teacher") {
        cout << "Invalid role. Registration failed.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Choose a username: ";
    getline(cin, newUser.username);

    // Check if username already exists
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == newUser.username) {
            cout << "Username already exists. Please choose another.\n";
            pressEnterToContinue();
            return;
        }
    }

    cout << "Choose a password: ";
    getline(cin, newUser.password);

    users[userCount++] = newUser;
    saveUsersToFile();
    cout << "Registration successful!\n";
    pressEnterToContinue();
}

// Login a user
bool login(User &currentUser) {
    clearScreen();
    cout << "===== Login =====\n";

    string username, password, role;

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    cout << "Role (student/teacher/admin): ";
    getline(cin, role);

    // Check for admin login
    if (role == "admin") {
        if (username == "admin" && password == "admin") {
            currentUser = {"admin", "admin", "Administrator", "admin"};
            return true;
        }
        return false;
    }

    // Check for regular user login
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username &&
            users[i].password == password &&
            users[i].role == role) {
            currentUser = users[i];
            return true;
        }
    }

    return false;
}

// Student menu
void studentMenu(const User &student) {
    int choice;

    do {
        clearScreen();
        cout << "===== Student Menu (" << student.name << ") =====\n";
        cout << "1. Post a tuition request\n";
        cout << "2. View my requests\n";
        cout << "3. Back to main menu\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                TuitionRequest newRequest;
                newRequest.studentUsername = student.username;

                cout << "Enter subject: ";
                getline(cin, newRequest.subject);

                cout << "Enter location: ";
                getline(cin, newRequest.location);

                cout << "Enter your budget: ";
                getline(cin, newRequest.budget);

                requests[requestCount++] = newRequest;
                saveRequestsToFile();
                cout << "Request posted successfully!\n";
                pressEnterToContinue();
                break;
            }

            case 2: {
                clearScreen();
                cout << "===== My Tuition Requests =====\n";

                bool hasRequests = false;
                for (int i = 0; i < requestCount; i++) {
                    if (requests[i].studentUsername == student.username) {
                        cout << "Subject: " << requests[i].subject << endl;
                        cout << "Location: " << requests[i].location << endl;
                        cout << "Budget: " << requests[i].budget << endl;
                        cout << "-------------------------\n";
                        hasRequests = true;
                    }
                }

                if (!hasRequests) {
                    cout << "You haven't posted any requests yet.\n";
                }

                pressEnterToContinue();
                break;
            }

            case 3:
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
        }
    } while (choice != 3);
}

// Teacher menu
void teacherMenu(const User &teacher) {
    int choice;

    do {
        clearScreen();
        cout << "===== Teacher Menu (" << teacher.name << ") =====\n";
        cout << "1. Set availability\n";
        cout << "2. View my availability\n";
        cout << "3. Check for matching requests\n";
        cout << "4. Back to main menu\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                TeacherAvailability newAvailability;
                newAvailability.teacherUsername = teacher.username;

                cout << "Enter subject you can teach: ";
                getline(cin, newAvailability.subject);

                cout << "Enter your location: ";
                getline(cin, newAvailability.location);

                cout << "Enter your expected salary: ";
                getline(cin, newAvailability.salary);

                availabilities[availabilityCount++] = newAvailability;
                saveAvailabilitiesToFile();
                cout << "Availability set successfully!\n";
                pressEnterToContinue();
                break;
            }

            case 2: {
                clearScreen();
                cout << "===== My Availability =====\n";

                bool hasAvailability = false;
                for (int i = 0; i < availabilityCount; i++) {
                    if (availabilities[i].teacherUsername == teacher.username) {
                        cout << "Subject: " << availabilities[i].subject << endl;
                        cout << "Location: " << availabilities[i].location << endl;
                        cout << "Expected Salary: " << availabilities[i].salary << endl;
                        cout << "-------------------------\n";
                        hasAvailability = true;
                    }
                }

                if (!hasAvailability) {
                    cout << "You haven't set any availability yet.\n";
                }

                pressEnterToContinue();
                break;
            }

            case 3: {
                clearScreen();
                cout << "===== Matching Student Requests =====\n";

                bool foundMatches = false;

                // Check each of the teacher's availabilities
                for (int i = 0; i < availabilityCount; i++) {
                    if (availabilities[i].teacherUsername == teacher.username) {
                        // Now check all requests for matches
                        for (int j = 0; j < requestCount; j++) {
                            if (requests[j].subject == availabilities[i].subject &&
                                requests[j].location == availabilities[i].location) {

                                cout << "Student: " << requests[j].studentUsername << endl;
                                cout << "Subject: " << requests[j].subject << endl;
                                cout << "Location: " << requests[j].location << endl;
                                cout << "Budget: " << requests[j].budget << endl;
                                cout << "-------------------------\n";
                                foundMatches = true;
                            }
                        }
                    }
                }

                if (!foundMatches) {
                    cout << "No matching student requests found.\n";
                } else {
                    cout << "Would you like to notify admin about these matches? (y/n): ";
                    char notify;
                    cin >> notify;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (notify == 'y' || notify == 'Y') {
                        // Add notifications for all matches
                        for (int i = 0; i < availabilityCount; i++) {
                            if (availabilities[i].teacherUsername == teacher.username) {
                                for (int j = 0; j < requestCount; j++) {
                                    if (requests[j].subject == availabilities[i].subject &&
                                        requests[j].location == availabilities[i].location) {

                                        Notification newNotif;
                                        newNotif.teacherUsername = teacher.username;
                                        newNotif.studentUsername = requests[j].studentUsername;
                                        newNotif.subject = requests[j].subject;
                                        newNotif.location = requests[j].location;
                                        notifications[notificationCount++] = newNotif;
                                    }
                                }
                            }
                        }
                        saveNotificationsToFile();
                        cout << "Admin has been notified.\n";
                    }
                }

                pressEnterToContinue();
                break;
            }

            case 4:
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
        }
    } while (choice != 4);
}

// Admin menu
void adminMenu() {
    int choice;

    do {
        clearScreen();
        cout << "===== Admin Menu =====\n";
        cout << "1. View all tuition requests\n";
        cout << "2. Delete a request\n";
        cout << "3. View teacher notifications\n";
        cout << "4. Back to main menu\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                clearScreen();
                cout << "===== All Tuition Requests =====\n";

                if (requestCount == 0) {
                    cout << "No tuition requests found.\n";
                } else {
                    for (int i = 0; i < requestCount; i++) {
                        cout << i+1 << ". Student: " << requests[i].studentUsername << endl;
                        cout << "   Subject: " << requests[i].subject << endl;
                        cout << "   Location: " << requests[i].location << endl;
                        cout << "   Budget: " << requests[i].budget << endl;
                        cout << "-------------------------\n";
                    }
                }

                pressEnterToContinue();
                break;
            }

            case 2: {
                clearScreen();
                cout << "===== Delete a Request =====\n";

                if (requestCount == 0) {
                    cout << "No tuition requests to delete.\n";
                } else {
                    for (int i = 0; i < requestCount; i++) {
                        cout << i+1 << ". Student: " << requests[i].studentUsername << endl;
                        cout << "   Subject: " << requests[i].subject << endl;
                        cout << "   Location: " << requests[i].location << endl;
                        cout << "   Budget: " << requests[i].budget << endl;
                        cout << "-------------------------\n";
                    }

                    cout << "Enter the number of the request to delete (0 to cancel): ";
                    int requestNum;
                    cin >> requestNum;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (requestNum > 0 && requestNum <= requestCount) {

                        for (int i = requestNum - 1; i < requestCount - 1; i++) {
                            requests[i] = requests[i + 1];
                        }
                        requestCount--;
                        saveRequestsToFile();
                        cout << "Request deleted successfully.\n";
                    } else if (requestNum != 0) {
                        cout << "Invalid request number.\n";
                    }
                }

                pressEnterToContinue();
                break;
            }

            case 3: {
                clearScreen();
                cout << "===== Teacher Notifications =====\n";

                if (notificationCount == 0) {
                    cout << "No notifications found.\n";
                } else {
                    for (int i = 0; i < notificationCount; i++) {
                        cout << "Teacher: " << notifications[i].teacherUsername << endl;
                        cout << "Student: " << notifications[i].studentUsername << endl;
                        cout << "Subject: " << notifications[i].subject << endl;
                        cout << "Location: " << notifications[i].location << endl;
                        cout << "-------------------------\n";
                    }
                }

                pressEnterToContinue();
                break;
            }

            case 4:
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
        }
    } while (choice != 4);
}

// Save all data to files
void saveAllData() {
    saveUsersToFile();
    saveRequestsToFile();
    saveAvailabilitiesToFile();
    saveNotificationsToFile();
}

// Load all data from files
void loadAllData() {
    loadUsersFromFile();
    loadRequestsFromFile();
    loadAvailabilitiesFromFile();
    loadNotificationsFromFile();
}

// Ensure admin account exists
void ensureAdminExists() {
    bool adminExists = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == "admin" && users[i].role == "admin") {
            adminExists = true;
            break;
        }
    }
    if (!adminExists) {
        users[userCount++] = {"admin", "admin", "Administrator", "admin"};
        saveUsersToFile();
    }
}

// File handling functions
void saveUsersToFile() {
    ofstream outFile("users.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            outFile << users[i].username << "|" << users[i].password << "|"
                   << users[i].name << "|" << users[i].role << "\n";
        }
        outFile.close();
    }
}

void loadUsersFromFile() {
    ifstream inFile("users.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1+1);
            size_t pos3 = line.find("|", pos2+1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                users[userCount].username = line.substr(0, pos1);
                users[userCount].password = line.substr(pos1+1, pos2-pos1-1);
                users[userCount].name = line.substr(pos2+1, pos3-pos2-1);
                users[userCount].role = line.substr(pos3+1);
                userCount++;
            }
        }
        inFile.close();
    }
}

void saveRequestsToFile() {
    ofstream outFile("requests.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < requestCount; i++) {
            outFile << requests[i].studentUsername << "|" << requests[i].subject << "|"
                   << requests[i].location << "|" << requests[i].budget << "\n";
        }
        outFile.close();
    }
}

void loadRequestsFromFile() {
    ifstream inFile("requests.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1+1);
            size_t pos3 = line.find("|", pos2+1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                requests[requestCount].studentUsername = line.substr(0, pos1);
                requests[requestCount].subject = line.substr(pos1+1, pos2-pos1-1);
                requests[requestCount].location = line.substr(pos2+1, pos3-pos2-1);
                requests[requestCount].budget = line.substr(pos3+1);
                requestCount++;
            }
        }
        inFile.close();
    }
}

void saveAvailabilitiesToFile() {
    ofstream outFile("availabilities.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < availabilityCount; i++) {
            outFile << availabilities[i].teacherUsername << "|" << availabilities[i].subject << "|"
                   << availabilities[i].location << "|" << availabilities[i].salary << "\n";
        }
        outFile.close();
    }
}

void loadAvailabilitiesFromFile() {
    ifstream inFile("availabilities.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1+1);
            size_t pos3 = line.find("|", pos2+1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                availabilities[availabilityCount].teacherUsername = line.substr(0, pos1);
                availabilities[availabilityCount].subject = line.substr(pos1+1, pos2-pos1-1);
                availabilities[availabilityCount].location = line.substr(pos2+1, pos3-pos2-1);
                availabilities[availabilityCount].salary = line.substr(pos3+1);
                availabilityCount++;
            }
        }
        inFile.close();
    }
}

void saveNotificationsToFile() {
    ofstream outFile("notifications.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < notificationCount; i++) {
            outFile << notifications[i].teacherUsername << "|" << notifications[i].studentUsername << "|"
                   << notifications[i].subject << "|" << notifications[i].location << "\n";
        }
        outFile.close();
    }
}

void loadNotificationsFromFile() {
    ifstream inFile("notifications.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1+1);
            size_t pos3 = line.find("|", pos2+1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                notifications[notificationCount].teacherUsername = line.substr(0, pos1);
                notifications[notificationCount].studentUsername = line.substr(pos1+1, pos2-pos1-1);
                notifications[notificationCount].subject = line.substr(pos2+1, pos3-pos2-1);
                notifications[notificationCount].location = line.substr(pos3+1);
                notificationCount++;
            }
        }
        inFile.close();
    }
}
