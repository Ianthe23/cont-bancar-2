#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure to represent a financial account
typedef struct {
    char accountType[50];
    double balance;
} Account;

// Structure to represent a financial transaction
typedef struct {
    char transactionType[50];
    double amount;
    int accountIndex;  // Index of the associated account

} Transaction;

// Structure to represent a customer
typedef struct {
    char username[20];
    char parola[20];
    Account accounts[100];
    Transaction transactions[100];  // Array to store transactions
    int numAccounts;
    int numTransactions;
} Customer;

void createCustomer(Customer *customers,int *numCustomemers)
{
    printf("\n----- Create Customer -----\n");
    printf("Enter username: ");
    char username[20];
    scanf("%s",username);
    validateInput(username);
    strcpy(customers[*numCustomemers].username, username);

    printf("Enter password: ");
    char parola[20];
    scanf("%s",parola);
    validateInput(parola);
    strcpy(customers[*numCustomemers].parola, parola);

    (*numCustomemers)++;

    printf("Customer created successfully.\n");

}

int log_in(Customer *customers,int *numCustomers)
{
    printf("\n----LOG_IN-----\n");
    printf("USERNAME:");
    char username[20];
    scanf("%s",username);
    validateInput(username);
    printf("PASSWORD:");
    char parola[20];
    scanf("%s",parola);
    validateInput(parola);
    for(int i=0;i<*numCustomers;i++)
    {
        if(strcmp(customers[i].username,username)==0&&strcmp(customers[i].parola,parola)==0)
            return i;
    }
    return -1;
}

void deleteAccount(Account *accounts, int *numAccounts)
{
    printf("\n----- Delete Account -----\n");
    printf("Which account to delete:");
    int accountIndex;
    scanf("%d", &accountIndex);
    if(accountIndex>*numAccounts||accountIndex<1)
        printf("Deletion cannot be performed.\n");
        else{
    for(int i=accountIndex-1;i<*numAccounts-1;i++)
    {
        strcpy(accounts[i].accountType,accounts[i+1].accountType);
        accounts[i].balance=accounts[i+1].balance;
    }
    (*numAccounts)--;


    printf("Deletion successful!");}

}

// Function prototypes
void createAccount(Account *accounts, int *numAccounts);
void recordTransaction(Account *accounts, Transaction *transactions, int *numTransactions, int accountIndex);
void generateReport(Account *accounts, Transaction *transactions, int numAccounts, int numTransactions);
void validateInput(char *input);

