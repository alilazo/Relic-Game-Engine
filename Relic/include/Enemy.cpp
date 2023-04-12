#include <SFML/Graphics.hpp>
#include <iostream>
#include <Projectile.cpp>
#include <Player.cpp>

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
    void setScore(int newScore) { score = newScore; }
    int getScore() const { return score; }
    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    void handleCollision(Projectile& projectile, Player& player) {
        if (collidesWith(projectile.getSprite())) {
            health -= projectile.getDamage();
            if (health <= 0) {
                std::cout << "(Enemy.cpp) Enemy died" << std::endl;
                setDamage(0);
                player.setScore(player.getScore() + getScore());
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
    //this->damage = 25;
}

void Enemy::setPosition(float xPos, float yPos){
    sf::Sprite::setPosition(xPos, yPos);
    x = xPos;
    y = yPos;
    //std::cout << "Position for enemy set at X: " << getX() << " Y: " << getY() << "  Health: " << getHealth() << "  Dmg: " << getDamage() << " ScaleX: " << getScale().x << " ScaleY: " << getScale().y << std::endl;
}

void Enemy::setX(float xPos){
    x = xPos;
}

void Enemy::setY(float yPos){
    y = yPos;
}
