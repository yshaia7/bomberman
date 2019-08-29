#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DynamObj.h"

class GameController;
//-------------------------------------------------------------------
class Guard : public DynamObj {
public: 
	Guard(sf::Vector2f& pos, sf::Texture &tex, GameController &game);
	virtual void move() = 0;
	bool catchPlayer()const;
	void kill_robot();
	bool canMove()const;
	bool collision(const sf::FloatRect & rect)const;
	void restartClock();
	~Guard();

protected:
	GameController & m_ctrl;
	bool m_colide;
	sf::SoundBuffer m_killBuffSound;
	sf::Sound m_killSound;
};