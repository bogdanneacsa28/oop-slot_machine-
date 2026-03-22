#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstring>
#include <vector>

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
    char* username;
    char* password;
    int credits;
    bool ageVerified;
    bool selfExclusion;
    public:
    Player();
    Player(const char* username, const char* password, const int credits, bool ageVerified, bool selfExclusion);
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();
    void setAgeVerified(bool ageVerified);
    void setSelfExclusion(bool selfExclusion);
    int getCredits() const;
    bool getAgeVerify() const;
    bool getSelfExclusion() const;
    void depositCredits(int credits);
    void withdrawCredits(int credits);
    char* getUsername() const;
};

int Player::noAccounts = getNumberAccounts();

Player::Player() {
    this->username = strcpy(new char[strlen("")+1], "");
    this->password = strcpy(new char[strlen("")+1], "");
    this->credits = 0;
    this->ageVerified = false;
    this->selfExclusion = false;
}

Player::Player(const char* username, const char* password, const int credits, bool ageVerified, bool selfExclusion) {
    this->username = strcpy(new char[strlen(username)+1], username);
    this->password = strcpy(new char[strlen(password)+1], password);
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

Player::Player(const Player &obj) {
    this->username = strcpy(new char[strlen(obj.username)+1], obj.username);
    this->password = strcpy(new char[strlen(obj.password)+1], obj.password);
    this->credits = obj.credits;
    this->ageVerified = obj.ageVerified;
    this->selfExclusion = obj.selfExclusion;
}
Player& Player::operator=(const Player& obj) {
    if (this == &obj) {
        return *this;
    }
    else{
        delete [] this->username;
        delete [] this->password;
        this->username = strcpy(new char[strlen(obj.username)+1], obj.username);
        this->password = strcpy(new char[strlen(obj.password)+1], obj.password);
        this->credits = obj.credits;
        this->ageVerified = obj.ageVerified;
        this->selfExclusion = obj.selfExclusion;
        return *this;
    }
};
Player::~Player() {
    delete[] username;
    delete[] password;
}
void Player::depositCredits(int credits) {
    this->credits = this->credits+credits;
}
void Player::withdrawCredits(int credits) {
    this->credits = this->credits-credits;
}
char* Player::getUsername() const {
    return this->username;
}
class SlotMachine {
private:
    const int machineID;
    static int noSlots;
    float jackpot;
    int* betHistory;
    int historySize;
public:
    SlotMachine();
    SlotMachine(float jackpot,int *betHistory, int historySize);
    SlotMachine(const SlotMachine& obj);
    SlotMachine& operator=(const SlotMachine& obj);
    ~SlotMachine();
};
int SlotMachine::noSlots = 0;
SlotMachine::SlotMachine():machineID(++noSlots) {
    this->jackpot = 0;
    this->betHistory = nullptr;
    this->historySize = 0;
}
SlotMachine::SlotMachine(float jackpot, int* betHistory, int historySize):machineID(++noSlots) {
    this->jackpot = jackpot;
    this->betHistory = new int[historySize];
    for (int i=0;i < historySize ;i++) {
        this->betHistory[i] = betHistory[i];
    }
    this->historySize = historySize;
}
SlotMachine::SlotMachine(const SlotMachine& obj):machineID(++noSlots) {
    this->jackpot = obj.jackpot;
    this->betHistory = new int[obj.historySize];
    for (int i=0; i < obj.historySize ; i++) {
        this->betHistory[i] = obj.betHistory[i];
    }
    this->historySize = obj.historySize;
}
SlotMachine& SlotMachine::operator=(const SlotMachine& obj) {
      if (this == &obj) {
          return *this;
      }
    else {
        this->jackpot = obj.jackpot;
        delete [] this->betHistory;
        this->betHistory = new int[obj.historySize];
        for (int i=0; i < obj.historySize ; i++) {
            this->betHistory[i] = obj.betHistory[i];
        }
        this->historySize = obj.historySize;
        return *this;
    }
};
SlotMachine::~SlotMachine() {
    delete [] this->betHistory;
}
class Reel {
    private:
    char currentSymbol;
    char* possibleSymbol;
    int numSymbols;
    bool isSpinning;
    public:
    Reel();
    Reel(char currentSymbol, char* possibleSymbol, int numSymbols, bool isSpinning);
    Reel(const Reel& obj);
    Reel& operator=(const Reel& obj);
    ~Reel();
    void roll();
};
class CasinoSession {
    private:
    long sessionDuration;
    float totalWagered;
    float totalWon;
    bool isActive;
    public:
    CasinoSession();
    CasinoSession(long sessionDuration,float totalWagered, float totalWon, bool isActive);
    CasinoSession(const CasinoSession& obj);
    CasinoSession& operator=(const CasinoSession& obj);
    ~CasinoSession();
};

class GameMenu {

};

bool isAgeVerified(const char* username) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == username) {
                dataBase.close();
                return a == "true";
            }
        }
    }
    dataBase.close();
    return false;
}

