#include <stdio.h>
#include <string.h>
#include "card.h"
#include "terminal.h"
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	sprintf(termData->transactionDate, "%02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

	if (termData->transactionDate == NULL)
	{
		printf("\nWRONG_DATE");
		return WRONG_DATE;
	}
		
	else if (termData->transactionDate[2] != 47 && termData->transactionDate[5] != 47)
	{
		printf("\nWRONG_DATE");
		return WRONG_DATE;
	}
		
	else if (strlen(termData->transactionDate) != 10)
	{
		printf("\nWRONG_DATE");
		return WRONG_DATE;
	}
	else
	{
		printf("\nTERMINAL_OK");
		return TERMINAL_OK;
	}
		
}	
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	const float zero = 0;
	printf("\nPlease,Input the amount of money you want to transect:");
	scanf_s ("%f", & termData->transAmount);
	if (termData->transAmount <= 0)
	{
		printf("\nINVALID_AMOUNT");
		return INVALID_AMOUNT;
	}
	else
	{
		printf("\nTERMINAL_OK");
		return TERMINAL_OK;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint8_t YY[3]; 
	uint8_t MM[3];
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	
	YY[0] = cardData->cardExpirationDate[3];
	YY[1] = cardData->cardExpirationDate[4];
	YY[2] = '\0';
	int year_int = atoi(YY);
	year_int = year_int + 2000;

	MM[0] = cardData->cardExpirationDate[0];
	MM[1] = cardData->cardExpirationDate[1];
	MM[2] = '\0';
	int month_int = atoi(MM);

	if (year_int == (tm->tm_year + 1900))
	{
		if (month_int < (tm->tm_mon + 1))
		{
			printf("\nEXPIRED_CARD");
			return EXPIRED_CARD;
		}
		else
		{
			printf ("\nTERMINAL_OK");
			return TERMINAL_OK;
		}
	}
	else if (year_int < (tm->tm_year+1900))
		return EXPIRED_CARD;
	else
	{
		printf("\nTERMINAL_OK");
		return TERMINAL_OK;
	}

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	const float zero = 0;
	printf("\nthis for the bank not the user: set MaxAmount for transaction:");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0.0)
	{
		printf("\nINVALID_MAX_AMOUNT");
		return INVALID_MAX_AMOUNT;
	}
		else
		{
			printf("\nTERMINAL_OK");
			return TERMINAL_OK;
		}

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->maxTransAmount < termData->transAmount)
	{
		printf("\nEXCEED_MAX_AMOUNT");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("\nTERMINAL_OK");
		return TERMINAL_OK;
	}

}
