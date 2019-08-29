#pragma once
#include <SFML/Graphics.hpp>
#include <SFML//Audio.hpp>
class OpenScreen
{
public:
	OpenScreen();
	void reloadAndSet();
	~OpenScreen();
	bool run(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	void setUpSizes(sf::Vector2f sizeS);

private:

	sf::Vector2f screenSize;
	void openScreen();
	sf::Sprite ScreenBackgrouond;
	sf::Texture tex;
	sf::Text m_start, m_exit;
	sf::Font m_font;
	sf::RectangleShape m_mouse;
	sf::SoundBuffer m_SoundBuff;
	sf::Sound m_sound;
};

