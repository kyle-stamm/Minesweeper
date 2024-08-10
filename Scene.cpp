
#include "Scene.h"

Scene::Scene() {
    screenHeight = 0;
    screenWidth = 0;
    screen = new RenderWindow;
    active = false;
}

Scene::Scene(string sceneName, int height, int width, Color backgroundColor) {
    name = sceneName;
    screenHeight = height;
    screenWidth = width;
    background = backgroundColor;
    screen = new RenderWindow;
    active = false;
}

string Scene::getName() {
    return name;
}

int Scene::getHeight() {
    return screenHeight;
}

int Scene::getWidth() {
    return screenWidth;
}

Color Scene::getBackgroundColor() {
    return background;
}

vector<Visual*> Scene::getElements() {
    return elements;
}

RenderWindow* Scene::getScreen() {
    return screen;
}

void Scene::addElement(Visual* element) {
    elements.push_back(element);
}

void Scene::draw() {
    screen->clear(background);
    for(Visual* element : elements) {
        element->draw(*screen);
    }
    screen->display();
}

void Scene::activateWindow() {
    screen->create(VideoMode(screenWidth, screenHeight), name);
    screen->setFramerateLimit(120);
    active = true;
}

void Scene::deactivateWindow() {
    if (active) {
        screen->close();
    }
}


//=========================================================================//


LeaderboardScene::LeaderboardScene(string sceneName, int height, int width, Color backgroundColor, Font fontChoice) :
                             Scene(sceneName, height, width, backgroundColor) {

    font = fontChoice;

    ifstream file("files/leaderboard.txt");
    string line;

    while(getline(file, line)) {

        istringstream stream(line);

        string token;
        string mins;
        string secs;
        getline(stream, token, ',');
        mins = token.substr(0, 2);
        secs = token.substr(3, 2);

        string name;
        getline(stream, name, ',');
        name = name.substr(1, name.size() - 1);

        scores.emplace_back(name, 60 * stoi(mins) + stoi(secs));
    }

    updateGraphic();
}

void LeaderboardScene::updateGraphic() {
    string textToDisplay;
    for(int x = 0; x < 5; x++) {
        textToDisplay += to_string(x + 1) + ".\t" + scores[x].name + "\t" + scores[x].minsStr + ":" + scores[x].secsStr + "\n\n";
    }
    Vector2f leaderBoardTextPos(screenWidth / 2, screenHeight / 2 + 20);
    TextElement* leaderboardText = new TextElement(textToDisplay, font, 18, Color::White, leaderBoardTextPos, true);
    leaderboardText->center();
    addElement(leaderboardText);
}

void LeaderboardScene::addElement(Visual* element) {
    if (!elements.empty()) {
        delete elements[0];
        elements.pop_back();
    }
    elements.push_back(element);
}

void LeaderboardScene::addScore(string name, int time) {
    for(auto& score : scores) {
        if (score.name[score.name.size() - 1] == '*') {
            score.name = score.name.substr(0, score.name.size() - 1);
        }
    }
    scores.emplace_back(name + "*", time);
    sortScores();
    updateGraphic();
    updateFile();
}

void LeaderboardScene::sortScores() {
    int min;
    for(int x = 0; x < scores.size(); x++) {
        min = x;
        for(int y = x + 1; y < scores.size(); y++) {
            if (scores[y] < scores[min]) {
                min = y;
            }
        }
        swap(scores[x], scores[min]);
    }
}

void LeaderboardScene::updateFile() {
    ofstream file("files/leaderboard.txt");
    for(int x = 0; x < 5; x++) {
        if (scores[x].name[scores[x].name.size() - 1] == '*') {
            file << scores[x].minsStr << ":" << scores[x].secsStr << ", " << scores[x].name.substr(0, scores[x].name.size() - 1) << endl;
        }
        else {
            file << scores[x].minsStr << ":" << scores[x].secsStr << ", " << scores[x].name << endl;
        }
    }
}


//==============================================================//


LeaderboardScene::Score::Score(string name, int time) {
    this->name = name;
    this->time = time;
    mins = time / 60;
    secs = time % 60;

    if (mins < 10) {
        minsStr = "0" + to_string(mins);
    }
    else {
        minsStr = to_string(mins);
    }

    if (secs < 10) {
        secsStr = "0" + to_string(secs);
    }
    else {
        secsStr = to_string(secs);
    }

}

bool LeaderboardScene::Score::operator<(const LeaderboardScene::Score& other) const {
    if (time < other.time) {
        return true;
    }
    return false;
}
