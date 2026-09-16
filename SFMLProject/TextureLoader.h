#pragma once
#include <vector>
#include "TileManager.h"
#include <SFML/Graphics.hpp>

// Populate Vector with Textures
// Index is ID, value is texture
void texture_init(std::vector<sf::Texture> &textures);


// Populates Json File With ID:TexturePath
void populate_json();

// Initializes the json file stack variable
void init_json();