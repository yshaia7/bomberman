
#pragma once
#include "SFML\Graphics.hpp"
#include "Settings.h"

//------------------------------------------------------------------
class Source
{
public:
	//load Source image
	Source()
	{
		//if(m_loadingFiles)
		{
		m_pTexture[0].loadFromFile("Image/Wall.jpg");
		m_pTexture[1].loadFromFile("Image/Rock.png");
		m_pTexture[2].loadFromFile("Image/Player.png");
		m_pTexture[3].loadFromFile("Image/Guard.png");
		m_pTexture[4].loadFromFile("Image/Gift.png");
		m_pTexture[5].loadFromFile("Image/Door.png");
		m_pTexture[6].loadFromFile("Image/Bomb.png");
		m_pTexture[7].loadFromFile("Image/Flame.png");
		m_pTexture[8].loadFromFile("Image/backgroundGame.jpg");
		m_pTexture[9].loadFromFile("Image/life.png");
		m_pTexture[10].loadFromFile("Image/Score.png");
		m_pTexture[11].loadFromFile("Image/Clock.png");
		m_pTexture[12].loadFromFile("Image/BombLeft.png");
		m_pTexture[13].loadFromFile("Image/Gameover.jpg");
		m_pTexture[14].loadFromFile("Image/Winner.png");
		//std::cout << "loading file";
		}
		//Source::m_loadingFiles = false;
	}
	//return the texture for each picture
	sf::Texture& getTexture(char c) {
		size_t pic_num;
		if (c == WALL)
			pic_num = 0;
		else if (c == ROCK || c == ROCKGIFT)
			pic_num = 1;
		else if (c == BOMBER)
			pic_num = 2;
		else if (c == GUARD)
			pic_num = 3;
		else if (c == GIFT)
			pic_num = 4;
		else if (c == DOOR)
			pic_num = 5;
		else if (c == BOMB)
			pic_num = 6;
		else if (c == FLAME)
			pic_num = 7;
		else if (c == BACKGROUND)
			pic_num = 8;
		else if (c == LIFE)
			pic_num = 9;
		else if (c == SCORE)
			pic_num = 10;
		else if (c == CLOCK)
			pic_num = 11;
		else if (c == BOMBLEFT)
			pic_num = 12;
		else if (c == GAMEOVER)
			pic_num = 13;
		else if (c == WINGAME)
			pic_num = 14;

		return m_pTexture[pic_num];
	}

	Source &getSourse()
	{
		return *this;
	}
private:
	static bool m_loadingFiles ;
	sf::Texture m_pTexture[ICONE_NUM];
	sf::Sprite m_pSprit[ICONE_NUM];
};

//bool Source::m_loadingFiles = false;