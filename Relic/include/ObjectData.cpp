/*

This header file defines a class ObjectData with data members and getter functions.
The class is used to store data about objects in the game, such as their type, texture, position, scale, health, damage, and score.
The class also has two constructors - one with parameters and one without. The class and its members are wrapped in an include guard.
*/

#ifndef OBJECTDATA_H
#define OBJECTDATA_H

class ObjectData {
public:
    std::string type;
    std::string texture;
    float posX;
    float posY;
    float scaleX;
    float scaleY;
    int health = 0;
    int damage = 0;
    int score = 0;

    ObjectData() {}

    ObjectData(std::string type, std::string texture, float posX, float posY, float scaleX, float scaleY, int health = 0, int damage = 0, int score = 0)
        : type(type), texture(texture), posX(posX), posY(posY), scaleX(scaleX), scaleY(scaleY), health(health), damage(damage), score(score){}

    // Getters
    std::string getType() const { return type; }
    std::string getTexture() const { return texture; }
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getScaleX() const { return scaleX; }
    float getScaleY() const { return scaleY; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    int getScore() const { return score; }
};

#endif
