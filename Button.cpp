
#include "Button.h"

Button::Button(int rows, int cols) : UIComponent(rows, cols) {}

void Button::reset() {
    clicked = false;
}


//==================================================//


Face::Face(){
    textures = nullptr;
    playerWin = false;
    playerLose = false;
}

Face::Face(int rows, int cols) : Button(rows, cols) {

    textureList = {"files/images/face_happy.png",
                   "files/images/face_win.png",
                   "files/images/face_lose.png"};

    pos = Vector2f(((float)numCols / 2.0f * 32) - 32, ((float)numRows + 0.5f) * 32);

    textures = new TextureManager(textureList);
    playerWin = false;
    playerLose = false;

    drawing.setTexture(*textures->textures["files/images/face_happy.png"]);
    drawing.setPosition(pos);
}

void Face::playerLoses() {
    playerLose = true;
    drawing.setTexture(*textures->textures["files/images/face_lose.png"]);
}

void Face::playerWins() {
    playerWin = true;
    drawing.setTexture(*textures->textures["files/images/face_win.png"]);
}

bool Face::click(Vector2f mousePos) {
    if (drawing.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        return true;
    }
    return false;
}

void Face::resetGraphic() {
    playerLose = false;
    playerWin = false;
    drawing.setTexture(*textures->textures["files/images/face_happy.png"]);
}


//=======================================================//


PausePlay::PausePlay() {
    clicked = false;
}

PausePlay::PausePlay(int rows, int cols) : Button(rows, cols) {

    textureList = {"files/images/pause.png",
                   "files/images/play.png"};

    pos = Vector2f(((float)numCols * 32) - 240, ((float)numRows + 0.5f) * 32);

    clicked = true;

    textures = new TextureManager(textureList);
    drawing.setTexture(*textures->textures["files/images/pause.png"]);
    drawing.setPosition(pos);
}

bool PausePlay::click(Vector2f mousePos) {
    if (drawing.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        if (clicked) {
            clicked = false;
            drawing.setTexture(*textures->textures["files/images/play.png"]);
        }
        else {
            clicked = true;
            drawing.setTexture(*textures->textures["files/images/pause.png"]);
        }
    }
    return clicked;
}

void PausePlay::reset() {
    drawing.setTexture(*textures->textures["files/images/pause.png"]);
    clicked = true;
}


//======================================================//


Debug::Debug() = default;

Debug::Debug(int rows, int cols) : Button(rows, cols) {

    textureList = {"files/images/debug.png"};

    pos = Vector2f(((float)numCols * 32) - 304, ((float)numRows + 0.5f) * 32);

    textures = new TextureManager(textureList);

    drawing.setTexture(*textures->textures["files/images/debug.png"]);
    drawing.setPosition(pos);
}

bool Debug::click(Vector2f mousePos) {

    if (drawing.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        if (clicked) {
            clicked = false;
        }
        else {
            clicked = true;
        }
    }
    return clicked;
}


//==================================================//


Leaderboard::Leaderboard() = default;

Leaderboard::Leaderboard(int rows, int cols) : Button(rows, cols) {

    vector<string> textureList = {"files/images/leaderboard.png"};

    pos = Vector2f(((float)numCols * 32) - 176, ((float)numRows + 0.5f) * 32);

    textures = new TextureManager(textureList);

    drawing.setTexture(*textures->textures["files/images/leaderboard.png"]);
    drawing.setPosition(pos);
}

bool Leaderboard::click(Vector2f mousePos) {

    if (drawing.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        if (clicked) {
            clicked = false;
        }
        else {
            clicked = true;
        }
    }
    return clicked;
}
