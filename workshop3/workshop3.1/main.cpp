#include "main.hpp"

void pollEvents(sf::RenderWindow &window)
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
}

void redrawFrame(sf::RenderWindow &window, initials &initials)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(initials);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Initials", sf::Style::Default, settings);

    sf::Vector2f position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - BALL_SIZE - OUTLINE_SIZE};

    initials initials(position);
    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window);
        initials.update(deltaTime);
        redrawFrame(window, initials);
    }
}