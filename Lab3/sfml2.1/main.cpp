#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
float xmax = 0;
float phase = 0;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    const sf::Vector2f position = {10, 350};
    float speedX = 100.f;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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

        float amplitudeY = 80.f;
        float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        float wavePhase = phase - time * float(2 * M_PI);
        float x = xmax + speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        if (x + 2 * BALL_SIZE >= WINDOW_WIDTH)
        {
            xmax = x;
            clock.restart();
            speedX = -speedX;
            phase = wavePhase;
        }

        if (x <= 0)
        {
            xmax = x;
            clock.restart();
            speedX = -speedX;
            phase = wavePhase;
        }

        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
}