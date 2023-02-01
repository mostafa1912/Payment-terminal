/* This portion of code is inspired by https://github.com/Hala-Abdelkader/Payment-Application */
#include "server.h"

ST_accountsDB_t accountsDB[255] = { 
	{2001,RUNNING,"8989374615436851"},
	{3234,RUNNING,"7623542289704361"},
	{5240,BLOCKED,"34510976342342591"},
	{12130,BLOCKED,"45782971234225824"},
	{14600,RUNNING,"7541682485237863"} };


extern ST_terminalData_t userTerm;
extern ST_cardData_t userCard;
extern int expCardFlag;
ST_transaction_t transDB[255] = { 0 };
int num;
int Account_NUM = 0;

extern int numberOfTransactions;

EN_transState_t recieveTransactionData(ST_transaction_t* transactionData) {

	if (isValidAccount(&userCard, accountsDB) == ACCOUNT_NOT_FOUND) {

		transactionData->transactionState = FRAUD_CARD;
		return FRAUD_CARD;
	}

	else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) {

		transactionData->transactionState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;

	}
	else if (isAmountAvailable(&userTerm, accountsDB) == LOW_BALANCE) {

		transactionData->transactionState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (saveTransaction(&userTerm) == SAVING_FAILED) {

		transactionData->transactionState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else if (isAmountAvailable(&userTerm, accountsDB) == SERVER_OK) {

		transactionData->transactionState = APPROVED;
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
			strcpy(transData->cardHolderData.cardHolderName, userCard.cardHolderName);
			strcpy(transData->cardHolderData.cardExpirationDate, userCard.cardExpirationDate);
			strcpy(transData->cardHolderData.primaryAccountNumber, userCard.primaryAccountNumber);
			strcpy(transData->terminalData.transactionDate, userTerm.transactionDate);
			transData->terminalData.maxTransAmount = userTerm.maxTransAmount;
			transData->terminalData.transAmount = userTerm.transAmount;
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
		printf("Transaction Sequence Number: %d\n", (*(transDB + num)).transactionSequenceNumber);
		printf("Transaction Date: %s\n", (*(transDB + num)).terminalData.transactionDate);
		printf("Transaction Amount: %.1f\n", (*(transDB + num)).terminalData.transAmount);

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

		printf("Terminal Max Amount: %.1f\n", (*(transDB + num)).terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", (*(transDB + num)).cardHolderData.cardHolderName);
		printf("PAN: %s\n", (*(transDB + num)).cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", (*(transDB + num)).cardHolderData.cardExpirationDate);
	}
	
	printf("#################################\n");

}