bool isSelfExclusion(const char* username) {
    ifstream dataBase("database.txt");
    string line, u, p, a, s;
    int c;
    while (getline(dataBase, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u == username) {
                dataBase.close();
                return s == "true";
            }
        }
    }
    dataBase.close();
    return false;
}


bool doesUsernameExist(const char* username) {
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


int verifyLogin(const char* username, const char* password) {
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

void updatePlayerInDatabase(const char* targetUsername, int newCredits, bool newAgeVerified, bool newSelfExclusion) {
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
void deletePlayerInDatabase(const Player& player) {
    ifstream inFile("database.txt");
    ofstream tempFile("tempdatabase.txt");
    string line, u, p, a, s;
    int c;
    while (getline(inFile, line)) {
        stringstream ss(line);
        if (ss >> u >> p >> c >> a >> s) {
            if (u != player.getUsername()) {
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
    char username[256], password[256];

    cout<<"Loading...";
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");

    cout << "💲 Welcome to Top-Dollar Casino! 💲" << endl;
    while (true) {
        cout << "[1] Sign in\n[2] Create account\n[3] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choiceNumber;

        switch (choiceNumber) {
            case 1: {
                system("clear");
                cout << "💎 Sign In 💎" << endl;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                if (verifyLogin(username, password)) {
                    Player currentPlayer(username, password, verifyLogin(username, password), isAgeVerified(username), isSelfExclusion(username));
                    system("clear");
                    cout << "✅ Login successful! Welcome, " << username << "." << endl;
                    bool isLoggedIn = true;
                    while(isLoggedIn) {
                        cout << "Credits: " << currentPlayer.getCredits() << endl;
                        if(currentPlayer.getAgeVerify() == false)
                            cout << "‼️ Warning: Age verification needed !"<<endl;
                        if (currentPlayer.getSelfExclusion())
                            cout << "‼️ Warning: You are self excluded . Your account will be deleted after logging out!"<<endl;
                        cout<<"[1] Account settings\n[2] Deposit\n[3] Withdrawal\n[4] Games\n[5] Log out\nEnter your choice: ";
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
                                        }
                                        else {
                                            system("clear");
                                            cout<<"✅ Age verified!"<<endl;
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
                                        system("clear");
                                        cout<<"Enter a valid choice!"<<endl;
                                    }
                                }
                                break;
                            }
                            case 2: {
                                system("clear");
                                cout << "💵 Deposit 💵\nYou currently have "<<currentPlayer.getCredits()<<"\n[1] Continue with the deposit\n[2] Back to menu\nEnter your choice: " ;
                                cin >> choiceNumber;
                                switch (choiceNumber) {
                                    case 1: {
                                        int depositCredits;
                                        bool isDepositDone = false;
                                        system("clear");
                                        while (!isDepositDone) {
                                            system("clear");
                                            cout <<"!! READ BEFORE DEPOSIT !!\n10 Credits are worth 1 RON\nThe deposit value needs to be higher than 200 credits(20 RON)\n";
                                            cout <<"Enter the value you wish to deposit(in credits): ";
                                            cin>>depositCredits;
                                            if (depositCredits >= 200) {
                                                isDepositDone = true;
                                                currentPlayer.depositCredits(depositCredits);
                                                cout<<"Please wait...";
                                                this_thread::sleep_for(chrono::seconds(2));
                                                system("clear");
                                                cout<<"❤️ Congratulations, you deposited successfully!"<<endl;
                                                updatePlayerInDatabase(username, currentPlayer.getCredits(),currentPlayer.getAgeVerify(), currentPlayer.getSelfExclusion());
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        system("clear");
                                        break;
                                    }
                                        default: {
                                        system("clear");
                                        cout<<"Enter a valid choice!"<<endl;
                                    }
                                }
                                break;
                            }
                                case 3: {
                                system("clear");
                                cout << "💸 Withdrawal 💸"<<endl;
                                cout <<"You currently have "<<currentPlayer.getCredits()<<"\n[1] Continue with the withdrawal\n[2] Back to menu\nEnter your choice: ";
                                cin >> choiceNumber;
                                switch (choiceNumber) {
                                    case 1: {
                                        int withdrawalCredits;
                                        bool isWithdrawalDone = false;
                                        while (!isWithdrawalDone) {
                                            system("clear");
                                            cout <<"!! READ BEFORE WITHDRAWAL !!\n10 Credits are worth 1 RON\nThe withdrawal value needs to be higher than 500 credits(50 RON)\n";
                                            cout <<"Current credits: "<<currentPlayer.getCredits()<<endl;
                                            cout<<"Enter the value you wish to withdraw(in credits): ";
                                            cin>>withdrawalCredits;
                                            if (withdrawalCredits >= 500 && withdrawalCredits <= currentPlayer.getCredits()) {
                                                isWithdrawalDone = true;
                                                currentPlayer.withdrawCredits(withdrawalCredits);
                                                cout<<"Please wait...";
                                                this_thread::sleep_for(chrono::seconds(2));
                                                system("clear");
                                                cout<<"❤️ Congratulations, you withdrew successfully!"<<endl;
                                                updatePlayerInDatabase(username, currentPlayer.getCredits(),currentPlayer.getAgeVerify(), currentPlayer.getSelfExclusion());
                                            }
                                        }
                                        break;
                                    }
                                        case 2: {
                                        system("clear");
                                        break;
                                    }
                                        default: {
                                        system("clear");
                                        cout<<"Enter a valid choice!"<<endl;
                                    }
                                }
                                break;
                            }
                                case 4: {
                                system("clear");
                                cout<<"🎰 Games 🎰"<<endl;
                                break;
                            }

                            case 5: {
                                if (currentPlayer.getSelfExclusion()) {
                                    deletePlayerInDatabase(currentPlayer);
                                }
                                system("clear");
                                cout<<"Logged out!"<<endl;
                                isLoggedIn = false;
                                break;
                            }
                            default: {
                                system("clear");
                                cout << "Enter a valid choice!" << endl;
                                break;
                            }
                        }
                    }
                } else {
                    system("clear");
                    cout << "❌ Invalid username or password!" << endl;
                }
                break;
            }
            case 2: {
                system("clear");
                cout << "💎 Create account! 💎" << endl;
                cout << "Username: "; cin >> username;

                if (doesUsernameExist(username)) {
                    cout << "⚠️ Error: The username already exists!" << endl;
                } else {
                    cout << "Password: "; cin >> password;

                    ofstream outFile("database.txt", ios::app);
                    if (outFile.is_open()) {
                        outFile << username << " " << password << " " << 500 << " false" <<" "<< "false" << endl;
                        outFile.close();
                        system("clear");
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