#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My First Game");

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        // Handle font loading error
        return 1;
    }

    sf::Text text("Welcome, player", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(550, 280);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
