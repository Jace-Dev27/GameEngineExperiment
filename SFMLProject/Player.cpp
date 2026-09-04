#include "Player.h"
#include <iostream>
namespace Engine {

	// 1-arg constructor
	Player::Player(const char* file_path) : p_texture_(file_path), p_sprite_(p_texture_), p_movespeed_(PLAYER_SPEED_) {
		std::cout << "Player Created!!" << std::endl;
	}
	Player::~Player() {
		std::cout << "Player Destroyed!" << std::endl;
	}

}

