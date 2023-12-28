
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <Windows.h>
#include <new>
#include <locale> 
#include <limits> 
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;


class Component
{
protected:
    string brand;
public:
    Component() {}
    Component(string brand)
    {
        this->brand = brand;
    }
    ~Component() {}
    string getBrand() const {
        return brand;
    }
    void setBrand(string newBrand) {
        brand = newBrand;
    }
};

class Processor : public Component {
protected:
    int cores;
public:
    Processor() {}
    Processor(int cores, string brand) :Component(brand)
    {
        this->cores = cores;
    }
    int getCores() const {
        return cores;
    }
    void setCores(int newCores) {
        cores = newCores;
    }
    ~Processor() {}
};

class RAM : public Component {
protected:
    int capacity;
public:
    RAM() {}
    RAM(int capacity, string brand) :Component(brand)
    {
        this->capacity = capacity;
    }
    int getCapacity() const {
        return capacity;
    }
    void setCapacity(int newCapacity) {
        capacity = newCapacity;
    }
    ~RAM() {}
};

class HDD : public Component {
protected:
    int size;
public:
    HDD() {}
    HDD(int size, string brand) : Component(brand)
    {
        this->size = size;
    }
    int getSize() const {
        return size;
    }
    void setSize(int newSize) {
        size = newSize;
    }
    ~HDD() {}
};

class Computer {
protected:
    int computerNumber;
    string nameComputer;
    Processor* processor;
    RAM* ram;
    HDD* hdd;
public:
    Computer() {}
    Computer(int computerNumber, string nameComputer, Processor* processor, RAM* ram, HDD* hdd)
    {
        this->computerNumber = computerNumber;
        this->nameComputer = nameComputer;
        this->processor = processor;
        this->ram = ram;
        this->hdd = hdd;
    }
    int getComputerNumber() const {
        return computerNumber;
    }
    int setComputerNumber(int newComputerNumber) {
        computerNumber = newComputerNumber;
    }
    string getNameComputer() const {
        return nameComputer;
    }
    void setNameComputer(const string& newNameComputer) {
        nameComputer = newNameComputer;
    }
    int getCores() const {
        return processor->getCores();
    }
    void setCores(int newCores) {
        processor->setCores(newCores);
    }
    int getCapacity() const {
        return ram->getCapacity();
    }
    void setCapacity(int newCapacity) {
        ram->setCapacity(newCapacity);
    }
    int getSize() const {
        return hdd->getSize();
    }
    void setSize(int newSize) {
        hdd->setSize(newSize);
    }
    ~Computer() {}
    void displayComputer() const {
        cout.setf(ios::left);
        std::cout << setw(4) << computerNumber << "|";
        std::cout.unsetf(ios::left);
        std::cout << setw(15) << nameComputer << "|";
        std::cout << setw(15) << processor->getBrand() << "|";
        std::cout << setw(10) << processor->getCores() << "|";
        std::cout << setw(15) << ram->getBrand() << "|";
        std::cout << setw(10) << ram->getCapacity() << "|";
        std::cout << setw(15) << hdd->getBrand() << "|";
        cout.setf(ios::right);
        std::cout << setw(10) << hdd->getSize() << "|";
        cout.unsetf(ios::right);
        std::cout << endl;
        std::cout << setw(102) << setfill('-') << "" << setfill(' ') << endl;
    }
};

bool compareComputers(const Computer& computer1, const Computer& computer2) {
    return computer1.getComputerNumber() < computer2.getComputerNumber();
}

void sortComputers(const vector<Computer>& computers) {
    vector<Computer> sortedComputers = computers;
    std::sort(sortedComputers.begin(), sortedComputers.end(), compareComputers);
}

class computerStorage {
private:
    vector<Computer> computers;
    set<int> computerNumbers;
public:
    void addComputer(Computer computer) {
        int computerNumber = computer.getComputerNumber();
        if (computerNumbers.find(computerNumber) != computerNumbers.end()) {
            throw invalid_argument("Ошибка: Компьютер с номером " + to_string(computerNumber) + " уже существует!");
        }
        computers.push_back(computer);
        computerNumbers.insert(computerNumber);
    }

    Computer findComputer(int computerNumber) const {
        for (Computer computer : computers) {
            if (computer.getComputerNumber() == computerNumber) {
                return computer;
            }
        }
        throw invalid_argument("Ошибка: Компьютер с номером " + to_string(computerNumber) + " не найден!");
    }

