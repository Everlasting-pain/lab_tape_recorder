#include <iostream>
#include <string>
#include <windows.h>
#include "TapeRecorder.h"
using namespace std;

int passed = 0, failed = 0;

void check(const string& name, bool action, bool expectOk, const TapeRecorder& tr, const string& expectState) {
    bool ok = (action == expectOk) && (tr.stateName() == expectState);
    cout << (ok ? "[OK]   " : "[FAIL] ") << name << " -> " << tr.stateName() << endl;
    if (ok) passed++; else failed++;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "--- Конструктор по умолчанию ---" << endl;
    TapeRecorder a;
    check("T1  начальное состояние", true, true, a, "Выключен, кассеты нет");
    check("T2  play без питания", a.play(), false, a, "Выключен, кассеты нет");
    check("T3  stop без питания", a.stop(), false, a, "Выключен, кассеты нет");
    check("T4  вставить кассету", a.changeCassette(), true, a, "Выключен, кассета вставлена");
    check("T5  record без питания", a.record(), false, a, "Выключен, кассета вставлена");
    check("T6  включить питание", a.changePower(), true, a, "Готов (остановлен)");
    check("T7  воспроизведение", a.play(), true, a, "Воспроизведение");
    check("T8  play повторно", a.play(), false, a, "Воспроизведение");
    check("T9  извлечь кассету при PLAY", a.changeCassette(), false, a, "Воспроизведение");
    check("T10 запись из PLAY", a.record(), true, a, "Запись");
    check("T11 перемотка из RECORD", a.rewind(), true, a, "Перемотка");
    check("T12 стоп", a.stop(), true, a, "Готов (остановлен)");
    check("T13 стоп повторно", a.stop(), false, a, "Готов (остановлен)");
    check("T14 извлечь кассету", a.changeCassette(), true, a, "Включен, кассеты нет");
    check("T15 rewind без кассеты", a.rewind(), false, a, "Включен, кассеты нет");
    check("T16 выключить питание", a.changePower(), true, a, "Выключен, кассеты нет");

    cout << "--- Конструктор с параметрами (true, true) ---" << endl;
    TapeRecorder b(true, true);
    check("T17 начальное состояние", true, true, b, "Готов (остановлен)");
    check("T18 запись", b.record(), true, b, "Запись");
    check("T19 выключить во время записи", b.changePower(), true, b, "Выключен, кассета вставлена");
    check("T20 режим сброшен в STOP", b.getMode() == STOP, true, b, "Выключен, кассета вставлена");

    cout << endl << "Пройдено: " << passed << ", ошибок: " << failed << endl;
    return failed == 0 ? 0 : 1;
}