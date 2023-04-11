#include <SFML/Graphics.hpp>
#include <Enemy.cpp>
#include <InputHandler.cpp>
#include <iostream>
#include <Rock.cpp>
#include <Health.cpp>
#include <Player.cpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <ObjectData.cpp>

//Map Reader implementation
std::string trim(const std::string& str) {
    auto first = std::find_if_not(str.begin(), str.end(), [](int c) { return std::isspace(c); });
    auto last = std::find_if_not(str.rbegin(), str.rend(), [](int c) { return std::isspace(c); }).base();
    return (first >= last) ? std::string() : std::string(first, last);
}

std::vector<ObjectData> readMapData(const std::string& filename) {
    std::vector<ObjectData> objects;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return objects;
    }

    std::string line;
    std::string currentSection = "";
    ObjectData currentObject;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
            continue;
        }

        std::string key, value;
        std::istringstream iss(line);
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            key = trim(key);
            value = trim(value);

            if (key == "Texture") {
                currentObject.texture = value;
            } else if (key == "Position") {
                std::string::size_type pos = value.find(' ');
                if (pos != std::string::npos) {
                    currentObject.posX = std::stof(value.substr(0, pos));
                    currentObject.posY = std::stof(value.substr(pos + 1));
                }
            } else if (key == "Scale") {
                std::string::size_type pos = value.find(' ');
                if (pos != std::string::npos) {
                    currentObject.scaleX = std::stof(value.substr(0, pos));
                    currentObject.scaleY = std::stof(value.substr(pos + 1));
                }
            } else if (key == "Health") {
                currentObject.health = std::stoi(value);
            } else if (key == "Damage") {
                currentObject.damage = std::stoi(value);
            } else {
                std::cerr << "Invalid key: " << key << std::endl;
            }
        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }

        if (currentObject.texture != "") {
            currentObject.type = currentSection;
            objects.push_back(currentObject);
            currentObject = ObjectData();
        }
    }

    if (currentObject.texture != "") {
        currentObject.type = currentSection;
        objects.push_back(currentObject);
    }

    file.close();
    return objects;
}