    bool computerExists(int computerNumber) const {
        return computerNumbers.find(computerNumber) != computerNumbers.end();
    }

    void displayComputers() {
        for (const Computer& computer : computers) {
            computer.displayComputer();
        }
    }

    int getNumComputers() const {
        return computers.size();
    }

    Computer& findComputerById(int computerNumber) {
        for (auto& computer : computers) {
            if (computer.getComputerNumber() == computerNumber) {
                return computer;
            }
        }
        throw invalid_argument("Ошибка: Компьютер с номером " + to_string(computerNumber) + " не найден!");
    }

    void deleteComputer(int computerNumber) {
        if (computerNumber >= 1 && computerNumber <= computers.size()) {
            auto it = computers.begin() + (computerNumber - 1);

            computerNumbers.erase(it->getComputerNumber());
            computers.erase(it);
        }
        else {
            std::cout << "Неверный номер компьютера." << endl;
        }
    }

    vector<Computer> getComputers() const {
        return computers;
    }
};

class MyException : public exception {
public:
    const char* what() const throw() {
        return "Ошибка: Максимальное количество сборок компьютера было достигнуто!";
    }
};

class MyExceptionComputer : public exception
{
public:
    const char* what() const throw() {
        return "Собранных компьютеров нет!";
    }
};

void termFunc() {
    std::cout << "Функция termFunc() вызвана функцией terminate().\n";
    abort();
    exit(-1);
}

void deleteComputer(computerStorage& computerStorage) {
    int computerFind;
    while (true) {
        std::cout << "Введите номер компьютера для удаления: ";
        std::cin >> computerFind;
        if (!std::cin.fail()) {
            break;
        }
        std::cin.clear();
        std::cout << "Неправильный ввод данных\n";
        std::cin.ignore(100, '\n');
    }
    try {
        Computer& foundComputer = computerStorage.findComputerById(computerFind);
        std::cout << "\nНайден компьютер с номером " << computerFind << ":" << endl;
        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
        std::cout << left << setw(4) << "№" << "|" << setw(15) << "Компьютер" << "|" << setw(15) << "Процессор" << "|" << setw(10) << "Ядра" << "|" << setw(15) << "Опер.память" << "|" << setw(10) << "Объем" << "|" << setw(15) << "Жесткий диск" << "|" << setw(10) << "Объем" << "|" << endl;
        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
        foundComputer.displayComputer();
        computerStorage.deleteComputer(computerFind);
        std::cout << "\nЗаказ успешно удален!" << endl;
    }
    catch (invalid_argument e) {
        std::cout << e.what() << endl;
    }
}

