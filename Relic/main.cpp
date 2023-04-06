#include <SFML/Graphics.hpp>
#include <Enemy.cpp>
#include <InputHandler.cpp>
#include <iostream>

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

    //Load the background texture
    sf::Texture bgTexture;
    if(!bgTexture.loadFromFile("Resources/Background.jpg")){ return EXIT_FAILURE; }

    //Create the player Texture
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("Resources/player.png")){ return EXIT_FAILURE; }

    //Create a sprite to hold the background texture
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(1.0f, 1.0f);

    //Create a player sprite
    //TODO: Create a "Hitbox" for the player also initilize size of the players dimensions.
    sf::Sprite player(playerTexture);
    player.setScale(0.3f, 0.3f);
    player.setPosition(120.f, 120.f);

    //Get the bounds from background
    sf::FloatRect bgBounds = bgSprite.getLocalBounds();

    //Create the Enemy
    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("Resources/enemy.png")){ return EXIT_FAILURE; }
    Enemy newEnemy(enemyTexture);
    newEnemy.setPosition(220, 120);
    newEnemy.setScale(0.3f, 0.3f);

    //Create bullet texture
    sf::Texture projectileTexture;
    if(!projectileTexture.loadFromFile("Resources/Bullet.png")){ return EXIT_FAILURE; }

    sf::View view(sf::FloatRect(0, 0, 900, 500));
    initView(view, view.getViewport(), bgBounds, player.getPosition(), 20.f);

    InputHandler gameInput(&player);
    gameInput.setProjectileTexture(projectileTexture);

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

        //Draw the background sprite
        window.clear();
        window.draw(bgSprite);
        window.draw(newEnemy);

        for (auto& projectile : gameInput.getProjectiles()) {
            projectile.update(deltaTime);
            window.draw(projectile.getSprite());
        }

        window.draw(player);
        window.display();
    }

    return 0;
}
