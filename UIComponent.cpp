
#include "UIComponent.h"

UIComponent::UIComponent() {
    numRows = 0;
    numCols = 0;
    pos = Vector2f(-1, -1);
    textures = nullptr;
}

UIComponent::UIComponent(int rows, int cols) {
    numRows = rows;
    numCols = cols;
    pos = Vector2f(0, 0);
    textures = nullptr;
}

void UIComponent::draw(sf::RenderWindow& screen) {
    screen.draw(drawing);
}
