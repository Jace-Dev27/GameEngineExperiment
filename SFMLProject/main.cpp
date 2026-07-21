#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;
const sf::Vector2u SCREEN_SIZE(1920, 1080);
const float PLAYER_SPEED = 250.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE), "SFML works!");
    sf::RectangleShape player(sf::Vector2f(10.0, 10.0));
    player.setFillColor(sf::Color::Green);
    player.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    sf::Clock clock;
    sf::Time delta_time;
    clock.start();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event ->is<sf::Event::Closed>())
                window.close();
        }
        delta_time = clock.restart();
        float dt = delta_time.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                cout << "Moving up!" << endl;
                player.move({ 0.0f, -PLAYER_SPEED * dt});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            cout << "Moving left!" << endl;
            player.move({ -PLAYER_SPEED * dt, 0.0f });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            cout << "Moving down!" << endl;
            player.move({ 0.0f, PLAYER_SPEED * dt });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            cout << "Moving right!" << endl;
            player.move({ PLAYER_SPEED * dt, 0.0f });
        }

        window.clear();
        window.draw(player);
        window.display();
    }
}