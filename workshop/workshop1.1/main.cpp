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
        "Arrow", sf::Style::Default, settings);
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    sf::ConvexShape arrow;

    arrow.setPosition({400, 300});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, 60});
    arrow.setPoint(1, {60, 0});
    arrow.setPoint(2, {0, -60});
    arrow.setPoint(3, {0, -30});
    arrow.setPoint(4, {-60, -30});
    arrow.setPoint(5, {-60, 30});
    arrow.setPoint(6, {0, 30});
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        window.draw(arrow);
        window.display();
    }
}