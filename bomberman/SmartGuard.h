
#pragma once
#include "Guard.h"
//------------------------------------------------
class SmartGuard : public Guard {
	using Guard::Guard;
	void move() override ;

private:
	sf::Vector2f m_playerPos;
	
};