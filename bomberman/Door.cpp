#include "Door.h"


//----------------------------------------
Door::Door(sf::Vector2f& pos, sf::Texture &tex,GameController & game)
	: StaticObj(pos, tex), m_ctrl(game)
{
}

//----------------------------------------
bool Door::collision(const sf::FloatRect & rect) const {

	if (m_pic.getGlobalBounds().intersects(m_ctrl.GetPlayerRect()))
	{//if player tuch the door
		m_ctrl.setDoorTuch();
		return true;
	}
	return  false;
}
//----------------------------------------
bool Door::collisionBomb(const sf::FloatRect & rect)const
{//bomb not kill door
	return false;
}
//----------------------------------------
bool Door::collisionGuard(const sf::FloatRect & rect)const
{//guard canot pass by door
	return m_pic.getGlobalBounds().intersects(rect);
}
//----------------------------------------
Door::~Door()
{
}
