//---------------------------------------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML//Audio.hpp>
class GameController;

//--------------------------------------------------------------------
class Bomb {
public:
	Bomb(const sf::Texture &bomb,  const sf::Texture &flame,
		const sf::Vector2f &pos, GameController & game);
	sf::FloatRect getExpaodRange(int num)const;
	void draw(sf::RenderWindow & window);
	void Stoper();
	bool exploded()const;
	~Bomb();

private:
	float m_time;
	bool m_boom;
	sf::Sprite m_picBomb;
	sf::Sprite m_picFlame;
	sf::Vector2f m_pos;
	sf::FloatRect m_rect;
	GameController & m_ctrl;
	sf::Clock clock;
	sf::Sprite flames[5];
	sf::RenderWindow m_window;
	sf::SoundBuffer m_explBuff;
    sf::SoundBuffer m_putBombBuff;
	sf::Sound m_explodSound;
	sf::Sound m_putBomb;
};

