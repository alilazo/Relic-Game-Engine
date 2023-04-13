#include<Main_Functions.cpp>

class GameState {
public:
    GameState() : state(0) {}

    int getState() const {
        return state;
    }

    void nextState() {
        state++;
    }

void loadNextMap(std::vector<ObjectData>& objectList, std::vector<Rock>& rockList, std::vector<Enemy*>& enemies, sf::Texture projectileTexture, sf::Sprite& bgSprite, sf::Sprite& Door, sf::Sprite& Key, sf::Texture& bgTexture, sf::Texture& doorTexture, sf::Texture& keyTexture, sf::Texture& rockTexture, sf::Texture& enemyTexture, Player& player, InputHandler& gameInput, Health& playerHealth, Score& score, sf::View& view, sf::FloatRect& bgBounds, sf::RenderWindow& window, const std::string& mapFileName)
{
    // Load the new map data
    objectList = readMapData(mapFileName);

    // Clear out the old rocks and enemies and reseting remainingEnemies
    rockList.clear();
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    Enemy::remainingEnemies = 0;

    // Load the new background texture and sprite
    if (!bgTexture.loadFromFile(objectList[0].texture)) { return; }
    bgSprite.setTexture(bgTexture);

    // Create new rocks and enemies based on the map data
    for (const auto& obj : objectList) {
        if (obj.type.find("Rock") != std::string::npos) {
            Rock rock(rockTexture);
            rock.setPosition(obj.posX, obj.posY);
            rock.setScale(obj.scaleX, obj.scaleY);
            rockList.push_back(rock);
        }
        else if (obj.type == "Enemy") {
            Enemy* newEnemy = new Enemy(enemyTexture);
            newEnemy->setPosition(obj.posX, obj.posY);
            newEnemy->setScale(obj.scaleX, obj.scaleY);
            newEnemy->setHealth(obj.health);
            newEnemy->setDamage(obj.damage);
            newEnemy->setScore(obj.score);
            Enemy::remainingEnemies++;
            enemies.push_back(newEnemy);
        }
    }

    // Load the new door and key textures and sprites
    doorTexture.loadFromFile("Resources/Door.png");
    Door.setTexture(doorTexture);
    keyTexture.loadFromFile("Resources/Key.png");
    Key.setTexture(keyTexture);

    // Set up the new player position, health, score, and input handler
    player.setPosition(objectList[1].posX, objectList[1].posY);
    player.setScale(objectList[1].scaleX, objectList[1].scaleY);
    player.setHealth(playerHealth.getHealth());
    player.setScore(score.getScore());
    gameInput.setProjectileTexture(projectileTexture);

    // Set up the new background bounds and camera view
    bgBounds = bgSprite.getLocalBounds();
    sf::Vector2f playerPos = player.getPosition();
    sf::FloatRect visibleArea(sf::Vector2f(view.getSize().x, view.getSize().y), view.getSize());
    initView(view, visibleArea, bgBounds, playerPos, 20.f);
    view.setCenter(playerPos.x + 20.f, playerPos.y + 20.f);

    // Reset the remaining enemies and key dropped flags
    KeyDropped = false;
    player.setKey(false);
}

private:
    int state;
};
