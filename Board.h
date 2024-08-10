#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Cell.h"
#include "Button.h"
#include "Digits.h"
#include "TextureManager.h"

#ifndef PROJECT_3_BOARD_H
#define PROJECT_3_BOARD_H


class Board : public Visual {

private:
    unsigned int numRows;
    unsigned int numCols;
    int numMines;
    int flagsUsed;
    vector<vector<Cell*>> grid;

    chrono::time_point<std::chrono::high_resolution_clock> last_frame = chrono::high_resolution_clock::now();
    chrono::time_point<std::chrono::high_resolution_clock> current_frame;

    TextureManager* cellTextures;
    vector<string> cellTextureList = {"files/images/mine.png",
                                      "files/images/tile_hidden.png",
                                      "files/images/tile_revealed.png",
                                      "files/images/number_1.png",
                                      "files/images/number_2.png",
                                      "files/images/number_3.png",
                                      "files/images/number_4.png",
                                      "files/images/number_5.png",
                                      "files/images/number_6.png",
                                      "files/images/number_7.png",
                                      "files/images/number_8.png",
                                      "files/images/flag.png"};

    Timer* timer;
    Counter* counter;
    map<string, Button*> buttons;
    Face* winGraphic;
    map<string, bool> statuses;

public:
    Board();
    Board(unsigned int rows, unsigned int cols, int mines);
    ~Board();

    unsigned int getNumRows() const;
    unsigned int getNumCols() const;
    vector<vector<Cell*>> getBoard();
    map<string, bool> getStatuses();
    double getTime();

    void addWinGraphic(Face* graphic);
    void addTimer(Timer* timerGraphic);
    void addCounter(Counter* counterGraphic);
    void addButton(const string& name, Button* button);
    void setupNeighbors();
    void setupMines();
    void startGame();

    void draw(RenderWindow& screen) override;
    void closeLeaderboard();
    void update(Vector2f mousePos, short mouseButton);
    void updateFlagCount();
    void checkWin();
    void statusActions();
    void resetBoard();

};

#endif
