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
