#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int searchForUsername(char *fname, char *str)
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
        if ((strstr(temp, str)) != NULL)
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
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
int searchForPassword(char *fname, char *str)
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
        if ((strstr(temp, str)) != NULL)
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
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

int main(int argc, char *argv[])
{
    char option;

    while (1)
    {
        printf("\n    Main Menu\n----------------\n'1' to Register\n'2' to Login\n'Q' to Quit\n----------------\n");
        option = getchar();

        /* 49 == '1' */
        if (option == 49)
        {
            system("CLS");
            registration();
        }
        /* 50 == '2' */
        else if (option == 50)
        {
            system("CLS");
            login();
        }
        /* 81 == 'Q' */
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

void login(void)
{
    char username[30], password[20];
    FILE *credentialsFile;
    int usernameFound = 1;
    char fileName[10] = "login.txt";

    credentialsFile = fopen(fileName, "r");

    if (credentialsFile == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    account_t userAccount;

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Enter Username: ");
    scanf("%s", userAccount.username);
    printf("Enter Password: ");
    scanf("%s", userAccount.password);

    /* Search credentialsFile for username */
    usernameFound = searchForUsername(fileName, userAccount.username);

    if (usernameFound == 0)
    {
        int passwordFound = searchForPassword(fileName, userAccount.password);
        if (passwordFound == 0)
        {
            printf("\nUser is logged in!");
        }
        else
        {
            printf("\nPassword incorrect!");
        }
    }
    else
    {
        printf("Username not found!");
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
        fprintf(log, "account_id,first_name,last_name,username,password\n");
    }
    fprintf(log, "%d,", newAccountID);
    fprintf(log, "%s,", userAccount.first_name);
    fprintf(log, "%s,", userAccount.last_name);
    fprintf(log, "%s,", userAccount.username);
    fprintf(log, "%s", userAccount.password);
    fprintf(log, "\n");

    fclose(log);

    printf("\nRegistration Successful!");
    printf("\nWelcome, %s!\n", userAccount.first_name);

    printf("\nPress enter to continue...");
    getchar();
}
