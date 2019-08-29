#include "Gift.h"
#include "GameController.h"

//-------------------------------------------------------
Gift::Gift(sf::Vector2f &pos, sf::Texture &tex, GameController & game)
	: StaticObj(pos, tex), m_ctrl(game)
{

}
//-------------------------------------------------------
void Gift::giftReveal()const
{
	m_ctrl.setGiftFound();
}

//-------------------------------------------------------
Gift::~Gift()
{
}