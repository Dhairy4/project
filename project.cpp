#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


void addAccount() {
    string accountNumber, name, address;
    double balance;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cin.ignore();  

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter address: ";
    getline(cin, address);

    cout << "Enter initial balance: ";
    cin >> balance;

    ofstream file;
    file.open(accountNumber + ".txt", ios::app);
    if (file.is_open()) {
        file << "Account Number: " << accountNumber << endl;
        file << "Name: " << name << endl;
        file << "Address: " << address << endl;
        file << "Balance: " << fixed << setprecision(2) << balance << endl;
        file.close();
        cout << "Account created successfully." << endl;
    } else {
        cout << "Error creating account." << endl;
    }
}


void viewAccount() {
    string accountNumber;
    cout << "Enter account number to view details: ";
    cin >> accountNumber;

    ifstream file;
    file.open(accountNumber + ".txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Account not found." << endl;
    }
}


void transact() {
    string accountNumber;
    double amount;
    char type;

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter amount: ";
    cin >> amount;

    cout << "Type of transaction (D for deposit, W for withdraw): ";
    cin >> type;

    ifstream fileIn(accountNumber + ".txt");
    ofstream fileOut("temp.txt");

    if (fileIn.is_open() && fileOut.is_open()) {
        string line;
        double balance = 0.0;
        while (getline(fileIn, line)) {
            if (line.find("Balance:") != string::npos) {
                balance = stod(line.substr(line.find(':') + 1));
            }
            fileOut << line << endl;
        }
        fileIn.close();
        fileOut.close();

        if (type == 'D' || type == 'd') {
            balance += amount;
        } else if (type == 'W' || type == 'w') {
            balance -= amount;
        } else {
            cout << "Invalid transaction type." << endl;
            return;
        }

        remove((accountNumber + ".txt").c_str());
        rename("temp.txt", (accountNumber + ".txt").c_str());

        ofstream file;
        file.open(accountNumber + ".txt", ios::app);
        if (file.is_open()) {
            file << "Balance: " << fixed << setprecision(2) << balance << endl;
            file.close();
            cout << "Transaction successful." << endl;
        } else {
            cout << "Error updating account." << endl;
        }
    } else {
        cout << "Account not found." << endl;
    }
}


int main() {
    int choice;
    do {
        cout << "\nBanking Record Management System\n";
        cout << "1. Add New Account\n";
        cout << "2. View Account Details\n";
        cout << "3. Deposit/Withdraw\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                transact();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
