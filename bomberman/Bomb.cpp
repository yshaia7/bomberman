
#include "Bomb.h"
#include <Windows.h>
#include "GameController.h"
#include <iostream>

//----------------------------------------
Bomb::Bomb(const sf::Texture &bomb, const sf::Texture &flame,
	const sf::Vector2f &pos, GameController & game)
	: m_ctrl(game), m_picBomb(bomb), m_pos(pos.x+25, pos.y+18),m_boom(false),
	m_picFlame(flame)
{	
	//create flame origin and load texture
	m_picBomb.setOrigin((m_picBomb.getGlobalBounds().width / 2),
		(m_picBomb.getGlobalBounds().height / 2));
	flames[0].setTexture(flame);
	flames[1].setTexture(flame);
	flames[2].setTexture(flame);
	flames[3].setTexture(flame);
	flames[4].setTexture(flame);
	
	//set origine for flame
	for(int i=0; i <5; i++)
	flames[i].setOrigin((m_picBomb.getGlobalBounds().width / 2),
		(m_picBomb.getGlobalBounds().height / 2));

	//set position of flame
	flames[0].setPosition(m_pos.x, m_pos.y);
	flames[1].setPosition(m_pos.x, m_pos.y - 45);
	flames[2].setPosition(m_pos.x + 45, m_pos.y);
	flames[3].setPosition(m_pos.x, m_pos.y + 45);
	flames[4].setPosition(m_pos.x - 45, m_pos.y);
	//load sound track
	if(!m_explBuff.loadFromFile("Sound/expload.flac"))
	{
		std::cout << "error loading sound";
		exit(EXIT_FAILURE);
	}
	if(!m_putBombBuff.loadFromFile("Sound/putbomb.flac"))
	{
		std::cout << "error loading sound";
		exit(EXIT_FAILURE);
	}
	//set up sound dittels
	m_putBomb.setBuffer(m_putBombBuff);
	m_explodSound.setBuffer(m_explBuff);
	m_explodSound.setVolume(30);
	m_putBomb.setVolume(10);
	m_putBomb.play();	
}

//------------------------------------------------
void Bomb::draw(sf::RenderWindow & window)
{
	if(!m_boom)
	{//befor exploed draw bomb
	m_picBomb.setPosition(m_pos);
	window.draw(m_picBomb);
	}
	else
	{ //after exploed draw flame
		window.draw(flames[0]);
		window.draw(flames[1]);
		window.draw(flames[2]);
		window.draw(flames[3]);
		window.draw(flames[4]);
	}
}

//-----------------------------------------------
void  Bomb::Stoper()
{
	
	m_time = clock.getElapsedTime().asSeconds();
	if (m_time >=2 && !m_boom)
	{//if time pass kill all around
		for(int i = 0; i < 5; i++)
			m_ctrl.killThemAll(flames[i].getGlobalBounds());
		
		m_boom = true;//exploed happand means draw flame
		m_explodSound.play();
	}
}

//----------------------------------------------
//tell controller when to delete bomb from arr
bool Bomb::exploded()const
{
	return m_time > 3.3;
}

Bomb::~Bomb()
{
}

//----------------------------------------------
//check all area
sf::FloatRect Bomb::getExpaodRange(int num)const
{
	return flames[num].getGlobalBounds();
}
