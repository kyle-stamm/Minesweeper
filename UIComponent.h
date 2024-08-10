#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Visual.h"
#include "TextureManager.h"

#ifndef PROJECT_3_UICOMPONENT_H
#define PROJECT_3_UICOMPONENT_H

class UIComponent : public Visual {

protected:
    vector<string> textureList;
    TextureManager* textures;
    Sprite drawing;

    int numRows;
    int numCols;
    Vector2f pos;

public:
    UIComponent();
    UIComponent(int rows, int cols);

    void draw(RenderWindow& screen) override;
    virtual ~UIComponent() = default;

};

#endif
