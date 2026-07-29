#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Transaction struct 
struct Transaction {
    string type;
    double amount;
    string details;
};

class Account {
private:
    string accNum;
    double balance;
    vector<Transaction> history; 

public:
    Account(string number, double initial) {
        accNum = number;
        balance = initial;
        
        // record initial deposit 
        if (initial > 0) {
            Transaction t;
            t.type = "Deposit";
            t.amount = initial;
            t.details = "Initial Setup";
            history.push_back(t);
        }
    }

    string getAccountNumber() { return accNum; }
    double getBalance() { return balance; }

    void deposit(double amt) {
        // check for negative amounts 
        if (amt <= 0) {
            cout << "Invalid deposit amount." << endl;
            return;
        }
        balance += amt;
        
        Transaction t;
        t.type = "Deposit";
        t.amount = amt;
        t.details = "Cash Deposit";
        history.push_back(t);
        
        cout << "Success: Deposited " << amt << endl;
    }

    void withdraw(double amt) {
        if (amt <= 0) {
            cout << "Invalid withdrawal amount." << endl;
            return;
        }
        if (amt > balance) {
            cout << "Error: Insufficient funds." << endl;
            return;
        }
        balance -= amt;
        
        Transaction t;
        t.type = "Withdrawal";
        t.amount = amt;
        t.details = "ATM withdrawal";
        history.push_back(t);
        
        cout << "Success: Withdrew " << amt << endl;
    }

    void transfer(Account &toAcc, double amt) {
        
        if (amt <= 0 || amt > balance) {
            cout << "Transfer failed. Check balance or amount." << endl;
            return;
        }

        balance -= amt;
        toAcc.balance += amt;

        // record outgoing
        Transaction out;
        out.type = "Transfer Out";
        out.amount = amt;
        out.details = "Sent to " + toAcc.getAccountNumber();
        history.push_back(out);
        
        // record incoming on other account
        Transaction in;
        in.type = "Transfer In";
        in.amount = amt;
        in.details = "Received from " + accNum;
        toAcc.history.push_back(in);

        cout << "Transferred " << amt << " to " << toAcc.getAccountNumber() << endl;
    }

    void printStatement() {
        cout << "\n--- Statement: " << accNum << " ---" << endl;
        cout << "Current Balance: " << balance << endl;
        
        if (history.empty()) {
            cout << "No transaction history." << endl;
            return;
        }

        // print all transactions
        for (int i = 0; i < history.size(); i++) {
            cout << " [" << i + 1 << "] ";
            cout << history[i].type << " | Amt: " << history[i].amount 
                 << " | Ref: " << history[i].details << endl;
        }
    }
};

// customer class - holds accounts and personal info
class Customer {
private:
    string id;
    string name;

public:
    vector<Account> accounts; // making this public so i can access it easily

    Customer(string custId, string custName) {
        id = custId;
        name = custName;
    }

    string getID() { return id; }
    string getName() { return name; }

    void showData() {
        cout << "\nClient: " << name << " (ID: " << id << ")" << endl;
        if (accounts.empty()) {
            cout << "No open accounts." << endl;
            return;
        }
        for (int i = 0; i < accounts.size(); i++) {
            cout << "  Acc: " << accounts[i].getAccountNumber() 
                 << " | Bal: " << accounts[i].getBalance() << endl;
        }
    }
};

// helper function 
Account* findAccount(vector<Customer>& clients, string accNo) {
    for (int i = 0; i < clients.size(); i++) {
        for (int j = 0; j < clients[i].accounts.size(); j++) {
            if (clients[i].accounts[j].getAccountNumber() == accNo) {
                return &clients[i].accounts[j];
            }
        }
    }
    return NULL;
}

int main() {
    vector<Customer> clients;
    int choice;
    
    cout << "=== BANKING APP ===" << endl;


    while (true) {
        cout << "\nMenu:\n1. New Customer\n2. Open Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Statement\n7. List Clients\n8. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        // exit early if they choose 8
        if (choice == 8) {
            cout << "Goodbye!" << endl;
            break;
        }

        switch (choice) {
            case 1: {
                string id, name;
                cout << "ID: "; 
                cin >> id;
                cin.ignore(); // need this to clear buffer
                cout << "Name: "; 
                getline(cin, name);

                Customer newCust(id, name);
                clients.push_back(newCust);
                cout << "Customer added." << endl;
                break;
            }
            case 2: {
                string id, accNo;
                double init;
                cout << "Customer ID: "; 
                cin >> id;

                // find the customer
                int found = -1;
                for (int i = 0; i < clients.size(); i++) {
                    if (clients[i].getID() == id) {
                        found = i;
                        break;
                    }
                }

                if (found == -1) {
                    cout << "Customer not found." << endl;
                } else {
                    cout << "Account Number: "; 
                    cin >> accNo;
                    cout << "Initial Deposit: "; 
                    cin >> init;
                    
                    Account newAcc(accNo, init);
                    clients[found].accounts.push_back(newAcc);
                    cout << "Account created." << endl;
                }
                break;
            }
            case 3: {
                string accNo; 
                double amt;
                cout << "Account #: "; 
                cin >> accNo;
                cout << "Amount: "; 
                cin >> amt;

                Account* acc = findAccount(clients, accNo);
                if (acc == NULL) {
                    cout << "Account not found." << endl;
                } else {
                    acc->deposit(amt);
                }
                break;
            }
            case 4: {
                string accNo; 
                double amt;
                cout << "Account #: "; 
                cin >> accNo;
                cout << "Amount: "; 
                cin >> amt;

                Account* acc = findAccount(clients, accNo);
                if (acc == NULL) {
                    cout << "Account not found." << endl;
                } else {
                    acc->withdraw(amt);
                }
                break;
            }
            case 5: {
                string fromAcc, toAcc; 
                double amt;
                cout << "From Account #: "; 
                cin >> fromAcc;
                cout << "To Account #: "; 
                cin >> toAcc;
                cout << "Amount: "; 
                cin >> amt;

                Account* src = findAccount(clients, fromAcc);
                Account* dest = findAccount(clients, toAcc);

                if (src == NULL || dest == NULL) {
                    cout << "One or both accounts missing." << endl;
                } else if (fromAcc == toAcc) {
                    cout << "Cannot transfer to the same account." << endl;
                } else {
                    src->transfer(*dest, amt);
                }
                break;
            }
            case 6: {
                string accNo;
                cout << "Account #: "; 
                cin >> accNo;

                Account* acc = findAccount(clients, accNo);
                if (acc == NULL) {
                    cout << "Account not found." << endl;
                } else {
                    acc->printStatement();
                }
                break;
            }
            case 7: {
                if (clients.empty()) {
                    cout << "No records." << endl;
                } else {
                    for (int i = 0; i < clients.size(); i++) {
                        clients[i].showData();
                    }
                }
                break;
            }
            default:
                cout << "Invalid selection." << endl;
        }
    }
    return 0;
}
