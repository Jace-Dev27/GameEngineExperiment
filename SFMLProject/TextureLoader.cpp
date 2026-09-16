#include "TextureLoader.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

json tile_data;

void texture_init(std::vector<sf::Texture> &textures) {
	init_json();
	std::cout << tile_data.size() << std::endl;
	for (int i = 0; i < tile_data.size(); i++) {
		textures.push_back(sf::Texture(tile_data[i]));
	}
}

void populate_json() {
	// Key is the ID#, Value is the Texture
	tile_data[0] = "Assets/TileMap/Tiles/Dirt.png";
	tile_data[1] = "Assets/TileMap/Tiles/Grass.png";
	tile_data[2] = "Assets/TileMap/Tiles/StoneBricks.png";

	// Write To json File
	std::ofstream id_outputFile("TileMap.json");
	if (id_outputFile.is_open()) {
		// 4 Space Indentation
		id_outputFile << std::setw(4) << tile_data << std::endl;
		id_outputFile.close();
		std::cout << "json file saved tile data!" << std::endl;
	}
}

void init_json() {
	std::ifstream id_inputFile("TileMap.json");
	if (!id_inputFile.is_open()) {
		std::cerr << "Could not open TileMap json file" << std::endl;
		return;
	}
	id_inputFile >> tile_data;
	id_inputFile.close();
}
