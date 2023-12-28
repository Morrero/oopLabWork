#include<iostream>
#include<string>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <typeinfo>
#include <vector>
#include <fstream>
#include<algorithm>

using namespace std;
const char* FILE_NAME = "data.dat";
void termFunc()
{
    cout << "Всего доброго!\nБудем рады видеть вас в нашем магазине!" << endl;
    exit(-1);
}
class MyExceptions : public exception {
public:
    const char* what() {
        return "Цена не должна быть отрицательной\n";
    }
};
class Stationery {
protected:
    float price;
    int quantity;
public:
    Stationery() {
        price = 0;
        quantity = 0;
    }
    Stationery(float price, int quantity) {
        cout << "Constructor of the Stationery class" << endl;
        this->price = price;
        this->quantity = quantity;
    }
    ~Stationery() {
        cout << "Destructor of the Stationery class" << endl;
    }
    void SetPrice(float price) { this->price = price; }
    void SetQuantity(int quantity) { this->quantity = quantity; }
    float GetPrice() { return price; }
    int GetQuantity() { return quantity; }
    friend int operator+(const Stationery& c1, const Stationery& c2) {
        return c1.quantity + c2.quantity;
    }
    friend int operator+(const int value, const Stationery& c2) {
        return value + c2.quantity;
    }
    friend int operator+(const Stationery& c1, const int value) {
        return c1.quantity + value;
    }
    float CountPrice() {
        return (price * quantity * 100) / 100;
    }
    virtual void Show() {
        cout << fixed << left << setprecision(2) << setw(7) << price;
    }

};
class WritingStationary :public Stationery {
protected:
    string kernel, HavingRubber;
public:
    WritingStationary() : Stationery() {
        kernel = "N/A";
        HavingRubber = "N/A";
    }
    WritingStationary(float price, int quentity, string kernel, string HavingRubber) :Stationery(price, quentity) {
        this->kernel = kernel;
        this->HavingRubber = HavingRubber;
    }
    string GetKernel() {
        return kernel;
    }
    string GetHavingRubber() {
        return HavingRubber;
    }
    void SetKernel(string kernel) {
        this->kernel = kernel;
    }
    void SetHavingRubber(string HavingRubber) {
        this->HavingRubber = HavingRubber;
    }
    void Show() {
        Stationery::Show();
        cout << setw(16) << kernel << setw(11) << HavingRubber;
    }
    friend istream& operator>>(istream& s, WritingStationary& wstationary);
};

istream& operator>>(istream& s, WritingStationary& wstationary) {
    char dummy;
    s >> wstationary.price >> dummy >> wstationary.quantity >> dummy >> wstationary.kernel >> dummy >> wstationary.HavingRubber;
    return s;
}

class Pen :public WritingStationary {
protected:
    string colour, TypeOfInk;
public:
    Pen() :WritingStationary() {
        kernel = "N/A";
        HavingRubber = "N/A";
        colour = "N/A";
        TypeOfInk = "N/A";
    }
    Pen(float price, int quentity, string kernel, string HavingRubber, string colour, string TypeOfInk) :WritingStationary(price, quentity, kernel, HavingRubber) {
        this->colour = colour;
        this->TypeOfInk = TypeOfInk;
    }
    string GetColour() {
        return colour;
    }
    string GetTypeOfInk() {
        return TypeOfInk;
    }
    void SetColour(string colour) {
        this->colour = colour;
    }
    void SetTypeOfInk(string TypeOfInk) {
        this->TypeOfInk = TypeOfInk;
    }
    void Show() {
        WritingStationary::Show();
        cout << setw(16) << colour << setw(24) << TypeOfInk << endl;
    }
};
class Pencil :public WritingStationary {
protected:
    string softness;
public:
    Pencil() :WritingStationary() {
        price = 0;
        quantity = 0;
        kernel = "N/A";
        HavingRubber = "N/A";
        softness = "N/A";
    }
    Pencil(float price, int quentity, string kernel, string HavingRubber, string softness) :WritingStationary(price, quentity, kernel, HavingRubber) {
        this->softness = softness;
    }
    string GetSoftness() {
        return softness;
    }
    void SetSoftness(string softness) {
        this->softness = softness;
    }
    void Show() {
        WritingStationary::Show();
        cout << setw(10) << softness << endl;
    }
};
class Ruler : public Stationery {
protected:
    float length;
    string material;
public:
    Ruler() :Stationery() {
        length = 0;
        material = "N/A";
    }
    Ruler(float price, int quentity, float length, string material) : Stationery(price, quentity) {
        try {
            cout << "Constructor of the Ruler class" << endl;
            if (price < 0) { MyExceptions exep; throw exep; }
            this->length = length;
            this->material = material;
        }
        catch (MyExceptions& ex) {
            cout << ex.what() << endl;
        }
    }
    ~Ruler() {
        cout << "Destructor of the Ruler class" << endl;
    }
    void SetLength(float length) { this->length = length; }
    void SetMaterial(string material) { this->material = material; }
    float GetLength() { return length; }
    string GetMaterial() { return material; }
    void Show() {
        Stationery::Show();
        cout << setw(10) << length << setw(10) << material << endl;
    }
};

