#include <stdio.h>
#include "terminal.h"

ST_terminalData_t user_terminal;
int expCardFlag = 0;

EN_terminalError_t getTransactionDate(ST_terminalData_t* terminalData) {
	
    EN_terminalError_t flag;
	printf("Enter transaction date in the format \"DD/MM/YYYY\" ");

   char date[20];
   int numChars =  scanf("%s", &date);

   int day, month, year;
   
   day = (date[0] - '0') * 10 + (date[1] - '0');
   month = (date[3] - '0') * 10 + (date[4] - '0');
   year = (date[8] - '0') * 10 + (date[9] - '0');

   if (strlen(date) != 10) {
            
       return WRONG_DATE;
   }

  
   //check year
   if (year >= 23 && year <= 99)
   {
       //check month
       if (month >= 1 && month <= 12)
       {
           //check days
           if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
               flag = TERMINAL_OK;
           //printf("Date is valid.\n");
           else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
               // printf("Date is valid.\n");
               flag = TERMINAL_OK;
           else if ((day >= 1 && day <= 28) && (month == 2))
               // printf("Date is valid.\n");
               flag = TERMINAL_OK;
           else if (day == 29 && month == 2 && ((year+2000) % 400 == 0 || ((year + 2000) % 4 == 0 && (year + 2000) % 100 != 0)))
               //printf("Date is valid.\n");
               flag = TERMINAL_OK;
           else
               flag = TERMINAL_OK;
           //printf("Day is invalid.\n");
       }
       else
       {
           flag = TERMINAL_OK;
           //printf("Month is not valid.\n");
       }
   }
   else
   {
       flag = TERMINAL_OK;
       //printf("Year is not valid.\n");
   }

   if (flag == TERMINAL_OK)
   {
       strcpy(terminalData->transactionDate, date);
       return flag;
   }
   else
       return flag;
    

}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    //In this function I need to compare the card expiry date with the transaction to to see if the card already expired

    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;
    //02/35
    uint8_t CardExpirationMonth =
        ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
    uint8_t CardExpirationYear =
        ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

    //02/12/2021
    uint8_t TransactionMonth =
        ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
    uint8_t TransactionYear =
        ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

    if ((CardExpirationYear < TransactionYear))
    {
        expCardFlag = 1;
        ThisFunction_ErrorState = EXPIRED_CARD;
    }
    else if ((CardExpirationYear == TransactionYear))
    {
        if ((CardExpirationMonth < TransactionMonth) ||
            (CardExpirationMonth == TransactionMonth))
        {
            expCardFlag = 1;
            ThisFunction_ErrorState = EXPIRED_CARD;
        }
    }
    

    return ThisFunction_ErrorState;


}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData) 
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    float transAmount = 0.0;
    printf("\nEnter transaction amount: ");

    scanf("%f", &transAmount);

    if ((0 >= transAmount))
    {
        ThisFunction_ErrorState = INVALID_AMOUNT;
    }
    else
    {
        terminalData->transAmount = transAmount;
    }
    return ThisFunction_ErrorState;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    if ((termData->transAmount > termData->maxTransAmount))
    {
        ThisFunction_ErrorState = EXCEED_MAX_AMOUNT;
    }
    return ThisFunction_ErrorState;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float* maxTransAmount)
{
    if (maxTransAmount <= 0) {

        return INVALID_MAX_AMOUNT;
    }

    else {
        termData->maxTransAmount = *maxTransAmount;
        return TERMINAL_OK;
    }
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
    //TODO
    return TERMINAL_OK;
}





