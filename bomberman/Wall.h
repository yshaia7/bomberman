#pragma once
#include "StaticObj.h"

class Wall : public StaticObj {

public:
	using StaticObj::StaticObj;

	//---------------------------------------------------
	//if player colid with wall - cannot pass
	bool collision( const sf::FloatRect & rect)const
	{
		return m_pic.getGlobalBounds().intersects(rect);
	}

	//---------------------------------------------------
	//bomb dont break the wall
	bool collisionBomb(const sf::FloatRect & rect)const
	{
		return false;
	}

	//---------------------------------------------------
	//if guard colid with wall-cannot pass
	// never got here
	bool collisionGuard(const sf::FloatRect & rect)const
	{
		return (m_pic.getGlobalBounds().intersects(rect));
	}
};

