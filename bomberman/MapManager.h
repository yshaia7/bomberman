#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Source.h"
#include <fstream>

//handel the file
//-------------------------------------------------------
class GameController;

//-------------------------------------------------------
class MapManager {

public:
	MapManager(GameController &game);
	sf::Vector2f getLevelSize() const;
	void drawMap(sf::RenderWindow &window);
	~MapManager();
	void restartReadFromMat();
	void readNextLevel();
	void restartAllGame();
	void create_background();

private:
	GameController & m_ctrl;
	std::ifstream input;
	bool readFile = false;
	Source  m_textures;
	sf::Sprite m_backgroundLevel;
	sf::Vector2i m_sizeOfLevel;
	void ReadFromFile(std::ifstream &input);
	void CreateLevel();
	std::vector<std::string> m_mapInitial;


	
};
