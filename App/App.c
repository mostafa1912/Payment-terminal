#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../App/App.h"



ST_cardData_t userCard;
ST_terminalData_t userTerm;
extern int AccountIndex;
extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t transactionDB[255];
int transactionCount;



bool card() {

	if (getCardHolderName(&userCard) == CARD_OK)
	{		

		if (getCardExpiryDate(&userCard) == CARD_OK)
		{

			if (getCardPAN(&userCard) == CARD_OK)
			{				
				return true;
			}
		}
	}

	return false;

}



void terminal() {
	
	if (getTransactionDate(&userTerm) == TERMINAL_OK) {

		if (isCardExpired(&userCard, &userTerm) == TERMINAL_OK) {
			
			if (getTransactionAmount(&userTerm) == TERMINAL_OK) {
				
				float m = 50000;

				if (setMaxAmount(&userTerm, &m ) == TERMINAL_OK) {

		

					if (isBelowMaxAmount(&userTerm) == TERMINAL_OK)
					{
						server();
					}

					else {
						printf("The amount you entered exceeds the max amount  \n");
					}

				}

			}
			else {

				printf("Invalid transaction amount \n");

			}

		}

		else {

			printf("Card is expired \n");
		}
	}
	else {

		printf("Wrong transaction date \n");
	}

}


void server() {

	if (isValidAccount(&userCard, accountsDB) == SERVER_OK) {

		if (isBlockedAccount(accountsDB) == SERVER_OK) {

			if (isAmountAvailable(&userTerm, accountsDB) == SERVER_OK) {

				accountsDB[AccountIndex].balance -= userTerm.transAmount;

				printf(" Successful transaction \n");

				printf("your balance now is : %.1f \n", accountsDB[AccountIndex].balance);
			}

			else
			{

				printf("Insufficient amount \n");
			}
		}

		else {

			printf("Blocked account \n");
		}
	}

	recieveTransactionData(transactionDB);
	saveTransaction(transactionDB);



}

void appStart() {

	printf("Please enter number of transactions: \n");
	scanf("%d", &transactionCount);

	for (int i = 0; i < transactionCount; i++)
	{
		if (card()) {
			terminal();
			listSavedTransactions();
			printf("Thank you\n");


		}
		else
			printf("Please try again \n");
		
	}
}

