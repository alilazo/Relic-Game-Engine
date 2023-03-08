#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy : sf::CircleShape{
public:
    Enemy(float, float, float);
    Enemy(float);
    void setX(float);
    void setY(float);
    void setPosition(float x, float y);
    float getX() {return x; }
    float getY() {return y; }
    void reColor();
    sf::CircleShape drawEnemy(){ return player;}
private:
    float x;
    float y;
    float width;
    float height;
    sf::CircleShape player;
};

Enemy::Enemy(float xPos, float yPos, float radius){
    sf::CircleShape newEnemy(radius);
    newEnemy.setFillColor(sf::Color::Blue);
    newEnemy.setPosition(xPos, yPos);
    x = xPos;
    y = yPos;
    player = newEnemy;
    std::cout << "New enemy created! At x: " << getX() << " y: " << getY() << std::endl;

}

Enemy::Enemy(float radius){
    std::cout << "New enemy created! ";
    sf::CircleShape newEnemy(radius);
    newEnemy.setFillColor(sf::Color::Blue);
    player = newEnemy;
}

void Enemy::setPosition(float xPos, float yPos){
    player.setPosition(xPos, yPos);
    x = xPos;
    y = yPos;
    std::cout << "Position for enemy set at X: " << getX() << " Y: " << getY() << std::endl;
}

void Enemy::reColor(){
    player.setFillColor(sf::Color::Green);
}

void Enemy::setX(float xPos){
    x = xPos;
}

void Enemy::setY(float yPos){
    y = yPos;
}
