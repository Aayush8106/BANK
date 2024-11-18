#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

struct Account {
    string firstName;
    string middleName;
    string surname;
    string phoneNumber;
    string panNumber;
    string address;
    long long accountNumber;
    int pin;
};

Account a2[100]; 
int accountCount = 0; 

void createAccount() {
    if (accountCount < 100) {
        Account a1;
        cout << "Enter first name: ";
        cin >> a1.firstName;
        cout << "Enter middle name: ";
        cin >> a1.middleName;
        cout << "Enter surname: ";
        cin >> a1.surname;
        cout << "Phone number: ";
        cin >> a1.phoneNumber;
        while (a1.phoneNumber.size() != 10) {
            cout << "Invalid phone number....Try again: ";
            cin >> a1.phoneNumber;
        }
        cout << "P.A.N number: ";
        cin >> a1.panNumber;
        while (a1.panNumber.size() != 10) {
            cout << "Invalid P.A.N number....Try again: ";
            cin >> a1.panNumber;
        }
        cin.ignore();
        cout << "Address: ";
        getline(cin, a1.address);
        cout << "Generate a 4-digit pin: ";
        cin >> a1.pin;
        while (a1.pin < 1000 || a1.pin > 9999) {
            cout << "Invalid pin.... try again: ";
            cin >> a1.pin;
        }
        srand(time(0)); 
        long long min = 1000000000LL; 
        long long max = 9999999999LL; 
        a1.accountNumber = min + (rand() % (max - min + 1)); 
        cout << "Account Number: " << a1.accountNumber << endl; 
        time_t x = time(0);
        cout << endl << "Creation time: " << ctime(&x);
        
        // Copy data to a2 and increment accountCount
        a2[accountCount] = a1;
        accountCount++;
        
        cout << "Account created successfully!" << endl;
    } else {
        cout << "Maximum account limit reached!" << endl;
    }
}


void cbalance(int bal) {
    cout << "Current Balance: " << bal << endl;
}

void deposit(int &bal) {
    int dep;
    cout << "Enter the deposit amount: ";
    cin >> dep;
    bal += dep;
    cout << "Balance: " << bal << endl;
}

void withdraw(int &bal) {
    int with;
    cout << "Enter the withdrawal amount: ";
    cin >> with;
    while (with > bal) {
        cout << "Insufficient Balance....try again: ";
        cin >> with;
    }
    bal -= with;
    cout << "Balance: " << bal << endl;
}

void changePin(int &pin) {
    int i, j;
    cout << "Enter existing pin: ";
    cin >> i;
    if (i == pin) {
        cout << "Enter new pin: ";
        cin >> j;
        cout << "Confirm pin: ";
        cin >> i;
        while (i != j) {
            cout << "Pins do not match. Try again." << endl;
            cout << "Enter new pin: ";
            cin >> j;
            cout << "Confirm pin: ";
            cin >> i;
        }
        pin = j;
    } else {
        cout << "Incorrect pin!!!" << endl;
        return;
    }
}

void details() {
    long long accountNum;
    int pin;
    cout << "Enter your account number: ";
    cin >> accountNum;
    cout << "Enter your 4-digit pin: ";
    cin >> pin;

    bool found = false;
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (a2[i].accountNumber == accountNum && a2[i].pin == pin) {
            found = true;
            index = i;
            break;
        }
    }

    if (found) {
        int bal = 0; // Initialize balance
        int accountPin = a2[index].pin;
        int c;
        cout << endl << "Account Found!" << endl;
        do {
            
            cout << "Your Account: \n";
            cout << "1. Check balance\n";
            cout << "2. Deposit money\n";
            cout << "3. Withdraw money\n ";
            cout <<"4. Change pin\n ";
            cout <<"5. Back: ";
            cin >> c;

            switch (c) {
                case 1:
                    cbalance(bal);
                    break;
                case 2:
                    deposit(bal);
                    break;
                case 3:
                    withdraw(bal);
                    break;
                case 4:
                    changePin(accountPin);
                    a2[index].pin = accountPin;
                    break;
                case 5:
                    return;
            }
        } while (c!=5);
    } else {
        cout << "Account not found!" << endl;
    }
}


void exitProgram() {
    cout << "Exiting program. Goodbye!" << endl;
}

int main() {
    int choice;
    do {
        cout<<endl << "1. Create Account" << endl;
        cout << "2. View Account Details" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                details();
                break;
            case 3:
                exitProgram();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}