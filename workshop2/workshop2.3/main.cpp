#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Ball
{
    sf::CircleShape Ball;
    sf::Vector2f speed;
    sf::Vector2f position;
    int ballsize;
};

void initBalls(Ball *ball, size_t size, float width, float height)
{
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].ballsize = 50;
        ball[i].Ball.setRadius(ball[i].ballsize);
        ball[i].Ball.setOrigin(ball[i].ballsize, ball[i].ballsize);
        float x = 0.01 * (rand() % 14000 - 7000);
        float y = 0.01 * (rand() % 14000 - 7000);
        ball[i].speed = {x, y};
    }

    ball[0].Ball.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    ball[1].Ball.setFillColor(sf::Color(0xFF, 0x00, 0xFF));
    ball[2].Ball.setFillColor(sf::Color(0x00, 0xFF, 0xFF));
    ball[3].Ball.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    ball[4].Ball.setFillColor(sf::Color(0x00, 0xFF, 0x00));

    ball[0].position = {100, 100};
    ball[1].position = {200, 200};
    ball[2].position = {300, 300};
    ball[3].position = {400, 400};
    ball[4].position = {500, 500};

    ball[0].Ball.setPosition(ball[0].position);
    ball[1].Ball.setPosition(ball[1].position);
    ball[2].Ball.setPosition(ball[2].position);
    ball[3].Ball.setPosition(ball[3].position);
    ball[4].Ball.setPosition(ball[4].position);
}

sf::Vector2f collision(sf::Vector2f &speed, sf::Vector2f &pos, float BallSize, float width, float height)
{
    if ((pos.x + BallSize > width) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y + BallSize > height) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((pos.x - BallSize < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y - BallSize < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    return (speed);
}

void update(Ball *ball, size_t size, float dt, int width, int height)
{
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].position += ball[i].speed * dt;
        ball[i].speed = collision(ball[i].speed, ball[i].position, ball[i].ballsize, width, height);
        ball[i].Ball.setPosition(ball[i].position);
    }
    for (size_t fi = 0; fi < size; ++fi)
    {
        for (size_t si = fi + 1; si < size; ++si)
        {
            if (sqrt(pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2)) <= ball[fi].ballsize + ball[si].ballsize)
            {
                float dot1 = ((ball[fi].speed.x - ball[si].speed.x) * (ball[fi].position.x - ball[si].position.x) + (ball[fi].speed.y - ball[si].speed.y) * (ball[fi].position.y - ball[si].position.y)) / (pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2));
                sf::Vector2f SumSpeed = ball[fi].speed + ball[si].speed;
                ball[fi].speed = {ball[fi].speed.x - dot1 * (ball[fi].position.x - ball[si].position.x), ball[fi].speed.y - dot1 * (ball[fi].position.y - ball[si].position.y)};
                ball[si].speed = SumSpeed - ball[fi].speed;
            }
        }
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
        window.draw(ball[i].Ball);
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