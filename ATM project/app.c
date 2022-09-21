#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
int main()
{
	
	ST_cardData_t card;
	ST_terminalData_t terminal;
	ST_transaction_t transaction;
	ST_accountsDB_t account;
	printf("%d", recieveTransactionData(&transaction));
	return 0;
}