#pragma once
#include "DynamObj.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

class GameController;
//--------------------------------------------------------
class Player : public DynamObj {
public:
	Player();
	Player(sf::Vector2f &pos, sf::Texture &tex
	, GameController *crtl);
	void KeyRelease(sf::Event &KeyRels);
	void move() override;
	void setUp();
	void keyPreset(sf::Event &keypres);
	const sf::FloatRect getPlayerRect() const;
	void setLife(int num);
	void resetLife(int num);
	int getLife()const;
	bool collision(const sf::FloatRect & rect)const;
	
	

private:
	int m_life;
	GameController *m_ctrl;
	sf::Vector2f inmaDirection;
};