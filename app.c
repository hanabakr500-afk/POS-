#include <stdio.h>
#include "app.h"

void appStart(void)
{
    ST_transaction transaction;

   

    getCardHolderName(&transaction.cardHolderData);
    getCardExpiryDate(&transaction.cardHolderData);
    getCardPAN(&transaction.cardHolderData);

    getTransactionDate(&transaction.terminalData);

    if (isCardExpired(&transaction.cardHolderData,
                      &transaction.terminalData))
    {
        printf("\nDeclined: Card is expired.\n");

        transaction.transState = DECLINED_EXPIRED_CARD;
        saveTransaction(&transaction);
        return;
    }

    getTransactionAmount(&transaction.terminalData);

    setMaxAmount(5000.0, &transaction.terminalData);

    if (!isBelowMaxAmount(&transaction.terminalData))
    {
        printf("\nDeclined: Amount exceeds maximum limit.\n");

        transaction.transState = DECLINED_EXCEED_MAX_AMOUNT;
        saveTransaction(&transaction);
        return;
    }

    if (receiveTransactionData(&transaction))
    {
        printf("\nTransaction approved!\n");
    }
    else
    {
        if (transaction.transState == DECLINED_INVALID_ACCOUNT)
        {
            printf("\nDeclined: Invalid account.\n");
        }
        else if (transaction.transState == DECLINED_INSUFFICIENT_FUND)
        {
            printf("\nDeclined: Insufficient funds.\n");
        }
        else
        {
            printf("\nTransaction declined.\n");
        }
    }
}