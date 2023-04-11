#include <SFML/Graphics.hpp>
#include <iostream>
#include <Projectile.cpp>

//Implemented Inheritance of Sprite
class Enemy : public sf::Sprite{
public:
    Enemy(sf::Texture&);
    void setX(float);
    void setY(float);
    void setPosition(float x, float y);
    float getX() {return x; }
    float getY() {return y; }
    int getHealth() {return health; }
    void setHealth(int newHealth) {health = newHealth; }
    int getDamage() { return damage; }
    void setDamage(int dmg) { damage = dmg; }
    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    void handleCollision(Projectile& projectile) {
        if (collidesWith(projectile.getSprite())) {
            health -= projectile.getDamage();
            if (health <= 0) {
                std::cout << "Enemy died" << std::endl;
                setDamage(0);
            }
        }
    }
private:
    float x;
    float y;
    int health;
    int damage;
    bool isDead = health <= 0;
};

Enemy::Enemy(sf::Texture &enemyTexture){
    this->setTexture(enemyTexture);
    this->damage = 25;
    std::cout << "New enemy created! ";
}

void Enemy::setPosition(float xPos, float yPos){
    sf::Sprite::setPosition(xPos, yPos);
    x = xPos;
    y = yPos;
    std::cout << "Position for enemy set at X: " << getX() << " Y: " << getY() << std::endl;
}

void Enemy::setX(float xPos){
    x = xPos;
}

void Enemy::setY(float yPos){
    y = yPos;
}
