#include <chrono>
using namespace std;

#include "UIComponent.h"

#ifndef PROJECT_3_DIGITS_H
#define PROJECT_3_DIGITS_H


class Digits : public UIComponent {

protected:
    vector<Sprite> digitSprites;
    Sprite negativeSprite;

public:
    Digits();
    Digits(int rows, int cols);

    virtual void update(double amount) = 0;
};


//======================================================================//


class Counter : public Digits {

    Sprite counter[3];
    int count;

public:
    Counter();
    Counter(int rows, int cols, int numMines);

    void update(double amount) override;

    void draw(RenderWindow& screen) override;
};


//========================================================================//


class Timer : public Digits {

    Sprite timer[4];
    double time;
    int mins;
    int secs;

public:
    Timer();
    Timer(int rows, int cols);

    void resetTime();
    void update(double amount) override;
    int getTime();

    void draw(RenderWindow& screen) override;
};

#endif //PROJECT_3_DIGITS_H
