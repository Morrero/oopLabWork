#include"Cards.h"
#pragma warning(disable : 4996)
bool stringCheck(char string[]) {
    setlocale(LC_ALL, "ru");
    int i = 0;
    while (i != strlen(string))
        if (!isalpha(string[i]) && !(string[i] >= '�' && string[i] <= '�') && !(string[i] == '�') && !(string[i] == '�') && !(string[i] == '-') && !(string[i] == ' '))return false;
        else i++;
    return true;
}
int menu_pay_system(string msg) {
    system("cls");
    while (1) {
        int choice = -1;
        cout << msg << endl;
        cout <<
            "1. VISA\n"
            "2. MasterCard\n"
            "3. Maestro\n"
            "��� �����: ";
        cin >> choice;
        if (cin.bad() || cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
        }
        switch (choice) {
        case 1:return 1;
        case 2:return 2;
        case 3:return 3;
        default:
            cout << "������ �������� ������� ���!" << endl;
            system("pause");
            break;
        }
    }
}
void input_card_number(char* card_number) {
    string copy;
    switch (menu_pay_system("�������� ��� �������� �������:")) {
    case 1: {
        copy = "4";
    }break;
    case 2: {
        copy = "5";
    }break;
    case 3: {
        copy = "6";
    }break;
    }
    copy = copy +"5788433";
    srand(time(0));
    string str;
    for (size_t i = 0; i < 8; i++)
        str += rand() % 10 + '0';
    copy = copy + str;
    strcpy(card_number, copy.c_str());
}
void input_string_check(string msg, char string[], int size, bool(*check_func)(char*)) {
    while (1) {

        rewind(stdin);
        if (char(cin.peek()) == '\n')
            cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cout << msg << endl;
        cin.getline(string, size);
        if (!check_func(string)) {
            cout << "A variable cannot contain these characters" << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else return;
    }
}
void Card:: write(vector<Card*>& card_vector) {
    int size = 0;
    ofstream ouf;//������� ofstream
    CardEnum atype;//��� ������� �������
    ouf.open("Cards.dat", ios::trunc | ios::binary);
    if (!ouf) {
        cout << "\n���������� ������� ����\n";
        return;
    }
    for (Card* acc : card_vector) {
        atype = acc->getType();
        ouf.write((char*)&atype, sizeof(atype));
        switch (atype) {
        case CardEnum::PrepaidCard_e:
            size = sizeof(PrepaidCard); break;
        case  CardEnum::DebitCard_e:
            size = sizeof(DebitCard); break;
        case  CardEnum::CreditCard_e:
            size = sizeof(CreditCard); break;
        }
        ouf.write((char*)acc, size);
    }
    ouf.close();
}

void Card::put_cash()
{
    float cash;
    input_positiv_number_range("������� �����, ������� ������ ��������: ", cash, 10000000.0f);
    if (typeid(*this) == typeid(PrepaidCard) && cash > 200.0f) {
        cout << "�� ����� ��� ����� ������ �������� ������ 200 � �����" << endl;
        system("pause");
    }else balance += cash;
}

void Card::withdraw_cash()
{
    float cash;
    input_positiv_number_range("������� ����� ��� ������:", cash, 1000000.0f);
    if (balance < cash && typeid(*this) == typeid(CreditCard))
        balance -= cash;
    if (balance < cash)
        cout << "������������ �������" << endl;
    else balance -= cash;
    system("pause");
}

CardEnum Card::getType()
{
    if (typeid(*this) == typeid(PrepaidCard))return CardEnum::PrepaidCard_e;
    else if (typeid(*this) == typeid(DebitCard)) return CardEnum::DebitCard_e;
    else if (typeid(*this) == typeid(CreditCard)) return CardEnum::CreditCard_e;
    else {
        cerr << "\n������������ ��� ";
        exit(1);
    }
    return CardEnum::PrepaidCard_e;
}

void Card::read(vector<Card*>& card_vector) {
    int size;
    CardEnum atype;
    ifstream inf;

    inf.open("Cards.dat", ios::binary);
    if (!inf) {
        cout << "\n���������� ������� ����\n";
        return;
    }
    inf.seekg(0);
    while (true) {
        inf.read((char*)&atype, sizeof(atype));//������ ���� 
        if (inf.eof()) {
            inf.close();
            return;
        }
        if (!inf) {//������ ������ ����
            cout << "\n���������� ������ ����\n";
            return;
        }
        switch (atype) {
        case CardEnum::PrepaidCard_e://����������� ����
        {
            PrepaidCard pr;
            size = sizeof(PrepaidCard);
            inf.read((char*)&pr, size);
            card_vector.push_back(new PrepaidCard(pr));

        }	break;
        case CardEnum::DebitCard_e:
        {
            {
                DebitCard deb;
                size = sizeof(DebitCard);
                inf.read((char*)&deb, size);
                card_vector.push_back(new DebitCard(deb));
            }
        }
        break;
        case CardEnum::CreditCard_e:
        {
            {
                CreditCard cred;
                size = sizeof(CreditCard);
                inf.read((char*)&cred, size);
                card_vector.push_back(new CreditCard(cred));
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
