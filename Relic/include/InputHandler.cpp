#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class InputHandler {
public:
    void setHandler(std::string setting, sf::CircleShape& shape, sf::Event event);
};

void InputHandler::setHandler(std::string setting, sf::CircleShape &player, sf::Event event){
    if(setting == "arrows"){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x + 20, player.getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x, player.getPosition().y + 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x - 20, player.getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x, player.getPosition().y - 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            std::cout << "Player Debug: X: " << player.getPosition().x << " Y: " << player.getPosition().y << std::endl;
        }
    } else if (setting == "keyboard"){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x + 20, player.getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x, player.getPosition().y + 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x - 20, player.getPosition().y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
        {
            player.setFillColor(sf::Color::Red);
            player.setPosition(player.getPosition().x, player.getPosition().y - 20);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            std::cout << "Player Debug: X: " << player.getPosition().x << " Y: " << player.getPosition().y << std::endl;
        }
    }
}

/*


if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
{
    player.setFillColor(sf::Color::Red);
    player.setPosition(player.getPosition().x + 20, player.getPosition().y);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
{
    player.setFillColor(sf::Color::Red);
    player.setPosition(player.getPosition().x, player.getPosition().y + 20);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
{
    player.setFillColor(sf::Color::Red);
    player.setPosition(player.getPosition().x - 20, player.getPosition().y);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
{
    player.setFillColor(sf::Color::Red);
    player.setPosition(player.getPosition().x, player.getPosition().y - 20);
}
else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
{
    std::cout << "Player Debug: X: " << player.getPosition().x << " Y: " << player.getPosition().y << std::endl;
}



*/
