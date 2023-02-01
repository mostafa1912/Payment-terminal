#include "card.h"
#include <stdio.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{ 
	printf("Please enter card holder name:\n\n");

	char input[10];
	
	scanf("%s", &input);

	if ((input) == NULL) //could all be ORred
	{
		return WRONG_NAME;
	}
	else if(strlen((input)) < 5) 
	{ 
		return WRONG_NAME;
	}
	else if (strlen((input)) > 25)
	{
		return WRONG_NAME;
	}
	else
	{
		strcpy(cardData->cardHolderName,input);
		return CARD_OK;
	}
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	char date[10]; 
	
	int dmonth = 0;
	int dyear = 0;
	printf("Enter the expiry date in the format MM/YY: ");
	int scanned = scanf("%s", &date);
	

	dmonth = (date[0] - '0') * 10 + (date[1] - '0');

	dyear = (date[3] - '0') * 10 + (date[4] - '0');

	printf("Month: %d\nYear: %d\n", dmonth, dyear);

	

	if (dmonth == -1 || dyear == -1 || dmonth > 12 || dmonth < 1  || dyear > 50 || dyear < 22)
	{
		return WRONG_EXP_DATE;
	}

	strcpy(cardData->cardExpirationDate,date);
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* CardData) {

	printf("Please enter PAN:\n\n");

	char input[20];

	scanf("%s", &input);


	if (strlen(input) > 15 || strlen(input) < 20)
	{
		for (int i = 0; i < strlen(input); i++)
		{

			if ((input[i]) > '9' || (input < '0')) {

				return WRONG_PAN;
			}
		}

		strcpy(CardData->primaryAccountNumber,input);

		return CARD_OK;
	}
	else
	{
		return WRONG_PAN;
	}
}

