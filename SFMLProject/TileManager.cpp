#include "TileManager.h"
#include <iostream>
#include <fstream>
#include <vector>

const float TILE_SIZE = 128.0f;
int screen_tile_width = 0;
int screen_tile_height = 0;


void tile_main(sf::Sprite tile, int (&map_arr)[ROWS][COLS], std::vector<sf::Texture> textures, sf::RenderWindow &window) {
	for (int i = 0; i < screen_tile_height; i++) {
		for (int j = 0; j < screen_tile_width; j++) {
			int text_id = map_arr[i][j];
			tile.setTexture(textures[text_id]);
			tile.setPosition({ j * TILE_SIZE, i * TILE_SIZE });
			window.draw(tile);
		}
	}




}

void tilemap_init(int (&map_arr)[ROWS][COLS], sf::Window &window) {
	// W for horizontal tiles
	// H for vertical tiles
	screen_tile_width = window.getSize().x / 128.0f;
	screen_tile_height = window.getSize().y / 128.0f;
	

}

void tilemap_load(int (&map_arr)[ROWS][COLS]) {
	// Grab Tile Data Json
	std::ifstream input_file("Assets/TileMap/MapData.txt");
	if (!input_file.is_open()) {
		std::cerr << "File Could Not Open" << std::endl;
		return;
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			input_file >> map_arr[i][j];
		}
	}
	input_file.close();

}

void tilemap_save() {
	std::cout << "Saving Tile Data!" << std::endl;
	std::ofstream map_outputFile("Assets/TileMap/MapData.txt");

}






