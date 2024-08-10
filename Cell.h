#include <vector>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Visual.h"
#include "TextureManager.h"

#ifndef PROJECT_3_CELL_H
#define PROJECT_3_CELL_H


class Cell : public Visual {

private:
    int row;
    int col;
    Vector2f pos;

    bool mine;

    Sprite cellDrawing;
    Sprite mineDrawing;
    Sprite numDrawing;
    Sprite flagDrawing;

    TextureManager* cellTextures;

    vector<Cell*> neighbors;
    int numNeighborsWithMine;

    bool clicked;
    bool flagged;
    bool debug;
    bool paused;
    bool playerLose;

public:
    Cell();
    Cell(int rowIndex, int colIndex, TextureManager* textures);

    int getRow();
    int getCol();
    vector<Cell*> getNeighbors();
    Sprite& getSprite();

    bool isRevealed();
    bool isFlagged();
    bool hasMine();

    void giveMine();
    void addNeighbor(Cell* neighbor);

    void draw(RenderWindow& screen) override;

    bool click();
    void flag();
    void unflag();
    void debugOn();
    void debugOff();

    void pause();
    void unpause();

    void resetCell();
    void gameEnd();

};


#endif
