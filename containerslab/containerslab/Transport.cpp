#include "Transport.h"

bool stringCheck(char* string) {
	setlocale(LC_ALL, "ru");
	int i = 0;
	while (string[i] != '\0')
		if (!isalpha(string[i]) && !(string[i] >= '�' && string[i] <= '�') && !(string[i] == '�') && !(string[i] == '�') && !(string[i] == ' ') && !(string[i] == '-'))return false;
		else i++;
	return true;
}
bool LicensePlateCheck(char* string) {
	setlocale(LC_ALL, "ru");
	int i = 0;
	while (string[i] != '\0')
		if (!isalpha(string[i]) && !isdigit(string[i]) && !(string[i] == ' ') && !(string[i] == '-'))return false;
		else i++;
	return true;
}

void InputPositiveNumber(int& number, string msg, int max_value) {
	while (1) {
		cout << msg << endl;
		cin >> number;
		if (cin.fail() || number < 0 || number > max_value) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void InputPositiveNumber(unsigned int& number, string msg, unsigned int max_value) {
	while (1) {
		cout << msg << endl;
		cin >> number;
		if (cin.fail() || number < 0 || number > max_value) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void InputPositiveNumber(float& number, string msg, float max_value) {
	while (1) {
		cout << msg << endl;
		cin >> number;
		if (cin.fail() || number < 0 || number > max_value) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void InputString(char* str, string msg) {
	while (1) {
		cout << msg << endl;
		cin.getline(str, 20);
		if (!stringCheck(str)) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void InputYear(unsigned int& number, string msg) {
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	while (1) {
		cout << msg << endl;
		cin >> number;
		if (cin.fail() || number < 0 || number < 1700 || number > 1900 + timeinfo.tm_year) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}
void InputLicensePlate(char* str, string msg) {
	while (1) {
		cout << msg << endl;
		rewind(stdin);
		cin.getline(str, 13);
		if (!LicensePlateCheck(str)) {
			cout << "A variable cannot contain these characters" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else return;
	}
}

void clearFile(const char* FILE_NAME) {
	ofstream ouf;
	ouf.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);
	ouf.close();
}

void Autotransport::read(list<Autotransport*>& l1, list<Autotransport*>& l2, const char* FILE_NAME) {
	int size;//������ ������� Employee
	AutotransportType etype;//��� ���������
	ifstream inf;

	inf.open(FILE_NAME, ios::binary);
	if (!inf) {
		cout << "\n���������� ������� ����\n";
		return;
	}

	inf.seekg(0);
	while (true) {
		inf.read((char*)&etype, sizeof(etype));//������ ���� 
		if (inf.eof()) {
			inf.close();
			return;
		}
		if (!inf) {//������ ������ ����
			cout << "\n���������� ������ ����\n";
			return;
		}

		switch (etype) {
		case AutotransportType::passenger://����������� ����
		{
			{
				Passenger_auto a;
				//r = new Passenger_auto;
				size = sizeof(Passenger_auto);
				inf.read((char*)&a, size);

				l1.push_back(new Passenger_auto(a));
			}
		}	break;
		case AutotransportType::cargo:
		{
			{
				Cargo_auto c;
				//r = new Cargo_auto;
				size = sizeof(Cargo_auto);
				inf.read((char*)&c, size);
				l2.push_back(new Cargo_auto(c));
			}
		}
		break;
		default: cout << "\n����������� ��� � �����\n"; return;
		}
		if (!inf) {//������, �� �� EOF
			cout << "\n������ ������ �� ����� ����������\n";
			return;
		}
	}
}
void Autotransport::write(list <Autotransport*>& list_t, char* FILE_NAME) {
	int size = 0;
	ofstream ouf;//������� ofstream
	AutotransportType etype;//��� ������� �������
	ouf.open(FILE_NAME, ios::app | ios::binary);
	if (!ouf) {
		cout << "\n���������� ������� ����\n";
		return;
	}
	list<Autotransport*>::iterator j = list_t.begin();
	int i = 0;
	while (j != list_t.end()) {//��� ������� ������� �������� ���
		etype = (*j)->getType();
		ouf.write((char*)&etype, sizeof(etype));
		switch (etype) {
		case AutotransportType::passenger:
			size = sizeof(Passenger_auto); break;
		case AutotransportType::cargo:
			size = sizeof(Cargo_auto); break;
		}
		Autotransport* w = *j;
		ouf.write((char*)w, size);//������ ������� Employee
		if (!ouf) {
			cout << "\n������ � ���� ����������\n";
			return;
		}
		j++;
	}
	ouf.close();
	/*ofstream fout;
	fout.open(FILE_NAME, ios::trunc | ios::binary);
	if (fout.is_open()) {
		for (int i = 0; i < list.size(); i++) {
			fout.write((char*)list[i], sizeof(T));
		}
	}
	else {
		cout << "\n���������� ������� ����\n";
		return;
	}*/
}
int  Autotransport::MenuAscOrDescOrder() {
	system("cls");
	int choice = -1;
	cout << "������� ��:" << endl;
	cout <<
		"\t1. �����������\n"
		"\t2. ��������\n"
		"\t��� �����: ";
	rewind(stdin);
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}

inline bool Autotransport::brandAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	if (strcmp(lhs->brand, rhs->brand) == -1)
		return true;
	return false;
}
inline bool Autotransport::brandDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	if (strcmp(lhs->brand, rhs->brand) == 1)
		return true;
	return false;
}
inline bool Autotransport::YearAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->release_year < rhs->release_year;
}
inline bool Autotransport::YearDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->release_year > rhs->release_year;
}
inline bool Autotransport::engVolAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->engine_volume < rhs->engine_volume;
}
inline bool Autotransport::engVolDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->engine_volume > rhs->engine_volume;
}
inline bool Autotransport::speedAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->max_speed < rhs->max_speed;
}
inline bool Autotransport::speedDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->max_speed > rhs->max_speed;
}

inline bool Passenger_auto::passeng_numbAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->getInt(1) < rhs->getInt(1);
}
inline bool Passenger_auto::passeng_numbDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->getInt(1) > rhs->getInt(1);
}

