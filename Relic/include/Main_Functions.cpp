#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ObjectData.cpp"
#include "Player.cpp"
#include "InputHandler.cpp"
#include "Health.cpp"
#include "Score.cpp"
#include "Rock.cpp"
#include "Enemy.cpp"

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
            if (currentObject.texture != "") {
                currentObject.type = currentSection;
                objects.push_back(currentObject);
                currentObject = ObjectData();
            }
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
                std::cout << "(Main_Functions.cpp) " << currentSection << "  Health: " << currentObject.health << std::endl;
            } else if (key == "Damage") {
                currentObject.damage = std::stoi(value);
                std::cout << "(Main_Functions.cpp) " << currentSection << "  Damage: " << currentObject.damage << std::endl;
            } else if (key == "Score"){
                currentObject.score = std::stoi(value);
                std::cout << "(Main_Functions.cpp) " << currentSection << "  Score: " << currentObject.score << std::endl;
            }else{
                std::cerr << "(Main_Functions.cpp) Invalid key: " << key << std::endl;
            }
        } else {
            std::cerr << "(Main_Functions.cpp) Failed to parse line: " << line << std::endl;
        }
    }

    if (!currentSection.empty() && !currentObject.texture.empty()) {
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
}bool KeyDropped;
#endif
