#include <iostream>
#include <string>
#include <windows.h>
#include "TapeRecorder.h"
using namespace std;

int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        getline(cin, s);
        try {
            size_t pos;
            int x = stoi(s, &pos);
            if (pos == s.size()) return x;
        } catch (...) {}
        cout << "Нужно целое число." << endl;
    }
}

void result(bool ok, const TapeRecorder& tr) {
    if (ok) cout << "Выполнено." << endl;
    else    cout << "Действие невозможно в текущем состоянии!" << endl;
    tr.show();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TapeRecorder tr;
    cout << "Создан магнитофон (конструктор по умолчанию)." << endl;
    tr.show();

    int work = 1;
    while (work) {
        cout << endl
             << "===== Магнитофон =====" << endl
             << "1. Вкл/выкл питание" << endl
             << "2. Вставить/извлечь кассету" << endl
             << "3. Воспроизведение" << endl
             << "4. Запись" << endl
             << "5. Перемотка" << endl
             << "6. Стоп" << endl
             << "7. Показать состояние" << endl
             << "0. Выход" << endl;
        int command = readInt("Введите номер команды -> ");

        switch (command) {
            case 1: result(tr.changePower(), tr); break;
            case 2: result(tr.changeCassette(), tr); break;
            case 3: result(tr.play(), tr); break;
            case 4: result(tr.record(), tr); break;
            case 5: result(tr.rewind(), tr); break;
            case 6: result(tr.stop(), tr); break;
            case 7: tr.show(); break;
            case 0: work = 0; break;
            default: cout << "Нет такой команды." << endl;
        }
    }
    cout << "До свидания!" << endl;
    return 0;
}