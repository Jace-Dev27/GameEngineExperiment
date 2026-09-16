#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Button.h"
#include "TileManager.h"
#include "TextureLoader.h"

using std::cout;
using std::endl;
const sf::Vector2u SCREEN_SIZE(768, 512);
const float PLAYER_SPEED = 500.0f;
const float GRAVITY = 10.0f;
const sf::Color C_SELECTED(sf::Color(255, 255, 255, 200));
const sf::Color C_ORIGINAL(sf::Color(255, 255, 255, 255));

int main()
{
    // Base Window
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE), "Main", sf::Style::Titlebar | sf::Style::Close);
    int map_arr[ROWS][COLS];
    // Loads the Map Tile Set from MapData.txt
    tilemap_load(map_arr);
    tilemap_init(map_arr, window);


    std::vector<sf::Texture> textures;
    texture_init(textures);
    // Base tile
    sf::Sprite tile(textures[0]);
   
    



    sf::RectangleShape mouse(sf::Vector2f(10.0, 10.0));

    Engine::Player player_obj("Assets/mercy2.png");

    Engine::Button start_button("Assets/button_02.png", window);
    start_button.b_collisionbox_.setFillColor(sf::Color(0, 0, 0, 0));


    sf::Texture timer_off("Assets/HUD_TIMER_0.png");
    sf::Texture timer_on("Assets/HUD_TIMER_1.png");

    Engine::Button timer(timer_off, window);
    sf::Font timer_font;
    if (!timer_font.openFromFile("Assets/comicbd.ttf")) {
        std::cerr << "Error Loading Font\n";
        return -1;
    }

    // Timer Text
    sf::Text timer_text(timer_font);
    timer.b_sprite_.setPosition( {(float)(window.getSize().x - 200), 245 } );
    timer_text.setString("0:0");
    timer_text.setPosition({ (float)(timer.b_sprite_.getPosition().x - 10.0), (float)(timer.b_sprite_.getPosition().y - 20.0)} );
    // Timer Button
    timer.b_collisionbox_.setSize({ 145.0f, 40.0f });
    timer.b_collisionbox_.setPosition({ (float)( timer.b_sprite_.getPosition().x + 30) , (float)(timer.b_sprite_.getPosition().y - 245.0) });
    // 1800 seconds = 30 minutes
    sf::Time timer_initial_time = sf::seconds(1800.0f);
    sf::Clock* timer_countdown = nullptr;
    bool timer_state = false;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Assets/timer_end.wav")) {
        return -1;
    }
    sf::Sound timer_endsound(buffer);

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

    mouse.setFillColor(sf::Color::Red);

    mouse.setOrigin(sf::Vector2f(mouse.getSize().x / 2.0, mouse.getSize().y / 2.0));

    sf::Clock clock;

    sf::Time delta_time;

    // start off in menu
    bool menu_state = true;


    clock.start();
    bool debug_mode = false;

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        float mouse_pos_x = (float)mouse_pos.x;
        float mouse_pos_y = (float)mouse_pos.y;
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
                // Can ESC to menu
                if (keyPressed->code == sf::Keyboard::Key::Escape && !menu_state) {
                    std::cout << "Escape Pressed!" << std::endl;
                    menu_state = true;
                }
            }

            // This is used for one time click, not runtime
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    if (timer.b_collisionbox_.getGlobalBounds().contains({mouse_pos_x, mouse_pos_y})) {
                   std::cout << "Timer Clicked" << std::endl;
                   if (timer_state == false) {
                       timer.b_sprite_.setTexture(timer_on);
                       timer_state = true;
                       // Point to a new clock on the heap
                       timer_countdown = new sf::Clock;
                   }
                   else {
                       timer.b_sprite_.setTexture(timer_off);
                       timer_countdown = nullptr;
                       timer_state = false;
                   }

                    }
                }
            }
       }
        
        if (menu_state) {

            // Start Button
            if ( start_button.b_collisionbox_.getGlobalBounds().contains({mouse_pos_x, mouse_pos_y}) ) {
                // Slight transparent effect
                start_button.b_sprite_.setColor(C_SELECTED);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                menu_state = false;
                window.clear();
                // Need To free up memory, menu screen is gone
                continue;
                }
            } else {
                // Original transparency
                start_button.b_sprite_.setColor(C_ORIGINAL);
            }

            // Settigns Button
            if (settings_bound_box.getGlobalBounds().contains({mouse_pos_x,mouse_pos_y })) {
                // Slight transparent effect
                settings_button.setColor(C_SELECTED);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                 
                }
            }
            else {
                // Original transparency
                settings_button.setColor(C_ORIGINAL);
            }

            if (timer_countdown != nullptr) {
                std::string t_text = std::to_string((int)timer_countdown->getElapsedTime().asSeconds());
                timer_text.setString(t_text);
                if (timer_state == true && timer_countdown->getElapsedTime().asSeconds() >= 3600.0f) {
                    std::cout << "30 Minutes Is Up" << std::endl;
                    timer_endsound.play();
                    timer_countdown = nullptr;
                    timer.b_sprite_.setTexture(timer_off);
                    timer_state = false;
                }

            }


            window.clear();

            window.draw(start_button.b_collisionbox_);
            window.draw(start_button.b_sprite_);

            window.draw(settings_bound_box);
            window.draw(settings_button);

            window.draw(timer.b_sprite_);
            //window.draw(timer.b_collisionbox_);
            window.draw(timer_text);
            window.display();

            continue;
        }
        
        delta_time = clock.restart();
        float dt = delta_time.asSeconds();

        if (debug_mode) {
            mouse.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        }

        window.clear();
        tile_main(tile, map_arr, textures, window);
        window.draw(mouse);
        window.display();
    }
}