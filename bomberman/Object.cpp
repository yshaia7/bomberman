#include "Object.h"
#include "GameController.h"

//---------------------------------------------------
Object::Object()
{

}


//---------------------------------------------------
//each object will restart get a position and texture
Object::Object(sf::Vector2f &pos, sf::Texture &tex)
	:m_pos({ pos.x*PIXIL_SIZE + 25, pos.y*PIXIL_SIZE + 25 }), m_pic(tex)
{
	m_pic.setOrigin((m_pic.getGlobalBounds().width / 2), (m_pic.getGlobalBounds().height / 2));
}

//---------------------------------------------------
Object::~Object()
{
}

//---------------------------------------------------
void Object::setPos(sf::Vector2f pos)
{
	m_pos = pos;
}

//---------------------------------------------------
sf::Vector2f Object::getPos() const
{
	return m_pos;
}

//---------------------------------------------------
void Object::draw(sf::RenderWindow & window)
{
	m_pic.setPosition(m_pos);
	window.draw(m_pic);
}

//---------------------------------------------------
sf::Sprite Object::getSprite() const
{
	return m_pic;
}


