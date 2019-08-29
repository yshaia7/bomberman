#pragma once
#include "Gift.h"
#include "GameController.h"

//----------------------------------------------------------------------
class GiftLife : public  Gift
{
public:
	using Gift::Gift;
	//-------------------------------------------------------------------
	//if player tuch gift, tell the controller and setUp dittel
	bool collision(const sf::FloatRect & rect) const {
		if (m_pic.getGlobalBounds().intersects(m_ctrl.GetPlayerRect()))
		{
			giftReveal();
			m_ctrl.setLife(lifePrice);	//set the price	
			return true;
		}
		else
			return false;
	}
private:
	int lifePrice = 1;
};
