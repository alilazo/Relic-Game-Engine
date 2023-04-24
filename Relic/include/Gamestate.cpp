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

bool loadNextMap(std::vector<ObjectData>& objectList, std::vector<sf::Texture>& enemyTextures, std::vector<sf::Texture>& rockTextures, std::vector<Rock>& rockList, std::vector<Enemy*>& enemies, sf::Texture projectileTexture, sf::Sprite& bgSprite, sf::Texture& bgTexture, Player& player, InputHandler& gameInput, Health& playerHealth, Score& score, sf::View& view, sf::FloatRect& bgBounds, sf::RenderWindow& window, const std::string& mapFileName)
{
    // Load the new map data
    objectList = readMapData(mapFileName);

    if (objectList.empty()) {
        return false;
    }

    // Clear out the old rocks and enemies and reseting remainingEnemies
    rockList.clear();
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    enemyTextures.clear();
    rockTextures.clear();
    Enemy::remainingEnemies = 0;

    // Load the new background texture and sprite
    if (!bgTexture.loadFromFile(objectList[0].texture)) { return false; }
    bgSprite.setTexture(bgTexture);

    //Assign PreLoaded Textures for Enemy
    for (const auto& obj : objectList) {
        if (obj.type == "Enemy") {
            sf::Texture enemyTexture;
            enemyTexture.loadFromFile(obj.getTexture());
            enemyTextures.push_back(enemyTexture);
            std::cout << "(Gamestate.cpp) Assigning Enemy Texture: " << obj.getTexture() << std::endl;
        }
    }

    //Assign PreLoaded Textures for Rock
    for (const auto& obj : objectList) {
        if (obj.type.find("Rock") != std::string::npos) {
            sf::Texture rockTexture;
            rockTexture.loadFromFile(obj.getTexture());
            rockTextures.push_back(rockTexture);
            std::cout << "(Gamestate.cpp) Assigning Rock Texture: " << obj.getTexture() << std::endl;
        }
    }

    // Create new rocks and enemies based on the map data
    int enemyTextureIteration = 0;
    int rockTextureIteration = 0;
    for (const auto& obj : objectList) {
        if (obj.type.find("Rock") != std::string::npos) {
            Rock rock(rockTextures[rockTextureIteration]);
            rock.setPosition(obj.posX, obj.posY);
            rock.setScale(obj.scaleX, obj.scaleY);
            rockList.push_back(rock);
            rockTextureIteration++;
        }
        else if (obj.type == "Enemy") {
            Enemy* newEnemy = new Enemy();
            newEnemy->setPosition(obj.posX, obj.posY);
            newEnemy->setScale(obj.scaleX, obj.scaleY);
            newEnemy->setHealth(obj.health);
            newEnemy->setDamage(obj.damage);
            newEnemy->setScore(obj.score);
            newEnemy->setTexture(enemyTextures[enemyTextureIteration]);
            Enemy::remainingEnemies++;
            enemies.push_back(newEnemy);
            enemyTextureIteration++;
        }
    }
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
    std::cout << "(Gamestate.cpp) State: " << getState() << std::endl;

    return true;
}

void displayEndScreen(bool& endGame, bool& restartButtonIsPressed, std::vector<ObjectData>& objectList, std::vector<sf::Texture>& enemyTextures, std::vector<sf::Texture>& rockTextures, std::vector<Rock>& rockList, std::vector<Enemy*>& enemies, sf::Texture projectileTexture, sf::Sprite& bgSprite, sf::Texture& bgTexture, Player& player, InputHandler& gameInput, Health& playerHealth, Score& score, sf::View& view, sf::FloatRect& bgBounds, sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/Zomboid.ttf")) {
        std::cerr << "Error loading font file." << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("END");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 200));

    std::ostringstream ss;
    ss << "Score: " << score.getScore();
    sf::Text scoreText(ss.str(), font, 30);
    scoreText.setPosition(window.getSize().x / 2 - scoreText.getLocalBounds().width / 2, window.getSize().y / 2 + 20);

    sf::Text restartText("Restart Game", font, 50);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(window.getSize().x / 2 - restartText.getLocalBounds().width / 2, window.getSize().y / 2 + 50);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (restartText.getGlobalBounds().contains(mousePosition)) {
                restartButtonIsPressed = true;
            }
        }

        //Restart button pressed
        if (restartButtonIsPressed) {
            restartButtonIsPressed = false;
            player.setHealth(100);
            playerHealth.setHealth(100);
            player.setScore(0);
            score.setScore(0);
            KeyDropped = false;
            player.setKey(false);
            std::cout << "(Gamestate.cpp) Restarting Game..." << std::endl;
            setState(1);
            endGame = false;
            loadNextMap(objectList, enemyTextures, rockTextures, rockList, enemies, projectileTexture, bgSprite, bgTexture, player, gameInput, playerHealth, score, view, bgBounds, window, "Maps/Room1.txt");
        }


        window.clear();
        window.draw(background);
        window.draw(text);
        window.draw(scoreText);
        window.draw(restartText);

    std::cout << "(Gamestate.cpp) END" << std::endl;
}

void setState(int gs){
    state = gs;
    std::cout << "(Gamestate.cpp) State: " << getState() << std::endl;
}


private:
    int state;
};
