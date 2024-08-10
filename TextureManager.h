#include <iostream>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef PROJECT_3_TEXTUREMANAGER_H
#define PROJECT_3_TEXTUREMANAGER_H


struct TextureManager {

    map<string, Texture*> textures;

    TextureManager();
    explicit TextureManager(const vector<string>& textureList);
};


#endif
