#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

float enemySpeed = .01;
sf::Vector2f getRandomDirection() {
    int x_dir = std::rand() % 2 == 0 ? -1 : 1;  // Randomly generates -1 or 1
    int y_dir = std::rand() % 2 == 0 ? -1 : 1;  // Randomly generates -1 or 1
    return sf::Vector2f(x_dir, y_dir) * enemySpeed;
}

int main() {
    srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My First Game");

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        // Handle font loading error
        return 1;
    }

    sf::Text text("X", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(550, 280);

    sf::Texture ufoTexture;
    if (!ufoTexture.loadFromFile("ufo.png")) {
        // Handle error if the image file cannot be loaded
        return 1;
    }

    sf::Sprite enemy(ufoTexture);
    enemy.setPosition(50, 50);
    enemy.scale(.1, .1);

    // sf::RectangleShape enemy = sf::RectangleShape(sf::Vector2f(50, 100));
    //  sf::CircleShape enemy = sf::CircleShape(50);
    // enemy.setPosition(50, 50);
    // enemy.setFillColor(sf::Color::Red);

    sf::FloatRect enemyBounds = enemy.getGlobalBounds();
    sf::RectangleShape collisionBounds(
        sf::Vector2f(enemyBounds.width, enemyBounds.height));
    collisionBounds.setPosition(enemyBounds.left, enemyBounds.top);
    collisionBounds.setFillColor(sf::Color::Transparent);
    collisionBounds.setOutlineColor(sf::Color::Cyan);
    collisionBounds.setOutlineThickness(2.0f);

    bool enemyVisible = true;

    sf::Clock clock;
    sf::Time updateTime = sf::seconds(2);
    sf::Time elapsedTime;
    // get first direction
    sf::Vector2f direction = getRandomDirection();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    std::cout << "mouseButtonPressed" << std::endl;
                    std::cout << event.mouseButton.x << " "
                              << event.mouseButton.y << std::endl;

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (enemy.getGlobalBounds().intersects(
                            sf::FloatRect(mousePos.x, mousePos.y, 1, 1))) {
                        enemyVisible = false;
                        std::cout << "clicked" << std::endl;
                    }
                    break;
                }

                case sf::Event::MouseMoved: {
                    std::string x = std::to_string(event.mouseMove.x);
                    std::string y = std::to_string(event.mouseMove.y);
                    text.setPosition(event.mouseMove.x + 30, event.mouseMove.y);
                    text.setString("(" + x + ", " + y + ")");
                    break;
                }
            }
        }

        elapsedTime += clock.restart();  // also returns time since clock
                                         // started
        if (elapsedTime > updateTime) {
            elapsedTime -= updateTime;
            std::cout << "triggered\n";
            direction = getRandomDirection();
        }
        enemy.move(direction);
        collisionBounds.move(direction);
        window.clear();

        if (enemyVisible) {
            window.draw(enemy);
        }
        window.draw(collisionBounds);

        window.draw(text);
        window.display();
    }

    return 0;
}