inline bool Cargo_auto::capacityAscend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->getFloat(1) < rhs->getFloat(1);
}
inline bool Cargo_auto::capacityDescend(Autotransport*& lhs, Autotransport*& rhs)
{
	return lhs->getFloat(1) > rhs->getFloat(1);
}

int Passenger_auto::MenuSearch() {
	system("cls");
	int choice = -1;
	cout << "����� ��:" << endl;
	cout <<
		"\t1. ��������� �����\n"
		"\t2. ����� ����\n"
		"\t3. ���� �������\n"
		"\t4. ���� ����������\n"
		"\t5. ���������� ����\n"
		"\t0. ����� \n"
		"\t��� �����: ";
	rewind(stdin);
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}
void Passenger_auto::search(list <Autotransport*>& list_t) {
	list<Autotransport*>::iterator result = list_t.begin();
	while (1) {
		switch (Passenger_auto::MenuSearch()) {
		case 1:
		{
			char value[14];
			rewind(stdin);
			InputLicensePlate(value, "������� �������� ���� ��� ������:");
			result = list_t.begin();
			result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
			//note the &. It means we are capturing all of the enclosing variables by reference
			if (result != list_t.end()) {
				Passenger_auto::Header();
				(*result)->Output();
			}
			else cout << "������������� �� ������!" << endl;
			system("pause");
		}break;
		case 2:
		{
			char value[16];
			rewind(stdin);
			InputString(value, "������� ����� ���� ��� ������:");
			result = list_t.begin();
			Passenger_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetBrand(), value); });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 3:
		{
			result = list_t.begin();
			unsigned int value;
			rewind(stdin);
			InputYear(value, "������� ��� ��� ������:");
			Passenger_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return transp->GetReleaseYear() == value; });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}	break;
		case 4:
		{
			result = list_t.begin();
			char value[13];
			rewind(stdin);
			InputString(value, "������� ��� ����������:");
			Passenger_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->getString(1), value); });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 5:
		{
			result = list_t.begin();
			int value;
			rewind(stdin);
			InputPositiveNumber(value, "������� ���������� ����������:", 2000);
			Passenger_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return transp->getInt(1) == value; });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 0: return;
		default:cout << "�������� ��������!" << endl;
			system("pause");
		}

	}
}

