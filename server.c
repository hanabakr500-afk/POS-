#include <stdio.h>
#include <string.h>
#include "server.h"

#define MAX_TRANSACTIONS 100

ST_accountsDB accounts[] =
{
    {2000.0, "1234567890123456"},
    {500.0,  "9876543210987654"},
    {10000.0, "1111222233334444"}
};

int accountCount = 3;
int i;

ST_transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

int isValidAccount(ST_cardData *cardData, ST_accountsDB *account)
{
    int i;

    for (i = 0; i < accountCount; i++)
    {
        if (strcmp(cardData->primaryAccountNumber,
                   accounts[i].primaryAccountNumber) == 0)
        {
            *account = accounts[i];
            return 1;
        }
    }

    return 0;
}

int isAmountAvailable(ST_terminalData *terminalData,
                      ST_accountsDB *account)
{
    if (terminalData->transAmount <= account->balance)
    {
        return 1;
    }

    return 0;
}

int saveTransaction(ST_transaction *transaction)
{
    if (transactionCount >= MAX_TRANSACTIONS)
    {
        return 0;
    }

    transactions[transactionCount] = *transaction;
    transactionCount++;

    return 1;
}

int receiveTransactionData(ST_transaction *transaction)
{
    ST_accountsDB account;

    if (!isValidAccount(&transaction->cardHolderData, &account))
    {
        transaction->transState = DECLINED_INVALID_ACCOUNT;
        saveTransaction(transaction);
        return 0;
    }

    if (!isAmountAvailable(&transaction->terminalData, &account))
    {
        transaction->transState = DECLINED_INSUFFICIENT_FUND;
        saveTransaction(transaction);
        return 0;
    }

    transaction->transState = APPROVED;

    if (!saveTransaction(transaction))
    {
        return 0;
    }

      for (i = 0; i < accountCount; i++)
    {
        if (strcmp(transaction->cardHolderData.primaryAccountNumber,
                   accounts[i].primaryAccountNumber) == 0)
        {
            accounts[i].balance -= transaction->terminalData.transAmount;
            break;
        }
    }


    return 1;
}