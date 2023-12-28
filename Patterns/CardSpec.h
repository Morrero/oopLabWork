#pragma once
#include"CardEnum.h"
#include<string>
#include<iostream>

using namespace std;

class CardSpec {
public:
	char type[25];
	char card_number[17];
	float balance;
	int valid_year;
	int valid_month;
	virtual CardEnum cardType() = 0;
};

class PrepaidCardSpec : public CardSpec {
public:
	PrepaidCardSpec(char card_number[], int valid_month, int valid_year, float replenishment_limit) {
		strcpy_s(this->type, "Предоплаченная");
		strcpy_s(this->card_number, card_number);
		this->balance = 0;
		this->valid_month = valid_month;
		this->valid_year = valid_year;
		this->replenishment_limit = replenishment_limit;
	}
	CardEnum cardType() { return PrepaidCard_e; }
	float replenishment_limit;
};


class DebitCardSpec : public CardSpec {
public:
	DebitCardSpec(char card_number[], int valid_month, int valid_year, float replenishment_limit,char name[], char surname[], char middleName[]) {
		strcpy_s(this->name, name);
		strcpy_s(this->surname, surname);
		strcpy_s(this->middleName, middleName);
		strcpy_s(this->type, "Дебетовая");
		strcpy_s(this->card_number, card_number);
		this->balance = balance;
		this->valid_month = valid_month;
		this->valid_year = valid_year;
	}
	CardEnum cardType() { return DebitCard_e; }
	char name[25];
	char surname[25];
	char middleName[25];
};
class CreditCardSpec : public CardSpec {
public:
	CreditCardSpec(char card_number[], int valid_month, int valid_year, float replenishment_limit, char name[], char surname[], char middleName[], float percent, int repayment_period) {
		strcpy_s(this->name, name);
		strcpy_s(this->surname, surname);
		strcpy_s(this->middleName, middleName);
		strcpy_s(this->type, "Дебетовая");
		strcpy_s(this->card_number, card_number);
		this->balance = balance;
		this->valid_month = valid_month;
		this->valid_year = valid_year;
		this->percent = percent;
		this->repayment_period = repayment_period;
	}
	CardEnum cardType() { return CreditCard_e; }
	char name[25];
	char surname[25];
	char middleName[25];
	float percent;
	int repayment_period;
};