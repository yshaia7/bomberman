#include "DynamObj.h"

//-------------------------------------------------------
DynamObj::DynamObj(sf::Vector2f &pos, sf::Texture &tex)
	:Object(pos, tex), m_initialPos(Object::m_pos)
	,m_speed(0)
{
	//make the charectore stand in place at the begining
	m_pic.setTextureRect(sf::IntRect(
		m_pic.getTexture()->getSize().x / 3*m_slide,0,
		m_pic.getTexture()->getSize().x / 3,
		m_pic.getTexture()->getSize().y / 4));
}

//-------------------
DynamObj::DynamObj()
{}

//-------------------------------------------------------
DynamObj::~DynamObj()
{

}

//-------------------------------------------------------
sf::Vector2f DynamObj::getInitialPos()const
{
	return m_initialPos;
}

//-------------------------------------------------------
void DynamObj::switchAnimation()
{

	//run over iall lines in spritsheet
	(m_slide == 2) ? m_slide = 0 : m_slide++;
	//make the correct picture from spritsheet visible
	m_pic.setTextureRect(sf::IntRect(
		m_pic.getTexture()->getSize().x / 3*m_slide,
		m_pic.getTexture()->getSize().y / 4*m_nextDirection,
		m_pic.getTexture()->getSize().x / 3,
		m_pic.getTexture()->getSize().y / 4));
}

