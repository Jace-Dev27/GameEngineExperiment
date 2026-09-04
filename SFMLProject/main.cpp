#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Button.h"

using std::cout;
using std::endl;
const sf::Vector2u SCREEN_SIZE(1920, 1080);
const float PLAYER_SPEED = 500.0f;
const float GRAVITY = 10.0f;
const sf::Color C_SELECTED(sf::Color(255, 255, 255, 200));
const sf::Color C_ORIGINAL(sf::Color(255, 255, 255, 255));

int main()
{
    // Base Window
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE), "Main");


    // sf::RectangleShape player(sf::Vector2f(10.0, 10.0));
    sf::RectangleShape mouse(sf::Vector2f(10.0, 10.0));
    sf::Texture mercy ("Assets/mercy2.png");
    sf::Texture hanzo("Assets/hanzo.png");
    sf::Sprite player(mercy);
    sf::Sprite player2(hanzo);

    Engine::Player player_obj("Assets/mercy2.png");

    Engine::Button start_button("Assets/button_02.png", window);

    // Settings Button
    sf::Texture settings_texture("Assets/button_01.png");
    sf::Sprite settings_button(settings_texture);

    settings_button.scale({ 4.0f, 4.0f });
    settings_button.setOrigin({ settings_texture.getSize().y / 2.0f, settings_texture.getSize().y / 2.0f });
    //settings_button.setPosition({start_button.getPosition().x, start_button.getPosition().y + 72.0f});
    
    // Bounding Box

    sf::FloatRect settings_bounds(
        sf::Vector2f(settings_button.getPosition().x - 184.0f, settings_button.getPosition().y - 32.0f),
        sf::Vector2f(364.0f, 64.0f)
    );

    sf::RectangleShape settings_bound_box(settings_bounds.size);
    settings_bound_box.setOrigin({ settings_bound_box.getPosition().x / 2.0f, settings_bound_box.getPosition().y / 2.0f});
    settings_bound_box.setPosition(settings_bounds.position);
    settings_bound_box.setFillColor(sf::Color::Red);

    player.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    player.setScale({ 0.25f, 0.25f });


    player2.setPosition({window.getSize().x / 2.5f, window.getSize().y / 2.5f });
    player2.setScale({ 0.25f, 0.25f });

    mouse.setFillColor(sf::Color::Red);

    mouse.setOrigin(sf::Vector2f(mouse.getSize().x / 2.0, mouse.getSize().y / 2.0));

    sf::Clock clock;

    sf::Time delta_time;

    // start off in menu
    bool menu_state = true;


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
        
        if (menu_state) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            // Start Button
            if ( start_button.b_collisionbox_.getGlobalBounds().contains( {(float)mouse_pos.x, (float)mouse_pos.y })) {
                // Slight transparent effect
                start_button.b_sprite_.setColor(C_SELECTED);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                menu_state = false;
                }
            } else {
                // Original transparency
                start_button.b_sprite_.setColor(C_ORIGINAL);
            }

            // Settigns Button
            if (settings_bound_box.getGlobalBounds().contains({ (float)mouse_pos.x, (float)mouse_pos.y })) {
                // Slight transparent effect
                settings_button.setColor(C_SELECTED);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                 
                }
            }
            else {
                // Original transparency
                settings_button.setColor(C_ORIGINAL);
            }

            window.clear();
            //window.draw(start_bound_box);
            //window.draw(start_button);
            window.draw(start_button.b_collisionbox_);
            window.draw(start_button.b_sprite_);

            window.draw(settings_bound_box);
            window.draw(settings_button);
            window.display();

            continue;
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