class Сalculator : public Stationery {
private:
    int capacity;
    string type;
public:
    Сalculator() :Stationery() {
        capacity = 0;
        type = "N/A";
    }
    Сalculator(float price, int quentity, int capacity, string type) : Stationery(price, quentity) {
        this->capacity = capacity;
        this->type = type;
    }
    void SetCapacity(int capacity) { this->capacity = capacity; }
    void SetType(string material) { this->type = type; }
    int GetCapacity() { return capacity; }
    string GetType() { return type; }
    void Show() {
        Stationery::Show();
        cout << setw(10) << capacity << setw(12) << type << endl;
    }

};
int Menu() {
    int choice;
    cout <<
        "1. Просмотр всех товаров\n"
        "2. Формирование заказа\n"
        "3. Просмотр информации о заказах\n"
        "4. Поиск по номеру заказа\n"
        "5. Редактировать заказ\n"
        "6. Удалить заказ\n"
        "7. Сортировка по возрастанию цены\n"
        "0. Выход \n"
        "Ваш выбор: ";
    while (1) {
        cin >> choice;
        if (cin.good()) break;
        cin.clear();
        cout << "Ошибка" << endl;

        cin.ignore(256, '\n');
    }
    return choice;
}
int ShowMenu() {
    int choice;
    system("cls");
    cout <<
        "1. Ручка\n"
        "2. Карандаш\n"
        "3. Калькулятор\n"
        "4. Линейка\n"
        "0. Назад\n"
        "Ваш выбор: ";
    while (1) {
        cin >> choice;
        if (!cin.bad()) break;
        cin.clear();
        cout << "Ошибка" << endl;
        system("pause");
        cin.ignore(256, '\n');
    }
    return choice;

}

