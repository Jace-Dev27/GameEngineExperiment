#include "Button.h"
#include <iostream>
namespace Engine {
	
	Button::Button(const char* file_path, sf::RenderWindow &window) : 
		b_texture_(file_path),
		b_sprite_(b_texture_),
		b_sizex_(b_texture_.getSize().x),
		b_sizey_(b_texture_.getSize().y),
		b_selected_(false)	{
		ButtonInit(window);
		std::cout << "Button Created!" << std::endl;
	}

	Button::Button(sf::Texture texture, sf::RenderWindow &window) : 
		b_texture_(texture),
		b_sprite_(b_texture_),
		b_sizex_(b_texture_.getSize().x),
		b_sizey_(b_texture_.getSize().y),
		b_selected_(false) {
		ButtonInit(window);
		std::cout << "Button Created!" << std::endl; 
	}

	Button::~Button() {
		std::cout << "Button Destroyed!" << std::endl;
	}
	void Button::ButtonInit(sf::RenderWindow &window) {
		b_sprite_.scale({ 4.0f, 4.0f });
		b_sprite_.setOrigin({ b_sizex_ / 2.0f , b_sizey_ / 2.0f });
		b_sprite_.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 3.0f });

		b_bounds_ = sf::FloatRect(
			sf::Vector2f(b_sprite_.getPosition().x - 184.0f, b_sprite_.getPosition().y - 32.0f),
			sf::Vector2f(364.0f, 64.0f)
		);
		b_collisionbox_ = sf::RectangleShape(b_bounds_.size);
		b_collisionbox_.setOrigin({ b_collisionbox_.getPosition().x / 2.0f, b_collisionbox_.getPosition().y / 2.0f });
		b_collisionbox_.setPosition(b_bounds_.position);
		b_collisionbox_.setFillColor(sf::Color::Red);

	}




}
