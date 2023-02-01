#include "card.h"

void getCardHolderNameTest(void)
{

	printf("Tester name: Mostafa   \nFunction Name: getCardHolderName \n\n\nTest case 1: ");
	char* input = "mostafa";
	EN_cardError_t result;

	printf("Input data is: %s", input);//printing input data
	printf("\nExpexted result: Card Ok \n");

	if (input == NULL)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) < 5)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) > 25)
	{
		result = WRONG_NAME;
	}
	else
	{
		result = CARD_OK;
	}

	if (result == WRONG_NAME)
	{
		printf("Actual result: Wrong name");
	}
	else if (result == CARD_OK)
	{
		printf("Actual result: Card Ok");
	}

	input = "MOSTAFA";


	printf("\n\n\nInput data is: %s", input);//printing input data
	printf("\nExpexted result: Card Ok\n");

	if (input == NULL)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) < 5)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) > 25)
	{
		result = WRONG_NAME;
	}
	else
	{
		result = CARD_OK;
	}


	if (result == WRONG_NAME)
	{
		printf("Actual result: Wrong name");
	}
	else if (result == CARD_OK)
	{
		printf("Actual result: Card Ok");
	}



	input = "MOSTAFA MOATAZEWJMFE noninoibyuygutc";


	printf("\n\n\nInput data is: %s", input);//printing input data
	printf("\nExpexted result: Wrong name \n");

	if (input == NULL)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) < 5)
	{
		result = WRONG_NAME;
	}
	else if (strlen(input) > 25)
	{
		result = WRONG_NAME;
	}
	else
	{
		result = CARD_OK;
	}


	if (result == WRONG_NAME)
	{
		printf("Actual result: Wrong name");
	}
	else if (result == CARD_OK)
	{
		printf("Actual result: Card Ok");
	}


}




void getCardPANTest(void) {

	printf("Tester name: Mostafa\nFunction name: getCardPan\n\n\nTest case 1:");
	char* input = "q5OM4";
	EN_cardError_t result = CARD_OK;
	printf("\n\nInput data: %s\nExpected result: Wrong Pan",input);

	if ((strlen(input)) > 20 || (strlen(input)) < 16)
	{
		result = WRONG_PAN;
	} 

	if (result == CARD_OK)
	{
		printf("\nActual result:card ok");

	}

	else if (result == WRONG_PAN)
	{
		printf("\nActual result: wrong PAN");
	}
	
	input = "mwe2ugSPAr7PN4tgMtOm2n"; //18 characters 
	result = CARD_OK;
	printf("\n\n\nTest case 2: \nInput data: %s\nExpected result: Wrong PAN", input);

	if ((strlen(input)) > 20 || (strlen(input)) < 16)
	{
		result = WRONG_PAN;
	}

	if (result == CARD_OK)
	{
		printf("\nActual result:card ok");

	}

	else if (result == WRONG_PAN)
	{
		printf("\nActual result: wrong PAN");
	}



}



void getCardExpiryDateTest(void) {

	EN_cardError_t result = CARD_OK;
	printf("Tester name: Mostafa   \nFunction Name: getCardHolderName \n\n\nTest case 1: ");

	int month = 23, year = 04;

	printf("Input data: 23/04\n\nExpected result: Wrong exp date ");

	
	if (month == -1 || year == -1 || month > 12 || month < 1 || year > 50 || year < 22)
	{
		result = WRONG_EXP_DATE;
	}

	printf("\nActual result: ");

	if (result == CARD_OK)
	{
		printf("card ok");

	}

	else if (result == WRONG_EXP_DATE)
	{
		printf("wrong exp date");
	}

	printf("\n\nTest case 2: ");

	 month = 12;
	 year = 35;


	 result = CARD_OK;
	printf("Input data: 12/35\n\nExpected result: card ok");
	
	if (month == -1 || year == -1 || month > 12 || month < 1 || year > 50 || year < 22)
	{
		result = WRONG_EXP_DATE;
	}

	

	printf("\nActual result: ");


	if (result == CARD_OK)
	{
		printf("card ok");

	}

	else if (result == WRONG_EXP_DATE)
	{
		printf("wrong exp date");
	}
}