/*
* file:    app.c
* auther:  Manal Nabil Donia
*
* Created on August 19 2023
 */
 #include"app.h"
 #include<string.h>
 #define NULL ((void*)0)

void appStart(void) {
    ST_transaction_t trans;
	EN_transState_t transvariable =  recieveTransactionData(&trans);

	ST_accountsDB_t ref;
	if (isCardExpired(&trans.cardHolderData, &trans.terminalData) == TERMINAL_OK) {

    if (isBelowMaxAmount(&trans.terminalData) == TERMINAL_OK) {

    if (isValidAccount(&trans.cardHolderData, &ref) == SERVER_OK) {

    if (transvariable == APPROVED)
				{
    if (saveTransaction(&trans) == SERVER_OK)
					{
						printf("\nTranscation Saved");
					}
    else
						printf("\nSaving Failed");
				}
    else if (transvariable == DECLINED_STOLEN_CARD)
				{
					printf("\nDeclined Invalid Account");
				}
    else if (transvariable == DECLINED_INSUFFECIENT_FUND) {
					printf("\nInsuffecient Funds");
				}
    else {
					printf("Hi");
				}

			}
		}

    else if (isBelowMaxAmount(&trans.terminalData) == EXCEED_MAX_AMOUNT) {
			printf("Exceed Max Amount");
		}
	}
	else if (isCardExpired(&trans.cardHolderData, &trans.terminalData) == EXPIRED_CARD) {
		printf("Expired Card");
	}


}
