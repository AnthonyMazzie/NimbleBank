#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

bool userLoggedIn = false;
string loggedInUsername;
int loggedInUserID = -1;

/* The user bank account class has an ID, first name, last name, username, password and account balance. */
class userBankAccount
{
public:
    userBankAccount(
        string account_id,
        string first_name,
        string last_name,
        string username,
        string password,
        string accountBalance)
    {
        Account_ID = account_id;
        First_name = first_name;
        Last_name = last_name;
        Username = username;
        Password = password;
        AccountBal = accountBalance;
    }

    void display()
    {
        cout << "     Account ID : " << Account_ID << endl;
        cout << "     First name : " << First_name << endl;
        cout << "      Last name : " << Last_name << endl;
        cout << "       Username : " << Username << endl;
        cout << "       Password : " << Password << endl;
        cout << "Account Balance : " << AccountBal << endl;
    }

    void setToNull()
    {
        Account_ID.clear();
        First_name.clear();
        Last_name.clear();
        Username.clear();
        Password.clear();
        AccountBal.clear();
    }

    string Account_ID;
    string First_name;
    string Last_name;
    string Username;
    string Password;
    string AccountBal;
};

/* Displays all bank accounts for the input vector file */
void displayAccounts(vector<userBankAccount> &accountsFile)
{
    for (auto userAccount : accountsFile)
    {
        userAccount.display();
        cout << endl;
    }
}

vector<userBankAccount> userBankAccountVector;

/* The login/account_t typedef struct represents a user attempting to login to the bank system */
typedef struct login
{
    int accountID;
    char first_name[30];
    char last_name[30];
    char username[30];
    char password[20];
    int accountBalance;
} account_t;

void login(void);        // Prototype
void registration(void); // Prototype

/* Reads contents of account file into C++ Class */
void readFileContents()
{
    printf("\nREADING FILE CONTENTS... ");
    fstream inputFile;
    inputFile.open("./login.txt", ios::in);
    string line = "";
    string dummyLine;              // To skip first line of CSV file
    getline(inputFile, dummyLine); // To skip first line of CSV file
    cout << endl;

    while (getline(inputFile, line))
    {
        stringstream inputString(line);

        string account_id;
        string first_name;
        string last_name;
        string username;
        string password;
        string accountBalance;

        getline(inputString, account_id, ',');
        getline(inputString, first_name, ',');
        getline(inputString, last_name, ',');
        getline(inputString, username, ',');
        getline(inputString, password, ',');
        getline(inputString, accountBalance, ',');

        userBankAccount thisAccount(account_id, first_name, last_name, username, password, accountBalance);
        userBankAccountVector.push_back(thisAccount);
        line = "";
    }
    displayAccounts(userBankAccountVector);
}

/* Updates the file with any updated information */
void writeNewFile()
{
    FILE *fp;
    fp = fopen("outputFile.txt", "w");
    fprintf(fp, "account_id,first_name,last_name,username,password,account_balance\n"); // Print header
    for (auto userAccount : userBankAccountVector)                                      // Print all accounts
    {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n", userAccount.Account_ID.c_str(), userAccount.First_name.c_str(), userAccount.Last_name.c_str(), userAccount.Username.c_str(), userAccount.Password.c_str(), userAccount.AccountBal.c_str());
    }
    if (fp)
    {
        fclose(fp);
    }
}

/* Returns 0 if username is found, 1 if username is not found */
int searchForUsername(char *fname, string accountUsername)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    // gcc
    // if((fp = fopen(fname, "r")) == NULL) {
    //	return(-1);
    // }

    // Visual Studio
    if ((fopen_s(&fp, fname, "r")) != NULL)
    {
        return (-1);
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, accountUsername.c_str())) != NULL)
        {
            printf("Match found, line: %d\n", line_num);
            loggedInUserID = line_num - 1;
            return 0;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        return 1;
    }

    if (fp)
    {
        fclose(fp);
    }

    return (0);
}

