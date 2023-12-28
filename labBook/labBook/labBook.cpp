

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class PrintProduct {
    protected:
        string Title;
        string Author;
        string Genre;
        float Price;
    public:
        PrintProduct(string Title_, string Author_, string Genre_, float Price_) {
            Title = Title_;
            Author = Author_;
            Genre = Genre_;
            Price = Price_;
        }

        void Display() {
            cout << "Название: " << Title << "; " << "Автор: " << Author << "; " << "Жанр: " << Genre << "; " << "Цена($): " << Price << endl;
        }
        
};

class DiscountedBook :public PrintProduct {
    public:
        protected:
            float Discounted;
        public:
            DiscountedBook(string Title_, string Author_, string Genre_, float Price_, float Discounted_) : PrintProduct(Title_, Author_, Genre_, Price_) {
                Discounted = Discounted_;
                Price = Price_ - Discounted_;
            }
            
};

class LimitedQuantityBook : private PrintProduct {
    protected:
        int Quantity;
    public:
        LimitedQuantityBook(string Title_, string Author_, string Genre_, float Price_, int Quantity_) : PrintProduct(Title_, Author_, Genre_, Price_) {
            Quantity = Quantity_;
        }
        void DisplayInfoWithQuantity() {
            cout << "Количество: " << Quantity << "; ";
            PrintProduct::Display();
        }
};

class RareBook :public DiscountedBook, private LimitedQuantityBook {
    public:
        RareBook(string Title_, string Author_, string Genre_, float Price_, float Discounted_, int Quantity_, string Rare_) :
            DiscountedBook(Title_, Author_, Genre_, Price_, Discounted_),
            LimitedQuantityBook(Title_, Author_, Genre_, Price_, Quantity_) {
            Rare = Rare_;
        }
        void DisplayRareBooks() {
            cout << "Редкость: " << Rare << "; " << "Скидка: " << Discounted << "; ";
            LimitedQuantityBook::DisplayInfoWithQuantity();
        }
    protected:
        string Rare;
};

int Check() {
    int numb;
    while (true) {
        cout << "Выберите действие: ";
        cin >> numb;
        if (cin.good() && numb >= 0 && numb<=5) break;
        cin.clear();
        cout << "\t\t\t\t\t\tНеверный ввод! Попробуйте еще раз!\n";
        cin.ignore(32767, '\n');
    }
    cin.ignore();
    return numb;
}

float CheckPrice() {
    float numb;
    while (true) {
        cin >> numb;
        if (cin.good() && numb > 0) break;
        cin.clear();
        cout << "\t\t\t\t\t\tНеверный ввод! Попробуйте еще раз!\n";
        cin.ignore(32767, '\n');
    }
    cin.ignore();
    return numb;
}

int CheckInt() {
    int numb;
    while (true) {
        cin >> numb;
        if (cin.good() && numb > 0) break;
        cin.clear();
        cout << "\t\t\t\t\t\tНеверный ввод! Попробуйте еще раз!\n";
        cin.ignore(32767, '\n');
    }
    cin.ignore();
    return numb;
}

