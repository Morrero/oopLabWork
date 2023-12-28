#pragma once
#include "CardSpec.h"
#include <iomanip>
#include<fstream>
#include<vector>
using namespace std;


template <typename T>
void input_positiv_number_range(string msg, T& val, T max_value) {
    while (1) {
        cout << msg << endl;
        cin >> val;
        if (!cin) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Значение должно быть числом" << endl;
        }
        else if (val < 0 || val > max_value) {
            cout << "Значение должно положительным числом" << endl;
        }
        else break;
    }
}
void input_string_check(string msg, char string[], int size, bool(*check_func)(char*));
bool stringCheck(char string[]);

int menu_pay_system(string msg);
void input_card_number(char* card_number);


class FIO {
public:
    char name[25];
    char surname[25];
    char middleName[25];
public:
    FIO() {
        strcpy_s(this->name, "N/A");
        strcpy_s(this->surname, "N/A");
        strcpy_s(this->middleName, "N/A");
    }
    FIO(FIO& obj) {
        strcpy_s(this->name, obj.name);
        strcpy_s(this->surname, obj.surname);
        strcpy_s(this->middleName, obj.middleName);
    }

};

class Card {
protected:
    char type[20];
    char card_number[17];
    float balance;
    int valid_year;
    int valid_month;
public:
    virtual void input() {
        input_card_number(card_number);
        balance = 0;
        get_valid_period(valid_month, valid_year);
    }
    virtual void output(){};
    virtual unique_ptr<Card> clone() = 0;
    static void get_valid_period(int& month, int& year) {
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        month = timeinfo.tm_mon; year = timeinfo.tm_year + 1905;
    }
    CardEnum getType();
    static void read(vector<Card*>& card_vector);
    static void write(vector<Card*>& card_vector);
    static void header() {
        cout << left << setw(18) << "Номер карты" << setw(20) << "Тип карты" << setw(9) << "Баланс" << setw(14) << "Срок действия" << endl;
        cout << setfill('-') << setw(67) << "" << endl;
        cout.fill(' ');
    }
    void short_decription() {
        cout << left << setw(18) << card_number << setw(20) << type << setw(9) << balance << setfill('0') << setw(2) << right << valid_month << "/" << setw(4) << valid_year << endl;
        cout << setfill('-') << setw(67) << "" << endl;
        cout.fill(' ');
    }
    char* getCardNumber() {
        return card_number;
    }
    void put_cash();
    void withdraw_cash();
};

class PrepaidCard : public Card {
protected:
    float replenishment_limit;
public:
    PrepaidCard() {}
    void input() {
        Card::input();
        strcpy_s(this->type, "Предоплаченная");
        input_positiv_number_range("Введите лимит пополнения в меяц: ", replenishment_limit, 200.0f);
    }
    PrepaidCard(PrepaidCard& obj){
        strcpy_s(this->type, "Предоплаченная");
        strcpy_s(this->card_number, obj.card_number);
        this->balance = obj.balance;
        this->valid_month = obj.valid_month;
        this->valid_year = obj.valid_year;
        this->replenishment_limit = obj.replenishment_limit;
    }
    PrepaidCard(PrepaidCardSpec* obj) {
        strcpy_s(this->type, "Предоплаченная");
        strcpy_s(this->card_number, obj->card_number);
        this->balance = obj->balance;
        this->valid_month = obj->valid_month;
        this->valid_year = obj->valid_year;
        this->replenishment_limit = obj->replenishment_limit;
    }
    unique_ptr<Card> clone()override { return  unique_ptr<Card>(new PrepaidCard(*this)); }
    void output() {}
};
class DebitCard : public Card {
protected:
    FIO owner;
public:
    void input() {
        input_string_check("Введите Фамилию: ", owner.surname, 25, stringCheck);
        input_string_check("Введите Имя: ", owner.name, 25, stringCheck);
        input_string_check("Введите  Отчество: ", owner.middleName, 25, stringCheck);
        strcpy_s(this->type, "Дебетовая");
        Card::input();
    }
    DebitCard() {}
    DebitCard(DebitCard& obj) {
        strcpy_s(this->owner.name, obj.owner.name);
        strcpy_s(this->owner.surname, obj.owner.surname);
        strcpy_s(this->owner.middleName, obj.owner.middleName);
        strcpy_s(this->type, "Дебетовая");
        strcpy_s(this->card_number, obj.card_number);
        this->balance = obj.balance;
        this->valid_month = obj.valid_month;
        this->valid_year = obj.valid_year;
    }
    DebitCard(DebitCardSpec* obj) {
        strcpy_s(this->owner.name, obj->name);
        strcpy_s(this->owner.surname, obj->surname);
        strcpy_s(this->owner.middleName, obj->middleName);
        strcpy_s(this->type, "Дебетовая");
        strcpy_s(this->card_number, obj->card_number);
        this->balance = obj->balance;
        this->valid_month = obj->valid_month;
        this->valid_year = obj->valid_year;
    }
    unique_ptr<Card> clone()override { return  unique_ptr<Card>(new DebitCard(*this)); }
    void output()override {}
};
class CreditCard : public Card {
protected:
    float percent;
    int repayment_period;
    FIO owner;
public:
    void input() {
        input_string_check("Введите Фамилию: ", owner.surname, 25, stringCheck);
        input_string_check("Введите Имя: ", owner.name, 25, stringCheck);
        input_string_check("Введите  Отчество: ", owner.middleName, 25, stringCheck);
        strcpy_s(this->type, "Кредитная");
        Card::input();
        input_positiv_number_range("Введите процент для займа: ", percent, 100.0f);
        input_positiv_number_range("Введите необходимый срок погашения: ", repayment_period, 365);
    }
    CreditCard() {}
    CreditCard(CreditCard& obj) {
        strcpy_s(this->owner.name, obj.owner.name);
        strcpy_s(this->owner.surname, obj.owner.surname);
        strcpy_s(this->owner.middleName, obj.owner.middleName);
        strcpy_s(this->type, "Дебетовая");
        strcpy_s(this->card_number, obj.card_number);
        this->balance = obj.balance;
        this->valid_month = obj.valid_month;
        this->valid_year = obj.valid_year;
        this->percent = obj.percent;
        this->repayment_period = obj.repayment_period;
    }
    CreditCard(CreditCardSpec* obj) {
        strcpy_s(this->owner.name, obj->name);
        strcpy_s(this->owner.surname, obj->surname);
        strcpy_s(this->owner.middleName, obj->middleName);
        strcpy_s(this->type, "Кредитная");
        strcpy_s(this->card_number, obj->card_number);
        this->balance = obj->balance;
        this->valid_month = obj->valid_month;
        this->valid_year = obj->valid_year;
        this->percent = obj->percent;
        this->repayment_period = obj->repayment_period;
    }
    unique_ptr<Card> clone()override { return  unique_ptr<Card>(new CreditCard(*this)); }
    void output()override {}
};