void ShowAll(Pen pen, Pencil pencil, Сalculator calculator, Ruler ruler) {
    while (1) {
        switch (ShowMenu())
        {
        case 1:
            cout << left << setw(5) << "Цена" << setw(12) << "Стержень" << setw(17) << "Наличие ластика" << setw(17) << "Цвет чернил" << setw(15) << "Тип чернил" << endl;
            pen.Show();
            system("pause");
            break;
        case 2:
            cout << left << setw(5) << "Цена" << setw(12) << "Стержень" << setw(17) << "Наличие ластика" << setw(17) << "Мягкость" << endl;
            pencil.Show();
            system("pause");
            break;
        case 3:
            cout << left << setw(5) << "Цена" << setw(7) << "Длина" << setw(2) << "Материал" << endl;
            ruler.Show();
            system("pause");
            break;
        case 4:
            cout << left << setw(5) << "Цена" << setw(12) << "Точность" << setw(7) << "Вид" << endl;
            calculator.Show();
            system("pause");
            break;
        case 0:return;
        default:
            cout << "Невероне значение!" << endl;
            break;
        }
    }
}
int GetNumber(string msg) {
    while (1) {
        try {
            int value;
            cout << msg;
            while (1) {
                cin >> value;
                if (value < 0) {
                    throw 1;
                }
                if (value == 0) throw 1.0;
                if (!cin.fail()) break;
                cin.clear();
                cout << "Ошибка" << endl;
                system("pause");
                cin.ignore(256, '\n');
            }
            return value;
        }
        catch (double) {
            cout << "Вы ввели 0" << endl;
            throw;
        }
        catch (int) {
            cout << "Число должно быть больше 0" << endl;
            throw;
        }
    }
    system("pause");
}
class Order {
protected:
    int kol_pen, kol_pencil, kol_calculator, kol_ruler;
    float sum;
public:
    Order() {
        kol_pen = kol_pencil = kol_calculator = kol_ruler = sum = 0;
    }
    int FormOrder(Pen& pen, Pencil& pencil, Сalculator& calculator, Ruler& ruler) {
        int val = 0;
        while (val != 1) {
            try {
                cout << "Какой товар хотите добавить в заказ\n" << endl;
                switch (ShowMenu()) {
                case 1:
                    kol_pen = GetNumber("Введите количество товара:");
                    break;
                case 2:
                    kol_pencil = GetNumber("Введите количество товара:");  break;
                case 3:
                    kol_calculator = GetNumber("Введите количество товара:");  break;
                case 4:
                    kol_ruler = GetNumber("Введите количество товара:");  break;
                case 0:val = 1; break;
                default:
                    cout << "Невероне значение!" << endl;
                }
            }
            catch (...) {
                cout << "Значение не установлено" << endl;

            }
            system("pause");
        }
        if (kol_pen == 0 && kol_pencil == 0 && kol_calculator == 0 && kol_ruler == 0) {
            cout << "\nВ заказ ничего не добавлено" << endl;
            system("pause");
            return 1;
        }
        sum = kol_pen * pen.GetPrice() + kol_pencil * pencil.GetPrice() + kol_calculator * calculator.GetPrice() + kol_ruler * ruler.GetPrice();
        cout.unsetf(ios::showpoint);//отоброжает только целочисленную часть, если дробная равна 0
        cout << "Сумма вашего заказа составила:" << setprecision(2) << sum << endl;
        cout.setf(ios::showpoint);
        cout.setf(ios::showbase);//указывает систему счисления
        cout << "Кол-во ручек в заказе:" << kol_pen << endl;
        cout << "Кол-во карандашей в заказе:" << kol_pencil << endl;
        cout << "Кол-во калькуляторов в заказе:" << kol_calculator << endl;
        cout << "Кол-во линеек в заказе:" << kol_ruler << endl;
        cout.unsetf(ios::showbase);
        system("pause");
        return 0;
    }

    friend ostream& operator<< (ostream& s, Order*& order);
    friend ostream& operator<< (ostream& s, Order& order);
    friend bool sortingSum(Order*& i, Order*& j);
    friend bool sortingPen(Order*& i, Order*& j);
    static void read(vector <Order*>& orders);
    static void writeAll(vector <Order*>& orders);
    static void findInFile();
    static void editInFile(Pen& pen, Pencil& pencil, Сalculator& calculator, Ruler& ruler);
    static void deleteInFile();
    static void SortSum(vector <Order*>& orders);
    static void SortKol(vector <Order*>& orders);
    static void header() {
        cout << setw(15) << left << "Номер заказа";
        cout << setw(15) << "Кол-во ручек";
        cout << setw(20) << "Кол-во карандашей";
        cout << setw(23) << "Кол-во калькуляторов";
        cout << setw(16) << "Кол-во линеек";
        cout << setw(12) << "Стоимость" << endl;
    }
};

