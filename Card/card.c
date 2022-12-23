#include "card.h"
#include <stdio.h>


ST_cardData_t user_card;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{ 
	
	if ((cardData->cardHolderName) == NULL) //could all be ORred
	{
		return WRONG_NAME;
	}
	else if(sizeof((cardData->cardHolderName)) < 20)
	{ 
		return WRONG_NAME;
	}
	else if (sizeof((cardData->cardHolderName)) > 25)
	{
		return WRONG_NAME;
	}
	else
	{
		strcpy(user_card.cardHolderName, (cardData->cardHolderName));
		return CARD_OK;
	}
	
}

EN_cardError_t getCardHolderNameForTest(char* name)
{
	if (name == NULL)
	{
		return WRONG_NAME;
	}
	else if (sizeof(name) < 20)
	{
		return WRONG_NAME;
	}
	else if (sizeof(name) > 25)
	{
		return WRONG_NAME;
	}
	else
	{
		strcpy(user_card.cardHolderName,name);
		return CARD_OK;
	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int month = -1, year = -1;

	printf("Enter a date in the format MM/YY: ");
	int scanned = scanf("%d/%d", &month, &year);
	if (scanned != 2) {
		return WRONG_EXP_DATE;
	}

	printf("Month: %d\nYear: %d\n", month, year);

	if (month == -1 || year == -1 || month > 12 || month < 1  || year > 2050 || year < 2022)
	{
		return WRONG_EXP_DATE;
	}


	char syear[5];
	itoa(year, syear, 10);

	char smonth[5];
	itoa(month, smonth, 10);

	char buf[256];
	snprintf(buf, sizeof(buf), "%s/%s", smonth, syear);

	strcpy(user_card.cardExpirationDate, buf);

	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* CardData) {
	strcpy(CardData->primaryAccountNumber, user_card.primaryAccountNumber);

	if (strlen(CardData->primaryAccountNumber) > 16 || strlen(CardData->primaryAccountNumber) < 19)
	{
		for (int i = 0; i < strlen(CardData->primaryAccountNumber); i++)
		{

			if ((CardData->primaryAccountNumber[i]) > '9' || (CardData->primaryAccountNumber[i] < '0')) {

				return WRONG_PAN;
			}
		}


		return CARD_OK;
	}
	else
	{
		return WRONG_PAN;
	}
}

void getCardPANTest(void) {

	printf("Testing for the account number \nPlease enter the  primary account number \n");
	scanf("%[^\n]%*c", &(user_card.primaryAccountNumber));


	if (getCardPAN(&user_card) == CARD_OK) {

		printf("The Primary account number is correct\n");
	}
	else {
		printf("The primary account number is wrong\n");

	}
}
void getCardExpiryDateTest(void) {

	printf("Testing for CardEexpiryDate:\n");

	if (getCardExpiryDate(&user_card) == CARD_OK) {

		printf("The expiry date is in correct format\n");
	}
	else {
		printf("The expiry date is in wrong format\n");
	}
}