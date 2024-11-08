
#include "Board.h"

Board::Board() {
    numRows = 0;
    numCols = 0;
    numMines = 0;
    flagsUsed = 0;
    cellTextures = nullptr;
    winGraphic = nullptr;
    timer = nullptr;
    counter = nullptr;
}

Board::Board(unsigned int rows, unsigned int cols, int mines) {
    numRows = rows;
    numCols = cols;
    numMines = mines;
    flagsUsed = 0;
    cellTextures = new TextureManager(cellTextureList);
    winGraphic = nullptr;
    timer = nullptr;
    counter = nullptr;

    for (int row = 0; row < numRows; row++) {
        vector<Cell*> newCol(numCols);
        for (int col = 0; col < numCols; col++) {
            newCol[col] = new  Cell(row, col, cellTextures);
        }
        grid.push_back(newCol);
    }
    setupNeighbors();
    setupMines();

    statuses.emplace("running", false);
    statuses.emplace("win", false);
    statuses.emplace("lose", false);
    statuses.emplace("leaderboard", false);
    statuses.emplace("debug", false);
    statuses.emplace("pause/play", true);
    statuses.emplace("reset", false);
}

Board::~Board() {
    for(int row = 0; row < numRows; row++) {
        for(int col = 0; col < numCols; col++) {
            delete grid[row][col];
        }
    }

    delete cellTextures;

    auto iter = buttons.begin();
    for(; iter != buttons.end(); ++iter) {
        delete iter->second;
    }

    delete counter;
    delete timer;
}

unsigned int Board::getNumRows() const {
    return numRows;
}

unsigned int Board::getNumCols() const {
    return numCols;
}

vector<vector<Cell*>> Board::getBoard() {
    return grid;
}

map<string, bool> Board::getStatuses() {
    return statuses;
}

double Board::getTime() {
    return timer->getTime();
}

void Board::addWinGraphic(Face* graphic) {
    winGraphic = graphic;
}

void Board::addTimer(Timer* timerGraphic) {
    timer = timerGraphic;
}

void Board::addCounter(Counter* counterGraphic) {
    counter = counterGraphic;
}

void Board::addButton(const string& name, Button* button) {
    buttons.emplace(name, button);
}

void Board::setupNeighbors() {
    for(int row = 0; row < numRows; row++) {
        for(int col = 0; col < numCols; col++) {

            vector<int*> neighborCoords;
            int* coords;

            if (col > 0) {
                coords = new int[2];
                coords[0] = row;
                coords[1] = col - 1;
                neighborCoords.push_back(coords);
            }

            if (col < numCols - 1) {
                coords = new int[2];
                coords[0] = row;
                coords[1] = col + 1;
                neighborCoords.push_back(coords);
            }

            if (row > 0) {
                coords = new int[2];
                coords[0] = row - 1;
                coords[1] = col;
                neighborCoords.push_back(coords);
            }

            if (row < numRows - 1) {
                coords = new int[2];
                coords[0] = row + 1;
                coords[1] = col;
                neighborCoords.push_back(coords);
            }

            if (col > 0 && row > 0) {
                coords = new int[2];
                coords[0] = row - 1;
                coords[1] = col - 1;
                neighborCoords.push_back(coords);
            }

            if (col > 0 && row < numRows - 1) {
                coords = new int[2];
                coords[0] = row + 1;
                coords[1] = col - 1;
                neighborCoords.push_back(coords);
            }

            if (col < numCols - 1 && row > 0) {
                coords = new int[2];
                coords[0] = row - 1;
                coords[1] = col + 1;
                neighborCoords.push_back(coords);
            }

            if (col < numCols - 1 && row < numRows - 1) {
                coords = new int[2];
                coords[0] = row + 1;
                coords[1] = col + 1;
                neighborCoords.push_back(coords);
            }

            for (auto& neighborCoord : neighborCoords) {
                grid[row][col]->addNeighbor(grid[neighborCoord[0]][neighborCoord[1]]);
                delete[] neighborCoord;
            }
        }
    }
}

