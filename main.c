#include <stdio.h>
#include "App/App.h"
extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t transactionDB[255];
extern ST_cardData_t userCard;
extern ST_terminalData_t userTerm;
extern int AccountIndex;



int main() {
	for (int i = 0; i < 5; i++) {
		if (accountsDB[i].primaryAccountNumber != 0)
		{
			printf("%s\n", accountsDB[i].primaryAccountNumber);

		}


	}
	//getCardHolderNameTest();
	
	//getCardExpiryDateTest();
	
	//getCardPANTest();
		
	//getTransactionDateTest();
	
	//isCardExpiredTest();
	
	//getTransactionAmountTest();
	
	//isBelowMaxAmountTest();
	
	//setMaxAmountTest();
	
	//isValidAccountTest();
	
	//isBlockedAccountTest();
	
	//isAmountAvailableTest();
	
	//recieveTransactionDataTest();
	
	//saveTransactionTest();
		
	//listSavedTransactionsTest();
	
	appStart();
	
}