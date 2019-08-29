/*This is a base class of obj */

#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

//-------------------------------------------------------
//this is the main object, base class of every body
class GameController;

class Object {

public:
	Object();
	Object(sf::Vector2f& pos, sf::Texture & tex);
	virtual ~Object() = 0;
	void setPos(sf::Vector2f  pos);
	sf::Vector2f getPos()const;
    void draw(sf::RenderWindow &window) ;
	sf::Sprite getSprite()const;
	
protected:
	sf::Vector2f m_pos;
	sf::Sprite m_pic;
	

};