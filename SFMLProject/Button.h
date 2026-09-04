#pragma once
#include <SFML/Graphics.hpp>
namespace Engine {

class Button
{
public:
	Button(const char* file_path, sf::RenderWindow &window);
	~Button();
	// Creates Button, Center's it's Sprite, and Creates Bounding Box
	void ButtonInit(sf::RenderWindow &window);

// Appearance Members
private:
	sf::Texture b_texture_;
public:
	sf::Sprite b_sprite_;

private:
	unsigned int b_sizex_;
	unsigned int b_sizey_;
	// Logic Members
	bool b_selected_;
	// Collision Members
	sf::FloatRect b_bounds_;
public:
	sf::RectangleShape b_collisionbox_;
};

}

