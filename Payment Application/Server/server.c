/*
* file:    server.c
* auther:  Manal Nabil Donia
*
* Created on August 19 2023
 */
 #include"server.h"
 #include<string.h>
 #define NULL ((void*)0)
 #define DB_ACCOUNTS_MAX  255
 #define DB_TRANSACTIONS_MAX  255


 static uint32_t SequenceNumber = 0;

 static ST_accountsDB_t accountsDB[DB_ACCOUNTS_MAX]={
      {2000.0,RUNNING,"8989 3746 1543 6851"}
     ,{1000.0,BLOCKED,"5807 0070 7604 3875"}
     ,{500.0,RUNNING,"8989 3746 1543 6858"}
     ,{8000.0,RUNNING,"5807 0070 7604 3870"}
     ,{7000.0,BLOCKED,"8989 3746 1573 6858"}};

 static ST_transaction_t transactionDB[DB_TRANSACTIONS_MAX]={0};



EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    ST_accountsDB_t account;

    //card file
    printf("\nEnter Card Holder Name :");
    getCardHolderName(&transData->cardHolderData);

    printf("\nEnter Card PAN : ");
    getCardPAN(&transData->cardHolderData);

    printf("\nEnter Card Expiry Date :");
    getCardExpiryDate(&transData->cardHolderData);

    //terminal file

    printf("\nEnter Transaction Date : ");
	getTransactionDate(&transData->terminalData);

	setMaxAmount(&transData->terminalData, 3000.00);

	printf("\nEnter Transaction amount : ");
	getTransactionAmount(&transData->terminalData);

	//check on server file

	if((isValidAccount(&transData->cardHolderData,&account))==SERVER_OK)
    {
        printf("\n SERVER_OK");

        //if PAN valid check if account RUNNING

        if(isBlockedAccount(&account)==SERVER_OK)
        {
            printf("\n SERVER_OK");

            //if account RUNNING check if amount available

            if(isAmountAvailable(&transData->terminalData,&account)==SERVER_OK)
            {
                printf("\n SERVER_OK");


                if(isCardExpired(&transData->cardHolderData,&transData->terminalData)==TERMINAL_OK)
                {
                    printf("\nAPPROVED");
                    return APPROVED;
                }
                else
                {
                    printf("\nFRAUD_CARD");
                    return FRAUD_CARD;

                }
            }
                else   //isAmountAvailable
            {
                        printf("\nDECLINED_INSUFFECIENT_FUND");
                        return DECLINED_INSUFFECIENT_FUND;
            }
                    //end check

        }

            else   //isBlockedAccount
        {
                printf("\nDECLINED_STOLEN_CARD");
                return DECLINED_STOLEN_CARD;
        }

    }
        else   //isValidAccount
    {
            printf("\nINTERNAL_SERVER_ERROR");
            return INTERNAL_SERVER_ERROR;
    }

}

