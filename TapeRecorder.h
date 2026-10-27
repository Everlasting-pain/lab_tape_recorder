#ifndef TAPERECORDER_H
#define TAPERECORDER_H

#include <string>

enum Mode { STOP, PLAY, RECORD, REWIND };

class TapeRecorder {
public:
    TapeRecorder();
    TapeRecorder(bool power, bool cassette);

    bool changePower();
    bool changeCassette();
    bool play();
    bool record();
    bool rewind();
    bool stop();

    bool getPower() const;
    bool getCassette() const;
    Mode getMode() const;
    std::string stateName() const;
    void show() const;

private:
    bool power;
    bool cassette;
    Mode mode;
};

#endif