/* Returns 0 if username is found, 1 if username is not found */
int searchForUsername2(char *fname, string accountUsername)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    fp = fopen("login.txt", "r");

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, accountUsername.c_str())) != NULL)
        {
            printf("Match found, line: %d\n", line_num);
            loggedInUserID = line_num - 1;
            return 0;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        return 1;
    }

    if (fp)
    {
        fclose(fp);
    }

    return (0);
}

/* Returns ID if found, -1 if ID is not found */
int searchForID(char *fname, string accountUsername)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    // gcc
    // if((fp = fopen(fname, "r")) == NULL) {
    //	return(-1);
    // }

    // Visual Studio
    if ((fopen_s(&fp, fname, "r")) != NULL)
    {
        return (-1);
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, accountUsername.c_str())) != NULL)
        {
            find_result++;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        return -1;
    }

    if (fp)
    {
        fclose(fp);
    }
    return line_num;
}

/* Returns 0 if password is found, 1 if password is not found */
int searchForPassword(char *fname, string userPassword)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    // gcc
    // if((fp = fopen(fname, "r")) == NULL) {
    //	return(-1);
    // }

    // Visual Studio
    if ((fopen_s(&fp, fname, "r")) != NULL)
    {
        return (-1);
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, userPassword.c_str())) != NULL)
        {
            // printf("Match found, line: I%d\n", line_num);
            // printf("\n%s\n", temp);
            find_result++;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        return 1;
    }

    if (fp)
    {
        fclose(fp);
    }
    return (0);
}

/* Determines what the new account ID should be and returns it */
int getNewAccountID()
{
    int totalAccountQuantity = 0;
    FILE *accountFile;
    accountFile = fopen("login.txt", "r");

    char c;
    for (c = getc(accountFile); c != EOF; c = getc(accountFile))
    {
        // Increment count if this character is newline
        if (c == '\n')
        {
            totalAccountQuantity++;
        }
    }

    fclose(accountFile);

    return totalAccountQuantity;
}

/* Allows a user to login if their username and password match in the file */
void login(void)
{
    char username[30], password[20];
    FILE *credentialsFile;
    int usernameFound = 1;
    char fileName[10] = "login.txt";
    string accountName;
    string userPassword;

    credentialsFile = fopen(fileName, "r");

    if (credentialsFile == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }
    else
    {
        readFileContents();
    }

    printf("Enter your login credentials below\n");
    printf("Enter Username: ");
    cin >> accountName; // get user input from the keyboard
    printf("Enter Password: ");
    cin >> userPassword; // get user input from the keyboard

    /* Search credentialsFile for username */
    usernameFound = searchForUsername(fileName, accountName);

    if (usernameFound == 0)
    {
        int passwordFound = searchForPassword(fileName, userPassword);
        if (passwordFound == 0)
        {
            // printf("\nUser is logged in!");
            userLoggedIn = true;
            loggedInUsername = accountName;
        }
        else
        {
            printf("\nPassword incorrect!");
            printf("\nPress enter to continue...");
            getchar();
            getchar();
        }
    }
    else // Username not found!
    {
        printf("Username not found!");
        printf("\nPress enter to continue...");
        getchar();
        getchar();
    }

    fclose(credentialsFile);
    return;
}

