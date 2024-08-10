
#include "TextureManager.h"

TextureManager::TextureManager() = default;

TextureManager::TextureManager(const vector<string>& textureList) {
    Texture* newTexture;
    for(const string& fileName : textureList) {
        newTexture = new Texture;
        if (newTexture->loadFromFile(fileName)) {
            textures[fileName] = newTexture;
        }
        else {
            throw runtime_error("Error: texture was not initialized. Possibly invalid file name.");
        }
    }
}