EN_serverError_t isValidAccount(ST_cardData_t*cardData,ST_accountsDB_t *accountRefrence){
    int x=0;


	for (int i = 0; i < DB_ACCOUNTS_MAX; i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
			accountRefrence->state = accountsDB[i].state;
			accountRefrence->balance = accountsDB[i].balance;
			strncpy_s(accountRefrence->primaryAccountNumber, 20, accountsDB[i].primaryAccountNumber);

			printf("Actual  Result : SERVER_OK\n");
			x=1;
			return SERVER_OK;
		}}

		if(x==0)
        {
			accountRefrence = NULL;

			printf("Actual Result : ACCOUNT_NOT_FOUND\n");

		}

	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    EN_serverError_t stat = BLOCKED_ACCOUNT;

    if(0==accountRefrence->state)
    {
        printf("Actual Result : SERVER_OK\n");
        stat = SERVER_OK;
    }
    else
    {
        printf("Actual Result : BLOCKED_ACCOUNT\n");
    }

    return stat;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t *accountRefrence){


	if (termData->transAmount <= accountRefrence->balance) {
		printf("Actual  Result : SERVER_OK");
		return SERVER_OK;
	}
	else {
		printf("Actual  Result : LOW_BALANCE");
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
     EN_serverError_t state = SERVER_OK;

     if(SequenceNumber>=255)
     {
         printf("Actual Result : SAVING_FAILED\n");
         state = SAVING_FAILED;
     }

     else
      {
        transData->transactionSequenceNumber = SequenceNumber;
        //card file
        strcpy(transactionDB[SequenceNumber].cardHolderData.cardHolderName,transData->cardHolderData.cardHolderName);
        strcpy(transactionDB[SequenceNumber].cardHolderData.primaryAccountNumber,transData->cardHolderData.primaryAccountNumber);
        strcpy(transactionDB[SequenceNumber].cardHolderData.cardExpirationDate,transData->cardHolderData.cardExpirationDate);

        //terminal file
        transactionDB[SequenceNumber].terminalData.transAmount = transData->terminalData.transAmount;
        strcpy(transactionDB[SequenceNumber].terminalData.transactionDate,transData->terminalData.transactionDate);

        //server file
        transactionDB[SequenceNumber].transstate = transData->transstate;
	    accountsDB[SequenceNumber].balance = accountsDB[SequenceNumber].balance - transData->terminalData.transAmount;

        printf("Your updated balance is : %f\n",accountsDB[SequenceNumber].balance);
        printf("Actual Result : SERVER_OK\n");

        ++SequenceNumber;
      }


    return state;


}

void listSavedTransactions(){
     ST_transaction_t data;
    recieveTransactionData(&data);
	saveTransaction(&data);
	printf("#########################\n");
	printf("Transaction Sequence Number : %d\n", SequenceNumber);
	printf("Transaction Date : %s\n", &data.terminalData.transactionDate);
	printf("Transaction Amount : %f\n", &data.terminalData.transAmount);

	switch (transactionDB[SequenceNumber].transstate) {
	case APPROVED:printf("APPROVED\n"); break;
	case DECLINED_INSUFFECIENT_FUND:printf("DECLINED_INSUFFECIENT_FUND\n"); break;
	case DECLINED_STOLEN_CARD:printf("DECLINED_STOLEN_CARD\n"); break;
	case FRAUD_CARD:printf("FRAUD_CARD\n"); break;
	case INTERNAL_SERVER_ERROR:printf("INTERNAL_SERVER_ERROR\n"); break;
	}

	printf("Terminal Max Amount : %f\n", &data.terminalData.maxTransAmount);
	printf("Cardholder Name : %s\n", &data.cardHolderData.cardHolderName);
	printf("PAN: %s\n", &data.cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date : %s\n", &data.cardHolderData.cardExpirationDate);
	printf("#########################\n");
}

void isValidAccountTest(){
    ST_terminalData_t data;
	ST_accountsDB_t ref;


	printf("Tester Name : Manal Nabil \n");
	printf("Function name : isValidAccount\n");
	printf("Test Case 1 : Exisiting : 8989 3746 1543 6851 \nExpected Result : SERVER_OK\nInput Data : ");
	getCardPAN(&data);
	isValidAccount(&data, &ref);
	printf("\n\nTest Case 2 : Not existing : 1234 1234 1234 1234\nExpected Result : ACCOUNT_NOT_FOUND\nInput Data : ");
	getCardPAN(&data);
	isValidAccount(&data, &ref);

}

void isBlockedAccountTest(){
    ST_terminalData_t data;
	ST_accountsDB_t ref;

	printf("Tester Name : Manal Nabil \n");
	printf("Function name : isBlockedAccount\n");
	printf("Test Case 1 : RUNNING : 8989 3746 1543 6851 \nExpected Result : SERVER_OK\nInput Data : ");
    getCardPAN(&data);
	isValidAccount(&data, &ref);
	isBlockedAccount(&ref);

	printf("\n\nTest Case 2 : BLOCKED : 5807 0070 7604 3875\nExpected Result : BLOCKED_ACCOUNT\nInput Data : ");
    getCardPAN(&data);
	isValidAccount(&data, &ref);
	isBlockedAccount(&ref);
}

void isAmountAvailableTest(){
    ST_transaction_t data;
	ST_accountsDB_t account;
	account.balance=1000.00;

	printf("Tester Name : Manal Nabil \n");
	printf("Function name : isAmountAvailable\n");
	printf("Test Case 1 : balance=1000:  \nExpected Result : SERVER_OK \nInput data : ");

	getTransactionAmount(&data);
	isAmountAvailable(&data,&account);

	printf("\n\nTest Case 2 : balance=1000  \nExpected Result : LOW_BALANCE \nInput data : ");

	getTransactionAmount(&data);
	isAmountAvailable(&data,&account);

}


void saveTransactionTest(){
    ST_transaction_t data;

	printf("Tester Name : Manal Nabil \n");
	printf("Function name : saveTransaction\n");
	printf("Test Case 1 : SERVER_OK \nExpected Result : SERVER_OK\nInput Data : ");
    saveTransaction(&data);

	printf("\n\nTest Case 2 : SAVING_FAILED \nExpected Result : SAVING_FAILED\nInput Data : ");

	//SequenceNumber=266;
	saveTransaction(&data);
}

void recieveTransactionDataTest(){
    ST_transaction_t data;


	printf("Tester Name : manal nabil donia\n");
	printf("Function name : recieveTransactionData\n");
	printf("Test Case 1 : APPROVED \nExpected Result : APPROVED\nInput Data : ");
	recieveTransactionData(&data);

	printf("\n\nTest Case 2 : DECLINED_INSUFFECIENT_FUND\nExpected Result : DECLINED_INSUFFECIENT_FUND\nInput Data : ");
	recieveTransactionData(&data);

	printf("\n\nTest Case 3 : DECLINED_STOLEN_CARD\nExpected Result : DECLINED_STOLEN_CARD\nInput Data : ");
	recieveTransactionData(&data);

	printf("\n\nTest Case 4 : FRAUD\nExpected Result : FRAUD_CARD\nInput Data : ");
	recieveTransactionData(&data);

	printf("\n\nTest Case 5 : INTERNAL_SERVER_ERROR \nExpected Result : INTERNAL_SERVER_ERROR\nInput Data : ");
	recieveTransactionData(&data);
}

void listSavedTransactionsTest(){
    ST_transaction_t data;

    printf("Tester Name : manal nabil donia\n");
	printf("Function name : listSavedTransactions\n");
	printf("Test Case 1 : ");

	listSavedTransactions();

	printf("Test Case 2 : ");

	listSavedTransactions();

}
