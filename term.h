#ifndef TERM_H
#define TERM_H
#include "card.h"

typedef struct ST_terminalData
{
    float transAmount;
    float maxTransAmount;
    char transactionDate[11];
} ST_terminalData;

void getTransactionDate(ST_terminalData *terminalData);
int isCardExpired(ST_cardData *cardData, ST_terminalData *terminalData);
void getTransactionAmount(ST_terminalData *terminalData);
int isBelowMaxAmount(ST_terminalData *terminalData);
void setMaxAmount(float maxAmount, ST_terminalData *terminalData);




#endif