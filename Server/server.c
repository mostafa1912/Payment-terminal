/* This portion of code is mostly from https://github.com/Hala-Abdelkader/Payment-Application */
#include "server.h"

ST_accountsDB_t accountsDB[255] = { 
	{2001,RUNNING,"8989374615436851"},
	{3234,RUNNING,"7623542289704361"},
	{5240,BLOCKED,"34510976342342591"},
	{12130,BLOCKED,"45782971234225824"},
	{14600,RUNNING,"7541682485237863"} };

ST_transaction_t transDB[255] = { 0 };

extern ST_cardData_t user_card;
extern ST_terminalData_t user_terminal;
extern int expCardFlag;


int Account_NUM = 0;

int NUM;

extern int numberOfTransactions;

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	if (isValidAccount(&user_card, accountsDB) == ACCOUNT_NOT_FOUND) {

		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}

	else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) {

		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;

	}
	else if (isAmountAvailable(&user_terminal, accountsDB) == LOW_BALANCE) {

		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (saveTransaction(&user_terminal) == SAVING_FAILED) {

		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else if (isAmountAvailable(&user_terminal, accountsDB) == SERVER_OK) {

		transData->transState = APPROVED;
		return APPROVED;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* CardData) {

	
	for (Account_NUM = 0; Account_NUM < 255; Account_NUM++)
	{
		if (strcmp((CardData->primaryAccountNumber), accountsDB[Account_NUM].primaryAccountNumber )== 0) 
		{
			return SERVER_OK;
			break;
		}
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence[Account_NUM].state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	else {
		return SERVER_OK;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference) {
	if (accountReference[Account_NUM].balance >= termData->transAmount) 
	{
		
		return SERVER_OK;
	}

	else if (accountReference[Account_NUM].balance < termData->transAmount)
	{
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	for (int i= 0; i < 255; i++)
	{
		if ((*(transData + i)).transactionSequenceNumber == 0)
		{
			strcpy(transData->cardHolderData.cardHolderName, user_card.cardHolderName);
			strcpy(transData->cardHolderData.cardExpirationDate, user_card.cardExpirationDate);
			strcpy(transData->cardHolderData.primaryAccountNumber, user_card.primaryAccountNumber);
			strcpy(transData->terminalData.transactionDate, user_terminal.transactionDate);
			transData->terminalData.maxTransAmount = user_terminal.maxTransAmount;
			transData->terminalData.transAmount = user_terminal.transAmount;
			transData->transactionSequenceNumber = i + 1;

			if (transData->cardHolderData.cardHolderName == 0) {
				return SAVING_FAILED;
			}

			else if (transData->cardHolderData.cardExpirationDate == 0) {

				return SAVING_FAILED;
			}

			else if (transData->cardHolderData.primaryAccountNumber == 0) {

				return SAVING_FAILED;
			}

			else if (transData->terminalData.transactionDate == 0) {

				return SAVING_FAILED;

			}

			else if (transData->terminalData.maxTransAmount == 0) {

				return SAVING_FAILED;

			}

			else if (transData->terminalData.transAmount == 0) {

				return SAVING_FAILED;

			}

			return SERVER_OK;
		}



	}
	return SAVING_FAILED;
}


void listSavedTransactions(void) {

	printf("#################################\n");
	

	if (expCardFlag)
	{
		printf("CARD EXPIRED\nTransaction Declined\n");
	}
	else
	{
		printf("Transaction Sequence Number: %d\n", (*(transDB + NUM)).transactionSequenceNumber);
		printf("Transaction Date: %s\n", (*(transDB + NUM)).terminalData.transactionDate);
		printf("Transaction Amount: %.1f\n", (*(transDB + NUM)).terminalData.transAmount);

		if (recieveTransactionData(transDB) == APPROVED) {

			printf("Transaction state: APPROVED \n");
		}

		else if (recieveTransactionData(transDB) == DECLINED_INSUFFECIENT_FUND) {
			printf("Transaction state: DECLINED_INSUFFECIENT_FUND \n");
		}

		else if (recieveTransactionData(transDB) == DECLINED_STOLEN_CARD) {
			printf("Transaction state: DECLINED_STOLEN_CARD \n");
		}

		else if (recieveTransactionData(transDB) == FRAUD_CARD) {
			printf("Transaction state: FRAUD_CARD \n");
		}
		else if (recieveTransactionData(transDB) == INTERNAL_SERVER_ERROR) {
			printf("Transaction state: INTERNAL_SERVER_ERROR \n");
		}

		printf("Terminal Max Amount: %.1f\n", (*(transDB + NUM)).terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", (*(transDB + NUM)).cardHolderData.cardHolderName);
		printf("PAN: %s\n", (*(transDB + NUM)).cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", (*(transDB + NUM)).cardHolderData.cardExpirationDate);
	}
	
	printf("#################################\n");

}





