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

void showAll(const TapeRecorder rec[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Магнитофон №" << i + 1 << ":" << endl;
        rec[i].show();
    }
}

void statistics(const TapeRecorder rec[], int n) {
    int on = 0, withCassette = 0, playing = 0, recording = 0, rewinding = 0;
    for (int i = 0; i < n; i++) {
        if (rec[i].getPower()) on++;
        if (rec[i].getCassette()) withCassette++;
        if (rec[i].getMode() == PLAY) playing++;
        if (rec[i].getMode() == RECORD) recording++;
        if (rec[i].getMode() == REWIND) rewinding++;
    }
    cout << "Всего магнитофонов: " << n << endl;
    cout << "Включено: " << on << ", выключено: " << n - on << endl;
    cout << "С кассетой: " << withCassette << endl;
    cout << "Воспроизводят: " << playing << ", записывают: " << recording
         << ", перематывают: " << rewinding << endl;
    cout << "Работают сейчас: " << playing + recording + rewinding << endl;
}

void turnOffAll(TapeRecorder rec[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (rec[i].getPower()) {
            rec[i].changePower();
            count++;
        }
    }
    cout << "Выключено магнитофонов: " << count << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TapeRecorder first;
    cout << "Создан магнитофон конструктором по умолчанию:" << endl;
    first.show();

    TapeRecorder second(true, true);
    cout << "Создан магнитофон конструктором с параметрами (true, true):" << endl;
    second.show();

    const int N = 3;
    TapeRecorder rec[N] = { first, second, TapeRecorder(true, false) };
    cout << endl << "Создан массив из " << N << " магнитофонов." << endl;
    showAll(rec, N);

    int cur = 0;
    int work = 1;
    while (work) {
        cout << endl
             << "===== Магнитофон №" << cur + 1 << " =====" << endl
             << "1. Вкл/выкл питание" << endl
             << "2. Вставить/извлечь кассету" << endl
             << "3. Воспроизведение" << endl
             << "4. Запись" << endl
             << "5. Перемотка" << endl
             << "6. Стоп" << endl
             << "7. Показать состояние" << endl
             << "8. Выбрать другой магнитофон" << endl
             << "9. Показать все магнитофоны" << endl
             << "10. Статистика по всем" << endl
             << "11. Выключить все" << endl
             << "0. Выход" << endl;
        int command = readInt("Введите номер команды -> ");

        switch (command) {
            case 1: result(rec[cur].changePower(), rec[cur]); break;
            case 2: result(rec[cur].changeCassette(), rec[cur]); break;
            case 3: result(rec[cur].play(), rec[cur]); break;
            case 4: result(rec[cur].record(), rec[cur]); break;
            case 5: result(rec[cur].rewind(), rec[cur]); break;
            case 6: result(rec[cur].stop(), rec[cur]); break;
            case 7: rec[cur].show(); break;
            case 8: {
                int k = readInt("Номер магнитофона (1-" + to_string(N) + "): ");
                if (k >= 1 && k <= N) {
                    cur = k - 1;
                    rec[cur].show();
                } else {
                    cout << "Нет магнитофона с таким номером." << endl;
                }
                break;
            }
            case 9: showAll(rec, N); break;
            case 10: statistics(rec, N); break;
            case 11: turnOffAll(rec, N); showAll(rec, N); break;
            case 0: work = 0; break;
            default: cout << "Нет такой команды." << endl;
        }
    }
    cout << "До свидания!" << endl;
    return 0;
}