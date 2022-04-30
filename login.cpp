#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct login
{
    char first_name[30];
    char last_name[30];
    char username[30];
    char password[20];
    int accountBalance;
};

void login(void);
void registration(void);

int main(void)
{
    char option;

    while (1)
    {
        printf("\n    Main Menu\n----------------\n'1' to Register\n'2' to Login\n'Q' to Quit\n");
        option = getchar();
        printf("Option entered: %c", option);

        if (option == 49)
        {
            system("CLS");
            registration();
        }

        else if (option == 50)
        {
            system("CLS");
            login();
        }
        else if (option == 81)
        {
            break;
        }
    }
    return 0;
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

// TODO
void login(void)
{
    char username[30], password[20];
    FILE *log;

    log = fopen("login.txt", "r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    struct login l;

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:  ");
    fgets(username, 30, stdin);
    printf("\nPassword: ");
    printf("\n");
    fgets(password, 20, stdin);
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);

    while (fread(&l, sizeof(l), 1, log))
    {
        int i;
        printf("\nTesting!!, %d", i);

        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)

        {
            printf("Username: %s\n", username);
            printf("Password: %s\n", password);
            printf("\nSuccessful Login\n");
        }
        else
        {
            printf("\nINCORRECT: Username: %s", username);
            printf("\nINCORRECT: Password: %s", password);
            printf("\nINCORRECT Login Details Provided. Exiting...");
        }
    }

    fclose(log);

    return;
}

void registration(void)
{
    int newAccountID = getNewAccountID();
    char firstname[15];
    FILE *log;

    log = fopen("login.txt", "a");
    if (log == NULL)
    {
        fputs("Error opening File!", stderr);
        exit(1);
    }

    struct login login;

    /* Gets new user information from user */
    printf("\nEnter First Name: ");
    scanf("%s", login.first_name);
    printf("Enter Last Name: ");
    scanf("%s", login.last_name);
    printf("Enter Username: ");
    scanf("%s", login.username);
    printf("Enter Password: ");
    scanf("%s", login.password);
    getchar(); // Scanf leaves '\n' in the input buffer. This 'getchar()' reads that new line so that the next 'getchar()' below will catch.

    /* Write new user information to file */
    /* Note: does not check for duplicate usernames / firstname+last name combinations */
    if (newAccountID == 1)
    {
        fprintf(log, "account_id,first_name,last_name,username,password\n");
    }
    fprintf(log, "%d,", newAccountID);
    fprintf(log, "%s,", login.first_name);
    fprintf(log, "%s,", login.last_name);
    fprintf(log, "%s,", login.username);
    fprintf(log, "%s", login.password);
    fprintf(log, "\n");

    fclose(log);

    printf("\nRegistration Successful!");
    printf("\nWelcome, %s!\n", login.first_name);

    printf("\nPress enter to continue...");
    getchar();

    // login();
}