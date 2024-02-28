/*
* file:    card.c
* auther:  Manal Nabil Donia
*
* Created on August 19 2023
 */

#include"card.h"
#include<string.h>
#include <stdbool.h>
#define NULL ((void*)0)

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
EN_cardError_t state = CARD_OK;
uint8_t CardHolderName[25]={0};

gets(CardHolderName);

uint8_t len =strlen(CardHolderName);

if((len<20)||(len>24)||(((void*)0)==CardHolderName))
{
    //printf("Actual Result : WRONG_NAME\n");
    state=WRONG_NAME;
}
else
{
    for(int i=0;i<len;i++)
    {
       cardData->cardHolderName[i]= CardHolderName[i] ;
    }
    cardData->cardHolderName[len]='\0';
    //printf("Actual Result : CARD_OK\n");
}

    return state;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    EN_cardError_t  state = CARD_OK;
    uint8_t CardExpiryDate[6]={0};

    gets(CardExpiryDate);

    uint8_t len =strlen(CardExpiryDate);


   if((len!=5)||(((void*)0)==CardExpiryDate)||(CardExpiryDate[2] != '/')||(CardExpiryDate[0]>'1')||((CardExpiryDate[0]=='1')&&(CardExpiryDate[1]>'2'))||(CardExpiryDate[3]<'2'))
    {
        //printf("Actual Result : WRONG_EXP_DATE\n");
         state=WRONG_EXP_DATE;
    }

    else{
        for(int i=0;i<len;i++)
        {
            cardData->cardExpirationDate[i]=CardExpiryDate[i];
        }
        cardData->cardExpirationDate[len]='\0';
        //printf("Actual Result : CARD_OK\n");
        }

    return state;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    EN_cardError_t  state = CARD_OK;
    uint8_t CardPAN[20]={0};
    uint8_t check = 0;
    gets(CardPAN);

    uint8_t len = strlen(CardPAN);

    for(int i=0;i<len;i++)
    {
        if((CardPAN[i]>'9')&&(CardPAN[i]!=' '))
        {
            check = 1;
        }
    }

    if((len>19)||(len<16)||(((void*)0)==CardPAN))
    {
        //printf("Actual Result : WRONG_PAN\n");
        state = WRONG_PAN;
    }
    else if(1==check)
    {
        //printf("Actual Result : WRONG_PAN\n");
        state = WRONG_PAN;
    }

    else
        {
            for(int i=0;i<len;i++)
            {
                cardData->primaryAccountNumber[i]=CardPAN[i];
            }
            cardData->primaryAccountNumber[len]='\0';
            //printf("Actual Result : CARD_OK\n");
        }
    return state;

}

void getCardExpiryDateTest(){
        ST_cardData_t card;
printf("Tester Name : Manal Nabil\n");
printf("Function name : getCardExpiryDate\n");
printf("Test case 1 : Null \nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 2 : 1/22 \nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 3 : 12.26\nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 4 : 22/26\nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 5 : 13/26\nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 6 : 11/16\nExpected output : WRONG_EXP_DATE\nInput Data : ");
getCardExpiryDate(&card);
printf("Test case 7 : 02/27\nExpected output : CARD_OK\nInput Data : ");
getCardExpiryDate(&card);
}
void getCardHolderNameTest(){
    ST_cardData_t card;
printf("Tester Name : Manal Nabil\n");
printf("Function name : getCardHolderName\n");
printf("Test case 1 : Null \nExpected output : WRONG_NAME\nInput Data : ");
getCardHolderName(&card);
printf("Test case 2 : menna \nExpected output : WRONG_NAME\nInput Data : ");
getCardHolderName(&card);
printf("Test case 3 : menna Ahmed Ahmed Nabil Donia\nExpected output : WRONG_NAME\nInput Data : ");
getCardHolderName(&card);
printf("Test case 4 : menna Nabil Ahmed Donia\nExpected output : CARD_OK\nInput Data : ");
getCardHolderName(&card);
}
void getCardPANTest(){
    ST_cardData_t card;
printf("Tester Name : Manal Nabil\n");
printf("Function name : getCardPAN\n");
printf("Test case 1 : Null \nExpected output : WRONG_PAN\nInput Data : ");
getCardPAN(&card);
printf("Test case 2 : 12345 \nExpected output : WRONG_PAN\nInput Data : ");
getCardPAN(&card);
printf("Test case 3 : 123456789123456789123456789\nExpected output : WRONG_PAN\nInput Data : ");
getCardPAN(&card);
printf("Test case 4 : 1234567891234hgfk\nExpected output : WRONG_PAN\nInput Data : ");
getCardPAN(&card);
printf("Test case 5 : 8989 3746 1543 6851\nExpected output : CARD_OK\nInput Data : ");
getCardPAN(&card);
printf("Test case 6 : 8989374615436851\nExpected output : CARD_OK\nInput Data : ");
getCardPAN(&card);

}
