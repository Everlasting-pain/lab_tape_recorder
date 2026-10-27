#include "TapeRecorder.h"
#include <iostream>
using namespace std;

TapeRecorder::TapeRecorder() {
    power = false;
    cassette = false;
    mode = STOP;
}

TapeRecorder::TapeRecorder(bool power, bool cassette) {
    this->power = power;
    this->cassette = cassette;
    mode = STOP;
}

bool TapeRecorder::changePower() {
    power = !power;
    if (!power) mode = STOP;
    return true;
}

bool TapeRecorder::changeCassette() {
    if (mode != STOP) return false;
    cassette = !cassette;
    return true;
}

bool TapeRecorder::play() {
    if (!power || !cassette || mode == PLAY) return false;
    mode = PLAY;
    return true;
}

bool TapeRecorder::record() {
    if (!power || !cassette || mode == RECORD) return false;
    mode = RECORD;
    return true;
}

bool TapeRecorder::rewind() {
    if (!power || !cassette || mode == REWIND) return false;
    mode = REWIND;
    return true;
}

bool TapeRecorder::stop() {
    if (!power || mode == STOP) return false;
    mode = STOP;
    return true;
}

bool TapeRecorder::getPower() const { return power; }
bool TapeRecorder::getCassette() const { return cassette; }
Mode TapeRecorder::getMode() const { return mode; }

string TapeRecorder::stateName() const {
    if (!power) return cassette ? "Выключен, кассета вставлена" : "Выключен, кассеты нет";
    if (!cassette) return "Включен, кассеты нет";
    switch (mode) {
        case PLAY:   return "Воспроизведение";
        case RECORD: return "Запись";
        case REWIND: return "Перемотка";
        default:     return "Готов (остановлен)";
    }
}

void TapeRecorder::show() const {
    const string modes[4] = {"STOP", "PLAY", "RECORD", "REWIND"};
    cout << "Питание: " << (power ? "вкл" : "выкл")
         << " | Кассета: " << (cassette ? "есть" : "нет")
         << " | Режим: " << modes[mode] << endl;
    cout << "Состояние: " << stateName() << endl;
}