#include <stdio.h>
#include "terminal.h"

ST_terminalData_t user_terminal;;
EN_terminalError_t getTransactionDate(ST_terminalData_t* terminalData) {
	
    EN_terminalError_t flag;
	printf("Enter transaction date in the format \"DD/MM/YYYY\" ");

	int dd, mm, yy;
   int numChars =  scanf("%d/%d/%d", &dd, &mm, &yy);
   printf("%d \n", numChars);
   //converting the nunbers to strings
   char dds[10], mms[10], yys[10];
   
   itoa(dd, dds,10); //this function converts integers to strings
   itoa(mm, mms, 10);
   itoa(yy, yys, 10);

   char dateAsString[50];
   snprintf(dateAsString,sizeof(dateAsString),"%s/%s/%s",dds,mms,yys);//I then concatenate the new substrings to form the date

   if (sizeof(dateAsString) < 10) {
            
       return WRONG_DATE;
   }


   //check year
   if (yy >= 1900 && yy <= 9999)
   {
       //check month
       if (mm >= 1 && mm <= 12)
       {
           //check days
           if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
               flag = TERMINAL_OK;
           //printf("Date is valid.\n");
           else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
               // printf("Date is valid.\n");
               flag = TERMINAL_OK;
           else if ((dd >= 1 && dd <= 28) && (mm == 2))
               // printf("Date is valid.\n");
               flag = TERMINAL_OK;
           else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
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
       strcpy(terminalData->transactionDate, dateAsString);
       return flag;
   }
   else
       return flag;
    

}


EN_terminalError_t getTransactionDateForTest() {


    EN_terminalError_t flag;

    printf("Enter transaction data in the format \"DD/MM/YYYY\" ");

    int dd, mm, yy;
    scanf("%d/%d/%d", &dd, &mm, &yy);
    //check year
    if (yy >= 1900 && yy <= 9999)
    {
        //check month
        if (mm >= 1 && mm <= 12)
        {
            //check days
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
                flag = TERMINAL_OK;
            //printf("Date is valid.\n");
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                // printf("Date is valid.\n");
                flag = TERMINAL_OK;
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
                // printf("Date is valid.\n");
                flag = TERMINAL_OK;
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
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
        strcpy();
   
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    //In this function I need to compare the card expiry date with the transaction to to see if the card already expired

    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    uint8_t CardExpirationMonth =
        ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
    uint8_t CardExpirationYear =
        ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

    uint8_t TransactionMonth =
        ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
    uint8_t TransactionYear =
        ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

    if ((CardExpirationYear < TransactionYear))
    {
        ThisFunction_ErrorState = EXPIRED_CARD;
    }
    else if ((CardExpirationYear == TransactionYear))
    {
        if ((CardExpirationMonth < TransactionMonth) ||
            (CardExpirationMonth == TransactionMonth))
        
            ThisFunction_ErrorState = EXPIRED_CARD;
        
    }
    

    return ThisFunction_ErrorState;


}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *terminalData) 
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    float transAmount = 0.0;
    printf("\n Enter transaction amount: ");

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

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    float maxTransAmount = 0.0;

    printf("\n Enter transaction maximum amount: ");
    scanf("%f", &maxTransAmount);

    if ((0 >= maxTransAmount))
    {
        ThisFunction_ErrorState = INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount = maxTransAmount;
    }

    return ThisFunction_ErrorState;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
    //TODO
    return TERMINAL_OK;
}




//TEST FUNCTIONS


#ifdef TERMINAL_TEST_FUNCTIONS

static uint8_t TEST_MODULE_Terminal(ST_cardData_t* MyCardModuleTest,
    ST_terminalData_t* MyTermianlModuleTest)
{
    uint8_t ThisFunction_ErrorState = 0;

    /** @defgroup Testing get the transaction data */
    if ((1 == TEST_getTransactionDate(MyTermianlModuleTest)))
    {
        printf("\n TEST_getTransactionDate: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n TEST_getTransactionDate: FAILED");
    }

    /** @defgroup Testing is card expired */
    if ((1 == isCardExpired(MyCardModuleTest, MyTermianlModuleTest)))
    {
        printf("\n isCardExpired: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n isCardExpired: FAILED");
    }

    /** @defgroup Testing is card pan valid */
    if ((1 == isValidCardPAN(MyCardModuleTest)))
    {
        printf("\n isValidCardPAN: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n isValidCardPAN: FAILED");
    }

    /** @defgroup Testing get the transaction amount */
    if ((1 == getTransactionAmount(MyTermianlModuleTest)))
    {
        printf("\n getTransactionAmount: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n getTransactionAmount: FAILED");
    }

    /** @defgroup Testing is below max */
    if ((1 == isBelowMaxAmount(MyTermianlModuleTest)))
    {
        printf("\n isBelowMaxAmount: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n isBelowMaxAmount: FAILED");
    }

    /** @defgroup Testing set the max amount */
    if ((1 == setMaxAmount(MyTermianlModuleTest)))
    {
        printf("\n setMaxAmount: PASSED"); ThisFunction_ErrorState = 1;
    }
    else
    {
        printf("\n setMaxAmount: FAILED");
    }

    /** @note: Means that the module test is passed */
    return ThisFunction_ErrorState;
}

static uint8_t TEST_getTransactionDate(ST_terminalData_t* termData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getTransactionDate(termData);

    if ((WRONG_DATE == ErrorState))
    {
        printf("\n TEST_getTransactionDate: WRONG_DATE");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isCardExpired(cardData, termData);

    if ((EXPIRED_CARD == ErrorState))
    {
        printf("\n TEST_isCardExpired: EXPIRED_CARD");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isValidCardPAN(ST_cardData_t* cardData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isValidCardPAN(cardData);

    if ((INVALID_CARD == ErrorState))
    {
        printf("\n TEST_isValidCardPAN: INVALID_CARD");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_getTransactionAmount(ST_terminalData_t* termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getTransactionAmount(termData);

    if ((INVALID_AMOUNT == ErrorState))
    {
        printf("\n TEST_getTransactionAmount: INVALID_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isBelowMaxAmount(ST_terminalData_t* termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isBelowMaxAmount(termData);

    if ((EXCEED_MAX_AMOUNT == ErrorState))
    {
        printf("\n TEST_isBelowMaxAmount: EXCEED_MAX_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_setMaxAmount(ST_terminalData_t* termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = setMaxAmount(termData);

    if ((INVALID_MAX_AMOUNT == ErrorState))
    {
        printf("\n TEST_setMaxAmount: INVALID_MAX_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

#endif

