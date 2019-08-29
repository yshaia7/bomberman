#pragma once
#include "Settings.h"
#include "StaticObj.h"
#include <SFML/Graphics.hpp>

//---------------------------------------------------------
class Gift : public  StaticObj
{
public:
	Gift(sf::Vector2f &pos, sf::Texture &tex, GameController & game);
	void giftReveal() const;//for tell game controller player find gift
	bool collisionBomb(const sf::FloatRect & rect)const { return false; }
	bool collisionGuard(const sf::FloatRect & rect)const { return false; }
	~Gift();

protected:
	GameController & m_ctrl;
	
};