ostream& operator<< (ostream& s, Order*& order) {
    s << setw(19) << order->kol_pen << setw(22) << order->kol_pencil << setw(18) << order->kol_calculator << setw(10) << order->kol_ruler << setw(18) << setprecision(2) << order->sum << endl;
    return s;
}
ostream& operator<< (ostream& s, Order& order) {
    s << setw(19) << order.kol_pen << setw(22) << order.kol_pencil << setw(18) << order.kol_calculator << setw(10) << order.kol_ruler << setw(18) << setprecision(2) << order.sum << endl;
    return s;
}
bool sortingSum(Order*& i, Order*& j) { return (i->sum < j->sum); }
bool sortingPen(Order*& i, Order*& j) { return (i->kol_pen < j->kol_pen); }
void Order::read(vector <Order*>& orders) {
    ifstream fin;
    fin.open(FILE_NAME, ios_base::in);
    if (fin.is_open()) {
        orders.clear();
        while (!fin.eof()) {
            orders.push_back(new Order);
            fin.read((char*)orders.back(), sizeof(Order));
            if (fin.bad()) {
                cout << "\nЧтение данных из файла невозможно\n";
                return;
            }
        }
        orders.erase(orders.begin() + orders.size() - 1);
        fin.close();
    }
    else
    {
        cout << "\nНевозможно открыть файл\n";
        return;
    }
}
void Order::writeAll(vector <Order*>& orders) {
    ofstream fout;
    fout.open(FILE_NAME, ios::trunc | ios::binary);
    if (fout.is_open()) {
        for (int i = 0; i < orders.size(); i++) {
            fout.write((char*)orders[i], sizeof(Order));
        }
    }
    else {
        cout << "\nНевозможно открыть файл\n";
        return;
    }
}
void Order::findInFile() {
    int number = GetNumber("Введите номер заказа:");
    ifstream fin;
    int size = sizeof(Order);
    fin.open(FILE_NAME, ios_base::in);
    fin.seekg(0, fin.end);
    int length = fin.tellg();
    if (length / size < number - 1) {
        cout << "\nТакого заказа нет\n" << endl;
        system("pause");
        return;
    }
    else {
        Order order;
        fin.seekg(size * (number - 1));
        if (fin.is_open()) {
            fin.read((char*)&order, size);
            if (fin.bad()) {
                cout << "\nЧтение данных из файла невозможно\n";
                return;
            }
            fin.close();
            Order::header();
            cout.setf(ios::fixed | ios::left);//По левому краю, десятичная систеиа 
            cout << setw(20) << number << order;
            system("pause");
        }
        else
        {
            cout << "\nНевозможно открыть файл\n";
            return;
        }
    }
}
void Order::editInFile(Pen& pen, Pencil& pencil, Сalculator& calculator, Ruler& ruler) {
    int number = GetNumber("Введите номер заказа:");
    fstream ios;
    int size = sizeof(Order);
    ios.open(FILE_NAME, ios_base::in | ios_base::out);
    ios.seekg(0, ios.end);
    int length = ios.tellg();
    if (length / size < number - 1) {
        cout << "\nТакого заказа нет\n" << endl;
        system("pause");
        return;
    }
    else {
        Order order;
        ios.seekg(size * (number - 1));
        if (ios.is_open()) {
            ios.read((char*)&order, size);
            if (ios.bad()) {
                cout << "\nЧтение данных из файла невозможно\n";
                return;
            }
            //fin.close();
            Order::header();
            cout.setf(ios::dec | ios::showpos);//десятичная система целых чисел, указыватьт явно знак +
            cout << fixed << setw(20) << left << number << order;
            cout.unsetf(ios::showpos);//снятие флага
            system("pause");
            order.FormOrder(pen, pencil, calculator, ruler);
            ios.seekg(-size, ios::cur);
            if (ios.good()) {
                ios.write((char*)&order, size);
            }
            else {
                cout << "\nНе удалось отредактировать файл" << endl;
                system("pause");
            }
            ios.close();
        }
        else
        {
            cout << "\nНевозможно открыть файл\n";
            return;
        }
    }
}
void Order::deleteInFile() {
    int number = GetNumber("Введите номер заказа:");
    fstream ios;
    ios.open(FILE_NAME, ios::binary | ios_base::in);
    int size = sizeof(Order);
    ios.seekg(0, ios.end);
    int length = ios.tellg();
    if (length / size < number - 1) {
        cout << "\nТакого заказа нет\n" << endl;
        system("pause");
        return;
    }
    else {
        ofstream fout("temp.dat", ios::trunc | ios::binary);
        Order order;
        ios.seekg(0);
        if (ios.is_open() && fout.is_open()) {
            int i = 1;
            while (ios.read((char*)&order, size)) {
                if (i != number) {
                    fout.write((char*)&order, size);
                }
                else
                {
                    Order::header();
                    cout.setf(ios::left, ios::adjustfield);//сбрасывает предыдущие форматирования и выравнивает по левому краю
                    cout << fixed << setw(20) << number << order;
                    cout << "\nВы действидельно хотите удалить эту запись?" << endl;
                    cout << "'y' - Да"
                        "\n'n' - Нет"
                        "\nВаш выбор: " << endl;
                    rewind(stdin);
                    char userChoice = getchar();

                    if (userChoice == 'y')
                        cout << "\nЗапись успешно удалена" << endl;
                    else {
                        cout << "\nЗапись не будет удалена" << endl;
                        fout.write((char*)&order, size);
                    }
                    system("pause");
                }
                i++;
            }
            ios.close();
            fout.close();
            remove(FILE_NAME);
            rename("temp.dat", FILE_NAME);
        }
        else
        {
            cout << "\nНевозможно открыть файл\n";
            return;
        }
    }
}
void Order::SortSum(vector <Order*>& orders) {
    sort(orders.begin(), orders.end(), sortingSum);
    cout << "Отсортированный список заказов\n";
    Order::header();
    for (int a = 0; a < orders.size(); a++) {
        cout << fixed << setw(20) << left << a + 1 << orders[a];
    }
    system("pause");
}
void Order::SortKol(vector <Order*>& orders) {
    sort(orders.begin(), orders.end(), sortingPen);
    cout << "Отсортированный список заказов\n";
    Order::header();
    for (int a = 0; a < orders.size(); a++) {
        cout << fixed << setw(20) << left << a + 1 << orders[a];
    }
    system("pause");
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <Order*> orders;
    try {
        Pen pen(7.02, 0, "чернила", "нет", "синий", "гелевый");
        Pencil pencil(1.53, 0, "грифель", "да", "HB");
        Сalculator calculator(25.50, 0, 12, "Инженерный");
        Ruler ruler(5.80, 0, 20, "Пластик");
        Order::read(orders);
        while (1) {
            system("cls");
            switch (Menu()) {
            case 1: ShowAll(pen, pencil, calculator, ruler); break;
            case 2:
                orders.push_back(new Order());
                orders.back()->FormOrder(pen, pencil, calculator, ruler);
                Order::writeAll(orders);
                break;
            case 3:
                Order::read(orders);
                if (orders.empty()) {
                    cout << "Заказов нет!" << endl;
                    system("pause");
                    break;
                }
                Order::header();
                for (int a = 0; a < orders.size(); a++) {
                    cout << fixed << setw(20) << left << a + 1 << orders[a];
                }
                system("pause");
                break;
            case 4: Order::findInFile(); break;
            case 5: Order::editInFile(pen, pencil, calculator, ruler); break;
            case 6: Order::deleteInFile(); break;
            case 7:
                system("cls");
                int ch;
                cout << "Сортировка по:\n"
                    "1. Сумме заказа\n"
                    "2. Количесиву ручек\n"
                    "Выш выбор: ";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    Order::SortSum(orders); break;
                case 2:
                    Order::SortKol(orders); break;
                default: cout << "Ошибка" << endl;
                    break;
                }
                break;

            case 0: return 0;
            default: cout << "Ошибка" << endl; break;
            }
        }
    }
    catch (...) { cout << "Exception handler" << endl; }
}