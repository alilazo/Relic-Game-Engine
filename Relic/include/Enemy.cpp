/*
    Enemy class header file.
    This class defines the behavior and properties of enemy objects.
    It inherits from the sf::Sprite class and adds additional functionality.

    Public Functions:
    Enemy(sf::Texture&): Constructor that takes an sf::Texture object and sets it as the sprite's texture.
    Enemy(): Default constructor.
    setX(float): Sets the x coordinate of the enemy's position.
    setY(float): Sets the y coordinate of the enemy's position.
    setPosition(float, float): Sets both x and y coordinates of the enemy's position.
    getX(): Returns the x coordinate of the enemy's position.
    getY(): Returns the y coordinate of the enemy's position.
    getHealth(): Returns the health of the enemy.
    setHealth(int): Sets the health of the enemy.
    getDamage(): Returns the damage of the enemy.
    setDamage(int): Sets the damage of the enemy.
    setScore(int): Sets the score of the enemy.
    getScore(): Returns the score of the enemy.
    collidesWith(const sf::Sprite&): Checks if the enemy collides with another sprite.
    getIsDead(): Returns whether the enemy is dead.
    setIsDead(bool): Sets whether the enemy is dead.
    handleCollision(Projectile&, Player&): Handles collisions with a projectile and player object.

    Private Variables:
    x: The x coordinate of the enemy's position.
    y: The y coordinate of the enemy's position.
    health: The health of the enemy.
    damage: The damage of the enemy.
    isDead: Whether the enemy is dead.
    score: The score of the enemy.
    remainingEnemies: The number of remaining enemies in the game.
*/

#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Projectile.cpp>
#include <Player.cpp>

class Enemy : public sf::Sprite{
public:
    Enemy(sf::Texture&);
    Enemy() {};
    static int remainingEnemies;
    void setX(float);
    void setY(float);
    void setPosition(float x, float y);
    float getX() {return x; }
    float getY() {return y; }
    int getHealth() {return health; }
    void setHealth(int newHealth) {health = newHealth; }
    int getDamage() { return damage; }
    void setDamage(int dmg) { damage = dmg; }
    void setScore(int newScore) { score = newScore; }
    int getScore() const { return score; }
    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }
    bool getIsDead() { return isDead; }
    void setIsDead(bool dead) { isDead = dead; }

    void handleCollision(Projectile& projectile, Player& player) {
        if (collidesWith(projectile.getSprite())) {
            health -= projectile.getDamage();
            if (health <= 0) {
                std::cout << "(Enemy.cpp) Enemy died " << std::endl;
                std::cout << "(Enemy.cpp) Enemies remaining:  " << remainingEnemies << std::endl;
                setDamage(0);
                player.setScore(player.getScore() + getScore());
                remainingEnemies--;
                //lastEnemyPos = getPosition();
                if(remainingEnemies == 0){
                    std::cout << "(Enemy.cpp) Last enemy killed, dropping key" << std::endl;
                }
            }
        }
    }
private:
    float x;
    float y;
    int health;
    int damage;
    bool isDead = health <= 0;
    int score;
};

Enemy::Enemy(sf::Texture &enemyTexture){
    this->setTexture(enemyTexture);
}

void Enemy::setPosition(float xPos, float yPos){
    sf::Sprite::setPosition(xPos, yPos);
    x = xPos;
    y = yPos;
}

void Enemy::setX(float xPos){
    x = xPos;
}

void Enemy::setY(float yPos){
    y = yPos;
}

int Enemy::remainingEnemies = 0;
#endif
