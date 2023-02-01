#include "server.h"
extern ST_cardData_t userCard;
extern ST_terminalData_t userTerm;

extern ST_accountsDB_t accountsDB[255];

extern ST_transaction_t transDB[255] ;

#define max_amount 50000

void isValidAccountTest(void) {

	printf("Tester name: Mostafa\nFunction tested: isValidAccount\n\n");
	strcpy(userCard.primaryAccountNumber, "uiuewrweiurwu");
	printf("Test Case 1\nInput data: uiuewrweiurwu\n\nExpected result: INVALID ACCOUNT");
	if (isValidAccount(&userCard, accountsDB) == SERVER_OK)
	{
		printf("\nActual result: VALID ACCOUNT \n");
	}
	else if (isValidAccount(&userCard, accountsDB) == ACCOUNT_NOT_FOUND)
	{
		printf("\nActual result: INVALID ACCOUNT \n");
	}






	strcpy(userCard.primaryAccountNumber, "7623542289704361");
	printf("\n\nTest Case 2\nInput data: 7623542289704361\n\nExpected result: VALID ACCOUNT");
	if (isValidAccount(&userCard, accountsDB) == SERVER_OK)
	{
		printf("\nActual result: VALID ACCOUNT \n");
	}
	else if (isValidAccount(&userCard, accountsDB) == ACCOUNT_NOT_FOUND)
	{
		printf("\nActual result: INVALID ACCOUNT \n");
	}
}

void isBlockedAccountTest(void) {

	printf("Tester name: Mostafa\nFunction tested: isBlockedAccount\n\n");
	
	strcpy(userCard.primaryAccountNumber, "7623542289704361");
	printf("Test Case 1\nInput data: 7623542289704361\n\nExpected result: UNBLOCKED ACCOUNT\n");
	
	if (isValidAccount(&userCard, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(accountsDB) == SERVER_OK) {

			printf("Actual result: UNBLOCKED ACCOUNT \n");
		}

		else {
			printf("Actual result: BLOCKED ACCOUNT \n");
		}
	}
	else {
		printf("Actual result: INVALID ACCOUNT \n");
	}


	strcpy(userCard.primaryAccountNumber, "34510976342342591");
	printf("Test Case 2\nInput data: 34510976342342591\n\nExpected result: BLOCKED ACCOUNT\n");

	if (isValidAccount(&userCard, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(accountsDB) == SERVER_OK) {

			printf("Actual result: UNBLOCKED ACCOUNT \n");
		}

		else {
			printf("Actual result: BLOCKED ACCOUNT \n");
		}
	}
	else {
		printf("Actual result: INVALID ACCOUNT \n");
	}

}

void isAmountAvailableTest(void) {

	printf("Tester name: Mostafa\nFunction tested: isAmountAvailable\n\n");

	strcpy(userCard.primaryAccountNumber, "7623542289704361");
	userTerm.transAmount = 100;
	printf("Test Case 1\nInput data: 7623542289704361\nwith amount: 4000\n\nExpected result: LOW BALANCE\n");


	if (isValidAccount(&userCard, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(&accountsDB) == SERVER_OK) {
			if (isAmountAvailable(&userTerm, accountsDB) == SERVER_OK) {
				printf("Actual result: APPROVED \n");
			}
			else {
				printf("Actual result: LOW BALANCE \n");
			}
		}
	}


	strcpy(userCard.primaryAccountNumber, "7541682485237863");
	printf("\n\n\nTest Case 2\nInput data: 7541682485237863\nwith amount: 4000\n\nExpected result: APPROVED\n");


	if (isValidAccount(&userCard, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(&accountsDB) == SERVER_OK) {
			if (isAmountAvailable(&userTerm, accountsDB) == SERVER_OK) {
				printf("Actual result: APPROVED \n");
			}
			else {
				printf("Actual result: LOW BALANCE \n");
			}
		}
		else
		{
			printf("\nAccount is blocked");
		}
	}
	else
	{
		printf("\nnot a valid account");
	}

}

//void recieveTransactionDataTest(void) {
//
//	printf("Tester name: Mostafa\nFunction tested: isAmountAvailable\n\n");
//
//	strcpy(user_card.cardHolderName, "Mostafa");
//	printf("Test Case 1\nName: Mostafa\n");
//
//
//
//	if (getCardHolderName(&user_card.cardHolderName) == CARD_OK)
//	{
//		strcpy(user_card.primaryAccountNumber, "7623542289704361");
//		scanf("\n");
//		scanf("%[^\n]%*c", &user_card.primaryAccountNumber);
//
//		if (getCardPAN(&user_card.primaryAccountNumber) == CARD_OK)
//		{
//
//			printf("Please enter the card expiry date \n");
//			scanf("\n");
//			scanf("%[^\n]%*c", &user_card.cardExpirationDate);
//
//
//
//			if (getCardExpiryDate(&user_card.cardExpirationDate) == CARD_OK)
//			{
//				printf("please enter the transaction date\n");
//				scanf("\n");
//				scanf("%[^\n]%*c", &(user_terminal.transactionDate));
//
//				if (getTransactionDate(&user_terminal) == TERMINAL_OK) {
//
//					if (isCardExpired(&user_card, &user_terminal) == TERMINAL_OK) {
//						printf("Please enter the transaction amount\n");
//						scanf("%f", &user_terminal.transAmount);
//
//						if (getTransactionAmount(&user_terminal) == TERMINAL_OK) {
//
//							if (setMaxAmount(&user_terminal,max_amount) == TERMINAL_OK) {
//
//								if (isBelowMaxAmount(&user_terminal) == TERMINAL_OK)
//								{
//									if (recieveTransactionData(transDB) == FRAUD_CARD) {
//										printf("FRAUD_CARD\n");
//									}
//									else if (recieveTransactionData(transDB) == DECLINED_STOLEN_CARD) {
//										printf("DECLINED_STOLEN_CARD\n");
//									}
//									else if (recieveTransactionData(transDB) == APPROVED) {
//										printf("APPROVED\n");
//									}
//									else if (recieveTransactionData(transDB) == DECLINED_INSUFFECIENT_FUND) {
//
//										printf("DECLINED_INSUFFECIENT_FUND\n");
//									}
//									else if (recieveTransactionData(transDB) == INTERNAL_SERVER_ERROR) {
//										printf("INTERNAL_SERVER_ERROR\n");
//									}
//								}
//							}
//						}
//					}
//				}
//
//			}
//
//		}
//
//	}
//
//}


//void saveTransactionTest(void) {
//	recieveTransactionDataTest();
//	if (saveTransaction(transDB) == SERVER_OK)
//	{
//		printf(" Data saved successfully\n");
//	}
//	else
//	{
//		printf("Saving failed\n");
//	}
//}
//
//void listSavedTransactionsTest(void)
//{
//	appStart();
//}