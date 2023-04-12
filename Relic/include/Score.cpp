class Score : public sf::Text {
private:
    int score;
    sf::Font font;
    void updateText() {
        std::stringstream ss;
        ss << "Score: " << score;
        setString(ss.str());
    }

public:
    Score(int playerScore){
        if (!font.loadFromFile("Resources/Fonts/Zomboid.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }
        setFont(font);
        setCharacterSize(38);
        setFillColor(sf::Color::White);
        setPosition(10, 10);
        score = playerScore;
        updateText();
    }

    void setFontFile(const std::string& filename) {
        sf::Font font;
        if (font.loadFromFile(filename)) {
            setFont(font);
        }
    }

    void setFontSize(unsigned int fontSize) {
        setCharacterSize(fontSize);
    }

    const sf::Font& getFont() const {
        return getFont();
    }

    void setScore(int newScore) {
        score = newScore;
        updateText();
    }

    int getScore() const {
        return score;
    }

    void addScore(int amount) {
        score += amount;
        updateText();
    }
};
