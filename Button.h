
#include "UIComponent.h"

#ifndef PROJECT_3_BUTTON_H
#define PROJECT_3_BUTTON_H


class Button : public UIComponent {

protected:
    bool clicked = false;

public:
    Button() = default;
    Button(int rows, int cols);
    virtual bool click(Vector2f mousePos) = 0;
    virtual void reset();
};


class Face : public Button {

    bool playerLose;
    bool playerWin;

public:
    Face();
    Face(int rows, int cols);

    void playerWins();
    void playerLoses();
    void resetGraphic();

    bool click(Vector2f mousePos) override;
};


//=========================================================//


class PausePlay : public Button {

public:
    PausePlay();
    PausePlay(int rows, int cols);

    bool click(Vector2f mousePos) override;
    void reset() override;
};


//========================================================//


class Debug : public Button {

public:
    Debug();
    Debug(int rows, int cols);

    bool click(Vector2f mousePos) override;
};


//=============================================================//


class Leaderboard : public Button {

public:
    Leaderboard();
    Leaderboard(int rows, int cols);

    bool click(Vector2f mousePos) override;
};
#endif //PROJECT_3_BUTTON_H
