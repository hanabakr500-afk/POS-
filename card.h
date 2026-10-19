#ifndef CARD_H
#define CARD_H

typedef struct ST_cardData
{
    char cardHolderName[25];
    char primaryAccountNumber[20];
    char cardExpirationDate[6];
} ST_cardData;

void getCardHolderName(ST_cardData *cardData);
void getCardExpiryDate(ST_cardData *cardData);
void getCardPAN(ST_cardData *cardData);

#endif