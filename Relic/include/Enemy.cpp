#include <SFML/Graphics.hpp>
#include <iostream>
#include <Projectile.cpp>

//Implemented Inheritance of Sprite
class Enemy : public sf::Sprite{
public:
    Enemy(sf::Texture&);
    void setX(float);
    void setY(float);
    void updatePosition(sf::Vector2f, float, float, float);
    void setPosition(float x, float y);
    float getX() {return x; }
    float getY() {return y; }
    int getHealth() {return health; }
    void setHealth(int newHealth) {health = newHealth; }
    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    void handleCollision(Projectile& projectile) {
        if (collidesWith(projectile.getSprite())) {
            health -= projectile.getDamage();
            if (health <= 0) {
                std::cout << "Enemy died" << std::endl;
            }
        }
    }
private:
    float x;
    float y;
    int health;
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

void Enemy::updatePosition(sf::Vector2f playerPosition, float deltaTime, float moveSpeed, float radius) {
    // Calculate distance between enemy and player
    float dx = playerPosition.x - x;
    float dy = playerPosition.y - y;
    float distance = sqrt(dx * dx + dy * dy);

    // Check if player is within radius
    if (distance < radius) {
        // Calculate angle between enemy and player
        float angle = atan2(dy, dx) * 180 / M_PI;

        // Move enemy in the direction of the player
        x += moveSpeed * deltaTime * cos(angle * M_PI / 180);
        y += moveSpeed * deltaTime * sin(angle * M_PI / 180);

        // Update enemy sprite position
        setPosition(x, y);
    }
}