/* Allows a user to register to the bank system */
void registration(void)
{
    int newAccountID = getNewAccountID();

    FILE *log;

    log = fopen("login.txt", "a");
    if (log == NULL)
    {
        fputs("Error opening file.", stderr);
        exit(1);
    }
    else
    {
        // readFileContents();
    }

    account_t userAccount;
    string userUsername;
    string userPassword;
    char fileName[10] = "login.txt";
    int initialAccountBalance = 0;

    /* Checks "database" text file for username, if it exists, get user input again */
    bool usernameChosen = false;
    while (usernameChosen == false)
    {
        /* Gets new user information from user */
        printf("\nEnter First Name: ");
        scanf("%s", userAccount.first_name);

        printf("Enter Last Name: ");
        scanf("%s", userAccount.last_name);

        printf("Enter Username: ");
        cin >> userUsername;                                            // get user input from the keyboard
        int usernameCheck = searchForUsername2(fileName, userUsername); // 0 if username is found, 1 if not
        if (usernameCheck == 1)
        {
            usernameChosen = true;
            printf("Enter Password: ");
            cin >> userPassword; // get user input from the keyboard
        }
        else
        {
            printf("\nUsername '%s' already exists in database! Try again...\n", userUsername.c_str());
        }
    }

    /* Write new user information to file */
    /* Note: does not check for duplicate usernames / firstname+last name combinations */
    if (newAccountID == 0)
    {
        fprintf(log, "account_id,first_name,last_name,username,password,account_balance\n");
        newAccountID++;
    }
    fprintf(log, "%d,", newAccountID);
    fprintf(log, "%s,", userAccount.first_name);
    fprintf(log, "%s,", userAccount.last_name);
    fprintf(log, "%s,", userUsername.c_str());
    fprintf(log, "%s,", userPassword.c_str());
    fprintf(log, "%d", initialAccountBalance);
    fprintf(log, "\n");

    fclose(log);

    printf("\nRegistration Successful!");
    printf("\nWelcome, %s!\n", userAccount.first_name);

    printf("\nPress enter to continue...");
    getchar();
    getchar();
}

/* Closes the account of the user who is logged in */
void closeAccount(int accountID)
{
    userBankAccountVector.at(accountID - 1).setToNull();
    userLoggedIn = false;
}

void loanApplication();

/* Updates internal data structure representing the bank accounts of all users */
void updateDataStructure()
{
    fstream inputFile;
    inputFile.open("./output.txt", ios::in);
    string line = "";
    string dummyLine;              // To skip first line of CSV file
    getline(inputFile, dummyLine); // To skip first line of CSV file
    cout << endl;

    while (getline(inputFile, line))
    {
        stringstream inputString(line);

        string account_id;
        string first_name;
        string last_name;
        string username;
        string password;
        string accountBalance;

        getline(inputString, account_id, ',');
        getline(inputString, first_name, ',');
        getline(inputString, last_name, ',');
        getline(inputString, username, ',');
        getline(inputString, password, ',');
        getline(inputString, accountBalance, ',');

        userBankAccount thisAccount(account_id, first_name, last_name, username, password, accountBalance);
        userBankAccountVector.push_back(thisAccount);
        line = "";
    }
    // displayAccounts(userBankAccountVector);
}

void withdrawFunds(int accountID)
{
    // system("CLS");
    int amount;
    printf("\nWithdrawing funds\n");
    printf("----------------------------");
    printf("\nEnter amount to withdraw: ");
    scanf("%d", &amount);
    getchar(); // Get '\n' from scanf above
    int currentAmount = stoi(userBankAccountVector.at(accountID - 1).AccountBal);
    if ((currentAmount - amount) < 0)
    {
        printf("Insufficient funds...");
        printf("\nPress enter to continue...");
        getchar();
        getchar();
    }
    else
    {
        printf("\nAmount withdrawn");
        userBankAccountVector.at(accountID - 1).AccountBal = to_string(currentAmount - amount);
        writeNewFile();
        updateDataStructure();
    }
}

/* Allows an authenticated user the ability to deposit funds into their account */
void depositFunds(int accountID)
{
    system("CLS");
    int amount;
    printf("\nDepositing funds\n");
    printf("----------------------------");
    printf("\nEnter amount to deposit: ");
    scanf("%d", &amount);
    getchar(); // Get '\n' from scanf above
    int currentAmount = stoi(userBankAccountVector.at(accountID - 1).AccountBal);
    userBankAccountVector.at(accountID - 1).AccountBal = to_string(currentAmount + amount);
    writeNewFile();
    updateDataStructure();
}

