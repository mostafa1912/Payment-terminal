﻿#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../App/App.h"



ST_cardData_t user_card;
ST_terminalData_t user_terminal;
extern int Account_NUM;
extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t transDB[255];
int number_of_transactions;



bool card() {

	if (getCardHolderName(&user_card) == CARD_OK)
	{		

		if (getCardExpiryDate(&user_card) == CARD_OK)
		{

			if (getCardPAN(&user_card) == CARD_OK)
			{				
				return true;
			}
		}
	}

	return false;




}



void terminal() {
	
	if (getTransactionDate(&user_terminal) == TERMINAL_OK) {

		if (isCardExpired(&user_card, &user_terminal) == TERMINAL_OK) {
			
			if (getTransactionAmount(&user_terminal) == TERMINAL_OK) {
				
				float m = 50000;

				if (setMaxAmount(&user_terminal, &m ) == TERMINAL_OK) {

		

					if (isBelowMaxAmount(&user_terminal) == TERMINAL_OK)
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

	if (isValidAccount(&user_card, accountsDB) == SERVER_OK) {

		if (isBlockedAccount(accountsDB) == SERVER_OK) {

			if (isAmountAvailable(&user_terminal, accountsDB) == SERVER_OK) {

				accountsDB[Account_NUM].balance -= user_terminal.transAmount;

				printf(" Successful transaction \n");

				printf("your balance now is : %.1f \n", accountsDB[Account_NUM].balance);
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

	recieveTransactionData(transDB);
	saveTransaction(transDB);



}

void appStart() {

	printf("Please enter number of transactions: \n");
	scanf("%d", &number_of_transactions);

	for (int n = 0; n < number_of_transactions; n++)
	{
		if (card() == true) {
			terminal();
			listSavedTransactions();
			printf("Thank you for your time\n");


		}
		else
		{
			printf("Please fill your info again \n");
		}
	}




}