void editComputer(computerStorage& computerStorage) {
    int fieldChoice = 0;
    int computerNumberToFind;
    while (true) {
        cout << "Введите номер компьютера для редактирования: ";
        cin >> computerNumberToFind;
        if (!cin.fail()) {
            break;
        }
        cin.clear();
        cout << "Неправильный ввод данных\n";
        cin.ignore(100, '\n');
    }
    try {
        Computer& foundComputer = computerStorage.findComputerById(computerNumberToFind);
        cout << "\nНайден компьютер с номером " << computerNumberToFind << ":" << endl;
        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
        std::cout << left << setw(4) << "№" << "|" << setw(15) << "Компьютер" << "|" << setw(15) << "Процессор" << "|" << setw(10) << "Ядра" << "|" << setw(15) << "Опер.память" << "|" << setw(10) << "Объем" << "|" << setw(15) << "Жесткий диск" << "|" << setw(10) << "Объем" << "|" << endl;
        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
        foundComputer.displayComputer();
        do {
            cout << "\nМеню редактирования " << endl;
            cout << "1 - Изменить название компьютера" << endl;
            cout << "2 - Изменить количество ядер" << endl;
            cout << "3 - Изменить объем памяти оперативной памяти" << endl;
            cout << "4 - Изменить объем памяти жесткого диска" << endl;
            cout << "0 - Выйти" << endl;
            while (true) {
                cout << "Выберите действие: ";
                cin >> fieldChoice;
                if (!cin.bad()) {
                    break;
                }
                cin.clear();
                cout << "Неправильный ввод данных\n";
                cin.ignore(100, '\n');
            }

            string newFieldValue;
            int newValue;
            switch (fieldChoice) {
            case 1: {
                system("cls");
                cout << "Введите новое название компьютера: ";
                cin.ignore();
                getline(cin, newFieldValue);
                foundComputer.setNameComputer(newFieldValue);
                cout << "Данные успешно изменены!";
                break;
            }
            case 2: {
                system("cls");
                cout << "Введите новое количество ядер: ";
                cin.ignore();
                cin >> newValue;
                foundComputer.setCores(newValue);
                cout << "Данные успешно изменены!";
                break;
            }
            case 3: {
                system("cls");
                int newExperience;
                cout << "Введите новый объем: ";
                cin >> newExperience;
                foundComputer.setCapacity(newExperience);
                cout << "Данные успешно изменены!";
                break;
            }
            case 4: {
                system("cls");
                cout << "Введите новый объем: ";
                cin.ignore();
                cin >> newValue;
                foundComputer.setSize(newValue);
                cout << "Данные успешно изменены!";
                break;
            }
            case 0: {
                return;
            }
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        } while (fieldChoice != 0);
    }
    catch (invalid_argument e) {
        cout << e.what() << endl;
    }
}

void displaySortedComputers(const vector<Computer>& sortedComputers) {
    std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
    std::cout << left << setw(4) << "№" << "|" << setw(15) << "Компьютер" << "|" << setw(15) << "Процессор" << "|" << setw(10) << "Ядра" << "|" << setw(15) << "Опер.память" << "|" << setw(10) << "Объем" << "|" << setw(15) << "Жесткий диск" << "|" << setw(10) << "Объем" << "|" << endl;
    std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
    for (const Computer& computer : sortedComputers) {
        computer.displayComputer();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int maxComputer = 5;
    int choice = 0;
    int size = 0;
    int i = 0;
    string nameComputer;
    string brand;
    string brand1;
    string brand2;
    int cores = 0;
    int capacity = 0;
    int number;
    string nameCom;
    Processor* processor = nullptr;
    RAM* ram = nullptr;
    HDD* hdd = nullptr;
    Computer* computer = nullptr;
    computerStorage computerStorage;
    bool isComputerCreated = false;
    set_terminate(termFunc);
    do {
        cout << "\nМеню выбора" << endl;
        cout << "1 - Добавить компьютер" << endl;
        cout << "2 - Просмотреть компьютеры" << endl;
        cout << "3 - Поиск компьютера" << endl;
        cout << "4 - Изменить информацию о компьютере" << endl;
        cout << "5 - Удалить собранный компьютер" << endl;
        cout << "6 - Сортировать компьютеры" << endl;
        cout << "0 - Выйти" << endl;
        while (true) {
            cout << "Выберите действие: ";
            cin >> choice;
            if (cin.good()) {
                break;
            }
            cin.clear();
            cout << "Неправильный ввод данных\n";
            cin.ignore(100, '\n');
        }

        try {
            switch (choice) {
            case 1: {
                system("cls");
                if (isComputerCreated) {
                    if (computerStorage.getNumComputers() >= maxComputer) {
                        throw MyException();
                    }
                }
                cout << "Введите номер компьютера: ";
                while (!std::cin.eof())
                {
                    cin >> number;

                    if (!std::cin.eof())
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Не удалось прочитать: " << number << std::endl;
                    }
                }
                cout << "\nВведите название компьютера: ";
                cin >> nameComputer;
                cout << "" << endl;
                if (number < 0) {
                    throw invalid_argument("Ошибка: Номер заказа не может быть отрицательным!");
                }
                cout << "Введите информацию про центральный процессор: " << endl;
                cout << "\nВыберите процессор (Intel или AMD): ";
                cin >> brand;
                if (brand != "Intel" && brand != "AMD")
                {
                    throw "Ошибка! Вы ввели неправильное название процессора!";
                }
                cout << "Введите количество ядер: ";
                cin >> cores;
                if (cores < 0) { throw "Ошибка! Вы ввели неправильное значение! "; }
                processor = new Processor(cores, brand);
                cout << "" << endl;
                cout << "Введите информацию про оперативную память: " << endl;
                cout << "\nВыберите тип оперативной памяти (DDR3 или DDR4): ";
                cin >> brand1;
                if (brand1 != "DDR3" && brand1 != "DDR4")
                {
                    throw "Ошибка! Вы ввели неправильный тип оперативной памяти!";
                }
                cout << "Введите объем памяти (в ГБ): ";
                cin >> capacity;
                if (capacity < 0) { throw "Ошибка! Память не может быть отрицательной!"; }
                ram = new RAM(capacity, brand1);
                cout << "" << endl;
                cout << "Введите информацию про жесткий диск: " << endl;
                cout << "\nВведите название бренда: ";
                cin >> brand2;
                std::cout << "Введите объем памяти жесткого диска (в ГБ): ";
                std::cin >> size;
                if (size < 0) { throw "Ошибка! Память не может быть отрицательной!"; }
                hdd = new HDD(size, brand2);
                computer = new Computer(number, nameComputer, processor, ram, hdd);
                computerStorage.addComputer(*computer);
                isComputerCreated = true;
                std::cout << "\nКомпьютер успешно собран!" << endl;
                break;
            }
            case 2: {
                system("cls");
                if (computerStorage.getNumComputers() == 0) {
                    cout << "Собранных компютеров нет!";
                }
                else {
                    std::cout << setw(102) << setfill('-') << "" << setfill(' ') << endl;
                    std::cout << left << setw(4) << "№" << "|" << setw(15) << "Компьютер" << "|" << setw(15) << "Процессор" << "|" << setw(10) << "Ядра" << "|" << setw(15) << "Опер.память" << "|" << setw(10) << "Объем" << "|" << setw(15) << "Жесткий диск" << "|" << setw(10) << "Объем" << "|" << endl;
                    std::cout << setw(102) << setfill('-') << "" << setfill(' ') << endl;
                    computerStorage.displayComputers();
                }
                break;
            }
            case 3: {
                system("cls");
                int computerNumberToFind;
                if (computerStorage.getNumComputers() == 0) {
                    cout << "Собранных компютеров нет!";
                }
                else {
                    while (true) {
                        std::cout << "Введите номер компьютера для поиска: ";
                        std::cin >> computerNumberToFind;
                        if (!std::cin.fail() && !std::cin.eof()) {
                            break;
                        }
                        std::cin.clear();
                        std::cout << "Неправильный ввод данных\n";
                        std::cin.ignore(100, '\n');
                    }
                    try {
                        Computer& foundComputer = computerStorage.findComputerById(computerNumberToFind);
                        std::cout << "\nНайден компьютер с номером " << computerNumberToFind << ":" << endl;
                        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
                        std::cout << left << setw(4) << "№" << "|" << setw(15) << "Компьютер" << "|" << setw(15) << "Процессор" << "|" << setw(10) << "Ядра" << "|" << setw(15) << "Опер.память" << "|" << setw(10) << "Объем" << "|" << setw(15) << "Жесткий диск" << "|" << setw(10) << "Объем" << "|" << endl;
                        std::cout << setw(101) << setfill('-') << "" << setfill(' ') << endl;
                        foundComputer.displayComputer();
                    }
                    catch (invalid_argument e) {
                        std::cout << e.what() << endl;
                    }
                }
                break;
            }
            case 4: {
                system("cls"); if (computerStorage.getNumComputers() == 0) {
                    cout << "Собранных компютеров нет!";
                }
                else {
                    editComputer(computerStorage);
                }
                break;
            }
            case 5: {
                system("cls");
                if (computerStorage.getNumComputers() == 0) {
                    cout << "Собранных компютеров нет!";
                }
                else {
                    deleteComputer(computerStorage);
                }
                break;
            }
            case 6: {
                system("cls");
                if (computerStorage.getNumComputers() == 0) {
                    cout << "Собранных компютеров нет!";
                }
                else {
                    const vector<Computer>& computers = computerStorage.getComputers();
                    vector<Computer> sortedComputers = computers;
                    sort(sortedComputers.begin(), sortedComputers.end(),
                        [](const Computer& computer1, const Computer& computer2) {
                            return computer1.getComputerNumber() < computer2.getComputerNumber();
                        });
                    displaySortedComputers(sortedComputers);
                    std::cout << "Компьютеры успешно отсортированы по номерам." << endl;
                }
                break;
            }
            }
        }
        catch (bad_alloc& ex) {
            std::cout << "Перехвачено исключение: " << ex.what() << endl;
        }
        catch (MyException& ex) {
            std::cout << "Перехвачено исключение: " << ex.what() << endl;
        }
        catch (MyExceptionComputer& ex) {
            std::cout << "Перехвачено исключение: " << ex.what() << endl;
        }
        catch (const char* ex) {
            std::cout << "Перехвачено исключение: " << ex << endl;
        }
    } while (choice != 0);
    return 0;
}
