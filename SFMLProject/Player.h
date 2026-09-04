#pragma once
#include <SFML/Graphics.hpp>
namespace Engine {

class Player
{

public:
float PLAYER_SPEED_ = 500.0f;
	// 1-arg constructor
	Player(const char* file_path);
	// Destructor
	~Player();


private:
	sf::Texture p_texture_;
	sf::Sprite p_sprite_;
	float p_movespeed_;



};

}