int main()
{


    Customer customers[100];  // Array to store customer data

    int numCustomers = 0;
    int contul_cu_nr_x = 0;
    int conectat;
    char gresit[256];

    printf("\n----WELCOME----\n");
    while(1)
    {
        printf("\n1.Create new customer\n");
        printf("2.Log in\n");
        printf("3.Exit the application.\n");

        printf("Enter choice: ");
        char choice1[2];
        scanf("%s", choice1);
        validateInput(choice1);

        switch (atoi(choice1)){
            case 1:
                createCustomer(customers,&numCustomers);
                break;
            case 2:
                conectat=log_in(customers,&numCustomers);
                if(conectat<0)
                    printf("Username or passwrord incorrect!");
                else
                    while (conectat>=0) {
                        printf("\n----- Accounting System Menu -----\n");
                        printf("1. Create Account\n");
                        printf("2. Record Transaction\n");
                        printf("3. Generate Report\n");
                        printf("4. Delete account\n");
                        printf("5. Exit\n");

                        printf("Enter your choice: ");
                        char choice2[2];
                        scanf("%s", choice2);
                        validateInput(choice2);

                        switch (atoi(choice2)) {
                            case 1:
                                createAccount(customers[conectat].accounts, &customers[conectat].numAccounts);
                                break;
                            case 2:
                                printf("For which account the transaction is made: ");
                                scanf("%d", &contul_cu_nr_x);
                                if (!contul_cu_nr_x) {
                                    fgets(gresit, 255, stdin);
                                    printf ("There is no such account!\n");
                                }
                                else if (contul_cu_nr_x <= customers[conectat].numAccounts)
                                    recordTransaction(customers[conectat].accounts,customers[conectat].transactions, &customers[conectat].numTransactions, contul_cu_nr_x - 1);
                                else printf("There is no such account!\n");
                                break;
                            case 3:
                                generateReport(customers[conectat].accounts, customers[conectat].transactions, customers[conectat].numAccounts, customers[conectat].numTransactions);
                                break;
                            case 5:
                                printf("Sign out!");
                                conectat=-1;
                                break;
                            case 4:
                                deleteAccount(&customers[conectat].accounts, &customers[conectat].numAccounts);
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    }
                    break;
                    case 3:
                        printf("Iesire din aplicatie!");
                        exit(0);

                    default:
                        printf("Invalid choice. Please try again later.\n");

    }
    }

    return 0;
}

void createAccount(Account *accounts, int *numAccounts) {
    printf("\n----- Create Account -----\n");
    printf("Enter account type: ");
    char accountType[50];
    scanf("%s", accountType);
    validateInput(accountType);

    strcpy(accounts[*numAccounts].accountType, accountType);
    accounts[*numAccounts].balance = 0.0;
    (*numAccounts)++;

    printf("Account created successfully!\n");
}

void recordTransaction(Account *accounts, Transaction *transactions, int *numTransactions, int accountIndex) {
    printf("\n----- Record Transaction -----\n");
    printf("Enter transaction type (e.g., deposit, withdrawal, transfer): ");
    char transactionType[50];
    int accountNumber, amount = -1;

    scanf("%s", transactionType);
    validateInput(transactionType);
    strcpy(transactions[*numTransactions].transactionType, transactionType);

    printf("Enter transaction amount: ");
    scanf("%lf", &amount);

    if (amount == -1)
        printf("The amount was not entered correctly!\n");
    else {
    transactions[*numTransactions].amount = amount;

    transactions[*numTransactions].accountIndex = accountIndex;

    // Update account balance based on the transaction type
    if (strcmp(transactionType, "deposit") == 0) {
        accounts[accountIndex].balance += transactions[*numTransactions].amount;
    } 
    else if (strcmp(transactionType, "withdrawal") == 0) {
        if (transactions[*numTransactions].amount <= accounts[accountIndex].balance) {
            accounts[accountIndex].balance -= transactions[*numTransactions].amount;
        } 
        else {
            printf("Insufficient funds for withdrawal. Transaction cancelled.\n");
            return;
        }
    } 
    else if (strcmp(transactionType, "transfer") == 0) {
        printf("Enter the account for transfer: ");
        scanf("%d", &accountNumber);
        if (transactions[*numTransactions].amount <= accounts[accountIndex].balance) {   

            accounts[accountIndex].balance -= transactions[*numTransactions].amount;

            (*numTransactions)++;
            strcpy(transactions[*numTransactions].transactionType, transactionType);
            transactions[*numTransactions].amount = transactions[*numTransactions-1].amount;
            transactions[*numTransactions].accountIndex = accountNumber - 1;

            accounts[accountNumber - 1].balance += transactions[*numTransactions].amount;
        }
        else {
            printf("Insufficient funds for transfer. Transaction cancelled.\n");
            return;
        }
    }
    else {
        printf("Invalid transaction type. Transaction cancelled.\n");
        return;
    }

    (*numTransactions)++;
    printf("Transaction recorded successfully for account %d!\n", accountIndex+1);
    }
}

void generateReport(Account *accounts, Transaction *transactions, int numAccounts, int numTransactions) {
    printf("\n----- Generate Report -----\n");
    printf("Account Report:\n");
    for (int i = 0; i < numAccounts; i++) {
        printf("Account Type: %s, Balance: $%.2f\n", accounts[i].accountType, accounts[i].balance);

        printf("Transactions for Account %d:\n", i + 1);
        for (int j = 0; j < numTransactions; j++) {
            if (transactions[j].accountIndex == i) {
                printf("Transaction Type: %s, Amount: $%.2f\n", transactions[j].transactionType, transactions[j].amount);
            }
        }
    }
}


void validateInput(char *input) {
    // Remove newline character from input
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}