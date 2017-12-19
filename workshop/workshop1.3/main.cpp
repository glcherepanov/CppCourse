#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "cat", sf::Style::Default, settings);
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Texture texture;
    texture.loadFromFile("../img/cat.png");

    sf::Sprite cat;
    cat.setTexture(texture);
    cat.setPosition(400, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.draw(cat);
        window.display();
    }
}