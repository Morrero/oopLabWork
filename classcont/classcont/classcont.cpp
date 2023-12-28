#include<iostream>
#include<string>
#include <stack>
#include <queue>
#include <vector>
#include <Windows.h>
#include <typeinfo>
#include <fstream>
#include <regex>
#include <iomanip>
#include <conio.h>

using namespace std;

inline int Julian(const int* date) {
	int a = (14 - date[1]) / 12;
	int y = date[2] + 4800 - a;
	int m = date[1] + 12 * a - 3;
	int JDN = date[0] + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
	return JDN;
}
int menu_main() {
	int choice = -1;
	cout <<
		"1. Просмотр абонентов\n"
		"2. Добавить абонента\n"
		"3. Удалить абонента\n"
		"4. Просмотр акций\n"
		"5. Добавить акцию\n"
		"6. Удалить акцию\n"
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
int menu_print() {
	int choice = -1;
	cout <<
		"1. Вывести через очередь\n"
		"2. Вывести через стек\n"
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
bool stringCheck(char string[]) {
	int i = 0;
	while (i != strlen(string))
		if (!isalpha(string[i]) && !(string[i] >= 'А' && string[i] <= 'я') && !(string[i] == 'ё') && !(string[i] == 'Ё') && !(string[i] == '-') && !(string[i] == ' ') && !(string[i] >= 48 && string[i] <= 57))return false;
		else i++;
	return true;
}
bool mobile_number_check(char number[])
{
	regex reg_number("^[\+][0-9]{3,4}[' '|\(]?[' '|\(]?[0-9]{2,3}[' '|[\)]?[' '|\(]?[0-9]{3}[-|' ']?[0-9]{4,6}$");
	if (regex_match(number, reg_number))
		return true;
	return false;
}
void input_string_check(string msg, char string[], int size, bool(*check_func)(char*)) {
	setlocale(LC_ALL, "ru");
	while (1) {
		cout << msg << endl;
		rewind(stdin);
		cin.getline(string, size);
		if (!check_func(string)) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void input_date(int* date) {
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	while (1) {
		cout << "Введите день: ";
		cin >> date[0];
		if (!cin || date[0] < 1 || date[0]>31) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Некорректное значение" << endl;
		}
		else break;
	}
	while (1) {
		cout << "Введите месяц: ";
		cin >> date[1];
		if (!cin || date[1] < 1 || date[1]>12) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Некорректное значение" << endl;
		}
		else break;
	}

	while (1) {
		cout << "Введите год: ";
		cin >> date[2];
		if (!cin || date[2] < 1900 + timeinfo.tm_year || (timeinfo.tm_mday > date[0] && timeinfo.tm_mon + 1 >= date[1] && 1900 + timeinfo.tm_year == date[2]) || (timeinfo.tm_mon + 1 > date[1] && 1900 + timeinfo.tm_year == date[2])) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Некорректное значение" << endl;
		}
		else break;
	}
}
class Subscriber {
protected:
	char number[19];
	char name[25];
	char surname[25];
	char tariff[35];
	int end_date[3];
public:
	Subscriber() {
		strcpy_s(this->number, "N/A");
		strcpy_s(this->name, "N/A");
		strcpy_s(this->surname, "N/A");
		strcpy_s(this->tariff, "N/A");
		end_date[0] = 0;
		end_date[1] = 0;
		end_date[2] = 0;
	}
	Subscriber(const Subscriber& orig) {
		strcpy_s(this->number, orig.number);
		strcpy_s(this->name, orig.name);
		strcpy_s(this->surname, orig.surname);
		strcpy_s(this->tariff, orig.tariff);
		end_date[0] = orig.end_date[0];
		end_date[1] = orig.end_date[1];
		end_date[2] = orig.end_date[2];

	}
	void set_number(char number[]) {
		strcpy_s(this->number, number);
	}
	char* get_number() {
		return number;
	}
	void set_name(char name[]) {
		strcpy_s(this->name, name);
	}
	char* get_name() {
		return name;
	}
	void set_surname(char surname[]) {
		strcpy_s(this->surname, surname);
	}
	char* get_surname() {
		return surname;
	}
	void set_tariff(char tariff[]) {
		strcpy_s(this->tariff, tariff);
	}
	char* get_tariff() {
		return tariff;
	}
	void set_end_date(int year, int month, int day) {
		this->end_date[2] = year;
		this->end_date[1] = month;
		this->end_date[0] = day;
	}
	void set_year(int year) {
		end_date[2] = year;
	}
	int get_year() {
		return end_date[2];
	}
	void set_month(int month) {
		end_date[1] = month;
	}
	int get_month() {
		return end_date[1];
	}
	void set_day(int day) {
		end_date[0] = day;
	}
	int get_day() {
		return end_date[0];
	}
	static void header() {
		cout.setf(ios::left);
		cout << left << setw(19) << "Номер телефона";
		cout << setw(25) << "Имя";
		cout << setw(25) << "Фамилия";
		cout << setw(35) << "Тарифный план";
		cout << setw(14) << "Конец Тарифа" << endl;
		cout << setfill('-') << setw(118) << "" << endl;
		cout.fill(' ');
		cout.unsetf(ios::left);
	}
	void input_data() {
		input_string_check("Введите номер:", number, 19, mobile_number_check);
		input_string_check("Введите Имя:", name, 25, stringCheck);
		input_string_check("Введите Фамилию:", surname, 25, stringCheck);
		input_string_check("Введите Название тарифа:", tariff, 35, stringCheck);
		input_date(end_date);
	}
	static void write(queue<Subscriber>& q, string FILE_NAME) {
		ofstream ouf;//открыть ofstream
		ouf.open(FILE_NAME, ios::trunc | ios::binary);
		int size = sizeof(Subscriber);
		if (!ouf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		while (!q.empty()) {
			ouf.write((char*)&q.front(), size);
			q.pop();
		}
		ouf.close();
	}
	static void read(queue<Subscriber>& q, string FILE_NAME) {
		ifstream inf;

		inf.open(FILE_NAME, ios::binary);
		if (!inf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		int size = sizeof(Subscriber);//размер объекта 
		inf.seekg(0);
		while (!q.empty()) {
			q.pop();
		}
		Subscriber sub;
		while (1) {
			inf.read((char*)&sub, size);
			if (inf.eof()) {
				inf.close();
				return;
			}
			q.push(sub);
			if (!inf) {//ошибка, но не EOF
				cout << "\nЧтение данных из файла невозможно\n";
				return;
			}
		}
	}
	static void read(stack<Subscriber>& s, string FILE_NAME) {
		ifstream inf;

		inf.open(FILE_NAME, ios::binary);
		if (!inf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		int size = sizeof(Subscriber);//размер объекта 
		inf.seekg(0);
		while (!s.empty()) {
			s.pop();
		}
		Subscriber sub;
		while (1) {
			inf.read((char*)&sub, size);
			if (inf.eof()) {
				inf.close();
				return;
			}
			s.push(sub);
			if (!inf) {//ошибка, но не EOF
				cout << "\nЧтение данных из файла невозможно\n";
				return;
			}
		}
	}
	static void delete_number(queue<Subscriber>& q, char number[], string FILE_NAME) {
		ofstream ouf;//открыть ofstream
		ouf.open(FILE_NAME, ios::trunc | ios::binary);
		int size = sizeof(Subscriber);
		if (!ouf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		while (!q.empty()) {
			if (!strcmp(q.front().number, number)) { q.pop(); continue; }
			ouf.write((char*)&q.front(), size);
			q.pop();
		}
		ouf.close();
	}
	friend ostream& operator<<(ostream& s, Subscriber& sub);
};
ostream& operator<<(ostream& s, Subscriber& sub)
{
	s << left << setw(19) << sub.number << setw(25) << sub.name << setw(25) << sub.surname << setw(35) << sub.tariff << setfill('0') << setw(2) << right << sub.end_date[0] << "." << setw(2) << sub.end_date[1] << "." << setw(4) << sub.end_date[2];
	s.fill(' ');
	return s;
}
class Promotion {
protected:
	char name_promo[45];
	int end_date[3];
public:
	Promotion() {
		strcpy_s(this->name_promo, "N/A");
		end_date[0] = 0;
		end_date[1] = 0;
		end_date[2] = 0;
	}
	Promotion(const Promotion& orig) {
		strcpy_s(this->name_promo, orig.name_promo);
		end_date[0] = orig.end_date[0];
		end_date[1] = orig.end_date[1];
		end_date[2] = orig.end_date[2];

	}
	void set_name_promo(char name_promo[]) {
		strcpy_s(this->name_promo, name_promo);
	}
	char* get_name_promo() {
		return name_promo;
	}
	void set_end_date(int year, int month, int day) {
		this->end_date[2] = year;
		this->end_date[1] = month;
		this->end_date[0] = day;
	}
	void set_year(int year) {
		end_date[2] = year;
	}
	int get_year() {
		return end_date[2];
	}
	void set_month(int month) {
		end_date[1] = month;
	}
	int get_month() {
		return end_date[1];
	}
	void set_day(int day) {
		end_date[0] = day;
	}
	int get_day() {
		return end_date[0];
	}
	static void header() {
		cout.setf(ios::left);
		cout << left << setw(46) << "Название акции";
		cout << setw(14) << "Конец Тарифа" << endl;
		cout << setfill('-') << setw(60) << "" << endl;
		cout.fill(' ');
		cout.unsetf(ios::left);
	}
	void input_data() {
		input_string_check("Введите название акции:", name_promo, 45, stringCheck);
		input_date(end_date);
	}
	static void write(priority_queue<Promotion, vector<Promotion>, Promotion>& pq, string FILE_NAME) {
		ofstream ouf;//открыть ofstream
		ouf.open(FILE_NAME, ios::trunc | ios::binary);
		if (!ouf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		int size = sizeof(Promotion);
		while (!pq.empty()) {
			ouf.write((char*)&pq.top(), size);
			pq.pop();
		}
		ouf.close();
	}
	static void read(priority_queue<Promotion, vector<Promotion>, Promotion>& pq, string FILE_NAME) {
		ifstream inf;
		inf.open(FILE_NAME, ios::binary);
		if (!inf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		int size = sizeof(Promotion);//размер объекта 
		inf.seekg(0);
		Promotion prom;
		while (1) {
			inf.read((char*)&prom, size);
			if (inf.eof()) {
				inf.close();
				return;
			}
			pq.push(prom);
			if (!inf) {//ошибка, но не EOF
				cout << "\nЧтение данных из файла невозможно\n";
				return;
			}
		}
	}
	static void delete_promo(priority_queue<Promotion, vector<Promotion>, Promotion>& pq, char promo_name[], string FILE_NAME) {
		ofstream ouf;//открыть ofstream
		ouf.open(FILE_NAME, ios::trunc | ios::binary);
		if (!ouf) {
			cout << "\nНевозможно открыть файл\n";
			return;
		}
		int size = sizeof(Promotion);
		while (!pq.empty()) {
			if (!strcmp(pq.top().name_promo, promo_name)) { pq.pop(); continue; }
			ouf.write((char*)&pq.top(), size);
			pq.pop();
		}
		ouf.close();
	}
	friend ostream& operator<<(ostream& s, const Promotion& wstationary);
	bool operator()(const Promotion& d1, const Promotion& d2) {
		if (Julian(d1.end_date) > Julian(d2.end_date))
			return true;
		else return false;
	}
	bool operator<(const Promotion& rhs) const noexcept
	{
		// logic here
		return Julian(this->end_date) < Julian(rhs.end_date);
	}
};

ostream& operator<<(ostream& s, const Promotion& promo) {
	s << left << setw(46) << promo.name_promo << setw(2) << setfill('0') << right << promo.end_date[0] << "." << setw(2) << promo.end_date[1] << "." << setw(4) << promo.end_date[2];
	s.fill(' ');
	return s;
}

int main() {
	system("chcp 1251");
	system("cls");
	priority_queue<Promotion, vector<Promotion>, Promotion> pq;
	queue<Subscriber> q;
	stack<Subscriber> s;
	string file_promo = "Promo.dat", file_sub = "Subscribers.dat";
	while (1) {
		system("cls");
		switch (menu_main()) {
		case 1: {
			switch (menu_print()) {
			case 1: {
				Subscriber::read(q, file_sub);
				if (q.empty()) { cout << "\nАбонентов нет" << endl; system("pause"); break; }
				Subscriber::header();
				while (!q.empty()) {
					cout << q.front() << endl;
					cout << setfill('-') << setw(118) << "" << endl;
					cout.fill(' ');
					q.pop();
				}
			}break;
			case 2: {
				Subscriber::read(s, file_sub);
				if (s.empty()) { cout << "\nАбонентов нет" << endl; system("pause"); break; }
				Subscriber::header();
				while (!s.empty()) {
					cout << s.top() << endl;
					cout << setfill('-') << setw(118) << "" << endl;
					cout.fill(' ');
					s.pop();
				}
			}break;
			default:cout << "Неверное значение!" << endl;
			}
			system("pause");
		}; break;
		case 2: {
			Subscriber::read(q, file_sub);
			Subscriber sub;
			sub.input_data();
			q.push(sub);
			Subscriber::write(q, file_sub);
		}; break;
		case 3: {
			Subscriber::read(q, file_sub);
			char number[19];
			input_string_check("Введите номер для удаления", number, 19, mobile_number_check);
			Subscriber::delete_number(q, number, file_sub);
		}; break;
		case 4: {
			Promotion::read(pq, file_promo);
			if (pq.empty()) { cout << "\nАкций нет" << endl; system("pause"); break; }
			Promotion::header();
			while (!pq.empty()) {
				cout << pq.top() << endl;
				cout << setfill('-') << setw(60) << "" << endl;
				cout.fill(' ');
				pq.pop();
			}
			system("pause");
		}; break;
		case 5: {
			Promotion::read(pq, file_promo);
			Promotion promo;
			promo.input_data();
			pq.push(promo);
			Promotion::write(pq, file_promo);
		}; break;
		case 6: {
			Promotion::read(pq, file_promo);
			char promo[45];
			input_string_check("Введите название для удаления: ", promo, 45, stringCheck);
			Promotion::delete_promo(pq, promo, file_promo);
		}; break;
		case 0:return 0;
		default:cout << "Неверное значение!" << endl;
			system("pause");
		}
	}
}