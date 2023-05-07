/*
This is the header file for the Health class, which inherits from sf::Text.
The Health class is responsible for displaying and managing the player's health in the game.

The class contains private variables such as the player's health, font, and font size.
The constructor initializes the font and the player's initial health, and creates and positions the text object.
The updateText() function updates the text object with the current player's health value.

The class also contains public functions for decreasing, increasing, and setting the player's health,
changing the font and font size, and setting the font file.
*/

#ifndef HEALTH_H
#define HEALTH_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Health : public sf::Text {
private:
    int health;
    sf::Font font;
    int fontSize;
public:
    Health(int initialHealth) {
        if (!font.loadFromFile("Resources/Fonts/Zomboid.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }

        setFont(font);
        setCharacterSize(38);
        setFillColor(sf::Color::White);
        setPosition(10, 10);
        health = initialHealth;
        updateText();
    }
    void updateText() {
        std::stringstream ss;
        ss << "Health: " << health;
        setString(ss.str());
    }
    void setHealth(int newHealth) {
        health = newHealth;
        updateText();
    }
    int getHealth(){
        return health;
    }
    void decreaseHealth(int amount) {
        health -= amount;
        updateText();
    }
    void increaseHealth(int amount) {
        health += amount;
        updateText();
    }
    void setFont(const sf::Font& newFont) {
        font = newFont;
        sf::Text::setFont(font);
    }

    const sf::Font& getFont() const {
        return font;
    }

    void setFontSize(int size) {
        fontSize = size;
        setCharacterSize(size);
    }
    int getFontSize() const {
        return fontSize;
    }
    void setFontFile(std::string filename) {
        if (!font.loadFromFile(filename)) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }
        setFont(font);
    }
};
#endif // HEALTH_H
