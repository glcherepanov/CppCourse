#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 360}), "Initials");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({720, 280});
    shape1.setRotation(0);
    shape1.setPosition({40, 40});
    shape1.setFillColor(sf::Color(255, 255, 255));
    window.draw(shape1);

    sf::RectangleShape shape21;
    shape21.setSize({120, 40});
    shape21.setRotation(0);
    shape21.setPosition({120, 80});
    shape21.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape21);

    sf::RectangleShape shape22;
    shape22.setSize({120, 40});
    shape22.setRotation(90);
    shape22.setPosition({120, 120});
    shape22.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape22);

    sf::RectangleShape shape23;
    shape23.setSize({120, 40});
    shape23.setRotation(0);
    shape23.setPosition({120, 240});
    shape23.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape23);

    sf::RectangleShape shape31;
    shape31.setSize({120, 40});
    shape31.setRotation(0);
    shape31.setPosition({360, 80});
    shape31.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape31);

    sf::RectangleShape shape32;
    shape32.setSize({120, 40});
    shape32.setRotation(90);
    shape32.setPosition({360, 120});
    shape32.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape32);

    sf::RectangleShape shape33;
    shape33.setSize({80, 40});
    shape33.setRotation(0);
    shape33.setPosition({360, 240});
    shape33.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape33);

    sf::RectangleShape shape34;
    shape34.setSize({40, 80});
    shape34.setRotation(0);
    shape34.setPosition({440, 160});
    shape34.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape34);

    sf::RectangleShape shape35;
    shape35.setSize({40, 40});
    shape35.setRotation(0);
    shape35.setPosition({400, 160});
    shape35.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape35);

    sf::RectangleShape shape41;
    shape41.setSize({200, 40});
    shape41.setRotation(90);
    shape41.setPosition({600, 80});
    shape41.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape41);

    sf::RectangleShape shape42;
    shape42.setSize({80, 40});
    shape42.setRotation(0);
    shape42.setPosition({600, 80});
    shape42.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape42);

    sf::RectangleShape shape43;
    shape43.setSize({80, 40});
    shape43.setRotation(0);
    shape43.setPosition({600, 160});
    shape43.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape43);

    sf::RectangleShape shape44;
    shape44.setSize({80, 40});
    shape44.setRotation(0);
    shape44.setPosition({600, 240});
    shape44.setFillColor(sf::Color(0, 0, 0));
    window.draw(shape44);

    window.display();

    sf::sleep(sf::seconds(5));
}