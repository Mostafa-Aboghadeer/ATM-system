#include <stdio.h>
#include <string.h>
#include "card.h"
#include "terminal.h"
#include <time.h>
#include "server.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>



int compare_strings(uint8_t a[], uint8_t b[])
{
	int c = 0;

	while (a[c] == b[c]) {
		if (a[c] == '\0' || b[c] == '\0')
			break;
		c++;
	}

	if (a[c] == '\0' && b[c] == '\0')
		return 0;
	else
		return -1;
}
struct ST_accountsDB_t server_sideaccounts[255] =
{
		{2000.0, RUNNING,"8989374615436851"},
		{50000.0, RUNNING,"8989384615436851"},
		{100000.0, BLOCKED,"5807007076043875"},
		{5000.0, RUNNING, "8989384615436789"},
		{890000.0, RUNNING,"8978984615436851"},
};
struct  ST_transaction_t server_sidetransactions[255] = { 0 };

ST_cardData_t card;
ST_terminalData_t terminal;
ST_transaction_t transaction;
ST_accountsDB_t account;
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	if (getCardHolderName(&card))
	{
		printf("WRONG_NAME");
		return WRONG_NAME;
	}

	else if (getCardExpiryDate(&card))
	{
		printf("WRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}

	else if (getCardPAN(&card))
	{
		
		printf("WRONG_PAN");
		return WRONG_PAN;
	}
	else
	{
		for (int i = 0; i < 255; i++)
		{
			
			if (!strcmp(server_sideaccounts[i].primaryAccountNumber,sahred))
			{
				printf("%d", server_sideaccounts[index_truePAN].state);
				index_truePAN = i;
				return SERVER_OK;

			}
		}
		printf("ACCOUNT_NOT_FOUND");
		return ACCOUNT_NOT_FOUND;
	}
	
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (getTransactionDate(&terminal))
	{
		printf("WRONG_DATE");
		return WRONG_DATE;
	}
	else if (isCardExpired(&card,&terminal))
	{
		printf("EXPIRED_CARD");
		return EXPIRED_CARD;
	}
	else if (setMaxAmount(&terminal))
	{
		printf("INVALID_MAX_AMOUNT");
		return INVALID_MAX_AMOUNT;
	}
	else if (getTransactionAmount(&terminal))
	{
		printf("INVALID_AMOUNT");
		return INVALID_AMOUNT;
	}
	else if (isBelowMaxAmount(&terminal))
	{
		printf("EXCEED_MAX_AMOUNT");
		return EXCEED_MAX_AMOUNT;
	}
	else if (termData->transAmount > server_sideaccounts[index_truePAN].balance)
	{
		printf("LOW_BALANCE");
		return LOW_BALANCE;
	}
	else
	{
		printf("SERVER_OK");
		return SERVER_OK;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (server_sidetransactions->transactionSequenceNumber < 255)
	{
		server_sidetransactions[counter].cardHolderData = transData->cardHolderData;
		server_sidetransactions[counter].terminalData = transData->terminalData;
		server_sidetransactions[counter].transState = transData->transState;
		counter++;
		if (getTransaction(0, &transaction))
			return SAVING_FAILED;
		else SERVER_OK;
	}
	else
		return SAVING_FAILED;
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	if (transactionSequenceNumber > counter)
		return TRANSACTION_NOT_FOUND;
	else
	{
		server_sidetransactions[transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		server_sidetransactions[transactionSequenceNumber].terminalData = transData->terminalData;
		server_sidetransactions[transactionSequenceNumber].transState = transData->transState;
		return SERVER_OK;
	}
		
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (server_sideaccounts[index_truePAN].state)
	{
		return DECLINED_STOLEN_CARD;
	}
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&card, &account))
	{
		printf("FRAUD_CARD");
		return FRAUD_CARD;
	}
	else if (isBlockedAccount(&account))
	{
		printf("DECLINED_STOLEN_CARD");
		return DECLINED_STOLEN_CARD;
	}

	else if (isAmountAvailable(&terminal))
	{
		printf("DECLINED_INSUFFECIENT_FUND");
		return DECLINED_INSUFFECIENT_FUND;
	}

	

	else if (saveTransaction(&transaction))
	{
		printf("INTERNAL_SERVER_ERROR");
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		server_sideaccounts[index_truePAN].balance = server_sideaccounts[index_truePAN].balance - transData->terminalData.transAmount;
		printf("APPROVED");
		return APPROVED;
	}
		
}
