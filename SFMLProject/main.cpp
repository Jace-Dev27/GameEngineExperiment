#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;
const sf::Vector2u SCREEN_SIZE(1920, 1080);
const float PLAYER_SPEED = 500.0f;
const float GRAVITY = 10.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE), "SFML works!");
    // sf::RectangleShape player(sf::Vector2f(10.0, 10.0));
    sf::RectangleShape mouse(sf::Vector2f(10.0, 10.0));
    sf::Texture mercy ("Assets/mercy2.png");
    sf::Texture hanzo("Assets/hanzo.png");
    sf::Sprite player(mercy);
    sf::Sprite player2(hanzo);


    player.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    player.setScale({ 0.25f, 0.25f });


    player2.setPosition({window.getSize().x / 2.5f, window.getSize().y / 2.5f });
    player2.setScale({ 0.25f, 0.25f });

    mouse.setFillColor(sf::Color::Red);

    mouse.setOrigin(sf::Vector2f(mouse.getSize().x / 2.0, mouse.getSize().y / 2.0));

    sf::Clock clock;

    sf::Time delta_time;


    clock.start();
    bool debug_mode = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event ->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::F3) {
                    debug_mode = !debug_mode;
                }
                if (keyPressed->code == sf::Keyboard::Key::I && debug_mode) {
                    cout << "x: " << mouse.getPosition().x;
                    cout << " y: " << mouse.getPosition().y << endl;
                }
            }
        }
        delta_time = clock.restart();
        float dt = delta_time.asSeconds();


        // User Keyboard Input 

        // Player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                player.move({ 0.0f, -PLAYER_SPEED * dt});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.move({ -PLAYER_SPEED * dt, 0.0f });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.move({ 0.0f, PLAYER_SPEED * dt });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.move({ PLAYER_SPEED * dt, 0.0f });
        }
        if (debug_mode) {
            mouse.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        }

        // Player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player2.move({ 0.0f, -PLAYER_SPEED * dt});

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player2.move({ -PLAYER_SPEED * dt, 0.0f });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player2.move({0.0f, PLAYER_SPEED * dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player2.move({PLAYER_SPEED * dt, 0.0f});
        }

        // FIND FIX FOR MAGIC NUMBERS
        // Adjust player origin and collision perfection

        // Player moves beyond right side of window
        if (player.getGlobalBounds().position.x > SCREEN_SIZE.x) {
            player.setPosition({ 0.0f, player.getPosition().y });
        }
        // Player moves beyond left side of window
        if (player.getGlobalBounds().position.x < 0.0f) {
            player.setPosition({ 1920.0f, player.getPosition().y});
        }
        // Player moves above the top side of window
        if (player.getGlobalBounds().position.y < 0.0f) {
            player.setPosition({ player.getPosition().x, 1080.0f});
        }
        // Player moves below the bottom side of window
        if (player.getGlobalBounds().position.y > SCREEN_SIZE.y) {
            player.setPosition({ player.getPosition().x, 0.0f });
        }


        // Player 2 moves beyond right side of window
        if (player2.getGlobalBounds().position.x > SCREEN_SIZE.x) {
            player2.setPosition({ 0.0f, player2.getPosition().y });
        }
        // Player 2 moves beyond left side of window
        if (player2.getGlobalBounds().position.x < 0.0f) {
            player2.setPosition({ 1920.0f, player2.getPosition().y });
        }
        // Player 2 moves above the top side of window
        if (player2.getGlobalBounds().position.y < 0.0f) {
            player2.setPosition({ player2.getPosition().x, 1080.0f });
        }
        // Player 2 moves below the bottom side of window
        if (player2.getGlobalBounds().position.y > SCREEN_SIZE.y) {
            player2.setPosition({ player2.getPosition().x, 0.0f });
        }

        // player 1 and player 2 collide
        if (player.getGlobalBounds().contains(player2.getGlobalBounds().position)) {
            cout << "Players Colliding!" << endl;

        }

        window.clear();
        window.draw(mouse);
        window.draw(player);
        window.draw(player2);
        window.display();
    }
}