int Passenger_auto::MenuSort() {
	system("cls");
	int choice = -1;
	cout << "���������� ��:" << endl;
	cout <<
		"\t1. ����� ����\n"
		"\t2. ���� �������\n"
		"\t3. ������ ���������\n"
		"\t4. ������������ ��������\n"
		"\t5. ���������� ����\n"
		"\t0. ����� \n"
		"\t��� �����: ";
	rewind(stdin);
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}
void Passenger_auto::sort(list <Autotransport*>& list_t) {
	while (1) {
		switch (Passenger_auto::MenuSort()) {
		case 1:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::brandAscend); break;
			case 2:
				list_t.sort(Autotransport::brandDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 2:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::YearAscend); break;
			case 2:
				list_t.sort(Autotransport::YearDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 3:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::engVolAscend); break;
			case 2:
				list_t.sort(Autotransport::engVolDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");

		}	break;
		case 4:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::speedAscend); break;
			case 2:
				list_t.sort(Autotransport::speedDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 5:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Passenger_auto::passeng_numbAscend); break;
			case 2:
				list_t.sort(Passenger_auto::passeng_numbDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 0: return;
		default:cout << "�������� ��������!" << endl;
			system("pause");
		}
		/*Passenger_auto::Header();
		for (list<Autotransport*>::iterator i = list_t.begin(); i != list_t.end(); ++i)
			(*i)->Output();*/
	}
}



int Cargo_auto::MenuSearch() {
	system("cls");
	int choice = -1;
	cout << "����� ��:" <<
		"\t1. ��������� �����\n"
		"\t2. ����� ����\n"
		"\t3. ���� �������\n"
		"\t4. ���� ������\n"
		"\t5. ����������������\n"
		"\t0. ����� \n"
		"\t��� �����: ";
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}
void Cargo_auto::search(list <Autotransport*>& list_t) {
	list<Autotransport*>::iterator result = list_t.begin();
	while (1) {
		switch (Cargo_auto::MenuSearch()) {
		case 1:
		{
			char value[14];
			rewind(stdin);
			InputLicensePlate(value, "������� �������� ���� ��� ������:");
			result = list_t.begin();
			result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
			//note the &. It means we are capturing all of the enclosing variables by reference
			if (result != list_t.end()) {
				Cargo_auto::Header();
				(*result)->Output();
			}
			else cout << "������������� �� ������!" << endl;
			system("pause");
		}break;
		case 2:
		{
			char value[16];
			rewind(stdin);
			InputString(value, "������� ����� ���� ��� ������:");
			result = list_t.begin();
			Cargo_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetBrand(), value); });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 3:
		{
			result = list_t.begin();
			unsigned int value;
			rewind(stdin);
			InputYear(value, "������� ��� ��� ������:");
			Cargo_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return transp->GetReleaseYear() == value; });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}	break;
		case 4:
		{
			result = list_t.begin();
			char value[13];
			rewind(stdin);
			InputString(value, "������� ��� ������:");
			Cargo_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return !strcmp(transp->getString(1), value); });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 5:
		{
			result = list_t.begin();
			float value;
			rewind(stdin);
			InputPositiveNumber(value, "������� ����������������:", 1000);
			Cargo_auto::Header();
			while (true) {
				result = find_if(result, list_t.end(), [&](Autotransport*& transp) {return transp->getFloat(1) == value; });
				if (result == list_t.end())break;
				(*result)->Output();
				result++;
			}
			system("pause");
		}break;
		case 0: return;
		default:cout << "�������� ��������!" << endl;
			system("pause");
		}

	}
}

