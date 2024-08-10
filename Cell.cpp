
#include "Cell.h"

Cell::Cell() {
    row = 0;
    col = 0;
    pos = Vector2f(0, 0);
    cellTextures = nullptr;
    clicked = false;
    mine = false;
    numNeighborsWithMine = 0;
    debug = false;
    flagged = false;
    playerLose = false;
    paused = false;
}

Cell::Cell(int rowIndex, int colIndex, TextureManager* textures) {
    row = rowIndex;
    col = colIndex;
    clicked = false;
    flagged = false;
    mine = false;
    debug = false;
    playerLose = false;
    numNeighborsWithMine = 0;
    paused = false;

    pos = Vector2f((float)col * 32, (float)row * 32);
    cellTextures = textures;

    cellDrawing.setTexture(*cellTextures->textures["files/images/tile_hidden.png"]);
    mineDrawing.setTexture(*cellTextures->textures["files/images/mine.png"]);

    cellDrawing.setPosition(pos.x, pos.y);
    mineDrawing.setPosition(pos.x, pos.y);
    numDrawing.setPosition(pos.x, pos.y);
    flagDrawing.setPosition(pos.x, pos.y);
}

int Cell::getRow() {
    return row;
}

int Cell::getCol() {
    return col;
}

vector<Cell*> Cell::getNeighbors() {
    return neighbors;
}

Sprite& Cell::getSprite() {
    return cellDrawing;
}

bool Cell::isFlagged() {
    return flagged;
}

bool Cell::hasMine() {
    return mine;
}

bool Cell::isRevealed() {
    return clicked;
}

void Cell::giveMine() {
    mine = true;
    mineDrawing.setTexture(*cellTextures->textures["files/images/mine.png"]);
    for(Cell* neighbor : neighbors) {
        neighbor->numNeighborsWithMine++;
    }
}

void Cell::addNeighbor(Cell* neighbor) {
    neighbors.push_back(neighbor);
}

void Cell::draw(RenderWindow& screen) {
    screen.draw(cellDrawing);
    if (!paused) {

        if (playerLose) {
            if (mine) {
                screen.draw(mineDrawing);
                if (flagged)
                    screen.draw(flagDrawing);
            }
            else {
                if (clicked)
                    screen.draw(numDrawing);
            }
        }
        else if (flagged) {
            screen.draw(flagDrawing);
        }
        else if (clicked) {
            if (mine) {
                screen.draw(mineDrawing);
            }
            else if (numNeighborsWithMine > 0) {
                screen.draw(numDrawing);
            }
        }
        else if (debug && mine) {
            screen.draw(mineDrawing);
        }
    }
}

bool Cell::click() {
    if (!clicked && !flagged) {
        cellDrawing.setTexture(*cellTextures->textures["files/images/tile_revealed.png"]);

        clicked = true;
        if (mine) {
            return true;
        }
        else if (numNeighborsWithMine > 0) {
            string numFileName = "files/images/number_" + to_string(numNeighborsWithMine) + ".png";
            numDrawing.setTexture(*cellTextures->textures[numFileName]);
            return false;
        }
        else {
            numDrawing.setTexture(*cellTextures->textures["files/images/tile_revealed.png"]);
            for (Cell* neighbor: neighbors) {
                if (!neighbor->hasMine())
                    neighbor->click();
            }
        }
    }
    return false;
}

void Cell::flag() {
    flagged = true;
    flagDrawing.setTexture(*cellTextures->textures["files/images/flag.png"]);
}

void Cell::unflag() {
    flagged = false;
    flagDrawing.setTexture(Texture());
}

void Cell::debugOn() {
    if (!debug) {
        debug = true;
    }
}

void Cell::debugOff() {
    if (debug) {
        debug = false;
    }
}

void Cell::resetCell() {
    cellDrawing.setTexture(*cellTextures->textures["files/images/tile_hidden.png"]);
    flagged = false;
    clicked = false;
    paused = false;
    mine = false;
    debug = false;
    playerLose = false;
    numNeighborsWithMine = 0;
}

void Cell::gameEnd() {
    playerLose = true;
    if (!mine) {
        flagged = false;
    }

    if (mine) {
        cellDrawing.setTexture(*cellTextures->textures["files/images/tile_revealed.png"]);
    }
}

void Cell::pause() {
    paused = true;
    cellDrawing.setTexture(*cellTextures->textures["files/images/tile_revealed.png"]);
}

void Cell::unpause() {
    paused = false;
    if (!clicked) {
        cellDrawing.setTexture(*cellTextures->textures["files/images/tile_hidden.png"]);
    }
}
