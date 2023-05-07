/*

This is a header file for the Player class, which inherits from sf::Sprite.
The Player class represents the player's character in the game.
It has private member variables for health, score, and whether the player possesses a key.
The class has public functions for setting and getting the player's health, score, and key possession.
There is also a function for handling collisions between the player and other sprites, which reduces the player's health based on the damage received.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
private:
    int health;
    int score = 0;
    bool possesKey = false;
public:
    bool hasKey(){ return possesKey; }
    void setKey(bool doesPlayerHaveKey) { possesKey = doesPlayerHaveKey;}
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
