#include "main.hpp"

void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
    sf::Vector2f delta = sf::Vector2f({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}) - mousePosition;
    float length = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
    std::cout << "Length: " << length << std::endl;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void updateLine(sf::VertexArray(&lines), sf::Vector2f &mousePosition)
{
    lines[0].position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    lines[1].position = mousePosition;

    lines[0].color = sf::Color::Black;
    lines[1].color = sf::Color::Black;
}

void redrawFrame(sf::RenderWindow &window, sf::VertexArray(&lines))
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(lines);
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Line");

    sf::Vector2f mousePosition = {200, 200};

    sf::VertexArray lines(sf::Lines, 2);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateLine(lines, mousePosition);
        redrawFrame(window, lines);
    }
}