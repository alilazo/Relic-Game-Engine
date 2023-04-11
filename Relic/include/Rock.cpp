#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Rock : public sf::Sprite {
public:
    Rock(sf::Texture& texture) {
        setTexture(texture);
        setOrigin(getLocalBounds().width / 2.f, getLocalBounds().height / 2.f); // set origin to center of image
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 360);
        float angle = dis(gen);
        setRotation(angle);
    }
    Rock(sf::Texture& texture, float x, float y) {
        setTexture(texture);
        setOrigin(getLocalBounds().width / 2.f, getLocalBounds().height / 2.f); // set origin to center of image
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 360);
        float angle = dis(gen);
        setRotation(angle);
        setPosition(x, y);
    }
};
