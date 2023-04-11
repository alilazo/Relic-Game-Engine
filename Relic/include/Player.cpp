#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
private:
    int health;
    //sf::Vector2f previousPlayerPosition;

public:
    Player(sf::Texture& texture) {
        setTexture(texture);
        setOrigin(getLocalBounds().width / 2.f, getLocalBounds().height / 2.f);
        //previousPlayerPosition = getPosition();

    }
    int getHealth() const {
        return health;
    }
    void setHealth(int newHealth) {
        health = newHealth;
    }

    /*
    void handleCollision(Rock& rock) {
        sf::FloatRect playerBounds = getGlobalBounds();
        sf::FloatRect rockBounds = rock.getGlobalBounds();

        // Determine which side of the rock the player collided with
        float overlapLeft = playerBounds.left + playerBounds.width - rockBounds.left;
        float overlapRight = rockBounds.left + rockBounds.width - playerBounds.left;
        float overlapTop = playerBounds.top + playerBounds.height - rockBounds.top;
        float overlapBottom = rockBounds.top + rockBounds.height - playerBounds.top;

        // Get the previous position of the player
        sf::Vector2f newPosition = previousPlayerPosition;

        // Move the player away from the rock based on the direction of the collision
        if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
            newPosition.x = getPosition().x + 50;
        } else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
            newPosition.x = getPosition().x - 50;
        } else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {
            newPosition.y = getPosition().y + 50;
        } else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop) {
            newPosition.y = getPosition().y - 50;
        }

        // Set the new position of the player
        setPosition(newPosition);
    }

    sf::Vector2f getPreviousPosition() const {
        return previousPlayerPosition;
    } */

    bool collidesWith(const sf::Sprite& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }
};
