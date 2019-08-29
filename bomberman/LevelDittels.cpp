#include "LevelDittels.h"
#include "MapManager.h"
#include "GameController.h"
#include <iostream>

//----------------------------------------------------------------------------------------------------
LevelDittels::LevelDittels(const sf::Vector2f &levelSize, MapManager & mapmang,GameController &game)
	:m_levelSize(levelSize), m_fileMang(mapmang),m_ctrl(game)
{
	createToollBar();
}
//------------------------------------------------------------
void LevelDittels::setSizeLevel(const sf::Vector2f &levelSize)
{
	m_levelSize = levelSize;
}

//------------------------------------------------------------
LevelDittels::~LevelDittels()
{
}

//------------------------------------------------------------
void LevelDittels::draw(sf::RenderWindow &window)
{
	//update dittel beffore print
	upDateDittels();

	window.draw(m_toolBarRect);
	window.draw(m_lifeHeart);
	window.draw(m_lifeHeartText);
	window.draw(m_score);
	window.draw(m_scoreText);
	window.draw(m_bombLeft);
	window.draw(m_bombLeftText);
	window.draw(m_levelText);
	window.draw(m_levelNumberText);
	window.draw(m_timeLeft);
	window.draw(m_timeLeftText);
}



void LevelDittels::createToollBar()
{
	//-----------------------load font----------------
	if (!m_font.loadFromFile("Fonts/GOUDYSTO.ttf"))
	{
		std::cout << "errorr loading font";
		exit(EXIT_FAILURE);
	}

	//tool bar rect
	m_toolBarRect.setSize({ (float)m_levelSize.x, 50 });
	m_toolBarRect.setFillColor(sf::Color(255, 204, 153));
	m_toolBarRect.setPosition(0, m_levelSize.y - 50);

	//level symbol
	m_levelText.setFont(m_font);
	m_levelText.setString("LEV");
	m_levelText.setPosition(2, m_levelSize.y - 46);
	m_levelText.setFillColor(sf::Color(0, 0, 0));
	m_levelText.setCharacterSize(35);
	m_levelText.setLetterSpacing(0.1f);
	m_levelText.setOutlineColor(sf::Color(200, 0, 0));
	m_levelText.setOutlineThickness(0.3f);

	//level number
	m_levelNumberText.setFont(m_font);
	m_levelNumberText.setPosition(120, m_levelSize.y - 46);
	m_levelNumberText.setFillColor(sf::Color(0, 0, 0));
	m_levelNumberText.setCharacterSize(35);
	m_levelNumberText.setLetterSpacing(0.1f);
	m_levelNumberText.setOutlineColor(sf::Color(200, 0, 0));
	m_levelNumberText.setOutlineThickness(0.3f);

	//life Symbol
	m_lifeHeart.setTexture(m_source.getTexture(LIFE));
	m_lifeHeart.setPosition(190, m_levelSize.y - 40);

	//life number left
	m_lifeHeartText.setFont(m_font);
	m_lifeHeartText.setPosition(235, m_levelSize.y - 39);
	m_lifeHeartText.setFillColor(sf::Color(255, 0, 0));
	m_lifeHeartText.setCharacterSize(24);

	//score Symbol
	m_score.setTexture(m_source.getTexture(SCORE));
	m_score.setPosition(290, m_levelSize.y - 39);

	//life number left
	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(332, m_levelSize.y - 38);
	m_scoreText.setFillColor(sf::Color(0, 0, 0));
	m_scoreText.setCharacterSize(24);
	
	//bomb Symbol
	m_bombLeft.setTexture(m_source.getTexture(BOMBLEFT));
	m_bombLeft.setPosition(420, m_levelSize.y - 45);

	//bomb number left
	m_bombLeftText.setFont(m_font);
	m_bombLeftText.setPosition(463, m_levelSize.y - 37);
	m_bombLeftText.setFillColor(sf::Color(0, 0,0));
	m_bombLeftText.setCharacterSize(24);
	
	//clock Symbol
	m_timeLeft.setTexture(m_source.getTexture(CLOCK));
	m_timeLeft.setPosition(540, m_levelSize.y - 48);

	//time number left
	m_timeLeftText.setFont(m_font);
	m_timeLeftText.setPosition(592, m_levelSize.y - 37);
	m_timeLeftText.setFillColor(sf::Color(0, 0, 0));
	m_timeLeftText.setCharacterSize(24);

}


//------------------------------------------
void LevelDittels::upDateDittels()
{
	int times;
	int bombs;
	bombs = m_ctrl.getNumOfBombLeft();
	times = (int)m_ctrl.getTimePass();

	//if bomb or time -1 dont show up in dittel
	 if(bombs==-1)
		 bomb ="";
	 else
		 bomb = std::to_string(bombs);

	 if (times==-1)
		 time = "";
	 else
		 time = std::to_string(times);

	 //for tool bar wirte it
	 life = std::to_string(m_ctrl.getLife());
	 score = std::to_string(m_ctrl.getScore());
	 level = std::to_string(m_ctrl.getLevel());

	 //set string
	 m_bombLeftText.setString(bomb);
	 m_scoreText.setString(score);
	 m_lifeHeartText.setString(life);
	 m_levelNumberText.setString(level);
	 m_timeLeftText.setString(time);
}