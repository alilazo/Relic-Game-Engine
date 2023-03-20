#define _USE_MATH_DEFINES


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

class InputHandler {
private:
    sf::Sprite *player;
public:
    InputHandler(sf::Sprite *p) { player = p;}
    void setMovementHandler(std::string setting, sf::Event event);
    void setPlayerPositionToMouse(sf::RenderWindow &window);
    sf::Sprite *getPlayer(){return player; };
};

//TODO: Mouse Origin is fixed at (0,0) needs to be fixed at player.
void InputHandler::setPlayerPositionToMouse(sf::RenderWindow &window){
    // Get the position of the mouse on the screen
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    // Calculate the angle between the position of the mouse and the position of the player
    sf::Vector2f playerPos = player->getPosition();

    float dx = mousePos.x;
    float dy = mousePos.y;
    float angle = atan2(dy, dx) * 180 / M_PI;

    // Rotate the player sprite to that angle
    player->setRotation(angle);
}

void InputHandler::setMovementHandler(std::string setting, sf::Event event){
    if(setting == "arrows"){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            player->setPosition(player->getPosition().x + 20, player->getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            player->setPosition(player->getPosition().x, player->getPosition().y + 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            player->setPosition(player->getPosition().x - 20, player->getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            player->setPosition(player->getPosition().x, player->getPosition().y - 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            std::cout << "Player Debug: X: " << player->getPosition().x << " Y: " << player->getPosition().y << std::endl;
        }
    } else if (setting == "keyboard"){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
        {
            player->setPosition(player->getPosition().x + 20, player->getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
        {
            player->setPosition(player->getPosition().x, player->getPosition().y + 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
        {
            player->setPosition(player->getPosition().x - 20, player->getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
        {
            player->setPosition(player->getPosition().x, player->getPosition().y - 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            std::cout << "Player Debug: X: " << player->getPosition().x << " Y: " << player->getPosition().y << std::endl;
        }
    }

    //setPlayerPositionToMouse(window);
}

/*


if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
{
    player->setFillColor(sf::Color::Red);
    player->setPosition(player->getPosition().x + 20, player->getPosition().y);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
{
    player->setFillColor(sf::Color::Red);
    player->setPosition(player->getPosition().x, player->getPosition().y + 20);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
{
    player->setFillColor(sf::Color::Red);
    player->setPosition(player->getPosition().x - 20, player->getPosition().y);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
{
    player->setFillColor(sf::Color::Red);
    player->setPosition(player->getPosition().x, player->getPosition().y - 20);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
{
    std::cout << "Player Debug: X: " << player->getPosition().x << " Y: " << player->getPosition().y << std::endl;
}



*/
