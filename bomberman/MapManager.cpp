#include <iostream>
#include "MapManager.h"
#include "GameController.h"



//-----------------------------------
MapManager::MapManager(GameController & game)
	:m_ctrl(game), m_textures()
{
	m_backgroundLevel.setTexture(m_textures.getTexture(BACKGROUND));
	ReadFromFile(input);
	CreateLevel();
	create_background();

}

//-----------------------------------
MapManager::~MapManager()
{
}

//if player die by pass the turn or time end
void MapManager::restartReadFromMat()
{
	CreateLevel();
}

//-----------------------------------
void MapManager::readNextLevel()
{
	m_mapInitial.clear();
	ReadFromFile(input);
	CreateLevel();
	create_background();

}

//-----------------------------------
sf::Vector2f MapManager::getLevelSize() const
{
	return { (m_sizeOfLevel.y)*PIXIL_SIZE,  (m_sizeOfLevel.x+1)*PIXIL_SIZE };
}

//-----------------------------------
void MapManager::drawMap(sf::RenderWindow & window)
{	
	window.draw(m_backgroundLevel);
}

//-------------------------------------
void MapManager::ReadFromFile(std::ifstream &input)
{
	
	int time, bomb;
		if(!readFile)
		{//for read from file only once
		 input.open("board.txt");	
		if (!input.is_open())
		{
			std::cerr << "cannot open file";
			exit(EXIT_FAILURE);
		}
		readFile = true;
		}
		input >> m_sizeOfLevel.x >> m_sizeOfLevel.y
			>> time >> bomb;

		m_ctrl.setInitialBomb(bomb);
		
		//if ther is limit on time
		if (time)
			m_ctrl.setTime(time);
		
		std::string line;
		getline(input, line);
	
		//read all file to matrix
		for (int i = 0; i < m_sizeOfLevel.x; i++)
		{
			getline(input, line);
			m_mapInitial.push_back(line);
		}
	
}

//--------------------------------------------------------
//run over all matrix and send the char to create cherecter
void MapManager::CreateLevel()
{
	char c;	

	for (int row = 0; row < m_sizeOfLevel.x; row++)
		for (int col = 0; col < m_sizeOfLevel.y; col++)
		{
			c = m_mapInitial[row][col];
			if (c == '\0')
				continue;

			if (isspace(c))
				continue;
			m_ctrl.createCharacters({(float)col,(float)row}, c);
		}
}

//--------------------------------------------------------
void MapManager::create_background()
{	//set origin for background
	m_backgroundLevel.setOrigin(m_backgroundLevel.getGlobalBounds().width / 2 +150,
								m_backgroundLevel.getGlobalBounds().height / 2 -30);
	m_backgroundLevel.setPosition(getLevelSize().x / 2 , getLevelSize().y / 2);
}

//--------------------------------------------------------
void MapManager::restartAllGame()
{
	input.clear();
	input.seekg(0, std::ios::beg);
	m_mapInitial.clear();
	ReadFromFile(input);
	CreateLevel();
}