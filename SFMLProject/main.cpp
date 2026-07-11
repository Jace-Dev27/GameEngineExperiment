#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;
const sf::Vector2u SCREEN_SIZE(1920, 1080);

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event ->is<sf::Event::Closed>())
                window.close();
        }
        shape.setOrigin( sf::Vector2f(shape.getRadius(), shape.getRadius()) );
        shape.setPosition(sf::Vector2f(window.getSize().x/2.0, window.getSize().y/2.0));
        window.clear();
        window.draw(shape);
        window.display();
    }
}