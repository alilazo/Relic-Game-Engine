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
    if(!bgTexture.loadFromFile("Resources/bg.jpg")){ return EXIT_FAILURE; }

    //Create the player Texture
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("Resources/player.png")){ return EXIT_FAILURE; }

    //Create a sprite to hold the background texture
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(2.0f, 2.0f);

    //Create a player sprite
    //TODO: Create a "Hitbox" for the player also initilize size of the players dimensions.
    sf::Sprite player(playerTexture);
    player.setScale(0.3f, 0.3f);
    player.setPosition(120.f, 120.f);

    //Get the bounds from background
    sf::FloatRect bgBounds = bgSprite.getLocalBounds();
    std::cout << "Background Bounds: Top: " << bgBounds.top << " Width: " << bgBounds.width << " Height: " << bgBounds.height << " Left: " << bgBounds.left << std::endl;

    //Create the Enemy
    Enemy newEnemy(20.f);
    newEnemy.setPosition(120.f, 120.f);


    //Create a view that matches the size of the window
    sf::View view(sf::FloatRect(0, 0, 900, 500));
    initView(view, view.getViewport(), bgBounds, player.getPosition(), 20.f);

    //Init the InputHandler
    InputHandler gameInput(&player);
    //gameInput.setPlayer(player);

    std::cout << "Finished init." << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            gameInput.setMovementHandler("keyboard", event);
        }

        gameInput.setPlayerPositionToMouse(window);

        //Get current pos of circle
        sf::Vector2f circlePos = player.getPosition();

        //Make the viewport stay in the bounds of the Background
        //Make function that has offsets to integrate it to the camera Class.
        if (circlePos.x < bgBounds.left + 230) {
            circlePos.x = bgBounds.left + 230;
        }
        else if (circlePos.x > bgBounds.width + 730) {
            circlePos.x = bgBounds.left + bgBounds.width + 730;
        }
        if (circlePos.y < bgBounds.top + 230) {
            circlePos.y = bgBounds.top + 230;
        }
        else if (circlePos.y > bgBounds.height + 730) {
            circlePos.y = bgBounds.top + bgBounds.height + 730;
        }

        //TODO: Restrict the view to the background bounds.
        sf::FloatRect visibleArea(sf::Vector2f(view.getSize().x, view.getSize().y), view.getSize());
        initView(view, visibleArea, bgBounds, circlePos, 20.f);

        //Update the view to the center on the circle with offset of radius
        view.setCenter(circlePos.x + 20.f, circlePos.y + 20.f);


        window.setView(view);

        //Draw the background sprite
        window.clear();
        window.draw(bgSprite);
        window.draw(newEnemy.drawEnemy());
        window.draw(player);
        window.display();
    }

    return 0;
}
