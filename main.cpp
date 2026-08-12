#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    double balance;

    string transactions[50];
    int transactionCount;

    void input()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        transactionCount = 0;

        transactions[transactionCount] = "Account Created";
        transactionCount++;
    }

    void display()
    {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << name;
        cout << "\nBalance: Rs. " << balance << endl;
    }

    void deposit()
    {
        double amount;

        cout << "\nEnter Deposit Amount: ";
        cin >> amount;

        if(amount > 0)
        {
            balance += amount;

            if(transactionCount < 50)
            {
                transactions[transactionCount] =
                    "Deposited Rs. " + to_string(amount);
                transactionCount++;
            }

            cout << "Amount Deposited Successfully!\n";
            cout << "Updated Balance: Rs. " << balance << endl;
        }
        else
        {
            cout << "Invalid Amount!\n";
        }
    }

    void withdraw()
    {
        double amount;

        cout << "\nEnter Withdrawal Amount: ";
        cin >> amount;

        if(amount <= 0)
        {
            cout << "Invalid Amount!\n";
        }
        else if(amount > balance)
        {
            cout << "Insufficient Balance!\n";
        }
        else
        {
            balance -= amount;

            if(transactionCount < 50)
            {
                transactions[transactionCount] =
                    "Withdrawn Rs. " + to_string(amount);
                transactionCount++;
            }

            cout << "Amount Withdrawn Successfully!\n";
            cout << "Updated Balance: Rs. " << balance << endl;
        }
    }

    void checkBalance()
    {
        cout << "\nCurrent Balance: Rs. " << balance << endl;
    }

    void showTransactions()
    {
        cout << "\n===== Transaction History =====\n";

        if(transactionCount == 0)
        {
            cout << "No Transactions Available!\n";
        }
        else
        {
            for(int i = 0; i < transactionCount; i++)
            {
                cout << i + 1 << ". " << transactions[i] << endl;
            }
        }
    }
};


