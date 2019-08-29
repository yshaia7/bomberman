#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

//base class of statics object
//-------------------------------------------------------------------
class StaticObj : public Object {
	using Object::Object;
public:
	virtual  bool collision(const sf::FloatRect & rect)const = 0;
	virtual  bool collisionBomb(const sf::FloatRect & rect)const = 0;
	virtual  bool collisionGuard(const sf::FloatRect & rect)const = 0;

};