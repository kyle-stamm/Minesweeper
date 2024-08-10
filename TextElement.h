#include <cctype>
using namespace std;

#include "UIComponent.h"

#ifndef PROJECT_3_TEXTELEMENT_H
#define PROJECT_3_TEXTELEMENT_H


class TextElement : public UIComponent {

protected:
    string text;
    Font font;
    int charSize;
    Color color;
    bool bold;
    bool underline;
    Vector2f pos;

    Text textObj;

public:
    TextElement();
    TextElement(string textToDisplay, Font fontChoice, int size, Color textColor, Vector2f position, bool isBold = false, bool isUnderline = false);

    void draw(RenderWindow& screen) override;
    void center();

};


//================================================================//


class TextInput : public TextElement {

    string input;

public:
    TextInput() = default;
    TextInput(const Font& fontChoice, int size, Color textColor, Vector2f position);

    string getName();

    void addInput(char inputChar);
    void removeChar();
};
#endif //PROJECT_3_TEXTELEMENT_H
