#include <stdio.h>
#include <stdlib.h>

#define ACCOUNT_LOCKED 'n'

int main()
{
    int ctr = 0;
    int pin;
    char myString;
    int choice;
    char balanceStatus[100];
    int amount;
    int withdraw;
    int deposit;

    FILE *file = fopen("n.txt", "r");

    fscanf(file, "%s", &myString);
    // printf("%c", myString);

    if (myString == 'y')
    {
        printf("Welcome!\n");
    }
    else if (myString == ACCOUNT_LOCKED)
    {
        printf("Your card is blocked.\n");
        return -2;
    }
     fclose(file);

    do
    {
        printf("Enter your pin: \n");
        scanf("%d", &pin);
        ++ctr;
        if (pin != 1234)
        {

            if (ctr == 3)
            {
                FILE *file = fopen("n.txt", "w");
                fprintf(file, "n\n");
                fclose(file);
                printf("System is locked!\n");
                return -1;
            }
            printf("Try again.\n");
        }

    } while (pin != 1234);
    do
    {
        FILE *file2;
        file2 = fopen("balance.txt", "r");

        while (!feof(file2))
        {
            fgets(balanceStatus, 100, file2);
            puts(balanceStatus);
        }

        fclose(file2);

        printf("1. Cash Withdrawal\n");
        printf("2.Cash Deposition\n");
        printf("3. Exit\n\n");

        printf("Please proceed with your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            file2 = fopen("balance.txt", "r");
            fgets(balanceStatus, sizeof(balanceStatus), file2);
            sscanf(balanceStatus, "You have %d", &amount);
            fclose(file2);
            printf("Enter the amount you'd like to withdraw:\n");
            scanf("%d", &withdraw);
            if (amount < withdraw)
            {
                printf("You haven't got enough balance!\n");
                break;
            }
            int newAmount = amount - withdraw;
            file2 = fopen("balance.txt", "w");
            fprintf(file2, "You have %d", newAmount);
            fclose(file2);

            break;
        case 2:
            file2 = fopen("balance.txt", "r");
            fgets(balanceStatus, sizeof(balanceStatus), file2);
            sscanf(balanceStatus, "You have %d", &amount);
            fclose(file2);
            printf("Enter the amount you'd like to deposit:\n");
            scanf("%d", &deposit);
            int newAmount = amount + deposit;
            file2 = fopen("balance.txt", "w");
            fprintf(file2, "You have %d", newAmount);
            fclose(file2);
            break;
        case 3:
            printf("Goodbye.\n");
            return -3;
        default:
            printf("Error.\n");
            break;
        }

        fclose(file2);

    } while (choice != '3');

        return 0;
}
