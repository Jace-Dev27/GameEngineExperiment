#pragma once

#include <SFML/Graphics.hpp>
constexpr int ROWS = 10;
constexpr int COLS = 10;

void tile_main(sf::Sprite tile, int(&map_arr)[ROWS][COLS], std::vector<sf::Texture> textures, sf::RenderWindow& window);

void tilemap_init(int(&map_arr)[ROWS][COLS], sf::Window &window);

// Populates map_arr using data from MapData.txt
void tilemap_load(int (&map_arr)[ROWS][COLS]);

// Stores the data id, map tile location data to a file
void tilemap_save();

