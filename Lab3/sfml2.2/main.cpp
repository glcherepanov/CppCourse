#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

int main()
{
    constexpr int pointCount = 200;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "rose",
        sf::Style::Default, settings);

    sf::Vector2f position = {400, 200};

    sf::ConvexShape rose;
    rose.setPosition(position);
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    rose.setPointCount(pointCount);

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

        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            float radius = 200 * sin(6 * angle);
            sf::Vector2f point = {
                radius * std::sin(angle),
                radius * std::cos(angle)};
            rose.setPoint(pointNo, point);
        }

        float i = i + 0.2;
        float angle = angle + 0.01;

        if ((angle == 3.14) || (angle == -3.14))
        {
            angle = -angle;
        }

        if (i > 359)
        {
            i = 0;
        }

        rose.setRotation(i);
        position.x = position.x + std::cos(angle);
        position.y = position.y + std::sin(angle);
        rose.setPosition(position);

        window.clear();
        window.draw(rose);
        window.display();
    }
}