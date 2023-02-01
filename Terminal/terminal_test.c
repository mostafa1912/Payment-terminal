#include "terminal.h" 

extern ST_cardData_t user_card;
extern ST_terminalData_t user_terminal;

void getTransactionDateTest(void) {


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
            {
                flag = TERMINAL_OK;
                printf("Date is valid.\n");
            }
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
            {   
                     printf("Date is valid.\n");
                    flag = TERMINAL_OK;
            }
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
            {
                printf("Date is valid.\n");
                flag = TERMINAL_OK;
            }
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
            {
                printf("Date is valid.\n");
                flag = TERMINAL_OK;
            }
            else
            {
                printf("Date is valid.\n");
                flag = TERMINAL_OK;
            }
        }
        else
        {
            flag = TERMINAL_OK;
            printf("Month is not valid.\n");
        }
    }
    else
    {
        flag = TERMINAL_OK;
        printf("Year is not valid.\n");
    }

    if (flag == TERMINAL_OK)
    {   
        char dds[10], mms[10], yys[10];
      
        itoa(dd, dds, 10); //this function converts integers to strings
        itoa(mm, mms, 10);
        itoa(yy, yys, 10);

        char dateAsString[50];

        //snprintf(dateAsString, sizeof(dateAsString), "%s/%s/%s", dds, mms, yys);//I then concatenate the new substrings to form the date

        *(user_terminal.transactionDate) = dateAsString; 
    
    
    }
}


void isCardExpiredTest(void)
{
    //In this function I need to compare the card expiry date with the transaction to to see if the card already expired
    printf("Test Case 1:\nThe assumed expiry date is 02/30\nInput transaction date is: 11/02/25\nExpected result: Pass");
    
    char cardExpDate[] = "02/2030";
    char input[] = "11/02/2025";

    uint8_t CardExpirationMonth =
        ((cardExpDate[0] - '0') * 10) + (cardExpDate[1] - '0');
    uint8_t CardExpirationYear =
        ((cardExpDate[5] - '0') * 10) + (cardExpDate[6] - '0');

    uint8_t TransactionMonth =
        ((input[3] - '0') * 10) + (input[4] - '0');
    uint8_t TransactionYear =
        ((input[8] - '0') * 10) + (input[9] - '0');

    if ((CardExpirationYear < TransactionYear))
    {
        printf("\nActual result: Card expired\n");
    }
    else if ((CardExpirationYear == TransactionYear))
    {
        if ((CardExpirationMonth < TransactionMonth) ||
            (CardExpirationMonth == TransactionMonth))
        {
            printf("\nActual result: Card expired\n");

        }
    }
    else
    {
        printf("\nActual result: Passed\n");
    }



    printf("\n\nTest Case 2:\n The assumed expiry date is 02/30\nInput transaction date is: 11/02/2035\nExpected result: card expired");

    char expiryDate2[]= "02/2030";
    char transDate2[] = "11/02/2035";
    strcpy(cardExpDate,expiryDate2);

    strcpy(input, transDate2);


     CardExpirationMonth =
        ((cardExpDate[0] - '0') * 10) + (cardExpDate[1] - '0');
     CardExpirationYear =
        ((cardExpDate[5] - '0') * 10) + (cardExpDate[6] - '0');

     TransactionMonth =
        ((input[3] - '0') * 10) + (input[4] - '0');
     TransactionYear =
        ((input[8] - '0') * 10) + (input[9] - '0');

    if ((CardExpirationYear < TransactionYear))
    {
        printf("\nActual result: Card expired\n");
    }
    else if ((CardExpirationYear == TransactionYear))
    {
        if ((CardExpirationMonth < TransactionMonth) ||
            (CardExpirationMonth == TransactionMonth))
        {
            printf("\nActual result: Card expired\n");

        }
    }
    else
    {
        printf("\nActual result: Passed\n");
    }



}


void getTransactionAmountTest(void)
{
    float transAmount = 1000.0;
    
    printf("Test Case 1: The input amount is:1000 \nExpected result: Pass");

    if ((0 >= transAmount))
    {
        printf("\nActual result: amount cant be less than zero");
    }
    else
    {
        printf("\nActual result: Pass");
        user_terminal.transAmount = transAmount;
    }


     transAmount = -123;
    
    printf("\n\n\nTest Case 2: The input amount is:-123 \nExpected result: amount cant be less than zero ");

    if ((0 >= transAmount))
    {
        printf("\nActual result: amount cant be less than zero");
    }
    else
    {
        printf("\nActual result: Pass");
        user_terminal.transAmount = transAmount;
    }
}


 void isBelowMaxAmountTest(void)
{
    printf("Test Case 1, Max Amount =5000\nThe input amount is:1000 \nExpected result: Pass");
    int input = 1000;


    if ((input > user_terminal.maxTransAmount))
    {
        printf("\nExceeded max amount");
    }
    else
        printf("pass");
   
    printf("Test Case 2, Max Amount =5000\nThe input amount is:6000 \nExpected result: Exceeded max amount");
     input = 6000;


    if ((input > user_terminal.maxTransAmount))
    {
        printf("\nExceeded max amount");
    }
    else
        printf("pass");
}

void setMaxAmountTest(void)
{

    printf("\n\Test case 1: The input amount is: 100\nExpected result: Pass ");

    float input = 100;
    
    if ((0 >= input))
    {
        printf("\nActual result: cant be negative");
    }
    else
    {
        printf("\nActual result: PASS");
    }


    printf("\n\Test case 2: The input amount is: -100\nExpected result: Pass ");

    input = -100;

    if ((0 >= input))
    {
        printf("\nActual result: cant be negative");
    }
    else
    {
        printf("\nActual result: PASS");
    }

}