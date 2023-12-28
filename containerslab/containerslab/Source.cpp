#include<iostream>
#include<string>
#include <Windows.h>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Transport.h"
using namespace std;
int Menu() {
    int choice = -1;
    cout <<
        "1. Просмотр всего автотранспорта\n"
        "2. Добавить автотранспорт\n"
        "3. Экспортировать в .txt\n"
        "4. Поиск\n"
        "5. Редактировать автотранспорт\n"
        "6. Сортировка\n"
        "7. Удалить автотранспорт\n"
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
int Menu_alternative(string msg) {
    system("cls");
    int choice = -1;
    cout << msg << endl;
    cout <<
        "1. Пассажирский автотранспорт\n"
        "2. Грузовой автотранспорт\n"
        "0. Выход \n"
        "Ваш выбор: ";
    //cin.unsetf(ios::skipws);
    cin >> choice;
    if (cin.bad() || cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        return -1;
    }
    return choice;
}

int main() {
    system("chcp 1251");
    system("cls");
    char FILE_NAME[100] = "Transport.dat";
    //cout << argv[1];

    list<Autotransport*> list_passeng_auto;
    list<Autotransport*> list_cargo_auto;
    unordered_map<string, list<Autotransport*>&> m;
    m.insert(pair<string, list<Autotransport*>& >("Пассажиркий", list_passeng_auto));
    m.insert(pair<string, list<Autotransport*>& >("Грузовой", list_cargo_auto));
    /*{char license_plate[14] = "BY 1234";
    char brand[16]= "Mersedes Benz";
    char engine_type[15]="gas";
    char str[12] = "bus";
   list_passeng_auto.push_back(new Passenger_auto(license_plate, brand, 2012, engine_type, 2.4, 120, str, 12));
    strcpy_s(license_plate, "BY 5678");
    strcpy_s(brand, "Audi");
    strcpy_s(engine_type, "petrol");
    strcpy_s(engine_type, "car");
    list_passeng_auto.push_back(new Passenger_auto(license_plate, brand, 2022, engine_type, 1.8, 220, str, 22));
    }*/
    try {
        Autotransport::read(list_passeng_auto, list_cargo_auto, FILE_NAME);
        while (1) {
            system("cls");
            switch (Menu()) {
            case 1: {
                if (list_passeng_auto.empty() && list_cargo_auto.empty()) {
                    cout << "Автотранспорта нет!" << endl;
                    system("pause");
                    break;
                }
                unordered_map<string, list<Autotransport*>&>::iterator it;//итератор map
                for (it = m.begin(); it != m.end(); it++)
                {
                    if (it->second.empty())continue;
                    cout << endl;
                    cout << setw(52) << " " << it->first << endl;
                    cout << setfill('-') << setw(115) << "" << endl;
                    cout.fill(' ');
                    if (it->first == "Пассажиркий")//получение названия ключа
                        Passenger_auto::Header();
                    else Cargo_auto::Header();

                    for (list<Autotransport*>::iterator i = it->second.begin(); i != it->second.end(); ++i) {//итератор листа
                        (*i)->Output();
                        cout << setfill('-') << setw(115) << "" << endl;
                        cout.fill(' ');
                    }
                }
                system("pause");
            } break;
            case 2:
            {int i = 0;
            while (i != 1) {
                switch (Menu_alternative("Какой автотранспорт хотите добавить:")) {
                case 1:
                    list_passeng_auto.push_back(new Passenger_auto);
                    list_passeng_auto.back()->Input();
                    break;
                case 2:
                    list_cargo_auto.push_back(new Cargo_auto);
                    list_cargo_auto.back()->Input();
                    break;
                case 0: i = 1; break;
                default:cout << "Неверное значение!" << endl;
                    system("pause");
                }
            }
            }break;
            case 3:
            {
                if (list_passeng_auto.empty() && list_cargo_auto.empty()) {
                    cout << "Автотранспорта нет!" << endl;
                    system("pause");
                    break;
                }
                clearFile("transport.txt");
                unordered_map<string, list<Autotransport*>&>::iterator it;
                for (it = m.begin(); it != m.end(); it++) {
                    if (it->second.empty())continue;
                    if (it->first == "Пассажиркий")
                        Passenger_auto::HeaderTXT("transport.txt");
                    else Cargo_auto::HeaderTXT("transport.txt");
                    for (list<Autotransport*>::iterator i = it->second.begin(); i != it->second.end(); ++i)
                        (*i)->ExportTXT("transport.txt");
                }
                system("pause");
            }break;
            case 4: {int i = 0;
                while (i != 1) {
                    switch (Menu_alternative("Какой автотранспорт хотите добавить:")) {
                    case 1:
                        Passenger_auto::search(list_passeng_auto);
                        break;
                    case 2:
                        Cargo_auto::search(list_cargo_auto);
                        break;
                    case 0: i = 1; break;
                    default:cout << "Неверное значение!" << endl;
                        system("pause");
                    }
                }
            }break;
            case 5: {
                int i = 0;
                while (i != 1) {
                    switch (Menu_alternative("Какой автотранспорт хотите редактировать:")) {
                    case 1:
                    {
                        list<Autotransport*>::iterator result = list_passeng_auto.begin();
                        char value[14];
                        rewind(stdin);
                        InputLicensePlate(value, "Введите номерной знак для поиска:");
                        result = list_passeng_auto.begin();
                        result = find_if(result, list_passeng_auto.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
                        //note the &. It means we are capturing all of the enclosing variables by reference
                        if (result != list_passeng_auto.end()) {
                            Passenger_auto::Header();
                            (*result)->Output();
                            (*result)->Input();
                        }
                        else cout << "Автотранспорт не найден!" << endl;
                        system("pause");
                    }    break;
                    case 2:
                    {
                        list<Autotransport*>::iterator result = list_cargo_auto.begin();
                        char value[14];
                        rewind(stdin);
                        InputLicensePlate(value, "Введите номерной знак для поиска:");
                        result = list_cargo_auto.begin();
                        result = find_if(result, list_cargo_auto.end(), [&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
                        //note the &. It means we are capturing all of the enclosing variables by reference
                        if (result != list_cargo_auto.end()) {
                            Cargo_auto::Header();
                            (*result)->Output();
                            (*result)->Input();
                        }
                        else cout << "Автотранспорт не найден!" << endl;
                        system("pause");
                    }    break;
                    case 0: i = 1; break;
                    default:cout << "Неверное значение!" << endl;
                        system("pause");
                    }
                }
            } break;
            case 6: {
                int i = 0;
                while (i != 1) {
                    switch (Menu_alternative("Какой автотранспорт хотите сортировать:")) {
                    case 1:
                        Passenger_auto::sort(list_passeng_auto);
                        break;
                    case 2:
                        Cargo_auto::sort(list_cargo_auto);
                        break;
                    case 0: i = 1; break;
                    default:cout << "Неверное значение!" << endl;
                        system("pause");
                    }
                }
            } break;
            case 7:
            {
                char value[20];
                int i = 0;
                while (i != 1) {
                    switch (Menu_alternative("Какой автотранспорт хотите удалить:")) {
                    case 1:
                        InputLicensePlate(value, "Введите номерной знак машины, которую нужно удалить:");
                        list_passeng_auto.remove_if([&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
                        system("pause");
                        break;
                    case 2:
                        InputLicensePlate(value, "Введите номерной знак машины, которую нужно удалить:");
                        list_cargo_auto.remove_if([&](Autotransport*& transp) {return !strcmp(transp->GetLicensePlate(), value); });
                        system("pause");
                        break;
                    case 0: i = 1; break;
                    default:cout << "Неверное значение!" << endl;
                        system("pause");
                    }
                }
            }
            case 0:
            {
                clearFile(FILE_NAME);
                unordered_map<string, list<Autotransport*>&>::iterator it;
                for (it = m.begin(); it != m.end(); it++) {
                    if (!it->second.empty())
                        Autotransport::write(it->second, FILE_NAME);
                }
            }
            return 0;
            default:cout << "Неверное значение!" << endl;
                system("pause");
            }
        }
    }
    catch (...) { cout << "Exception handler" << endl; }


    return 0;
}