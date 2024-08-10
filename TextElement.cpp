
#include "TextElement.h"

TextElement::TextElement() {
    charSize = 0;
    bold = false;
    underline = false;
}

TextElement::TextElement(string textToDisplay, Font fontChoice, int size, Color textColor, Vector2f position, bool isBold, bool isUnderline) {
    text = textToDisplay;
    font = fontChoice;
    charSize = size;
    color = textColor;
    bold = isBold;
    underline = isUnderline;

    textObj = Text(text, font, charSize);
    textObj.setFillColor(color);

    pos = position;
    center();


    if (bold)
        textObj.setStyle(Text::Bold);

    if (underline)
        textObj.setStyle(Text::Underlined);
}

void TextElement::draw(RenderWindow& screen) {
    screen.draw(textObj);
}

void TextElement::center() {
    FloatRect textRect = textObj.getLocalBounds();
    textObj.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    textObj.setPosition(pos);
}


//=====================================================================//


TextInput::TextInput(const Font& fontChoice, int size, Color textColor, Vector2f position) :
           TextElement("|", fontChoice, size, textColor, position, true) {
}

string TextInput::getName() {
    return input;
}

void TextInput::addInput(char inputChar) {
    if (input.size() < 10 && isalpha(inputChar)) {
        input += inputChar;
        input[0] = toupper(input[0]);
        for(int x = 1; x < input.size(); x++) {
            input[x] = tolower(input[x]);
        }
        textObj.setString(input + "|");
        center();
    }
}

void TextInput::removeChar() {
    if (!input.empty()) {
        input = input.substr(0, input.size() - 1);
        textObj.setString(input + "|");
        center();
    }
}
