#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Visual.h"
#include "TextElement.h"

#ifndef PROJECT_3_SCENE_H
#define PROJECT_3_SCENE_H


class Scene {

protected:
    string name;
    int screenHeight;
    int screenWidth;
    RenderWindow* screen;
    vector<Visual*> elements;
    Color background;
    bool active;

public:
    Scene();
    Scene(string sceneName, int height, int width, Color backgroundColor);

    string getName();
    int getHeight();
    int getWidth();
    vector<Visual*> getElements();
    Color getBackgroundColor();
    RenderWindow* getScreen();

    virtual void addElement(Visual* element);

    void activateWindow();
    void deactivateWindow();

    virtual void draw();
};


//======================================================================//


class LeaderboardScene : public Scene {

    struct Score {

        string name;
        int time;
        int mins;
        int secs;

        string minsStr;
        string secsStr;

        Score(string name, int time);
        bool operator<(const Score& other) const;

    };

    vector<Score> scores;
    Font font;

public:
    LeaderboardScene() = default;
    LeaderboardScene(string sceneName, int height, int width, Color backgroundColor, Font fontChoice);

    void updateGraphic();

    void addElement(Visual* element) override;
    void addScore(string name, int time);
    void sortScores();
    void updateFile();

};
#endif //PROJECT_3_SCENE_H
