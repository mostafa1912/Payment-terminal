#include "card.h"
#include <stdio.h>
ST_cardData_t data;
EN_cardError_t getCardHolderName()
{
	char name[100];
	scanf("%s", name);
	if (name == NULL)
	{
		return WRONG_NAME;
	}
	else if(sizeof(name) < 20)
	{ 
		return WRONG_NAME;
	}
	else if (sizeof(name) > 25)
	{
		return WRONG_NAME;
	}
	else
	{
		strcpy(data.cardHolderName, name);
		return CARD_OK;
	}
	
}
EN_cardError_t getCardHolderNameForTest(char* name)
{
	//char name[100];
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
		strcpy(data.cardHolderName, name);
		return CARD_OK;
	}

}
void getCardHolderNameTest(void)
{
	printf("Tester Name: your name: Mostafa \n\nFunction Name: getCardHolderName \n\n\n");
	//test case 1 -- less than 25
	char name [100] = "mostafa";

	int result = getCardHolderNameForTest(name);

	printf("Test case 1 \n Input: %s expected result is : 1 \n actual result is %d \n", name, result);

	//test case 2 -- over 25 chars
	strcpy(name,"heiwefuiehweoweifhwoeihfowehfwioehfoiwheiohwf");

	 result = getCardHolderNameForTest(name);

	printf("\n Test case 2 \n Input: %s expected result is : 1 \n actual result is %d \n", name, result);

	//test case 3 -- happy
	strcpy(name,"heiwefuiehweowweqr");

	result = getCardHolderNameForTest(name);

	printf("\n Test case 3 \n Input: %s expected result is : 1 \n actual result is %d \n", name, result);

}
int main() {
	//EN_cardError_t error = getCardHolderName();
	 getCardHolderNameTest();
	//printf("%d", error);
	return 0;
}