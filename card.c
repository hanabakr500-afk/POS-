#include <stdio.h>
#include <string.h>
#include "card.h"

void getCardHolderName(ST_cardData *cardData)
{
    printf("Enter cardholder name: ");
    fgets(cardData->cardHolderName,
          sizeof(cardData->cardHolderName), stdin);

    cardData->cardHolderName[
        strcspn(cardData->cardHolderName, "\n")] = '\0';
}

void getCardExpiryDate(ST_cardData *cardData)
{
    printf("Enter card expiry date (MM/YY): ");
    scanf("%5s", cardData->cardExpirationDate);

    while (getchar() != '\n');
}

void getCardPAN(ST_cardData *cardData)
{
    printf("Enter card number: ");
    fgets(cardData->primaryAccountNumber,
          sizeof(cardData->primaryAccountNumber), stdin);

    cardData->primaryAccountNumber[
        strcspn(cardData->primaryAccountNumber, "\n")] = '\0';
}