/* Returns the current account balance of the logged in user */
int balanceCheck(int accountID)
{
    // readFileContents();
    printf("\n-------------------------");
    printf("\nBALANCE CHECK");
    int userBal = stoi(userBankAccountVector.at(accountID - 1).AccountBal);
    printf("\nUser ID         : %d", stoi(userBankAccountVector.at(accountID - 1).Account_ID));
    printf("\nUsername        : %s", userBankAccountVector.at(accountID - 1).Username.c_str());
    printf("\nAccount balance : %d", userBal);

    // system("CLS");

    printf("\n-------------------------\n");
    printf("\nPress enter to continue...");
    getchar();
    getchar();
    return (0);
}

/* Prints to the screen all current information stored for the logged in user */
int getAccountInfo()
{
    // system("CLS");
    char fileName[10] = "login.txt";
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    // gcc
    // if((fp = fopen(fname, "r")) == NULL) {
    //	return(-1);
    // }

    // Visual Studio
    if ((fopen_s(&fp, fileName, "r")) != NULL)
    {
        return (-1);
    }
    printf("\n-------------------------");
    printf("\nACCOUNT INFORMATION ");

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, loggedInUsername.c_str())) != NULL)
        {
            int readIndex = 0;
            char *pt;
            pt = strtok(temp, ",");
            while (pt != NULL)
            {
                string a = pt;
                if (readIndex == 0)
                {
                    printf("\nAccountID      : %s", a.c_str());
                }
                else if (readIndex == 1)
                {
                    printf("\nFirst name     : %s", a.c_str());
                }
                else if (readIndex == 2)
                {
                    printf("\nLast name      : %s", a.c_str());
                }
                else if (readIndex == 3)
                {
                    printf("\nUsername       : %s", a.c_str());
                }
                else if (readIndex == 5)
                {
                    printf("\nAccount balance: %s", a.c_str());
                }

                pt = strtok(NULL, ",");
                readIndex++;
            }
            find_result++;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        return 1;
    }

    if (fp)
    {
        fclose(fp);
    }

    printf("-------------------------\n");

    printf("\nPress enter to continue...");
    getchar();
    getchar();
    return (0);
}

/* Logs the user out */
void logOut()
{
    // system("CLS");
    userLoggedIn = false;
    loggedInUsername = " ";
    printf("\nUser logged out.");
}

int main(int argc, char *argv[])
{
    char option;

    while (1)
    {
        if (userLoggedIn == true)
        {
            fflush(stdin);
            // system("CLS");
            printf("\nUser Account Menu");
            printf("\n---------------------");
            printf("\n'B'alance check");
            printf("\n'W'ithdraw");
            printf("\n'D'eposit");
            printf("\n'T'ransfer funds");
            printf("\n'L'oan application");
            printf("\n'I'nfo");
            printf("\n'C'lose account");
            printf("\n'E'scape (log out)");
            printf("\n---------------------\n");

            option = getchar();

            /* 'C' == 67 */
            if (option == 67)
            {
                closeAccount(loggedInUserID);
            }
            /* 'D' == 68 */
            else if (option == 68)
            {
                depositFunds(loggedInUserID);
            }
            /* 'B' == 66 */
            else if (option == 66)
            {
                balanceCheck(loggedInUserID);
            }
            /* 'I' == 73 */
            else if (option == 73)
            {
                getAccountInfo();
            }
            /* 'L' == 76 */
            else if (option == 76)
            {
                // loanApplication();
            }
            /* 'W' == 87 */
            else if (option == 87)
            {
                withdrawFunds(loggedInUserID);
            }
            /* 'E" == 69 */
            else if (option == 69)
            {
                logOut();
            }
        }
        else // User is not logged in
        {
            fflush(stdin);
            // system("CLS");
            printf("\n    Main Menu\n----------------\n'1' to Register\n'2' to Login\n'Q' to Quit\n----------------\n");
            option = getchar();

            /* 49 == '1' */
            if (option == 49)
            {
                registration();
            }
            /* 50 == '2' */
            else if (option == 50)
            {
                login();
            }
            /* 81 == 'Q' */
            else if (option == 81)
            {
                break;
            }
        }
    }
    return 0;
}