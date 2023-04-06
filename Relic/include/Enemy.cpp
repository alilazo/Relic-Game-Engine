#include <SFML/Graphics.hpp>
#include <iostream>

//Implemented Inheritance of Sprite
class Enemy : public sf::Sprite{
public:
    Enemy(sf::Texture&);
    void setX(float);
    void setY(float);
    void setPosition(float x, float y);
    float getX() {return x; }
    float getY() {return y; }
private:
    float x;
    float y;
};

Enemy::Enemy(sf::Texture &enemyTexture){
    this->setTexture(enemyTexture);
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
