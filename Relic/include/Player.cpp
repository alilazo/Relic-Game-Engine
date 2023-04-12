#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
private:
    int health;
    int score = 0;
public:
    bool isAlive = health > 0;
    Player(sf::Texture& texture) {
        setTexture(texture);
        setOrigin(getLocalBounds().width / 2.f, getLocalBounds().height / 2.f);
    }
    int getScore() const { return score; }
    void setScore(int playerScore) { score = playerScore; }
    int getHealth() const {
        return health;
    }
    void setHealth(int newHealth) {
        health = newHealth;
    }

    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    void handleCollision(int damage) {
        health -= damage;
        if (health <= 0) {
            std::cout << "Player died" << std::endl;
            // Handle player death
        }
    }
};
#endif // PLAYER_H
