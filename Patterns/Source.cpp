#include<vector>
#include<Windows.h>
#include<algorithm>
#include"Cards.h"
#include"CardWork.h"
#include "CardFabric.h"
using namespace std;

int confirmation()
{
	int confirm = 0;
	cout << "\nДля подтверждения действия нажмите 1" << endl;
	cin >> confirm;
	if (cin.fail()) {
		cout << "A variable cannot contain these characters" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	return confirm;
}

int menu_main() {
	system("cls");
	int choice = -1;
	cout << "\t\tMENU"<<endl;
	cout << "-------------------------------"<<endl;
	cout <<
		"1. Общий просмотр\n"
		"2. Добавить Предоплаченную карту\n"
		"3. Добавить Дебетовую карту\n"
		"4. Добавить Кредитную карту\n"
		"5. Удалить\n"
		"6. Положить деньги\n"
		"7. Снять деньги\n"
		"0. Выход \n"
		"Ваш выбор: ";
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}
int menu_fabric() {
	system("cls");
	int choice = -1;
	cout <<
		"1. Фабрика\n"
		"2. Фабрика с париметрами\n"
		"3. Полиморфная фабрика\n"
		"4. Полиморфное копирование\n"
		"Ваш выбор: ";
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Card*> cards_vec;
	Card::read(cards_vec);
	CardsFabric* fabric = new  CardsFabric;
	while(1){
		switch (menu_main()){
		case 1: {
			Card::header();
			for (auto it : cards_vec)
				it->short_decription();
			system("pause");
		}break;
		case 2: {
			switch (menu_fabric())
			{
			case 1: {
				Card* card = fabric->makeCard(CardEnum::PrepaidCard_e);
				card->input();
				cards_vec.push_back(card);
				break;
			}
			case 2: {
				char card_number[17];
				int valid_year;
				int valid_month;
				float replenishment_limit;
				input_card_number(card_number);
				Card::get_valid_period(valid_month, valid_year);
				input_positiv_number_range("Введите лимит пополнения в меяц: ", replenishment_limit, 300.0f);
				CardSpec* spec = new PrepaidCardSpec(card_number, valid_month, valid_year, replenishment_limit);
				Card* card = fabric->makeCard(spec);
				cards_vec.push_back(card);
				break;
			}
			case 3: {
				CardWork* prep = new MakingPrepaidCard;
				Card* card = prep->makeCard();
				card->input();
				cards_vec.push_back(card);
				break;
			}
			case 4: {
				unique_ptr<Card> p(new PrepaidCard);
				p->input();
				unique_ptr<Card> b = p->clone();
				cards_vec.push_back(b.get());
				break;
			}
			default: cout << "Неверный ввод" << endl; break;
			}
		} break;
		case 3: {
			Card* card = fabric->makeCard(CardEnum::DebitCard_e);
			card->input();
			cards_vec.push_back(card);
		} break;
		case 4: {
			Card* card = fabric->makeCard(CardEnum::CreditCard_e);
			card->input();
			cards_vec.push_back(card);
		} break;
		case 5: {
			char card_num[20];
			cout << "Введите номер карты, который хотите удалить:" << endl;
			rewind(stdin);
			cin.getline(card_num, 20);
			vector<Card*>::iterator card = find_if(cards_vec.begin(), cards_vec.end(), [&](Card*& card_f) {return !strcmp(card_num, card_f->getCardNumber()); });
			if (card == cards_vec.end()) {
				cout << "\nТакой карты нет" << endl;
				system("pause");
				break;
			}
			if (confirmation() == 1)
				cards_vec.erase(card);
			else cout << "\nКарта не удалена" << endl;
			system("pause");
		} break;
		case 6: {
			char card_num[20];
			cout << "Введите номер карты, куда хотите положить деньги:" << endl;
			rewind(stdin);
			cin.getline(card_num, 20);
			vector<Card*>::iterator card = find_if(cards_vec.begin(), cards_vec.end(), [&](Card*& card_f) {return !strcmp(card_num, card_f->getCardNumber()); });
			if (card == cards_vec.end()) {
				cout << "\nТакой карты нет" << endl;
				system("pause");
				break;
			}
			(*card)->put_cash();
		} break;
		case 7: {
			char card_num[20];
			cout << "Введите номер карты, с который хотите снять деньги:" << endl;
			rewind(stdin);
			cin.getline(card_num, 20);
			vector<Card*>::iterator card = find_if(cards_vec.begin(), cards_vec.end(), [&](Card*& card_f) {return !strcmp(card_num, card_f->getCardNumber()); });
			if (card == cards_vec.end()) {
				cout << "\nТакой карты нет" << endl;
				system("pause");
				break;
			}
			(*card)->withdraw_cash();
		}break;
		case 0: {
			Card::write(cards_vec);
			return 0;
		}
		default:
			break;
		}
	}
}