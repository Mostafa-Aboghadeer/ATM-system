#include <stdio.h>
#include "card.h"
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	printf("\nPlease, type your name: ");
	gets(cardData->cardHolderName);
	if (cardData->cardHolderName == NULL)
	{
		printf("\nWRONG_NAME");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20)
	{
		printf("\nWRONG_NAME");
		return WRONG_NAME;
	}
	else
	{
		printf("\nOK");
		return OK;
	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nPlease, Enter the card's expired date:");
	gets(cardData->cardExpirationDate);
	

	if (cardData->cardExpirationDate == NULL)
	{
		printf("\nWRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}
	else if (strlen(cardData->cardExpirationDate) != 5)
	{
		printf("\nWRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != 47)
	{
		printf("\nWRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("\nOK");
		return OK;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("\nplease type in your PAN:");
	gets(cardData->primaryAccountNumber);
	strcpy(sahred, cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber == NULL)
	{
		printf("\nWRONG_PAN");
		return WRONG_PAN;
	}
	else if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->cardHolderName) < 16)
	{
		printf("\nWRONG_PAN");
		return WRONG_PAN;
	}
	else
	{
		printf("\nOK");
		return OK;
	}

}