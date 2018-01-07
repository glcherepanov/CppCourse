#include "main.hpp"

void pollEvents(sf::RenderWindow &window, sf::View view, std::vector<Ball> &balls, sf::Color *color, size_t colorSize)
{
    sf::Event event;
    sf::Vector2i mousePosition;
    sf::Vector2f worldPosition;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            mousePosition = sf::Mouse::getPosition(window);
            worldPosition = window.mapPixelToCoords(mousePosition);
            std::cout << mousePosition.x << "; " << mousePosition.y << std::endl;
            initBall(balls, color, colorSize, worldPosition);
            break;
        default:
            break;
        }
    }
}

void update(std::vector<Ball> &balls, sf::View &view, float deltaTime)
{
    moveBalls(balls, deltaTime);
    ballsCollision(balls);
    moveView(view, deltaTime);
}

void redrawFrame(sf::RenderWindow &window, sf::View view, sf::ConvexShape shape, std::vector<Ball> &balls)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.setView(view);
    window.draw(shape);
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Balls", sf::Style::Default, settings);

    sf::ConvexShape shape;
    initGround(shape);

    sf::Clock clock;

    std::vector<Ball> balls(5, Ball());

    sf::View view;
    initView(view);

    sf::Color(color[8]);
    initPalette(color);

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, view, balls, color, std::size(color));
        update(balls, view, deltaTime);
        redrawFrame(window, view, shape, balls);
    }
}