// Search Account
void searchAccount(Account accounts[], int n)
{
    int searchNumber;

    cout << "\nEnter Account Number to Search: ";
    cin >> searchNumber;

    bool found = false;

    for(int i = 0; i < n; i++)
    {
        if(accounts[i].accountNumber == searchNumber)
        {
            cout << "\nAccount Found!\n";
            accounts[i].display();

            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}


// Duplicate Account Number Check
bool isDuplicateAccountNumber(Account accounts[], int n, int number)
{
    for(int i = 0; i < n; i++)
    {
        if(accounts[i].accountNumber == number)
        {
            return true;
        }
    }

    return false;
}

void deleteAccount(Account accounts[], int &n)
{
    int deleteNumber;

    cout << "\nEnter Account Number to Delete: ";
    cin >> deleteNumber;

    bool found = false;

    for(int i = 0; i < n; i++)
    {
        if(accounts[i].accountNumber == deleteNumber)
        {
            for(int j = i; j < n - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }

            n--;

            cout << "\nAccount Deleted Successfully!\n";

            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void updateAccount(Account accounts[], int n)
{
    int updateNumber;

    cout << "\nEnter Account Number to Update: ";
    cin >> updateNumber;

    bool found = false;

    for(int i = 0; i < n; i++)
    {
        if(accounts[i].accountNumber == updateNumber)
        {
            cout << "\nAccount Found!\n";

            cin.ignore();

            cout << "Enter New Account Holder Name: ";
            getline(cin, accounts[i].name);

            cout << "\nAccount Updated Successfully!\n";

            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void saveToFile(Account accounts[], int n)
{
    ofstream file("accounts.txt");

    for(int i = 0; i < n; i++)
    {
        file << accounts[i].accountNumber << endl;
        file << accounts[i].name << endl;
        file << accounts[i].balance << endl;
        file << accounts[i].transactionCount << endl;

        for(int j = 0; j < accounts[i].transactionCount; j++)
        {
            file << accounts[i].transactions[j] << endl;
        }
    }

    file.close();

    cout << "\nAccounts Saved Successfully!\n";
}

void loadFromFile(Account accounts[], int &n)
{
    ifstream file("accounts.txt");

    if(!file)
    {
        return;
    }

    n = 0;

    while(n < 100 && file >> accounts[n].accountNumber)
    {
        file.ignore();

        getline(file, accounts[n].name);

        file >> accounts[n].balance;
        file >> accounts[n].transactionCount;

        file.ignore();

        for(int j = 0; j < accounts[n].transactionCount; j++)
        {
            getline(file, accounts[n].transactions[j]);
        }

        n++;
    }

    file.close();

    cout << "\nAccounts Loaded Successfully!\n";
}

int main()
{
    Account accounts[100];

    int n = 0;
    int choice;

    // Load saved accounts
    loadFromFile(accounts, n);

    cout << "========== Bank Management System ==========\n";

    do
    {
        cout << "\n\n========== MENU ==========";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Check Balance";
        cout << "\n7. Transaction History";
        cout << "\n8. Delete Account";
        cout << "\n9. Update Account";
        cout << "\n10. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                if(n >= 100)
                {
                    cout << "\nAccount limit reached!\n";
                    break;
                }

                int accountNumber;

                cout << "\nEnter Account Number: ";
                cin >> accountNumber;

                if(isDuplicateAccountNumber(accounts, n, accountNumber))
                {
                    cout << "\nAccount Number already exists!\n";
                    cout << "Please use another Account Number.\n";
                    break;
                }

                accounts[n].accountNumber = accountNumber;

                cin.ignore();

                cout << "Enter Account Holder Name: ";
                getline(cin, accounts[n].name);

                cout << "Enter Initial Balance: ";
                cin >> accounts[n].balance;

                if(accounts[n].balance < 0)
                {
                    cout << "\nInvalid Initial Balance!\n";
                    break;
                }

                accounts[n].transactionCount = 0;

                if(accounts[n].balance > 0)
                {
                    accounts[n].transactions[accounts[n].transactionCount] =
                        "Account Created with Initial Balance Rs. " +
                        to_string(accounts[n].balance);

                    accounts[n].transactionCount++;
                }
                else
                {
                    accounts[n].transactions[accounts[n].transactionCount] =
                        "Account Created";

                    accounts[n].transactionCount++;
                }

                n++;

                saveToFile(accounts, n);

                cout << "\nAccount Created Successfully!\n";

                break;
            }

            case 2:
            {
                if(n == 0)
                {
                    cout << "\nNo Accounts Available!\n";
                }
                else
                {
                    cout << "\n===== All Accounts =====\n";

                    for(int i = 0; i < n; i++)
                    {
                        accounts[i].display();
                    }
                }

                break;
            }

            case 3:
            {
                searchAccount(accounts, n);
                break;
            }

            case 4:
            {
                int accountNumber;
                bool found = false;

                cout << "\nEnter Account Number: ";
                cin >> accountNumber;

                for(int i = 0; i < n; i++)
                {
                    if(accounts[i].accountNumber == accountNumber)
                    {
                        accounts[i].deposit();

                        saveToFile(accounts, n);

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nAccount Not Found!\n";
                }

                break;
            }

            case 5:
            {
                int accountNumber;
                bool found = false;

                cout << "\nEnter Account Number: ";
                cin >> accountNumber;

                for(int i = 0; i < n; i++)
                {
                    if(accounts[i].accountNumber == accountNumber)
                    {
                        accounts[i].withdraw();

                        saveToFile(accounts, n);

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nAccount Not Found!\n";
                }

                break;
            }

            case 6:
            {
                int accountNumber;
                bool found = false;

                cout << "\nEnter Account Number: ";
                cin >> accountNumber;

                for(int i = 0; i < n; i++)
                {
                    if(accounts[i].accountNumber == accountNumber)
                    {
                        accounts[i].checkBalance();

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nAccount Not Found!\n";
                }

                break;
            }

            case 7:
            {
                int accountNumber;
                bool found = false;

                cout << "\nEnter Account Number: ";
                cin >> accountNumber;

                for(int i = 0; i < n; i++)
                {
                    if(accounts[i].accountNumber == accountNumber)
                    {
                        accounts[i].showTransactions();

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nAccount Not Found!\n";
                }

                break;
            }

            case 8:
            {
                deleteAccount(accounts, n);

                saveToFile(accounts, n);

                break;
            }

            case 9:
            {
                updateAccount(accounts, n);

                saveToFile(accounts, n);

                break;
            }

            case 10:
            {
                saveToFile(accounts, n);

                cout << "\nExiting Program...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid Choice!\n";
            }
        }

    } while(choice != 10);

    return 0;
}