float checkDiscound(float price) {
    float numb;
    while (true) {
        cin >> numb;
        if (cin.good() && numb > 0 && numb <= price) break;
        cin.clear();
        cout << "\t\t\t\t\t\tНеверный ввод! Попробуйте еще раз!\n";
        cin.ignore(32767, '\n');
    }
    cin.ignore();
    return numb;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int maxBook = 100;
    PrintProduct* defaultBook[maxBook];
    int defaultBookSize = 0;

    DiscountedBook* discountedBooks[maxBook];
    int discountedBooksSize = 0;

    LimitedQuantityBook* limitedQuantityBooks[maxBook];
    int limitedQuantitySize = 0;

    RareBook* rareBooks[maxBook];
    int rareBooksSize = 0;


    int choice = -1;

    cout << "\n Меню" << endl;

    while (choice != 0) {
        cout << "1. Добавить книгу" << endl;
        cout << "2. Добавить книгу со скидкой" << endl;
        cout << "3. Добавить книгу с ограниченным кол-вом" << endl;
        cout << "4. Добавить редкую книгу" << endl;
        cout << "5. Вывести всю информацию" << endl;
        cout << "0. Выход" << endl;
        choice = Check();

        switch (choice) {
            case 1:
            {
                cin.clear();
                system("cls");
                cout << "Номер книги: " << defaultBookSize + 1 << endl;
                string Title_, Author_, Genre_; float Price_;
                cout << "Введите название книги: ";
                getline(cin, Title_);
                cout << endl;
                cout << "Введите автора книги: ";
                getline(cin, Author_);
                cout << endl;
                cout << "Введите жанр книги: ";
                getline(cin, Genre_);
                cout << endl;
                cout << "Введите цену книги($): ";
                Price_ = CheckPrice();
                cout << endl;
                defaultBook[defaultBookSize] = new PrintProduct(Title_, Author_, Genre_, Price_);
                defaultBookSize++;
                break;
            }
            case 2:
            {
                cin.clear();
                system("cls");
                cout << "Номер книги: " << discountedBooksSize + 1 << endl;
                string Title_, Author_, Genre_; float Price_, Discounted_;
                cout << "Введите название книги: ";
                getline(cin, Title_);
                cout << endl;
                cout << "Введите автора книги: ";
                getline(cin, Author_);
                cout << endl;
                cout << "Введите жанр книги: ";
                getline(cin, Genre_);
                cout << endl;
                cout << "Введите цену книги($): ";
                Price_ = CheckPrice();
                cout << endl;
                cout << "Введите скидку($): ";
                Discounted_ = checkDiscound(Price_);
                cout << endl;
                discountedBooks[discountedBooksSize] = new DiscountedBook(Title_, Author_, Genre_, Price_, Discounted_);
                discountedBooksSize++;
                break;
            }
            case 3:
            {
                cin.clear();
                system("cls");
                cout << "Номер книги: " << limitedQuantitySize + 1 << endl;
                string Title_, Author_, Genre_; float Price_; int Quantity_;
                cout << "Введите название книги: ";
                getline(cin, Title_);
                cout << endl;
                cout << "Введите автора книги: ";
                getline(cin, Author_);
                cout << endl;
                cout << "Введите жанр книги: ";
                getline(cin, Genre_);
                cout << endl;
                cout << "Введите цену книги($): ";
                Price_ = CheckPrice();
                cout << endl;
                cout << "Введите кол-во: ";
                Quantity_ = CheckInt();
                cout << endl;
                limitedQuantityBooks[limitedQuantitySize] = new LimitedQuantityBook(Title_, Author_, Genre_, Price_, Quantity_);
                limitedQuantitySize++;
                break;
            }
            case 4:
            {
                cin.clear();
                system("cls");
                cout << "Номер книги: " << rareBooksSize + 1 << endl;
                string Title_, Author_, Genre_, Rare_; float Price_, Discounted_; int Quantity_;
                cout << "Введите название книги: ";
                getline(cin, Title_);
                cout << endl;
                cout << "Введите автора книги: ";
                getline(cin, Author_);
                cout << endl;
                cout << "Введите жанр книги: ";
                getline(cin, Genre_);
                cout << endl;
                cout << "Введите цену книги($): ";
                Price_ = CheckPrice();
                cout << endl;
                cout << "Введите скидку($): ";
                Discounted_ = checkDiscound(Price_);
                cout << endl;
                cout << "Введите кол-во: ";
                Quantity_ = CheckInt();
                cout << endl;
                cout << "Введите редкость книги: ";
                getline(cin, Rare_);
                rareBooks[rareBooksSize] = new RareBook(Title_, Author_, Genre_, Price_,Discounted_, Quantity_, Rare_);
                rareBooksSize++;
                break;
            }
            case 5:
            {
                system("cls");
                int choiceBook;
                cout << "\t\t\t\t\t\tВыберите книгу для просмотра информации\n";
                cout << "1. Книги без скидки" << endl;
                cout << "2. Книги со скидкой" << endl;
                cout << "3. Книги с ограниченным кол-вом" << endl;
                cout << "4. Редкие книги" << endl;
                cout << "Ваш выбор: ";
                cout << endl;
                choiceBook = CheckInt();
                if (choiceBook == 1) {
                    for (int i = 0; i < defaultBookSize; i++) {
                        defaultBook[i]->Display();
                    }
                }
                else if (choiceBook == 2) {
                    for (int i = 0; i < discountedBooksSize; i++) {
                        discountedBooks[i]->Display();
                    }
                }
                else if (choiceBook == 3) {
                    for (int i = 0; i < limitedQuantitySize; i++) {
                        limitedQuantityBooks[i]->DisplayInfoWithQuantity();
                    }
                }
                else if (choiceBook == 4) {
                    for (int i = 0; i < rareBooksSize; i++) {
                        rareBooks[i]->DisplayRareBooks();
                    }
                }
                else {
                    cout << "Неправильный ввод" << endl;
                }
                break;
            }
        }
    }

    return 0;
}