//Use call by reference instead of value
void initView(sf::View& view, sf::FloatRect visibleArea, sf::FloatRect backgroundBounds, sf::Vector2f playerPos, float playerRadius) {
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.0f));
    // Restrict the view to the visible area of the background sprite
    if (view.getCenter().x - view.getSize().x / 2 < backgroundBounds.left + playerRadius) {
        view.setCenter(backgroundBounds.left + view.getSize().x / 2 + playerRadius, view.getCenter().y);
    }
    if (view.getCenter().y - view.getSize().y / 2 < backgroundBounds.top + playerRadius) {
        view.setCenter(view.getCenter().x, backgroundBounds.top + view.getSize().y / 2 + playerRadius);
    }
    if (view.getCenter().x + view.getSize().x / 2 > backgroundBounds.left + backgroundBounds.width - playerRadius) {
        view.setCenter(backgroundBounds.left + backgroundBounds.width - view.getSize().x / 2 - playerRadius, view.getCenter().y);
    }
    if (view.getCenter().y + view.getSize().y / 2 > backgroundBounds.top + backgroundBounds.height - playerRadius) {
        view.setCenter(view.getCenter().x, backgroundBounds.top + backgroundBounds.height - view.getSize().y / 2 - playerRadius);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440, 720), "Powered by Relic");
    window.setFramerateLimit(60);

    std::vector<ObjectData> objectList = readMapData("Maps/Room1.txt");

    //Initialization
    sf::Clock playerCollisionClock;


    std::cout << "Objects: " << objectList.size() << std::endl;
    for(int i = 0; i < objectList.size(); i++){
        std::cout << objectList[i].type << "    -   " << objectList[i].texture << std::endl;
    }

    //Load the background texture
    sf::Texture bgTexture;
    if(!bgTexture.loadFromFile(objectList[0].texture)){ return EXIT_FAILURE; }

    //Create a sprite to hold the background texture
    sf::Sprite bgSprite(bgTexture);


    sf::Texture playerTexture;
    Player player(playerTexture);

    for (const auto& obj : objectList) {
        if (obj.type == "Player") {
            sf::Texture tempPlayerTexture;
            tempPlayerTexture.loadFromFile(obj.texture);

            // Create the player sprite
            Player tempPlayer(tempPlayerTexture);
            tempPlayer.setScale(obj.scaleX, obj.scaleY);
            tempPlayer.setPosition(obj.posX, obj.posY);

            player = tempPlayer;
            playerTexture = tempPlayerTexture;

            // ...
        }
    }
    // Create the player sprite
    //player.setScale(objectList[1].scaleX, objectList[1].scaleY);
    //player.setPosition(objectList[1].posX, objectList[1].posY);
    std::cout << objectList[1].scaleX << "   " << objectList[1].scaleY << "   " << objectList[1].posX << "  " << objectList[1].posY <<  std::endl;

    //Create a Rock.
    sf::Texture rockTexture;
    if(!rockTexture.loadFromFile("Resources/rock.png")){ return EXIT_FAILURE; }
    Rock rock(rockTexture);
    rock.setPosition(120.f, 120.f);
    rock.setScale(0.1f, 0.1f);

    //Get the bounds from background
    sf::FloatRect bgBounds = bgSprite.getLocalBounds();

    //Create the Enemy with Array
    std::vector<Enemy*> enemies;

    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("Resources/enemy.png")){ return EXIT_FAILURE; }
    Enemy* newEnemy = new Enemy(enemyTexture);
    newEnemy->setPosition(220, 120);
    newEnemy->setScale(0.3f, 0.3f);
    newEnemy->setHealth(100);
    enemies.push_back(newEnemy);

    Enemy* newEnemy2 = new Enemy(enemyTexture);
    newEnemy2->setPosition(276, 170);
    newEnemy2->setScale(0.3f, 0.3f);
    newEnemy2->setHealth(100);
    enemies.push_back(newEnemy2);

    //Create bullet texture
    sf::Texture projectileTexture;
    if(!projectileTexture.loadFromFile("Resources/Bullet.png")){ return EXIT_FAILURE; }

    sf::View view(sf::FloatRect(0, 0, 900, 500));
    initView(view, view.getViewport(), bgBounds, player.getPosition(), 20.f);

    InputHandler gameInput(&player);
    gameInput.setProjectileTexture(projectileTexture);

    Health playerHealth(100);
    playerHealth.setPosition(10.f, 0.f);
    player.setHealth(playerHealth.getHealth());

    // Create a fixed view for the top left corner of the screen
    sf::View fixedView(sf::FloatRect(0.f, 0.f, window.getSize().x/4.f, window.getSize().y/4.f));
    fixedView.setViewport(sf::FloatRect(0.f, 0.f, 0.4f, 0.4f));

    std::cout << "Finished init." << std::endl;

    //Fixed time step system
    sf::Clock clock;

    const float fixedTimeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;
        while(accumulator >= fixedTimeStep)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            gameInput.setMovementHandler("keyboard", event, fixedTimeStep);
            gameInput.setPlayerPositionToMouse(window);

            sf::Vector2f playerPos = player.getPosition();

            if (playerPos.x < bgBounds.left + 430) {
                playerPos.x = bgBounds.left + 430;
            } else if (playerPos.x > bgBounds.width - 470) {
                playerPos.x = bgBounds.left + bgBounds.width - 470;
            }

            if (playerPos.y < bgBounds.top + 230) {
                playerPos.y = bgBounds.top + 230;
            } else if (playerPos.y > bgBounds.height - 270) {
                playerPos.y = bgBounds.top + bgBounds.height - 270;
            }

            sf::FloatRect visibleArea(sf::Vector2f(view.getSize().x, view.getSize().y), view.getSize());
            initView(view, visibleArea, bgBounds, playerPos, 20.f);

            view.setCenter(playerPos.x + 20.f, playerPos.y + 20.f);

            accumulator -= fixedTimeStep;
        }

        window.setView(view);

        window.clear();

        window.draw(bgSprite);
        window.draw(rock);

        //This displays a unlimited amount of given enemies and also has projectile collision implemented here.
        for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ++itEnemy)
        {
            Enemy* currentEnemy = *itEnemy;
            if(currentEnemy && currentEnemy->getHealth() >= 0){
                window.draw(*currentEnemy);

                //Calculate distance between player and enemy
                sf::Vector2f playerPos = player.getPosition();
                sf::Vector2f enemyPos = currentEnemy->getPosition();
                float distance = std::sqrt(std::pow(playerPos.x - enemyPos.x, 2) + std::pow(playerPos.y - enemyPos.y, 2));

                //If player is within a certain radius, move towards the player
                if(distance <= 600) {
                    float angle = std::atan2(playerPos.y - enemyPos.y, playerPos.x - enemyPos.x);
                    currentEnemy->setRotation(angle * 180 / M_PI);
                    currentEnemy->move(std::cos(angle) * 50.0f * deltaTime, std::sin(angle) * 50.0f * deltaTime);
                }
            }

            //Check for player collision with enemy
            if (player.collidesWith(*currentEnemy) && player.isAlive) {
                if(player.getHealth() <= 0) {
                    player.isAlive = false;
                    player.setHealth(0);
                } else {
         if (playerCollisionClock.getElapsedTime().asSeconds() >= 0.5f) {
            int damage = currentEnemy->getDamage();
            player.setHealth(player.getHealth() - damage);
            std::cout << "Player health: " << player.getHealth() << std::endl;
            playerHealth.decreaseHealth(damage);
            playerCollisionClock.restart();
        }
                }
            }

            for (auto itProjectile = gameInput.getProjectiles().begin(); itProjectile != gameInput.getProjectiles().end(); )
            {
                itProjectile->update(deltaTime);
                itProjectile->setDamage(25);
                if (itProjectile->getSprite().getGlobalBounds().intersects(currentEnemy->getGlobalBounds()) && currentEnemy->getHealth() >= 0 || itProjectile->getSprite().getGlobalBounds().intersects(rock.getGlobalBounds()))
                {
                    if(currentEnemy->getHealth() >= 0 && currentEnemy->collidesWith(itProjectile->getSprite())) {
                            std::cout << "\nHit, Enemy health is: " <<  currentEnemy->getHealth() << std::endl;
                            currentEnemy->handleCollision(*itProjectile);
                    }
                    itProjectile = gameInput.getProjectiles().erase(itProjectile);
                    continue;
                }
                window.draw(itProjectile->getSprite());
                ++itProjectile;
            }
        }

        window.setView(fixedView);
        window.draw(playerHealth);
        window.setView(view);

        window.draw(player);
        window.display();
    }

    return 0;
}
