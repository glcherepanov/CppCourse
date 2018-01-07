#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::Vector2f position;
    int ballSize;
};

void initBalls(Ball *ball, size_t size, float width, float height)
{
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].ballSize = 50;
        ball[i].ball.setRadius(ball[i].ballSize);
        ball[i].ball.setOrigin(ball[i].ballSize, ball[i].ballSize);
    }
    ball[0].ball.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    ball[1].ball.setFillColor(sf::Color(0xFF, 0x00, 0xFF));
    ball[2].ball.setFillColor(sf::Color(0x00, 0xFF, 0xFF));
    ball[3].ball.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    ball[4].ball.setFillColor(sf::Color(0x00, 0xFF, 0x00));

    ball[0].position = {100, 100};
    ball[1].position = {200, 200};
    ball[2].position = {300, 300};
    ball[3].position = {400, 400};
    ball[4].position = {500, 500};

    ball[0].speed = {45, 45};
    ball[1].speed = {-45, -45};
    ball[2].speed = {30, -30};
    ball[3].speed = {30, 30};
    ball[4].speed = {50, 50};

    ball[0].ball.setPosition(ball[0].position);
    ball[1].ball.setPosition(ball[1].position);
    ball[2].ball.setPosition(ball[2].position);
    ball[3].ball.setPosition(ball[3].position);
    ball[4].ball.setPosition(ball[4].position);
}

sf::Vector2f collision(sf::Vector2f &speed, sf::Vector2f &pos, float ballSize, float width, float height)
{
    if ((pos.x + ballSize > width) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y + ballSize > height) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((pos.x - ballSize < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y - ballSize < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    return (speed);
}

void update(Ball *ball, size_t size, float dt, int width, int height)
{
    for (size_t fi = 0; fi < size; ++fi)
    {
        for (size_t si = fi + 1; si < size; ++si)
        {
            if (sqrt(pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2)) <= ball[fi].ballSize + ball[si].ballSize)
            {
                float dot1 = ((ball[fi].speed.x - ball[si].speed.x) * (ball[fi].position.x - ball[si].position.x) + (ball[fi].speed.y - ball[si].speed.y) * (ball[fi].position.y - ball[si].position.y)) / (pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2));
                sf::Vector2f SumSpeed = ball[fi].speed + ball[si].speed;
                ball[fi].speed = {ball[fi].speed.x - dot1 * (ball[fi].position.x - ball[si].position.x), ball[fi].speed.y - dot1 * (ball[fi].position.y - ball[si].position.y)};
                ball[si].speed = SumSpeed - ball[fi].speed;
                std::cout << fi << ": " << ball[fi].speed.x << ";" << ball[fi].speed.y << "  " << si << ": " << ball[si].speed.x << ";" << ball[si].speed.y << std::endl;
            }
        }
    }
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].position += ball[i].speed * dt;
        ball[i].speed = collision(ball[i].speed, ball[i].position, ball[i].ballSize, width, height);
        ball[i].ball.setPosition(ball[i].position);
    }
}

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

void redrawFrame(sf::RenderWindow &window, Ball *ball, size_t size)
{
    window.clear();
    for (size_t i = 0; i < size; ++i)
    {
        window.draw(ball[i].ball);
    }
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls", sf::Style::Default, settings);

    sf::Clock clock;

    Ball ball[5];

    initBalls(ball, std::size(ball), WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window);
        update(ball, std::size(ball), dt, WINDOW_WIDTH, WINDOW_HEIGHT);
        redrawFrame(window, ball, std::size(ball));
    }
}