#pragma once
#include <SFML/Graphics.hpp>
#include "Source.h"

//--------------------
class MapManager;
class GameController;

//-------------------------------------------------------------------------------------------------
class LevelDittels
{
public:
	LevelDittels(const sf::Vector2f &levelSize , MapManager & mapmang, GameController &game);
	void createToollBar();
	void upDateDittels();
	void draw(sf::RenderWindow &window);
	void setSizeLevel(const sf::Vector2f & levelSize);
	~LevelDittels();


private:
	GameController & m_ctrl;
	sf::Font m_font;
	sf::Text m_lifeHeartText, m_scoreText, m_bombLeftText,  m_levelNumberText, m_timeLeftText, m_levelText;
	sf::RectangleShape m_toolBarRect;
	sf::Sprite m_lifeHeart ,m_score, m_bombLeft, m_level, m_timeLeft;
	Source m_source;
	sf::Vector2f m_levelSize;
	MapManager & m_fileMang;
	std::string life, score, bomb, level,time;

	
};


