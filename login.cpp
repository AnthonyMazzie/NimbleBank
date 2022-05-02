#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

bool userLoggedIn = false;

typedef struct login
{
    char first_name[30];
    char last_name[30];
    char username[30];
    char password[20];
    int accountBalance;
} account_t;

void login(void);
void registration(void);

void Usage(char *filename)
{
    printf("Usage: %s <file> <string>\n", filename);
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
            // printf("A match found on line: %d\n", line_num);
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
            // printf("A match found on line: %d\n", line_num);
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
    totalAccountQuantity++;

    return totalAccountQuantity;
}

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

    printf("\nPlease Enter your login credentials below\n\n");
    printf("\nEnter Username: ");
    cin >> accountName; // get user input from the keyboard
    printf("\nEnter Password: ");
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

    account_t userAccount;

    int initialAccountBalance = 0;

    /* Gets new user information from user */
    printf("\nEnter First Name: ");
    scanf("%s", userAccount.first_name);
    printf("Enter Last Name: ");
    scanf("%s", userAccount.last_name);
    printf("Enter Username: ");
    scanf("%s", userAccount.username);
    printf("Enter Password: ");
    scanf("%s", userAccount.password);
    getchar(); // Scanf leaves '\n' in the input buffer. This 'getchar()' reads that new line so that the next 'getchar()' below will catch.

    /* Write new user information to file */
    /* Note: does not check for duplicate usernames / firstname+last name combinations */
    if (newAccountID == 1)
    {
        fprintf(log, "account_id,first_name,last_name,username,password,account_balance\n");
    }
    fprintf(log, "%d,", newAccountID);
    fprintf(log, "%s,", userAccount.first_name);
    fprintf(log, "%s,", userAccount.last_name);
    fprintf(log, "%s,", userAccount.username);
    fprintf(log, "%s,", userAccount.password);
    fprintf(log, "%d", initialAccountBalance);
    fprintf(log, "\n");

    fclose(log);

    printf("\nRegistration Successful!");
    printf("\nWelcome, %s!\n", userAccount.first_name);

    printf("\nPress enter to continue...");
    getchar();
}

void closeAccount();
void depositFunds();
void loanApplication();
void transferFunds();
void withdrawFunds();
void balanceCheck();
void logOut();

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
            printf("\n----------------");
            printf("\n'B'alance check");
            printf("\n'W'ithdraw");
            printf("\n'D'eposit");
            printf("\n'T'ransfer funds");
            printf("\n'L'oan application");
            printf("\n'C'lose account");
            printf("\n'ESC'ape\n");
            option = getchar();

            /* 'C' == 67 */
            if (option == 67)
            {
                // system("CLS");
                // closeAccount();
            }
            /* 'D' == 68 */
            else if (option == 68)
            {
                // system("CLS");
                // depositFunds();
            }
            /* 'B' == 66 */
            else if (option == 68)
            {
                // system("CLS");
                // balanceCheck();
            }
            /* 'L' == 76 */
            else if (option == 76)
            {
                // system("CLS");
                // loanApplication();
            }
            /* 'T' == 84 */
            else if (option == 84)
            {
                // system("CLS");
                // transferFunds();
            }
            /* 'W' == 87 */
            else if (option == 87)
            {
                // system("CLS");
                // withdrawFunds();
            }
            /* 'ESC" == 27 */
            else if (option == 27)
            {
                // system("CLS");
                // logOut();
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
                // system("CLS");
                registration();
            }
            /* 50 == '2' */
            else if (option == 50)
            {
                // system("CLS");
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