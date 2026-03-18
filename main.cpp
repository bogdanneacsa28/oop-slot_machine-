#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>


using namespace std;

int getNumberAccounts() {
    int number=0;
    ifstream dataBase("database.txt");
    string line;
    while (getline(dataBase, line)) {
        number++;
    }
    dataBase.close();
    return number;
}

class Player {
    private:
    static int noAccounts;
    string username;
    string password;
    int credits;
    bool ageVerified;
    bool selfExclusion;
    public:
    //constructors and destructors
    Player();
    Player(string username, string password, int credits, bool ageVerified, bool selfExclusion);
    ~Player();
    //operators
    //setters
    void setAgeVerified(bool ageVerified);
    void setSelfExclusion(bool selfExclusion);
    //getters
    int getCredits() const;
    bool getAgeVerify() const;
    bool getSelfExclusion() const;
    //methods

};
int Player::noAccounts = getNumberAccounts();
Player::Player() {
    this->username = "";
    this->password = "";
    this->credits = 0;
    this->ageVerified = false;
    this->selfExclusion = false;
}
Player::Player(string username,string password,int credits,bool ageVerified,bool selfExclusion) {
    this->username = username;
    this->password = password;
    this->credits = credits;
    this->ageVerified = ageVerified;
    this->selfExclusion = selfExclusion;
}

int Player::getCredits() const{
    return this->credits;
}

bool Player::getAgeVerify() const {
    return this->ageVerified;
}
void Player::setAgeVerified(bool ageVerify) {
    this->ageVerified = ageVerify;
}
bool Player::getSelfExclusion() const {
    return this->selfExclusion;
}
void Player::setSelfExclusion(bool selfExclusion) {
    this->selfExclusion = selfExclusion;
}
Player::~Player() {
}
bool isAgeVerified(string username) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == username && a == "true") {
                dataBase.close();
                return true;
            }
            else{
                dataBase.close();
                return false;
            }

        }
    }
    dataBase.close();
    return false;
}
bool isSelfExclusion(string username) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == username && s == "true") {
                dataBase.close();
                return true;
            }
            else{
                dataBase.close();
                return false;
            }

        }
    }
    dataBase.close();
    return false;
}
// check if username already exists
bool doesUsernameExist(string username) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s)
            if (u == username) {
            dataBase.close();
            return true;
            }
    }
    dataBase.close();
    return false;
}

// verify the login credentials
int verifyLogin(string username, string password) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == username && p == password) {
                dataBase.close();
                return c;
            }
        }
    }
    dataBase.close();
    return 0;
}
void updatePlayerInDatabase(string targetUsername, int newCredits, bool newAgeVerified, bool newSelfExclusion) {
    ifstream inFile("database.txt");
    ofstream tempFile("tempdatabase.txt");
    string line, u, p, a, s;
    int c;
    while (getline(inFile, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == targetUsername) {
                string ageStr = newAgeVerified ? "true" : "false";
                string selfStr = newSelfExclusion ? "true" : "false";
                tempFile << u << " " << p << " " << newCredits << " " << ageStr << " " << selfStr << endl;
            } else {
                tempFile << line << endl;
            }
        }
    }
    inFile.close();
    tempFile.close();
    remove("database.txt");
    rename("tempdatabase.txt", "database.txt");
}

int main() {
    int choiceNumber;
    string username, password;
    cout<<"Loading..."<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
    cout << "\n💲 Welcome to Top-Dollar Casino! 💲" << endl;
    while (true) {
        cout << "[1] Sign in\n[2] Create account\n[3] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choiceNumber;

        switch (choiceNumber) {
            case 1: {
                system("clear");
                cout <<endl;
                cout << "💎 Sign In 💎" << endl;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;

                if (verifyLogin(username, password)) {
                    Player currentPlayer(username,password,verifyLogin(username, password),isAgeVerified(username),isSelfExclusion(username));
                    system("clear");
                    cout << "\n✅ Login successful! Welcome, " << username << "." << endl;
                    while(true) {
                        cout << "Credits: " << currentPlayer.getCredits() << endl;
                        if(currentPlayer.getAgeVerify() == false)
                            cout << "‼️ Warning: Age verification needed !"<<endl;
                        if (currentPlayer.getSelfExclusion())
                            cout << "‼️ Warning: You are self excluded !"<<endl;
                        cout<<"[1] Account settings\n[2] Deposit\n[3] Withdrawal\n[4] Games\n[5] Exit\nEnter your choice: ";
                        cin >> choiceNumber;
                        switch (choiceNumber) {
                            case 1: {
                                system("clear");
                                cout <<"[1] Verify age\n[2] Self exclusion\n[3] Back to menu\nEnter your choice: ";
                                cin >> choiceNumber;
                                switch (choiceNumber) {
                                    case 1: {
                                        if (currentPlayer.getAgeVerify() == false) {
                                            int age;
                                            system("clear");
                                            cout << "Enter your age: ";
                                            cin >> age;
                                            if (age >= 18) {
                                                    currentPlayer.setAgeVerified(true);
                                                    system("clear");
                                                    cout<<"✅ Age verified!"<<endl;
                                                    updatePlayerInDatabase(username, currentPlayer.getCredits(), currentPlayer.getAgeVerify(), currentPlayer.getSelfExclusion());
                                            }
                                            else {
                                                system("clear");
                                                cout<<"‼️ Warning: Too young to gamble !";
                                            }
                                            break;
                                        }
                                        case 2: {
                                            system("clear");
                                            string selfExclusionChoice;
                                            if (currentPlayer.getSelfExclusion() == false) {
                                                cout <<"‼️ IMPORTANT ‼️"<<endl;
                                                cout <<"Self-exclusion is a formal, voluntary agreement to ban yourself from gambling\nvenues or online platforms for a set period, helping you stop gambling. It acts as a protective barrier, requiring operators to close accounts and refuse service. Common services include GAMSTOP (online) or venue-specific agreements."<<endl;
                                                cout <<"Are you sure you want to self exclude? (yes/no) :";
                                                cin >> selfExclusionChoice;
                                                if (selfExclusionChoice == "yes") {
                                                    currentPlayer.setSelfExclusion(true);
                                                    updatePlayerInDatabase(username, currentPlayer.getCredits(), currentPlayer.getAgeVerify(), currentPlayer.getSelfExclusion());
                                                }
                                            }
                                            system("clear");
                                            break;
                                        }
                                        case 3: {
                                            system("clear");
                                            break;
                                        }
                                        default: {
                                            cout<<"Enter a valid choice!"<<endl;
                                            break;
                                        }
                                    }
                                }
                                }
                            }
                        }
                    }
                break;
            }
            case 2: {
                system("clear");
                cout <<endl;
                cout << "💎 Create account! 💎" << endl;
                cout << "Username: "; cin >> username;

                if (doesUsernameExist(username)) {
                    cout << "⚠️ Error: The username already exists!" << endl;
                } else {
                    cout << "Password: "; cin >> password;

                    ofstream outFile("database.txt", ios::app);
                    if (outFile.is_open()) {
                        outFile << username << " " << password << " " << 500 << "false" <<" "<< "false" << endl;
                        outFile.close();
                        cout << "✅ Account created! You received 500 starting credits." << endl;
                    }
                }
                break;
            }
            case 3:
                return 0;
            default:
                system("clear");
                cout << "Enter a valid choice!" << endl;
        }
    }
}