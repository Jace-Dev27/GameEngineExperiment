#pragma once

#include <SFML/Graphics.hpp>
constexpr int ROWS = 10;
constexpr int COLS = 10;

void tile_main();

void tilemap_init(int(&map_arr)[ROWS][COLS], sf::Window &window);

// Populates map_arr using data from MapData.txt
void tilemap_load(int (&map_arr)[ROWS][COLS]);

void tilemap_save();

