/*
* file:    Terminal.c
* auther:  Manal Nabil Donia
*
* Created on August 19 2023
 */

 #include"Terminal.h"
 #include<string.h>
 #define NULL ((void*)0)

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
EN_cardError_t state = TERMINAL_OK;
uint8_t TransactionDate[11]={0};

gets(TransactionDate);

uint8_t len =strlen(TransactionDate);


if((len!=10)||
   (((void*)0)==TransactionDate)||
   (TransactionDate[0]>'3')||
   ((TransactionDate[0]=='3'))&&(TransactionDate[1]>'1')||
   (TransactionDate[6]<'2')||
   (TransactionDate[3]>'1')||
   ((TransactionDate[3]=='1')&&(TransactionDate[4]>'2')))

{
    //printf("Actual Result : WRONG_DATE\n");
    state=WRONG_DATE;
}
else
    {

        for(int i=0;i<len;i++)
        {
            termData->transactionDate[i]=TransactionDate[i];
        }
        termData->transactionDate[len]='\0';
        //printf("Actual Result : TERMINAL_OK\n");
    }

    return state;
}


EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    EN_terminalError_t state = TERMINAL_OK;

   if(
    (cardData->cardExpirationDate[4] < termData->transactionDate[9])||
       ((termData->transactionDate[3])>(cardData->cardExpirationDate[0]))||
       (((termData->transactionDate[3])==(cardData->cardExpirationDate[0]))&&((termData->transactionDate[4])>(cardData->cardExpirationDate[1]))))
    {
        printf("Actual Result : EXPIRED_CARD\n");
        state = EXPIRED_CARD;
    }
    else
    {
        printf("Actual Result : TERMINAL_OK\n");
    }


    return state;

}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    EN_cardError_t state = TERMINAL_OK;
    float TransactionAmount;

    scanf("%f",&TransactionAmount);

    if((TransactionAmount==0)||(TransactionAmount<0))
      {
         // printf("Actual Result : INVALID_AMOUNT\n");
          state=INVALID_AMOUNT;
        }
    else
        {
            termData->transAmount=TransactionAmount;
           // printf("Actual Result : TERMINAL_OK\n");
        }
        return state;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){

    EN_cardError_t state = TERMINAL_OK;


    if(termData->transAmount>termData->maxTransAmount)
    {
        printf("Actual Result : EXCEED_MAX_AMOUNT\n");
        state=EXCEED_MAX_AMOUNT;
    }
    else
    {
        printf("Actual Result : TERMINAL_OK\n");
    }
    return state;

}


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    EN_cardError_t state = TERMINAL_OK;


    if((maxAmount==0)||(maxAmount<0))
    {
        //printf("Actual Result : INVALID_MAX_AMOUNT\n");
        state=INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount=maxAmount;
        //printf("Actual Result : TERMINAL_OK\n");
    }

    return state;

}

void getTransactionDateTest(){
    ST_terminalData_t terminal;
printf("Tester Name : Manal Nabil\n");
printf("Function name : getTransactionDate\n");
printf("Test case 1 : NULL \nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 2 : 22/12/20232 \nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 3 : 22/12\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 4 : 32/12/2025\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 5 : 22/13/2025\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 6 : 22/21/2025\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 7 : 22/12/1999\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 8 : 42/12/2025\nExpected output : WRONG_DATE\nInput Data : ");
getTransactionDate(&terminal);
printf("Test case 9 : 22/12/2025\nExpected output : TERMINAL_OK\nInput Data : ");
getTransactionDate(&terminal);
}

void isCardExpiredTest(){
    ST_terminalData_t terminal;
    ST_cardData_t card;
printf("Tester Name : Manal Nabil\n");
printf("Function name : isCardExpired\n");


printf("Test case 1 : (11/26)_(05/11/2027)\nExpected output : EXPIRED_CARD\nInput Data (exp): ");
getCardExpiryDate(&card);
printf("Input Data (trans) :");
getTransactionDate(&terminal);
isCardExpired(&card,&terminal);


printf("Test case 2 : (01/26)_(05/12/2026) \nExpected output : EXPIRED_CARD\nInput Data (exp) : ");
getCardExpiryDate(&card);
printf("Input Data (trans) :");
getTransactionDate(&terminal);
isCardExpired(&card,&terminal);


printf("Test case 3 : (11/26)_(05/12/2026)\nExpected output : EXPIRED_CARD\nInput Data (exp): ");
getCardExpiryDate(&card);
printf("Input Data (trans) :");
getTransactionDate(&terminal);
isCardExpired(&card,&terminal);


printf("Test case 4 : (11/26)_(05/11/2025)\nExpected output : TERMINAL_OK\nInput Data (exp): ");
getCardExpiryDate(&card);
printf("Input Data (trans) :");
getTransactionDate(&terminal);
isCardExpired(&card,&terminal);

}

void setMaxAmountTest(){
    ST_terminalData_t tarminal;
printf("Tester Name : Manal Nabil\n");
printf("Function name : setMaxAmount\n");
printf("Test case 1 : MaxAmount=0 \nExpected output : INVALID_MAX_AMOUNT\n ");
float MAX ;
MAX =0.00;
setMaxAmount(&tarminal,MAX);
printf("Test case 2 : MaxAmount<0 \nExpected output : INVALID_MAX_AMOUNT\n ");
MAX =-100.00;
setMaxAmount(&tarminal,MAX);
printf("Test case 3 : MaxAmount>0=(1000)\nExpected output : TERMINAL_OK\n ");
MAX =100000.00;
setMaxAmount(&tarminal,MAX);
}

void getTransactionAmountTest(){
        ST_terminalData_t tarminal;
printf("Tester Name : Manal Nabil\n");
printf("Function name : getTransactionAmount\n");
printf("Test case 1 : Amount=0 \nExpected output : INVALID_AMOUNT\nInput Data : ");
getTransactionAmount(&tarminal);
printf("Test case 2 : Amount<0 \nExpected output : INVALID_AMOUNT\nInput Data : ");
getTransactionAmount(&tarminal);
printf("Test case 2 : Amount=500\nExpected output : TERMINAL_OK\nInput Data : ");
getTransactionAmount(&tarminal);
}

void isBelowMaxAmountTest(){
     ST_terminalData_t terminal;
printf("Tester Name : Manal Nabil\n");
printf("Function name : isBelowMaxAmount\n");
terminal.transAmount=1000.00;
terminal.maxTransAmount=100.00;
printf("Test case  : Amount>MaxAmount \nExpected output : EXCEED_MAX_AMOUNT\n ");
isBelowMaxAmount(&terminal);
terminal.transAmount=100.00;
terminal.maxTransAmount=1000.00;
printf("Test case  : Amount<MaxAmount  \nExpected output : TERMINAL_OK\n");
isBelowMaxAmount(&terminal);

}