int Cargo_auto::MenuSort() {
	system("cls");
	int choice = -1;
	cout << "���������� ��:" << endl;
	cout <<
		"\t1. ����� ����\n"
		"\t2. ���� �������\n"
		"\t3. ������ ���������\n"
		"\t4. ������������ ��������\n"
		"\t5. ����������������\n"
		"\t0. ����� \n"
		"\t��� �����: ";
	rewind(stdin);
	cin >> choice;
	if (cin.bad() || cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return -1;
	}
	return choice;
}
void Cargo_auto::sort(list <Autotransport*>& list_t) {
	while (1) {
		switch (Passenger_auto::MenuSort()) {
		case 1:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::brandAscend); break;
			case 2:
				list_t.sort(Autotransport::brandDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 2:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::YearAscend); break;
			case 2:
				list_t.sort(Autotransport::YearDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 3:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::engVolAscend); break;
			case 2:
				list_t.sort(Autotransport::engVolDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");

		}	break;
		case 4:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Autotransport::speedAscend); break;
			case 2:
				list_t.sort(Autotransport::speedDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 5:
		{
			switch (Autotransport::MenuAscOrDescOrder())
			{
			case 1:
				list_t.sort(Cargo_auto::capacityAscend); break;
			case 2:
				list_t.sort(Cargo_auto::capacityDescend); break;
			default:
				cout << "�������� ��������!" << endl;
				break;
			}
			system("pause");
		}break;
		case 0: return;
		default:cout << "�������� ��������!" << endl;
			system("pause");
		}
		/*Passenger_auto::Header();
		for (list<Autotransport*>::iterator i = list_t.begin(); i != list_t.end(); ++i)
			(*i)->Output();*/
	}
}

void Autotransport::ExportTXT(const char* FILE_NAME) {}
void Passenger_auto::ExportTXT(const char* FILE_NAME)
{
	ofstream ouf;//������� ofstream
	ouf.open(FILE_NAME, ios::app);
	if (!ouf) {
		cout << "\n���������� ������� ����\n";
		return;
	}
	ouf << left << setw(5) << this->GetName();
	ouf << setw(14) << this->GetLicensePlate();
	ouf << setw(15) << this->GetBrand();
	ouf << setw(12) << this->GetReleaseYear();
	ouf << setw(14) << this->GetEngineType();
	ouf << setw(16) << this->GetEngineVolume();
	ouf << setw(14) << this->GetMaxSpeed();
	ouf << setw(12) << this->GetTransportType();
	ouf << setw(11) << this->GetPassengersNumber() << endl;
	if (!ouf) {
		cout << "\n������ � ���� ����������\n";
		return;
	}

}
void Cargo_auto::ExportTXT(const char* FILE_NAME)
{
	ofstream ouf;//������� ofstream
	ouf.open(FILE_NAME, ios::app);
	if (!ouf) {
		cout << "\n���������� ������� ����\n";
		return;
	}
	ouf << left << setw(5) << this->GetName();
	ouf << setw(14) << this->GetLicensePlate();
	ouf << setw(15) << this->GetBrand();
	ouf << setw(12) << this->GetReleaseYear();
	ouf << setw(14) << this->GetEngineType();
	ouf << setw(16) << this->GetEngineVolume();
	ouf << setw(14) << this->GetMaxSpeed();
	ouf << setw(12) << this->GetBodyType();
	ouf << setw(11) << this->GetCapacity() << endl;
	if (!ouf) {
		cout << "\n������ � ���� ����������\n";
		return;
	}

}
void Passenger_auto::HeaderTXT(const char* FILE_NAME) {
	ofstream ouf;//������� ofstream
	ouf.open(FILE_NAME, ios::app);
	if (!ouf) {
		cout << "\n���������� ������� ����\n";
		return;
	}
	ouf << setw(52) << "�����������" << endl;
	ouf << setfill('-') << setw(115) << "" << endl;
	ouf.fill(' ');
	ouf.setf(ios::left);
	ouf << setw(5) << "���";
	ouf << setw(14) << "�������� ����";
	ouf << setw(15) << "����� ����";
	ouf << setw(12) << "��� �������";
	ouf << setw(14) << "��� ���������";
	ouf << setw(16) << "����� ���������";
	ouf << setw(14) << "Max. ��������";
	ouf << setw(12) << "��� ������.";
	ouf << setw(11) << "���-�� ����" << endl;
	ouf << setfill('-') << setw(115) << "" << endl;
	ouf.fill(' ');
	ouf.unsetf(ios::left);
	ouf.close();
}
void Cargo_auto::HeaderTXT(const char* FILE_NAME) {
	ofstream ouf;//������� ofstream
	ouf.open(FILE_NAME, ios::app);
	if (!ouf) {
		cout << "\n���������� ������� ����\n";
		return;
	}
	ouf << setw(52) << "��������" << endl;
	ouf << setfill('-') << setw(115) << "" << endl;
	ouf.fill(' ');
	ouf.setf(ios::left);
	ouf << setw(5) << "���";
	ouf << setw(14) << "�������� ����";
	ouf << setw(15) << "����� ����";
	ouf << setw(12) << "��� �������";
	ouf << setw(14) << "��� ���������";
	ouf << setw(16) << "����� ���������";
	ouf << setw(14) << "Max. ��������";
	ouf << setw(11) << "��� ������";
	ouf << setw(13) << "������������." << endl;
	ouf << setfill('-') << setw(115) << "" << endl;
	ouf.fill(' ');
	ouf.unsetf(ios::left);
	ouf.close();
}
AutotransportType Autotransport::getType()
{
	if (typeid(*this) == typeid(Passenger_auto))return
		AutotransportType::passenger;
	else if (typeid(*this) == typeid(Cargo_auto)) return
		AutotransportType::cargo;
	else {
		cerr << "\n������������ ��� ";
		exit(1);
	}
	return AutotransportType::passenger;
}

