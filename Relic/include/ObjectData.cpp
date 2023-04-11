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

    ObjectData() {}

    ObjectData(std::string type, std::string texture, float posX, float posY, float scaleX, float scaleY, int health = 0, int damage = 0)
        : type(type), texture(texture), posX(posX), posY(posY), scaleX(scaleX), scaleY(scaleY), health(health), damage(damage) {}

    // Getters
    std::string getType() const { return type; }
    std::string getTexture() const { return texture; }
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getScaleX() const { return scaleX; }
    float getScaleY() const { return scaleY; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
};
