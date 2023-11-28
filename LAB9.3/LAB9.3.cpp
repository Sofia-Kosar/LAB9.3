#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;

struct Route
{
    string sname;
    string ename;
    int rnum{};
};

void Create(Route* p, const int N);
void Print(Route* p, const int N);
void Sort(Route* p, const int N);
void PrintAll(Route* p, const int N);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введіть кількість маршрутів N: "; cin >> N;
    Route* p = new Route[N];
    double proc = 0, avg = 0, Kurs = 0, average = 0;
    string prizv;
    int found = 0;
    char filename[100]{};
    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран за номером" << endl;
        cout << " [3] - вивід масиву " << endl;
        cout << " [4] - вивід впорядкованого масиву" << endl;
        cout << " [5] - зберегти дані в файл" << endl;
        cout << " [6] - завантажити дані з файлу" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;

        case 2:
            Print(p, N);
            break;

        case 3:
            Sort(p, N);
            PrintAll(p, N);
            break;

        case 4:
            Sort(p, N); // Викликаємо функцію Sort перед виведенням масиву
            PrintAll(p, N);
            break;

        case 5:
            cout << "Введіть ім'я файлу для збереження: "; cin >> filename;
            SaveToFile(p, N, filename);
            cout << "Дані збережено в файл." << endl;
            break;

        case 6:
            cout << "Введіть ім'я файлу для завантаження: "; cin >> filename;
            LoadFromFile(p, N, filename);
            cout << "Дані завантажено з файлу." << endl;
            break;

        case 0:
            break;

        default:
            cout << "Ви ввели помилкове значення!" <<
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);
    delete[] p; // Don't forget to free the allocated memory
    return 0;
}

void Create(Route* p, const int N)
{
    int Predmet = 0;
    for (int i = 0; i < N; i++)
    {
        int n = 0;
        cin.get();
        cin.sync();
        cout << " Початковий пункт : "; getline(cin, p[i].sname);
        cout << " Кінцевий пункт : "; cin >> p[i].ename;
        cout << " Номер маршруту : "; cin >> p[i].rnum;
        cout << endl;
    }
}

void Print(Route* p, const int N)
{
    int routenumber, count = 0;
    cout << "Введіть номер маршруту: "; cin >> routenumber;
    for (int i = 0; i < N; i++) {
        if (routenumber == p[i].rnum)
            count++;
    }
    if (count > 0) {
        cout << "=================================="
            << endl;
        cout << "__________________________________"
            << endl;
        cout << "|  Початок  |  Кінець  |  Номер  |"
            << endl;
        cout << "----------------------------------"
            << endl;
        for (int i = 0; i < N; i++)
        {
            if (routenumber == p[i].rnum) {
                cout << "| " << setw(10) << left << p[i].sname
                    << "| " << setw(10) << left << p[i].ename
                    << "| " << setw(6) << left << p[i].rnum << "|" << endl;
            }
        }
        cout << "=================================="
            << endl;
        cout << endl;
    }
    else
        cout << "\nВи ввели невірний номер!\n"
        "Слід ввести число - номер існуючого маршруту" << endl;
}

void Sort(Route* p, const int N)
{
    Route tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            if (p[i1].rnum > p[i1 + 1].rnum)
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

void PrintAll(Route* p, const int N)
{
    cout << "=================================="
        << endl;
    cout << "__________________________________"
        << endl;
    cout << "|  Початок  |  Кінець  |  Номер  |"
        << endl;
    cout << "----------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(10) << left << p[i].sname
            << "| " << setw(10) << left << p[i].ename
            << "| " << setw(6) << left << p[i].rnum << "|" << endl;
    }
    cout << "=================================="
        << endl;
    cout << endl;
}

void SaveToFile(Route* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
    fout.write((char*)&N, sizeof(N)); // записали кількість елементів
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Route)); // записали елементи масиву
    fout.close(); // закрили файл
}

void LoadFromFile(Route*& p, int& N, const char* filename)
{
    delete[] p; // знищили попередні дані
    ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
    fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
    p = new Route[N]; // створили динамічний масив
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Route)); // прочитали елементи масиву
    fin.close(); // закрили файл
}
