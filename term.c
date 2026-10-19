#include <stdio.h>
#include <string.h>
#include "term.h"

void getTransactionDate(ST_terminalData *terminalData)
{
    printf("Enter transaction date (DD/MM/YYYY): ");

    fgets(terminalData->transactionDate,
          sizeof(terminalData->transactionDate), stdin);

    terminalData->transactionDate[
        strcspn(terminalData->transactionDate, "\n")] = '\0';
}

int isCardExpired(ST_cardData *cardData, ST_terminalData *terminalData)
{
    int cardMonth, cardYear;
    int transMonth, transYear;

    sscanf(cardData->cardExpirationDate, "%d/%d",
           &cardMonth, &cardYear);

    sscanf(terminalData->transactionDate, "%*d/%d/%d",
           &transMonth, &transYear);

    if (cardYear < transYear % 100)
        return 1;

    if (cardYear == transYear % 100 && cardMonth < transMonth)
        return 1;

    return 0;
}

void getTransactionAmount(ST_terminalData *terminalData)
{
    printf("Enter transaction amount: ");
    scanf("%f", &terminalData->transAmount);

    while (getchar() != '\n');
}

int isBelowMaxAmount(ST_terminalData *terminalData)
{
    if (terminalData->transAmount <= terminalData->maxTransAmount)
        return 1;

    return 0;
}

void setMaxAmount(float maxAmount, ST_terminalData *terminalData)
{
    terminalData->maxTransAmount = maxAmount;
}