#include <SFML/Graphics.hpp>

void initView(sf::View& view, sf::FloatRect visibleArea, sf::FloatRect backgroundBounds, sf::Vector2f shapePos, float shapeRadius) {
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    // Restrict the view to the visible area of the background sprite
    if (view.getCenter().x - view.getSize().x / 2 < backgroundBounds.left + shapeRadius) {
        view.setCenter(backgroundBounds.left + view.getSize().x / 2 + shapeRadius, view.getCenter().y);
    }
    if (view.getCenter().y - view.getSize().y / 2 < backgroundBounds.top + shapeRadius) {
        view.setCenter(view.getCenter().x, backgroundBounds.top + view.getSize().y / 2 + shapeRadius);
    }
    if (view.getCenter().x + view.getSize().x / 2 > backgroundBounds.left + backgroundBounds.width - shapeRadius) {
        view.setCenter(backgroundBounds.left + backgroundBounds.width - view.getSize().x / 2 - shapeRadius, view.getCenter().y);
    }
    if (view.getCenter().y + view.getSize().y / 2 > backgroundBounds.top + backgroundBounds.height - shapeRadius) {
        view.setCenter(view.getCenter().x, backgroundBounds.top + backgroundBounds.height - view.getSize().y / 2 - shapeRadius);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Powered by Relic");
    window.setFramerateLimit(60);

    //Load the background texture
    sf::Texture bgTexture;
    if(!bgTexture.loadFromFile("Resources/bg.jpg")){ return EXIT_FAILURE; }

    //Create a sprite to hold the background texture
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(2.0f, 2.0f);

    //Get the bounds
    sf::FloatRect bgBounds = bgSprite.getLocalBounds();

    sf::CircleShape shape(50.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(20.0f, 100.0f);

    //Create a view that matches the size of the window
    sf::View view(sf::FloatRect(0, 0, bgBounds.width, bgBounds.height));
    view.setCenter(bgBounds.width/2, bgBounds.height/2);

    initView(view, view.getViewport(), bgBounds, shape.getPosition(), shape.getRadius());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(shape.getPosition().x + 20, shape.getPosition().y);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(shape.getPosition().x, shape.getPosition().y + 20);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(shape.getPosition().x - 20, shape.getPosition().y);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(shape.getPosition().x, shape.getPosition().y - 20);
            }
        }
        //Get current pos of circle
        sf::Vector2f circlePos = shape.getPosition();
        float circleRadius = shape.getRadius();

        //Check if the circle i outside the background bounds (COLLISION)
        if (circlePos.x < bgBounds.left + shape.getRadius()) {
            circlePos.x = bgBounds.left + shape.getRadius();
        }
        else if (circlePos.x > bgBounds.left + bgBounds.width - shape.getRadius()) {
            circlePos.x = bgBounds.left + bgBounds.width - shape.getRadius();
        }
        if (circlePos.y < bgBounds.top + shape.getRadius()) {
            circlePos.y = bgBounds.top + shape.getRadius();
        }
        else if (circlePos.y > bgBounds.top + bgBounds.height - shape.getRadius()) {
            circlePos.y = bgBounds.top + bgBounds.height - shape.getRadius();
        }

        //TODO: Restrict the view to the background bounds.
        sf::FloatRect visibleArea(circlePos - sf::Vector2f(view.getSize().x / 2.f, view.getSize().y / 2.f), view.getSize());
        initView(view, visibleArea, bgBounds, circlePos, circleRadius);

        //Update the view to the center on the circle with offset of radius
        view.setCenter(circlePos);


        window.setView(view);

        //Draw the background sprite
        window.clear();
        window.draw(bgSprite);

        window.draw(shape);
        window.display();
    }

    return 0;
}
