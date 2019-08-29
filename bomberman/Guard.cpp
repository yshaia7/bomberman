#include "Guard.h"
#include "GameController.h"
#include <iostream>
//-------------------------------------------------------
Guard::Guard(sf::Vector2f& pos, sf::Texture & tex, GameController &game)
	:DynamObj(pos, tex), m_ctrl(game)
{
	//set origin to defuld, for use spritesheet
	m_pic.setOrigin(0.f, 0.f);
	m_speed = 50;
	//--------------------load sound from file----------
	if (!m_killBuffSound.loadFromFile("Sound/die.flac"))
	{
		std::cout << "errorr loading sound";
		exit(EXIT_FAILURE);
	}
	//load sound
	m_killSound.setBuffer(m_killBuffSound);
	m_killSound.setVolume(40);

}

//----------------------------------------------------------------
bool Guard::catchPlayer()const
{
	return m_pic.getGlobalBounds().intersects(m_ctrl.GetPlayerRect());
}

//----------------
Guard::~Guard()
{
}

//--------------------------
void Guard::kill_robot()
{
	m_killSound.play();
	m_ctrl.restartTheLevel();
}

//------------------------
bool Guard::canMove()const
{
	return m_ctrl.can_go_guard(m_pic.getGlobalBounds());
}

//------------------------
bool Guard::collision(const sf::FloatRect & rect)const
{
	return m_pic.getGlobalBounds().intersects(rect);
}

void Guard::restartClock()
{
	m_clock.restart();
}
