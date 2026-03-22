#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstring>
#include <vector>
#include <ctime>

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
int findMultiplier(char symbol) {
    if (symbol == 'J')
        return 2;
    if (symbol == 'Q')
        return 5;
    if (symbol == 'K')
        return 10;
    if (symbol == 'A')
        return 25;
    return 0;
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
    friend istream& operator>>(istream& in, Player& obj);
    friend ostream& operator<<(ostream& out, Player& obj);
    ~Player();
    void setAgeVerified(bool ageVerified);
    void setSelfExclusion(bool selfExclusion);
    int getCredits() const;
    bool getAgeVerify() const;
    bool getSelfExclusion() const;
    void depositCredits(int credits);
    void withdrawCredits(int credits);
    void betCredits(int credits);
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

void Player::betCredits(int credits) {
    this->credits = this->credits-credits;
}

char* Player::getUsername() const {
    return this->username;
}
class Reel {
private:
    char topSymbol;
    char middleSymbol;
    char bottomSymbol;
    char* possibleSymbols;
    int numSymbols;
public:
    Reel();
    ~Reel();
    Reel(const Reel& obj);
    Reel& operator=(const Reel& obj);
    char showTopSymbol();
    char showMiddleSymbol();
    char showBottomSymbol();
    void roll();
};

Reel::Reel() {
    this->numSymbols = 15;
    this->possibleSymbols = new char[this->numSymbols + 1];
    strcpy(this->possibleSymbols, "JJJJJQQQQKKKAA");
    this->possibleSymbols[14] = '$';
    this->possibleSymbols[15] = '\0';
}
char Reel::showTopSymbol() {
    return this->topSymbol;
}
char Reel::showMiddleSymbol() {
    return this->middleSymbol;
}
char Reel::showBottomSymbol() {
    return this->bottomSymbol;
}

void Reel::roll() {
    int randomIndex = rand() % this->numSymbols;
    this->topSymbol = this->possibleSymbols[randomIndex];
    this->middleSymbol = this->possibleSymbols[(randomIndex + 1) % this->numSymbols];
    this->bottomSymbol = this->possibleSymbols[(randomIndex + 2) % this->numSymbols];
}
Reel::Reel(const Reel& obj) {
    this->numSymbols = obj.numSymbols;
    this->possibleSymbols = new char[this->numSymbols + 1];
    strcpy(this->possibleSymbols, obj.possibleSymbols);
    this->topSymbol = obj.topSymbol;
    this->middleSymbol = obj.middleSymbol;
    this->bottomSymbol = obj.bottomSymbol;
}

Reel& Reel::operator=(const Reel& obj) {
    if (this == &obj)
        return *this;
    delete[] this->possibleSymbols;
    this->numSymbols = obj.numSymbols;
    this->possibleSymbols = new char[this->numSymbols + 1];
    strcpy(this->possibleSymbols, obj.possibleSymbols);
    this->topSymbol = obj.topSymbol;
    this->middleSymbol = obj.middleSymbol;
    this->bottomSymbol = obj.bottomSymbol;
    return *this;
}
Reel::~Reel() {
    delete [] possibleSymbols;
}
class CasinoSession {
private:
    string lastGamePlayed;
    float totalWagered;
    float totalWon;
    bool isActive;
public:
    CasinoSession();
    void setTotalWagered(float creditsWagered);
    void setTotalWon(float creditsWon);
    void getLastGamePlayed(char lastGame[50]);
    friend ostream& operator<<(ostream& out,CasinoSession& obj);
    void setSessionStatus(bool sessionStatus);
    bool isSessionActive() const;
    ~CasinoSession();
};
void CasinoSession::setSessionStatus(bool sessionStatus) {
    this->isActive = sessionStatus;
}

bool CasinoSession::isSessionActive() const {
    return this->isActive;
}

CasinoSession::CasinoSession() {
    this->lastGamePlayed = "No game played yet";
    this->totalWagered = 0;
    this->totalWon = 0;
    this->isActive = false;
}
void CasinoSession::setTotalWagered(float creditsWagered) {
    this->totalWagered = this->totalWagered + creditsWagered;
}
void CasinoSession::setTotalWon(float creditsWon) {
    this->totalWon = this->totalWon + creditsWon;
}
void CasinoSession::getLastGamePlayed(char lastGame[50]) {
    this->lastGamePlayed = lastGame;
}
ostream& operator<<(ostream& out, CasinoSession& obj) {
    out<<"Last game played: "<<obj.lastGamePlayed<<endl;
    out<<"Total wagered: "<<obj.totalWagered<<endl;
    out<<"Total won: "<<obj.totalWon<<endl;
    return out;
}

CasinoSession::~CasinoSession() {
}

class SlotMachine {
private:
    Reel reelList[3];
    const int machineID;
    static int noSlots;
    char* slotName;
    float jackpot;
    int* betHistory;
    int historySize;
    char specialSymbol;
public:
    SlotMachine();
    SlotMachine(char* slotName,float jackpot,int *betHistory, int historySize,char specialSymbol);
    SlotMachine(const SlotMachine& obj);
    SlotMachine& operator=(const SlotMachine& obj);
    friend ifstream& operator>>(ifstream& in, SlotMachine& obj);
    friend ostream& operator<<(ostream& out,SlotMachine& obj);
    char* getSlotName() const;
    ~SlotMachine();
    void startSlotMachine(Player& currentPlayer,CasinoSession& currentSession);
    void symbolTranslate(char symbol) {
        if (symbol == '$') {
            if (this->specialSymbol == '!') {
                cout<<"🔥";
            }
            else
                if (this->specialSymbol == '^') {
                    cout<<"👑";
                }
                else
                    if (this->specialSymbol == '*') {
                        cout<<"💎";
                    }
        }
        else
            if (symbol == 'J') {
                cout<<"🍒";
            }
        else
            if (symbol == 'Q') {
                cout<<"🍊";
            }
        else
            if (symbol == 'K') {
                cout<<"🍉";
            }
        else
            if (symbol == 'A') {
                cout<<"❤️";
            }
    }
};
int SlotMachine::noSlots = 0;
SlotMachine::SlotMachine():machineID(++noSlots) {
    this->slotName = strcpy(new char[4], "N\A");
    this->jackpot = 0;
    this->betHistory = nullptr;
    this->historySize = 0;
    this->specialSymbol = '-';
}
SlotMachine::SlotMachine(char* slotName,float jackpot, int* betHistory, int historySize,char specialSymbol):machineID(++noSlots) {
    this->slotName = strcpy(new char[strlen(slotName)+1], slotName);
    this->jackpot = jackpot;
    this->betHistory = new int[historySize];
    for (int i=0;i < historySize ;i++) {
        this->betHistory[i] = betHistory[i];
    }
    this->historySize = historySize;
    this->specialSymbol = specialSymbol;
}
SlotMachine::SlotMachine(const SlotMachine& obj):machineID(++noSlots) {
    this->jackpot = obj.jackpot;
    this->slotName = strcpy(new char[strlen(obj.slotName)+1], obj.slotName);
    this->betHistory = new int[obj.historySize];
    for (int i=0; i < obj.historySize ; i++) {
        this->betHistory[i] = obj.betHistory[i];
    }
    this->historySize = obj.historySize;
    this->specialSymbol = obj.specialSymbol;
}
SlotMachine& SlotMachine::operator=(const SlotMachine& obj) {
      if (this == &obj) {
          return *this;
      }
    else {
        delete [] this->slotName;
        this->slotName = strcpy(new char[strlen(obj.slotName)+1], obj.slotName);
        this->jackpot = obj.jackpot;
        delete [] this->betHistory;
        this->betHistory = new int[obj.historySize];
        for (int i=0; i < obj.historySize ; i++) {
            this->betHistory[i] = obj.betHistory[i];
        }
        this->historySize = obj.historySize;
        this->specialSymbol = obj.specialSymbol;
        return *this;
    }
};
SlotMachine::~SlotMachine() {
    delete [] this->slotName;
    delete [] this->betHistory;
}
ostream& operator<<(ostream& out, SlotMachine& obj) {
    out<<obj.slotName<<" | Current jackpot: "<<obj.jackpot<<endl;
    return out;
}
ifstream& operator>>(ifstream& in, SlotMachine& obj) {
    char tempName[256];
    if (in >> tempName >> obj.jackpot >> obj.specialSymbol) {
        delete [] obj.slotName;
        obj.slotName = strcpy(new char[strlen(tempName)+1], tempName);
    }

    return in;
}

char* SlotMachine::getSlotName() const{
    return this->slotName;
}

class GamesMenu {
    private:
    vector<SlotMachine*> slotMachines;
    void printSlotMachines() const;
    void addSlotMachinesFromDataBase();
    public:
    GamesMenu();
    ~GamesMenu();
    void run(Player& currentPlayer);
};
GamesMenu::~GamesMenu() {
    for (size_t i=0; i < slotMachines.size(); i++) {
        delete slotMachines[i];
    }
    slotMachines.clear();
}
void GamesMenu::printSlotMachines() const{
    if (slotMachines.empty()) {
        cout << "‼️ Games Menu: No slots available." << endl;
        return;
    }
    for (size_t i=0; i < slotMachines.size(); i++) {
        cout<<"["<<i<<"] "<<slotMachines[i]->getSlotName()<<endl;
    }
    cout<<"["<<slotMachines.size()<<"] Exit"<<endl;
}
void GamesMenu::addSlotMachinesFromDataBase() {
    ifstream dataBase("database_slotmachines.txt");
    SlotMachine obj;
    while (dataBase >> obj) {
        slotMachines.push_back(new SlotMachine(obj));
    }
    dataBase.close();
}
GamesMenu::GamesMenu() {
    addSlotMachinesFromDataBase();
}
void GamesMenu::run(Player& currentPlayer) {
    CasinoSession casinoSession;
    while (true) {
        cout<<"[1] List current games\n[2] Jackpots\n[3] Player stats this session\n[4] Exit\nEnter your choice: ";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1: {
                system("clear");
                this->printSlotMachines();
                cout<<"Enter your choice: ";
                cin>>choice;
                if (choice == slotMachines.size()) {
                    cout<<"Leaving..."<<endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    system("clear");
                }
                if (choice < 0 || choice > slotMachines.size()) {
                    system("clear");
                    cout << "Enter a valid choice! " << endl;
                }
                else {
                    slotMachines[choice]->startSlotMachine(currentPlayer,casinoSession);
                    break;
                }
            }
                case 2: {
                system("clear");
                for (size_t i=0; i < slotMachines.size(); i++)
                    cout<<*slotMachines[i]<<endl;
                break;
            }
            case 3: {
                system("clear");
                cout<<casinoSession;
                break;
            }
                case 4: {
                system("clear");
                return;
            }
                default: {
                system("clear");
                cout<<"Enter a valid choice! " << endl;
            }
        }
    }
}

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
ostream& operator<<(ostream& out,Player& obj) {
    out<<"Player: "<<obj.username<<" | "<<"Credits: "<<obj.credits<<endl;
    return out;
}
istream& operator>>(istream& in,Player& obj) {
    char tempUsername[256];
    char tempPassword[256];
    in.ignore();
    cout<<"Enter username: ";
    in.getline(tempUsername,256);
    if (doesUsernameExist(tempUsername)) {
        system("clear");
        cout << "⚠️ Error: The username already exists!" << endl;
        return in;
    } else {
        cout<<"Enter password: ";
        in.getline(tempPassword,256);
    }
    delete[] obj.username;
    delete[] obj.password;
    obj.username = strcpy(new char[strlen(tempUsername)+1],tempUsername);
    obj.password = strcpy(new char[strlen(tempPassword)+1],tempPassword);
    obj.credits = 500;
    obj.ageVerified = false;
    obj.selfExclusion = false;
    ofstream outFile("database.txt", ios::app);
    if (outFile.is_open()) {
        outFile << obj.username << " " << obj.password << " " << 500 << " false" <<" "<< "false" << endl;
        outFile.close();
        system("clear");
        cout << "✅ Account created! You received 500 starting credits." << endl;
    }
    return in;
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
void updateSlotsDataBase(const char* targetUsername, int newJackpot) {
    ifstream inFile("database_slotmachines.txt");
    ofstream tempFile("tempdatabase_slotmachines.txt");
    string line,n,s;
    int j;
    while (getline(inFile, line)) {
        stringstream ss(line);
        if (ss >> n >> j >> s) {
            if (n == targetUsername) {
                tempFile << n <<" "<< newJackpot<<" "<< s << endl;
            }
            else
                tempFile<<line<<endl;
        }
    }
    inFile.close();
    tempFile.close();
    remove("database_slotmachines.txt");
    rename("tempdatabase_slotmachines.txt", "database_slotmachines.txt");
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
void SlotMachine::startSlotMachine(Player &currentPlayer, CasinoSession &currentSession) {
    currentSession.getLastGamePlayed(this->getSlotName());
    currentSession.setSessionStatus(true);
    system("clear");
    cout<<"Please wait..."<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
    int currentBet=10;
    int choice;
    while (currentSession.isSessionActive()) {
        cout<<*this<<endl;
        cout<<currentPlayer<<endl;
        cout<<"[1] Spin for "<<currentBet<<endl;
        cout<<"[2] Change bet" <<endl;
        cout<<"[3] Exit"<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                if (currentPlayer.getCredits()>=currentBet) {
                    system("clear");
                    cout<<"GOOD LUCK!"<<endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    currentSession.setTotalWagered(currentBet);
                    currentPlayer.betCredits(currentBet);
                    this->jackpot = this->jackpot + currentBet;
                    updateSlotsDataBase(this->slotName,this->jackpot);
                    updatePlayerInDatabase(currentPlayer.getUsername(),currentPlayer.getCredits(),currentPlayer.getAgeVerify(),currentPlayer.getSelfExclusion());
                    reelList[0].roll();
                    reelList[1].roll();
                    reelList[2].roll();
                    cout<<"[ ";
                    symbolTranslate(reelList[0].showTopSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[1].showTopSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[2].showTopSymbol());
                    cout<<" ]"<<endl;
                    cout<<"[ ";
                    symbolTranslate(reelList[0].showMiddleSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[1].showMiddleSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[2].showMiddleSymbol());
                    cout<<" ]"<<endl;
                    cout<<"[ ";
                    symbolTranslate(reelList[0].showBottomSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[1].showBottomSymbol());
                    cout<<" ] ";
                    cout<<"[ ";
                    symbolTranslate(reelList[2].showBottomSymbol());
                    cout<<" ]"<<endl;
                    int totalWins=0;
                    char paylines[3][3] = {
                        reelList[0].showTopSymbol(), reelList[1].showTopSymbol(), reelList[2].showTopSymbol(),
                        reelList[0].showMiddleSymbol(),reelList[1].showMiddleSymbol(), reelList[2].showMiddleSymbol(),
                        reelList[0].showBottomSymbol(),reelList[1].showBottomSymbol(), reelList[2].showBottomSymbol(),
                    };
                    int nrJackpots=0;
                    for (int i=0;i<3;i++) {
                        for (int j=0;j<3;j++) {
                            if (paylines[i][j]=='$') {
                                nrJackpots++;
                            }
                        }
                    }
                    if (nrJackpots==3) {
                        system("clear");
                        cout<<endl;
                        cout<<"========================================="<<endl;
                        cout<<"🚨🚨 JACKPOT WINNER 🚨🚨 YOU'VE WON "<<this->jackpot<<endl;
                        cout<<"========================================="<<endl;
                        totalWins += this->jackpot;
                        this->jackpot = 0;
                        updateSlotsDataBase(this->slotName,this->jackpot);
                        updatePlayerInDatabase(currentPlayer.getUsername(),currentPlayer.getCredits(),currentPlayer.getAgeVerify(),currentPlayer.getSelfExclusion());
                    }
                    for (int i=0;i<3;i++) {
                        if (paylines[i][0]==paylines[i][1] && paylines[i][1]==paylines[i][2]) {
                            totalWins=totalWins + currentBet*findMultiplier(paylines[i][0]);
                        }
                    }
                    if (paylines[0][0]==paylines[1][1] && paylines[1][1]==paylines[2][2]) {
                        totalWins=totalWins + currentBet*findMultiplier(paylines[1][1]);
                    }
                    if (paylines[0][2]==paylines[1][1] && paylines[1][1]==paylines[2][0]) {
                        totalWins=totalWins + currentBet*findMultiplier(paylines[1][1]);
                    }
                    if (totalWins>0) {
                        cout<<"========================================="<<endl;
                        cout<<"GAME ALERT: You've won "<<totalWins<<endl;
                        cout<<"========================================="<<endl;
                        currentSession.setTotalWon(totalWins);
                        currentPlayer.depositCredits(totalWins);
                        updatePlayerInDatabase(currentPlayer.getUsername(),currentPlayer.getCredits(),currentPlayer.getAgeVerify(),currentPlayer.getSelfExclusion());
                    }
                }
                break;
            }
            case 2: {
                system("clear");
                cout<<"==========================================================="<<endl;
                cout<<"10       50      100     200     400     800     1000"<<endl;
                cout<<"==========================================================="<<endl;
                int chooseBet;
                cout<<"Choose Bet: ";
                cin>>chooseBet;
                switch (chooseBet) {
                    case 10: {
                        currentBet=10;
                        break;
                    }
                        case 50: {
                        currentBet=50;
                        break;
                    }
                        case 100: {
                        currentBet=100;
                        break;
                    }
                        case 200: {
                        currentBet=200;
                        break;
                    }
                        case 400: {
                        currentBet=400;
                        break;
                    }
                        case 800: {
                        currentBet=800;
                        break;
                    }
                        case 1000: {
                        currentBet=1000;
                        break;
                    }
                        default: {
                        system("clear");
                        cout<<"Choose a valid bet!"<<endl;
                    }
                }
                break;
            }
                case 3: {
                currentSession.setSessionStatus(false);
                system("clear");
                break;
            }
                default: {
                system("clear");
                cout<<"Enter a valid choice!"<<endl;
            }
        }
    }
}

int main() {
    srand(time(0));
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
                                if (currentPlayer.getSelfExclusion()) {
                                    cout<<"‼️ Warning: You are self exclusion . Your account will be deleted after logging out !";
                                }
                                else {
                                    GamesMenu menu;
                                    menu.run(currentPlayer);
                                }
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
                    cout << "\n💎 Create account! 💎" << endl;
                    Player contNou;
                    cin >> contNou;
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