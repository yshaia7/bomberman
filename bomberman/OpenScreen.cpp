#include "OpenScreen.h"
#include <iostream>

//---------------------------------------------------
OpenScreen::OpenScreen()
{
	reloadAndSet();
	
}

//---------------------------------------------------
//load all source for open screen
void OpenScreen::reloadAndSet()
{
	if(!tex.loadFromFile("Image/OpenScreen.png"))
	{
		std::cout << "error loading font";
		exit(EXIT_FAILURE);
	}

	if (!m_font.loadFromFile("Fonts/BUTTON.otf"))
	{
		std::cout << "error loading font";
		exit(EXIT_FAILURE);
	}

	if (!m_SoundBuff.loadFromFile("Sound/open.flac"))
	{
		std::cout << "errorr loading font";
		exit(EXIT_FAILURE);
	}
	m_sound.setBuffer(m_SoundBuff);
	m_sound.setVolume(50);
	
	ScreenBackgrouond.setTexture(tex);
	m_start.setFont(m_font);
	m_exit.setFont(m_font);


	m_start.setString("START  NEW  GAME");
	m_exit.setString("EXIT");

	m_start.setCharacterSize(35);
	m_exit.setCharacterSize(35);
	m_mouse.setSize({ 10,20 });

	m_start.setFillColor(sf::Color(255, 255, 50));
	m_exit.setFillColor(sf::Color(255, 255, 50));

	m_start.setLetterSpacing((float)0.1);
	m_exit.setLetterSpacing((float)0.1);

	m_start.setOutlineThickness((float)0.3);
	m_exit.setOutlineThickness((float)0.3);
	
	m_start.setOutlineColor(sf::Color(0, 0, 255));
	m_exit.setOutlineColor(sf::Color(0, 0, 255));

}

OpenScreen::~OpenScreen()
{
}

//----------------------------------------------------
//draw the ditels of open screen
void OpenScreen::draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(ScreenBackgrouond);
	window.draw(m_start);
	window.draw(m_exit);
	window.display();
}

//------------------------------------------------------
//set the corect size of logo and massage of open screen
void OpenScreen::setUpSizes(sf::Vector2f sizeS)
{
	screenSize = sizeS;
	
	ScreenBackgrouond.setPosition(screenSize.x / 2, screenSize.y / 2);
	ScreenBackgrouond.setOrigin(ScreenBackgrouond.getGlobalBounds().width / 2, 
		ScreenBackgrouond.getGlobalBounds().height / 2 +50);

	m_start.setPosition(ScreenBackgrouond.getPosition().x - 161,
		ScreenBackgrouond.getPosition().y + 190);

	m_exit.setPosition(m_start.getPosition().x + 105,
		m_start.getPosition().y + 60);

}

//----------------------------------------------------
void OpenScreen::openScreen()
{
	
}

//-----------------------------------------------------
//handel the open screen
bool OpenScreen::run(sf::RenderWindow &window)
{
	m_sound.play();
	sf::Event event;
	while (window.isOpen())
	while (window.pollEvent(event))
	{
		//the user doesnt want to start new game
			switch (event.type)
			{
				//close the window
			case sf::Event::Closed:
				m_sound.stop();
				window.close();
				break;

			// light start/exit massage if mouse on top of that
			case sf::Event::MouseMoved:
				m_mouse.setPosition(float(event.mouseMove.x),float(event.mouseMove.y));
						
				if (m_start.getGlobalBounds().intersects(m_mouse.getGlobalBounds()))
					m_start.setOutlineColor(sf::Color(0,0,0));
				else 
					m_start.setOutlineColor(sf::Color(0, 0, 255));

				if (m_exit.getGlobalBounds().intersects(m_mouse.getGlobalBounds()))
					m_exit.setOutlineColor(sf::Color(0, 0, 0));
				else
					m_exit.setOutlineColor(sf::Color(0, 0, 255));
				
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					//player start the game
					if (m_start.getGlobalBounds().intersects(m_mouse.getGlobalBounds()))
					{
						m_sound.stop();
						return true;
					}
					//player exit from the game				
					else if (m_exit.getGlobalBounds().intersects(m_mouse.getGlobalBounds()))
					{
						m_sound.stop();
						 return false;	
					}
				}
				
			}
			draw(window);
	}

}