void Board::setupMines() {

    srand(time(nullptr));
    int num = 0;
    while (num < numMines) {
        int row = rand() % numRows;
        int col = rand() % numCols;
        if (!grid[row][col]->hasMine()) {
            grid[row][col]->giveMine();
            num++;
        }
    }

}

void Board::draw(RenderWindow& screen) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            grid[row][col]->draw(screen);
        }
    }
}

void Board::startGame() {
    statuses["running"] = true;
}

void Board::closeLeaderboard() {
    statuses["leaderboard"] = false;
    buttons["leaderboard"]->reset();
}

void Board::update(Vector2f mousePos, short mouseButton) {

    current_frame = chrono::high_resolution_clock::now();
    if (statuses["running"] && !statuses["leaderboard"]) {
        if (statuses["pause/play"] && !statuses["lose"] && !statuses["win"]) {

            chrono::duration<double> delta_time = current_frame - last_frame;
            timer->update(delta_time.count());

            for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < numCols; col++) {
                    if (grid[row][col]->getSprite().getGlobalBounds().contains(mousePos)) {
                        if (mouseButton == 1) {
                            if (grid[row][col]->click()) {
                                statuses["lose"] = true;
                            }
                        }
                        else if (mouseButton == 2 && !grid[row][col]->isRevealed()) {
                            if (!grid[row][col]->isFlagged()) {
                                grid[row][col]->flag();
                            }
                            else if (grid[row][col]->isFlagged()) {
                                grid[row][col]->unflag();
                            }
                        }

                        updateFlagCount();
                        checkWin();
                    }
                }
            }
        }


        if (!statuses["lose"] && !statuses["win"]) {
            statuses["pause/play"] = buttons["pause/play"]->click(mousePos);
            statuses["debug"] = buttons["debug"]->click(mousePos);
        }
        statuses["leaderboard"] = buttons["leaderboard"]->click(mousePos);
        statuses["reset"] = buttons["face"]->click(mousePos);
    }
    statusActions();
    last_frame = current_frame;
}

void Board::updateFlagCount() {
    flagsUsed = 0;
    for(int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col]->isFlagged()) {
                flagsUsed++;
            }
        }
    }
    counter->update(numMines - flagsUsed);
}

void Board::checkWin() {
    for(int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (!grid[row][col]->hasMine() && !grid[row][col]->isRevealed()) {
                return;
            }
        }
    }
    statuses["win"] = true;
}

void Board::statusActions() {

    for(int row = 0; row < numRows; row++) {
        for(int col = 0; col < numCols; col++) {
            if (statuses["debug"]) {
                grid[row][col]->debugOn();
            }
            else {
                grid[row][col]->debugOff();
            }

            if (!statuses["pause/play"]) {
                grid[row][col]->pause();
            }
            else {
                grid[row][col]->unpause();
            }

            if (statuses["leaderboard"]) {
                grid[row][col]->pause();
            }
        }
    }

    if (statuses["win"]) {
        winGraphic->playerWins();
        for(int row = 0; row < numRows; row++) {
            for(int col = 0; col < numCols; col++) {
                if (grid[row][col]->hasMine()) {
                    if (!grid[row][col]->isFlagged()) {
                        grid[row][col]->flag();
                    }
                }
                else if (grid[row][col]->isFlagged() && !grid[row][col]->hasMine()) {
                    grid[row][col]->unflag();
                }
            }
        }
    }
    updateFlagCount();

    if (statuses["lose"]) {
        winGraphic->playerLoses();
        for(int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                grid[row][col]->gameEnd();
            }
        }
    }

    if (statuses["reset"]) {
        resetBoard();
    }
}

void Board::resetBoard() {
    flagsUsed = 0;

    for(int row = 0; row < numRows; row++) {
        for(int col = 0; col < numCols; col++) {
            grid[row][col]->resetCell();
        }
    }

    setupMines();

    auto iter = statuses.begin();
    for(; iter != statuses.end(); ++iter) {
        iter->second = false;
    }
    statuses["running"] = true;

    auto iter2 = buttons.begin();
    for(; iter2 != buttons.end(); ++iter2) {
        iter2->second->reset();
    }

    winGraphic->resetGraphic();
    timer->resetTime();

    updateFlagCount();
}
