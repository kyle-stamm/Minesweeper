#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "GUI.h"

void loadConfig(int& rows, int& cols, int& numMines, Font& font) {
    ifstream config("files/config.cfg");
    string line;

    getline(config, line);
    cols = stoi(line);

    getline(config, line);
    rows = stoi(line);

    getline(config, line);
    numMines = stoi(line);

    font.loadFromFile("files/font.ttf");
}

void update(Vector2f mousePos, short mouseButton, Board& board) {
    board.update(mousePos, mouseButton);
}

void render(vector<Scene*>& scenes) {

    for (Scene* scene : scenes) {
        scene->draw();
    }
}

int main() {


    Font font;
    int rows, cols, mines;
    loadConfig(rows, cols, mines, font);

    map<string, Scene*> scenes;

    Scene welcome("Welcome", (rows * 32) + 100, cols * 32, Color::Blue);
    scenes["welcome"] = &welcome;

    Vector2f titlePos((float) scenes["welcome"]->getWidth() / 2, (float) scenes["welcome"]->getHeight() / 2 - 150);
    auto* title = new TextElement("WELCOME TO MINESWEEPER!", font, 24, Color::White, titlePos, true, true);
    scenes["welcome"]->addElement(title);

    Vector2f enterPos((float) scenes["welcome"]->getWidth() / 2, (float) scenes["welcome"]->getHeight() / 2 - 75);
    auto* enterName = new TextElement("Enter your name:", font, 20, Color::White, enterPos, true);
    scenes["welcome"]->addElement(enterName);

    Vector2f inputPos(scenes["welcome"]->getWidth() / 2, scenes["welcome"]->getHeight() / 2 - 45);
    auto* input = new TextInput(font, 18, Color::Yellow, inputPos);
    scenes["welcome"]->addElement(input);



    Scene game("Minesweeper", (rows * 32) + 100, cols * 32, Color::White);
    scenes["game"] = &game;

    auto* board = new Board(rows, cols, mines);
    scenes["game"]->addElement(board);

    Face* face = new Face(rows, cols);
    scenes["game"]->addElement(dynamic_cast<Visual*>(face));
    board->addButton("face", face);
    board->addWinGraphic(face);

    auto* pauseplay = new PausePlay(rows, cols);
    scenes["game"]->addElement(dynamic_cast<Visual*>(pauseplay));
    board->addButton("pause/play", pauseplay);

    auto* debug = new Debug(rows, cols);
    scenes["game"]->addElement(dynamic_cast<Visual*>(debug));
    board->addButton("debug", debug);

    auto* leaderboard = new Leaderboard(rows, cols);
    scenes["game"]->addElement(dynamic_cast<Visual*>(leaderboard));
    board->addButton("leaderboard", leaderboard);

    auto* counter = new Counter(rows, cols, mines);
    scenes["game"]->addElement(counter);
    board->addCounter(counter);

    auto* timer = new Timer(rows, cols);
    scenes["game"]->addElement(timer);
    board->addTimer(timer);



    LeaderboardScene leaderboardWindow = LeaderboardScene("Leaderboard", (rows * 16) + 50, cols * 16, Color::Blue, font);
    scenes["leaderboard"] = &leaderboardWindow;


    RenderWindow* activeScene = scenes["welcome"]->getScreen();
    scenes["welcome"]->activateWindow();
    vector<Scene*> scenesList = {scenes["welcome"]};


    Vector2f mousePos;
    bool clicking = false;
    bool wait = false;
    short mouseButton;

    while (activeScene->isOpen()) {

        Event event;
        while (activeScene->pollEvent(event)) {
            if (event.type == Event::Closed) {

                if (activeScene == scenes["leaderboard"]->getScreen()) {
                    activeScene->close();
                    activeScene = scenesList[0]->getScreen();
                    board->closeLeaderboard();
                }
                else {
                    activeScene->close();
                    return 0;
                }

            }

            if (event.type == Event::MouseButtonReleased) {
                clicking = false;
            }


            if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Backspace)) {
                input->removeChar();
            }

            if (event.type == sf::Event::TextEntered) {
                char inputChar = event.text.unicode;
                input->addInput(inputChar);
            }

            if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Enter)) {
                if (!input->getName().empty())
                    board->startGame();
            }

        }

        if (!clicking && Mouse::isButtonPressed(Mouse::Left)) {
            mousePos = activeScene->mapPixelToCoords(Mouse::getPosition(*activeScene));
            clicking = true;
            mouseButton = 1;
        }
        else if (!clicking && Mouse::isButtonPressed(Mouse::Right)) {
            mousePos = activeScene->mapPixelToCoords(Mouse::getPosition(*activeScene));
            clicking = true;
            mouseButton = 2;
        }
        else {
            mousePos = Vector2f(-1.f, -1.f);
            mouseButton = 0;
        }


        if (board->getStatuses()["running"] && scenesList[0] != scenes["game"]) {
            scenesList[0]->deactivateWindow();
            scenesList[0] = scenes["game"];
            scenesList[0]->activateWindow();

            activeScene = scenes["game"]->getScreen();
        }

        if (board->getStatuses()["leaderboard"] && scenesList.size() < 2) {
            scenesList.push_back(scenes["leaderboard"]);
            scenes["leaderboard"]->activateWindow();
            activeScene = scenes["leaderboard"]->getScreen();
        }
        else if (!board->getStatuses()["leaderboard"] && scenesList.size() == 2){
            scenes["leaderboard"]->deactivateWindow();
            scenesList.pop_back();
            activeScene = scenes["game"]->getScreen();
        }

        if (board->getStatuses()["win"] && !wait) {
            wait = true;
            leaderboardWindow.addScore(input->getName(), (int)board->getTime());
        }

        if (!board->getStatuses()["win"] && wait) {
            wait = false;
        }

        update(mousePos, mouseButton, *board);
        render(scenesList);
    }
    return 0;
}