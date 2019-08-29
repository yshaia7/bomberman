#pragma once
#include "StaticObj.h" 

//----------------------------------------------------------
class Rock :  public StaticObj {
public:
	using StaticObj::StaticObj;

	//--------------------------------------------------
	//if charechter colid cannot pass
	bool collision(const sf::FloatRect & rect)const
	{
		return m_pic.getGlobalBounds().intersects(rect);
	}

	//----------------------------------------------------
	//if bomb exploed colid rock broke
	bool collisionBomb(const sf::FloatRect & rect) const
	{
		return (m_pic.getGlobalBounds().intersects(rect));		
	}
	//------------------------------------------------------
	// if charechter colid cannot pass
	//never got here
	bool collisionGuard(const sf::FloatRect & rect)const
	{
		return (m_pic.getGlobalBounds().intersects(rect));
	}
	
};