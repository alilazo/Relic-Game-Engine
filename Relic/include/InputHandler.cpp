#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <Projectile.cpp>

class InputHandler {
private:
    sf::Sprite *player;
    sf::Texture projectileTexture;
    std::vector<Projectile> projectiles;
    bool rightKeyPressed;
    bool downKeyPressed;
    bool leftKeyPressed;
    bool upKeyPressed;
    sf::Clock shootClock;
public:
    InputHandler(sf::Sprite *p) { player = p; rightKeyPressed = false; downKeyPressed = false; leftKeyPressed = false; upKeyPressed = false; }
    void setMovementHandler(std::string setting, sf::Event event, float deltaTime);
    void setPlayerPositionToMouse(sf::RenderWindow &window);
    sf::Sprite *getPlayer(){return player; };
    void setProjectileTexture(sf::Texture projectileText){ projectileTexture = projectileText; }
    void shoot();
    std::vector<Projectile>& getProjectiles() {
        return projectiles;
    }
};

void InputHandler::setPlayerPositionToMouse(sf::RenderWindow &window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f playerPos = player->getPosition();

    float dx = mousePos.x - playerPos.x;
    float dy = mousePos.y - playerPos.y;
    float angle = atan2(dy, dx) * 180 / M_PI;

    player->setRotation(angle);

    //std::cout << "Origin X:" << player->getOrigin().x << ",    Y:" << player->getOrigin().y << ".   Dx " << dx << "    Dy " << dy << "      Player Width: " << player->getLocalBounds().width << "   Height: " << player->getLocalBounds().height << std::endl;
}

void InputHandler::setMovementHandler(std::string setting, sf::Event event, float deltaTime){
    float movementSpeed = 300.0f;
    movementSpeed *= deltaTime;

    if (setting == "arrows") {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            rightKeyPressed = true;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
        {
            rightKeyPressed = false;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            downKeyPressed = true;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
        {
            downKeyPressed = false;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            leftKeyPressed = true;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
        {
            leftKeyPressed = false;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            upKeyPressed = true;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
        {
            upKeyPressed = false;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            std::cout << "Player Debug: X: " << player->getPosition().x << " Y: " << player->getPosition().y << std::endl;
        }
    } else if (setting == "keyboard"){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rightKeyPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rightKeyPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            downKeyPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            downKeyPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            leftKeyPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            leftKeyPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            upKeyPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            upKeyPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            std::cout << "Player Debug: X: " << player->getPosition().x << " Y: " << player->getPosition().y << std::endl;
        }
    }
    if (rightKeyPressed) {
        player->move(movementSpeed, 0);
    }
    if (downKeyPressed) {
        player->move(0, movementSpeed);
    }
    if (leftKeyPressed) {
        player->move(-movementSpeed, 0);
    }
    if (upKeyPressed) {
        player->move(0, -movementSpeed);
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        shoot();
    }
    //setPlayerPositionToMouse(window);
}

void InputHandler::shoot(){
    if (shootClock.getElapsedTime().asSeconds() < 0.3) { // Change 0.5 to the desired delay in seconds
        return;
    }
    shootClock.restart();
    sf::Vector2f playerPos = sf::Vector2f(player->getPosition().x, player->getPosition().y);
    float playerAngle = player->getRotation();
    Projectile projectile(projectileTexture, 600.f, playerPos, playerAngle, 25);
    projectiles.push_back(projectile);
    std::cout << "Pew";
}
#endif
