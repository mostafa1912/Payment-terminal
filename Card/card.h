#include <stdint.h>
#ifndef  CARD_H
#define CARD_H

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25]; //25 characters
	uint8_t primaryAccountNumber[20];//20 numbers stored in 20 bytes
	uint8_t cardExpirationDate[5];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

EN_cardError_t getCardPAN(ST_cardData_t* cardData);




#endif

