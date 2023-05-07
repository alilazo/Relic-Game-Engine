/*

This code defines a Projectile class that represents a projectile in a game.
It has a sprite, a velocity vector, and a damage value.
It has a constructor that takes in a texture, speed, position, angle, and damage value and sets up the sprite and velocity vector accordingly.
It has an update function that updates the position of the projectile based on its velocity and the time elapsed since the last update.
It also has getters and setters for the damage and hasHitEnemy flags.
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H
#define _USE_MATH_DEFINES

#include <iostream>
#include<SFML/Graphics.hpp>
#include <cmath>

class Projectile {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    int damage;
    bool hasHitEnemy;
public:
    Projectile(sf::Texture& texture, float speed, sf::Vector2f position, float angle, int damageValue) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setRotation(angle);
        sprite.setScale(0.1f, 0.1f);

        float vx = speed * std::cos(angle * M_PI / 180);
        float vy = speed * std::sin(angle * M_PI / 180);
        velocity = sf::Vector2f(vx, vy);

        damage = damageValue;
        hasHitEnemy = false;
    }

    void update(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

   int getDamage() const {
        return damage;
    }
    bool getHasHitEnemy() const {
        return hasHitEnemy;
    }
    void setDamage(int bulletDamage) {
        damage = bulletDamage;
    }

    void setHasHitEnemy(bool flag) {
        hasHitEnemy = flag;
    }
};
#endif // PROJECTILE_H
