class Projectile {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
public:
    Projectile(sf::Texture& texture, float speed, sf::Vector2f position, float angle) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setRotation(angle);
        sprite.setScale(0.1f, 0.1f);

        float vx = speed * std::cos(angle * M_PI / 180);
        float vy = speed * std::sin(angle * M_PI / 180);
        velocity = sf::Vector2f(vx, vy);
    }

    void update(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }
};