void Autotransport::Input() {
	rewind(stdin);
	InputLicensePlate(this->license_plate, "������� �������� ����:");
	rewind(stdin);
	InputString(this->brand, "������� ����� ����������: ");
	InputYear(this->release_year, "������� ��� �������: ");
	rewind(stdin);
	InputString(this->engine_type, "������� ��� ���������: ");

	if (!strcmp(this->engine_type, "electro") || !strcmp(this->engine_type, "�������") || !strcmp(this->engine_type, "����������������")) {
		InputPositiveNumber(this->max_speed, "������� ������������ ��������: ", 600);
	}
	else {
		InputPositiveNumber(this->engine_volume, "������� ����� ���������: ", 100);
		InputPositiveNumber(this->max_speed, "������� ������������ ��������: ", 600);
	}
}
void Passenger_auto::Input() {
	Autotransport::Input();
	rewind(stdin);
	InputString(this->transport_type, "������� ��� ����������: ");
	InputPositiveNumber(this->passengers_number, "������� ���������� ����������: ", 2000);
}
void Cargo_auto::Input() {
	Autotransport::Input();
	rewind(stdin);
	InputString(this->body_type, "������� ��� ������: ");
	InputPositiveNumber(this->capacity, "������� ����������������(�����): ", 1000);
}
void Autotransport::Output() {
	cout << left << setw(5) << name;
	cout << setw(14) << license_plate;
	cout << setw(15) << brand;
	cout << setw(12) << release_year;
	cout << setw(14) << engine_type;
	cout << setw(16) << engine_volume;
	cout << setw(14) << max_speed;

}
void Passenger_auto::Output() {
	Autotransport::Output();
	cout << setw(12) << transport_type;
	cout << setw(11) << passengers_number << endl;
}
void Cargo_auto::Output() {
	Autotransport::Output();
	cout << setw(11) << body_type;
	cout << setw(13) << capacity << endl;
}
void Passenger_auto::Header() {
	cout.setf(ios::left);
	cout << setw(5) << "���";
	cout << setw(14) << "�������� ����";
	cout << setw(15) << "����� ����";
	cout << setw(12) << "��� �������";
	cout << setw(14) << "��� ���������";
	cout << setw(16) << "����� ���������";
	cout << setw(14) << "Max. ��������";
	cout << setw(12) << "��� ������.";
	cout << setw(11) << "���-�� ����" << endl;
	cout << setfill('-') << setw(115) << "" << endl;
	cout.fill(' ');
	cout.unsetf(ios::left);
}
void Cargo_auto::Header() {
	cout.setf(ios::left);
	cout << setw(5) << "���";
	cout << setw(14) << "�������� ����";
	cout << setw(15) << "����� ����";
	cout << setw(12) << "��� �������";
	cout << setw(14) << "��� ���������";
	cout << setw(16) << "����� ���������";
	cout << setw(14) << "Max. ��������";
	cout << setw(11) << "��� ������";
	cout << setw(13) << "������������." << endl;
	cout << setfill('-') << setw(115) << "" << endl;
	cout.fill(' ');
	cout.unsetf(ios::left);
}
istream& operator>>(istream& s, Autotransport& autotransport) {
	rewind(stdin);
	InputLicensePlate(autotransport.license_plate, "������� �������� ����:");
	InputString(autotransport.brand, "������� ����� ����������: ");
	InputYear(autotransport.release_year, "������� ��� �������: ");
	rewind(stdin);
	InputString(autotransport.engine_type, "������� ��� ���������: ");

	if (autotransport.engine_type == "electro" || autotransport.engine_type == "�������" || autotransport.engine_type == "����������������") {
		InputPositiveNumber(autotransport.max_speed, "������� ������������ ��������: ", 600);
		return s;
	}
	InputPositiveNumber(autotransport.engine_volume, "������� ����� ���������: ", 100);
	InputPositiveNumber(autotransport.max_speed, "������� ������������ ��������: ", 600);
	return s;
}
istream& operator>>(istream& s, Passenger_auto& passeng_auto) {
	rewind(stdin);
	InputString(passeng_auto.brand, "������� ����� ����������: ");
	InputYear(passeng_auto.release_year, "������� ��� �������: ");
	rewind(stdin);
	InputString(passeng_auto.engine_type, "������� ��� ���������: ");

	if (passeng_auto.engine_type == "electro" || passeng_auto.engine_type == "�������" || passeng_auto.engine_type == "����������������") {
		InputPositiveNumber(passeng_auto.max_speed, "������� ������������ ��������: ", 600);
		InputString(passeng_auto.transport_type, "������� ��� ����������: ");
		InputPositiveNumber(passeng_auto.passengers_number, "������� ���������� ����������: ", 2000);
		return s;
	}
	InputPositiveNumber(passeng_auto.engine_volume, "������� ����� ���������: ", 100);
	InputPositiveNumber(passeng_auto.max_speed, "������� ������������ ��������: ", 600);
	rewind(stdin);
	InputString(passeng_auto.transport_type, "������� ��� ����������: ");
	InputPositiveNumber(passeng_auto.passengers_number, "������� ���������� ����������: ", 2000);
	return s;
}
ostream& operator<<(ostream& s, Passenger_auto& passeng_auto) {
	s << left << setw(4) << passeng_auto.name;
	s << setw(13) << passeng_auto.license_plate;
	s << setw(15) << passeng_auto.brand;
	s << setw(11) << passeng_auto.release_year;
	s << setw(13) << passeng_auto.engine_type;
	s << setw(15) << passeng_auto.engine_volume;
	s << setw(13) << passeng_auto.max_speed;
	s << setw(11) << passeng_auto.transport_type;
	s << setw(11) << passeng_auto.passengers_number << endl;
	return s;
}
istream& operator>>(istream& s, Cargo_auto& cargo_auto) {
	rewind(stdin);
	InputLicensePlate(cargo_auto.license_plate, "������� �������� ����:");
	rewind(stdin);
	InputString(cargo_auto.brand, "������� ����� ����������: ");
	InputYear(cargo_auto.release_year, "������� ��� �������: ");
	rewind(stdin);
	InputString(cargo_auto.engine_type, "������� ��� ���������: ");

	if (cargo_auto.engine_type == "electro" || cargo_auto.engine_type == "�������" || cargo_auto.engine_type == "����������������") {
		InputPositiveNumber(cargo_auto.max_speed, "������� ������������ ��������: ", 600);
		rewind(stdin);
		InputString(cargo_auto.body_type, "������� ��� ������: ");
		InputPositiveNumber(cargo_auto.capacity, "������� ����������������: ", 1000);
		return s;
	}
	InputPositiveNumber(cargo_auto.engine_volume, "������� ����� ���������: ", 100);
	InputPositiveNumber(cargo_auto.max_speed, "������� ������������ ��������: ", 600);
	rewind(stdin);
	InputString(cargo_auto.body_type, "������� ��� ������: ");
	InputPositiveNumber(cargo_auto.capacity, "������� ����������������(�����): ", 1000);
	return s;
}
ostream& operator<<(ostream& s, Cargo_auto& cargo_auto) {
	s << left << setw(4) << cargo_auto.name;
	s << setw(13) << cargo_auto.license_plate;
	s << setw(15) << cargo_auto.brand;
	s << setw(11) << cargo_auto.release_year;
	s << setw(13) << cargo_auto.engine_type;
	s << setw(15) << cargo_auto.engine_volume;
	s << setw(13) << cargo_auto.max_speed;
	s << setw(10) << cargo_auto.body_type;
	s << setw(13) << cargo_auto.capacity << endl;
	return s;
}