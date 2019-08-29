#pragma once
#include "StaticObj.h"
#include "GameController.h"


//----------------------------------------
class Door : public StaticObj
{
public:
	Door(sf::Vector2f& pos, sf::Texture &tex,GameController & game);
	bool collision(const sf::FloatRect & rect)const;
	bool  collisionBomb(const sf::FloatRect & rect)const;
	bool collisionGuard(const sf::FloatRect & rect)const;
	~Door();

private:
	GameController & m_ctrl;
	const sf::FloatRect *playerRect;
};

