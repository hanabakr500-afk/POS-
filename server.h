#ifndef SERVER_H
#define SERVER_H
#include "card.h"
#include "term.h"


typedef struct ST_accountsDB
{
    float balance;
    char primaryAccountNumber[20];
} ST_accountsDB;

typedef enum EN_transState
{
    APPROVED,
    DECLINED_INVALID_ACCOUNT,
    DECLINED_INSUFFICIENT_FUND,
    DECLINED_EXCEED_MAX_AMOUNT,
    DECLINED_EXPIRED_CARD
} EN_transState;

typedef struct ST_transaction
{
    ST_cardData cardHolderData;
    ST_terminalData terminalData;
    EN_transState transState;
    unsigned int transactionSequenceNumber;
} ST_transaction;

int isValidAccount(ST_cardData *cardData, ST_accountsDB *account);
int isAmountAvailable(ST_terminalData *terminalData, ST_accountsDB *account);
int saveTransaction(ST_transaction *transaction);
int receiveTransactionData(ST_transaction *transaction);













#endif