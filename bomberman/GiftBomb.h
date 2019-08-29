#pragma once
#include "Gift.h"
#include "GameController.h"

//----------------------------------------------------------------------
class GiftBomb : public  Gift
{
public:
	using Gift::Gift;
	//-------------------------------------------------------------------
	//if player tuch gift, tell the controller and setUp ditele
	bool collision(const sf::FloatRect & rect) const {
		if (m_pic.getGlobalBounds().intersects(m_ctrl.GetPlayerRect()))
		{
			giftReveal();
			m_ctrl.setBomb(bombPrice);//set the price
			return true;
		}
		else
			return false;
	}
private:
	int bombPrice = 3;
};
