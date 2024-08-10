
#include "Digits.h"

Digits::Digits() = default;

Digits::Digits(int rows, int cols) : UIComponent(rows, cols) {

    textureList = {"files/images/digits.png"};
    textures = new TextureManager(textureList);

    for(int x = 0; x < 11; x++) {
        digitSprites.emplace_back(*textures->textures["files/images/digits.png"], IntRect(x * 21, 0, 21, 32));
    }
}


//========================================================//


Counter::Counter() {
    count = 0;
};

Counter::Counter(int rows, int cols, int numMines) : Digits(rows, cols) {
    count = numMines;
    int temp = abs(count);

    counter[0] = digitSprites[temp / 100];
    temp %= 100;

    counter[1] = digitSprites[temp / 10];
    temp %= 10;

    counter[2] = digitSprites[temp];

    for(int x = 0; x < 3; x++) {
        counter[x].setPosition(33 + x * 21, 32 * (numRows + 0.5f) + 16);
    }

    negativeSprite = digitSprites[10];
    negativeSprite.setPosition(12, 32 * (numRows + 0.5f) + 16);
}

void Counter::draw(sf::RenderWindow& screen) {
    if (count < 0) {
        screen.draw(negativeSprite);
    }

    for(int x = 0; x < 3; x++) {
        screen.draw(counter[x]);
    }
}

void Counter::update(double amount) {
    count = (int)amount;
    int temp = abs(count);

    counter[0] = digitSprites[temp / 100];
    temp %= 100;

    counter[1] = digitSprites[temp / 10];
    temp %= 10;

    counter[2] = digitSprites[temp];

    for(int x = 0; x < 3; x++) {
        counter[x].setPosition(33 + x * 21, 32 * (numRows + 0.5f) + 16);
    }
}


//==========================================================//


Timer::Timer() {
    time = 0;
    mins = 0;
    secs = 0;
}

Timer::Timer(int rows, int cols) : Digits(rows, cols){
    time = 0;

    int temp;

    mins = (int)time / 60;
    temp = mins;
    timer[0] = digitSprites[temp / 10];
    temp %= 10;
    timer[1] = digitSprites[temp];

    secs = (int)time % 60;
    temp = secs;
    timer[2] = digitSprites[temp / 10];
    temp %= 10;
    timer[3] = digitSprites[temp];

    for(int x = 0; x < 2; x++) {
        timer[x].setPosition((x * 21) + (numCols * 32) - 97, 32 * (numRows + 0.5f) + 16);
    }
    for(int y = 2; y < 4; y++) {
        timer[y].setPosition(((y - 2) * 21) + (numCols * 32) - 54, 32 * (numRows + 0.5f) + 16);
    }
}

void Timer::draw(RenderWindow& screen) {
    for(int x = 0; x < 4; x++) {
        screen.draw(timer[x]);
    }
}

void Timer::resetTime() {
    time = 0;
}

void Timer::update(double amount) {

    time += amount;

    int temp;

    mins = (int)time / 60;
    temp = mins;
    timer[0] = digitSprites[temp / 10];
    temp %= 10;
    timer[1] = digitSprites[temp];

    secs = (int)time % 60;
    temp = secs;
    timer[2] = digitSprites[temp / 10];
    temp %= 10;
    timer[3] = digitSprites[temp];

    for(int x = 0; x < 2; x++) {
        timer[x].setPosition((x * 21) + (numCols * 32) - 97, 32 * (numRows + 0.5f) + 16);
    }
    for(int y = 2; y < 4; y++) {
        timer[y].setPosition(((y - 2) * 21) + (numCols * 32) - 54, 32 * (numRows + 0.5f) + 16);
    }
}

int Timer::getTime() {
    return (int)time;
}