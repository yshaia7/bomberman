#pragma once
//base class of player and guards
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Object.h"

//------------------------------------------------------------
//direction for player and guard
enum Direction {  Down,  left ,Up,Right, Stand, width, hight};

//-------------------------------------------------------------
class DynamObj : public Object {
public:
	DynamObj();
	DynamObj(sf::Vector2f &pos, sf::Texture &tex);
	virtual void move() = 0;
	sf::Vector2f getInitialPos()const;
	void switchAnimation();

	~DynamObj();
protected:
	sf::Clock m_clock;
	float m_speed;
	sf::Vector2f m_initialPos;
	int m_nextDirection;
	sf::Vector2f m_lastMove;
	float m_distance;
	int m_slide=0;//switch the inmation

};