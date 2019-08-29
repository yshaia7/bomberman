
#include "GameController.h"
#include "Wall.h"
#include "GiftLife.h"
#include "GiftBomb.h"
#include <iostream>
#include "GiftTime.h"
#include "Rock.h"
#include "Door.h"
#include "SmartGuard.h"
#include "StupidGuard.h"


//----------------------------------------------------------
GameController::GameController()
	:m_fileMang(*this), m_levelDitel(m_fileMang.getLevelSize(),
		m_fileMang, *this), m_openScreen()
{
	reloadDittels();
}

//-----------------------------------------------------
//load and set up (sound)
void GameController::reloadDittels()
{
	 if(!m_SoundBuff.loadFromFile("Sound/game.flac"))
	 {
		 std::cout << "error loading sound";
		 exit(EXIT_FAILURE);
	 }

	 if (!m_soundBuff.loadFromFile("Sound/gift.flac"))
	 {
		 std::cout << "error loading sound";
		 exit(EXIT_FAILURE);
	 }
	 if (!m_scoreBuff.loadFromFile("Sound/points.flac"))
	 {
		 std::cout << "errorr loading sound";
		 exit(EXIT_FAILURE);
	 }
	 if (!m_gameOverBuff.loadFromFile("Sound/gameover.flac"))
	 {
		 std::cout << "errorr loading sound";
		 exit(EXIT_FAILURE);
	 }
	 if (!m_finishBuff.loadFromFile("Sound/wingame.flac"))
	 {
		 std::cout << "errorr loading sound";
		 exit(EXIT_FAILURE);
	 }
	 m_gameOver.setBuffer(m_gameOverBuff);
	 m_finishGame.setBuffer(m_finishBuff);
	 m_scoreSound.setBuffer(m_scoreBuff);
	 m_scoreSound.setVolume(30);
	 m_soundGift.setBuffer(m_soundBuff);
	 m_soundGift.setVolume(10);
	 m_BackgSound.setBuffer(m_SoundBuff);
	 m_BackgSound.setVolume(50);
	 m_gameOver.setVolume(50);
	 m_finishGame.setVolume(50);
	 m_openScreen.setUpSizes(m_fileMang.getLevelSize());
	 m_BackgSound.setLoop(true);
}

//----------------------------------------------------------
GameController::~GameController()
{
}

//----------------------------------------------------------
//main process of the game
void GameController::run()
{

	sf::Event event;
	//open window
	m_window.create(sf::VideoMode((unsigned)m_fileMang.getLevelSize().x,
		(unsigned)m_fileMang.getLevelSize().y), "BOMBERMAN", sf::Style::Close);
	//limit frame for movment
	m_window.setFramerateLimit(8);
	sig.m_gameRun = false;
	if(openScreenRutine())//if true start game-else exit
	{
		sig.m_gameRun = true;
		gameDittel.m_level++;//level 1
		m_BackgSound.play();//sound of background
		
		for (size_t i = 0; i < m_ArrGuard.size(); i++)
			m_ArrGuard[i]->restartClock();
	while (m_window.isOpen())
	{
		clock.restart();
		while (sig.m_gameRun && (gameDittel.m_timePass < gameDittel.m_time || gameDittel.m_time == -1)
			&& m_player.getLife() > 0)
		{//each time draw all cherectors
			draw();
			if(gameDittel.m_time != -1)//if no limit on time, eximin time 
				gameDittel.m_timePass = clock.getElapsedTime().asSeconds();

			for (size_t i = 0; i < m_ArrBomb.size(); i++)
				m_ArrBomb[i]->Stoper();//if ther is bomb, check if time up -exploed
			
			//player keybord events
			if (m_window.pollEvent(event))
				switch (event.type)
				{//for start movment or actoin
				case sf::Event::KeyPressed:
					m_player.keyPreset(event);
					break;
				//for stop movment
				case sf::Event::KeyReleased:
					m_player.KeyRelease(event);
					break;

				case sf::Event::Closed:
					m_BackgSound.stop();
					m_window.close();
					exit(EXIT_SUCCESS);
					break;
				}
			//player press space - mean he want to restart the level
			if (sig.m_restartLevel)
			{
				sig.m_gameRun = false;
				break;
			}
			//player moovment
			m_player.move();
			//guards moovment							
			for (size_t i = 0; i < m_ArrGuard.size(); i++)
				m_ArrGuard[i]->move();
			//if bomb exploed - delete from arr of bomb
			for (size_t i = 0; i < m_ArrBomb.size(); i++)
			{
				if (m_ArrBomb[i]->exploded())
					m_ArrBomb.erase(m_ArrBomb.begin() + i);
			}
				
		}
		if (sig.m_restartLevel)
		{//if from any reasone need to start the level
			clearCharactersArray();
			int life = m_player.getLife();
			life--;//save the life and update the new player read from file
			m_fileMang.restartReadFromMat();
			m_player.resetLife(life);
			sig.m_restartLevel = false;
			sig.m_gameRun = true;

		}
		if (gameDittel.m_timePass >= gameDittel.m_time  && gameDittel.m_time != -1)
		{//if time finish, and ther is limit on time in the level
			clock.restart();
			gameDittel.m_timePass = clock.getElapsedTime().asSeconds();;
			restartTheLevel();
		}
		//if player life ends - restart the game
		if (m_player.getLife() < 1)
		{//set up correct size of the window-for massage
		    m_openScreen.setUpSizes(m_fileMang.getLevelSize());
			sig.m_gameRun = false;
			clock.restart();
			m_BackgSound.stop();
			m_gameOver.play();
			startEndMassage('G');

			if (m_openScreen.run(m_window))
			{//if true start new game - else close the program
				gameDittel.m_bombNumTemp = 0;
				clearCharactersArray();
				m_fileMang.restartAllGame();
				gameDittel.m_score = 0;
				gameDittel.m_level = 1;
				//set the area be show
				setVisibleArea();
				sig.m_gameRun = true;
			}
			else
				break;//if got here game end program close
		}

	}
	}
}

//----------------------------------------------
//draw all cherectors to the screen
//guards,player, static object,bomb
void GameController::draw()
{

	m_window.clear();
	m_fileMang.drawMap(m_window);
	m_levelDitel.draw(m_window);

	for (size_t place = 0; place < m_statObj.size(); place++)
		m_statObj[place]->draw(m_window);
	
	for (size_t i = 0; i < m_ArrGuard.size(); i++)
		m_ArrGuard[i]->draw(m_window);


	for(size_t i=0;  i < m_ArrBomb.size(); i++)
		m_ArrBomb[i]->draw(m_window);
	
	m_player.draw(m_window);
	m_window.display();
}

//--------------------------------------------
//for gift say gift found
void GameController::setGiftFound()
{
	sig.m_giftFound = true;
}

//--------------------------------------------
//door say player tuch me ,go the next level
void GameController::setTouchDoor()
{
	sig.m_doorTuch = true;
}

//---------------------------------------------
void GameController::setRestartLevel()
{
	sig.m_restartLevel = true;
}

//----------------------------------------------
//for leveldittel for print information to screen
int GameController::getNumOfBombLeft()
{
	return gameDittel.m_bombNumTemp;
}

//------------------------------------------------
//for leveldittel for print information to screen
int GameController::getLife()
{
	return m_player.getLife();
}

//---------------------------------------
void GameController::setBomb(int num)
{
	gameDittel.m_bombNumTemp += num;
	sig.m_arm = true;
	//for know if bomb left 
}

//---------------------------------------------
void GameController::setLife(int num)
{
	m_player.setLife(num);
}

//------------------------------------------------------------
//
bool GameController::can_go_player(const sf::FloatRect & rect)
{
	for (size_t i = 0; i < m_statObj.size(); i++)
	{//save colide
		bool is_colid = m_statObj[i]->collision(rect);

		if (is_colid)
		{//if colision event happand with some obj
			if (sig.m_giftFound)
			{//gift found, need to set it up
				sig.m_giftFound = false;
				m_statObj.erase(m_statObj.begin() + i);
				m_soundGift.play();
			}
			else if (sig.m_doorTuch)
			{//door found, level up
				sig.m_doorTuch = false;	
				clearCharactersArray();
				gameDittel.m_level++;
				gameDittel.m_score = gameDittel.m_score + END_OF_LEVEL;
				m_scoreSound.play();
				
				gameDittel.m_timePass = 0;
				if (gameDittel.m_level == NUM_OF_LEVELS)
				{//no level left, game end with win
					m_BackgSound.stop();
					m_finishGame.play();
					startEndMassage('W');
					exit(EXIT_SUCCESS);
				}
				//make the correct size of window for next level
				m_fileMang.readNextLevel();
				setVisibleArea();		
			}
			//other senrio return that colide happande
			return false;
		}
	}
	//if not colide
	return true;
}

//-----------------------------------------------------------------
bool GameController::can_go_guard(const sf::FloatRect & rect) const
{
	for ( size_t  i = 0; i < m_statObj.size(); i++)
	{
		if (m_statObj[i]->collisionGuard(rect))
			return false;
	}
	return true;
}

//-----------------------------------------------------------------
void GameController::setDoorTuch()
{
	sig.m_doorTuch = true;
}

//-----------------------------------------------------------------
//guard check if cutch the player
const sf::FloatRect GameController::GetPlayerRect()const
{
	return  m_player.getPlayerRect();
}

//------------------------------------------------------------------
//for guard chase the player
const sf::Vector2f GameController::GetPlayerPos() const
{
	return m_player.getPos();
}

//------------------------------------------------------------------
//bomb check who around and kill
void GameController::killThemAll(const sf::FloatRect & rect)
{
	if (m_player.collision(rect))
	{//if bomb cutch the player
		restartTheLevel();
	}
	
	for (size_t place = 0; place < m_ArrGuard.size(); place++)
	{//if bomb cutch the guard
		if (m_ArrGuard[place]->collision(rect))
		{
			m_ArrGuard.erase(m_ArrGuard.begin() + place);
			place--;//array size decrease,means index stay in place
			gameDittel.m_score = gameDittel.m_score + (GUARDDIEPOINTS * gameDittel.m_numOfGuard);
			m_scoreSound.play();
		}
	}

	for (size_t place = 0; place < m_statObj.size(); place++)
	{//if bomb colid with rock kill them- if it other static object do nothing	
		if (m_statObj[place]->collisionBomb(rect))
		{
			m_statObj.erase(m_statObj.begin() + place);
			place--;//array size decrease,means index stay in place
		}
			
	}
	
}

//-------------------------------------------------------
//player wants to add new bomb
void GameController::addBomb(const sf::Vector2f & pos)
{
	int bombLeft = gameDittel.m_bombNumTemp;
	if (bombLeft == -1)//if no limit on bomb at level, create anyway
		createBomb( pos);	
	else
	{//if ther is limit-check if bombe dosent end				
		if (bombLeft > 0) {
			createBomb( pos);			
			gameDittel.m_bombNumTemp--;
			}			
	}
}

//-------------------------------------------------------
void GameController::restartTheLevel()
{
	//if guard cuatch the player he restart the level
	sig.m_gameRun = false;
	restartWitoutMat();
	sig.m_gameRun = true;

}

//----------------------------------------------------------
float GameController::getTimePass()
{
	return (gameDittel.m_time - gameDittel.m_timePass);
}

//----------------------------------------------------------
bool GameController::openScreenRutine()
{//if true game start, else game end program closed
	if(m_openScreen.run(m_window))
		return true;
	else
		return false;
}

//------------------------------------------------------------
//set the new size of window each time level size change
void GameController::setVisibleArea()
{
	m_fileMang.create_background();
	m_levelDitel.setSizeLevel(m_fileMang.getLevelSize());
	m_levelDitel.createToollBar();
	m_window.setSize({ (unsigned)m_fileMang.getLevelSize().x,
		(unsigned)m_fileMang.getLevelSize().y });
	//adjusting the window acording to the new size
	sf::FloatRect visibleArea(0, 0, (float)m_fileMang.getLevelSize().x,
		(float)m_fileMang.getLevelSize().y);
	m_window.setView(sf::View(visibleArea));
}

//---------------------------------------------------------------------
//create all static and dynamic objects
void GameController::createCharacters(sf::Vector2f pos,char c)
{
	int r = 0;
	int gift_type;
			if (c == WALL)
				m_statObj.push_back(std::make_unique<Wall>(pos, m_textures.getTexture(WALL)));
			else if (c == ROCK)
				m_statObj.push_back(std::make_unique<Rock>(pos, m_textures.getTexture(ROCK)));
			else if (c == GUARD)
			{
				r = rand() % 2 + 1;
				//create guard randomize
				if (r == 1)
					m_ArrGuard.push_back(std::make_unique<StupidGuard>
					(pos, m_textures.getTexture(GUARD), *this));
				else
					m_ArrGuard.push_back(std::make_unique<SmartGuard>
					(pos, m_textures.getTexture(GUARD), *this));
				gameDittel.m_numOfGuard++;
			}
			else if (c == BOMBER)
				m_player = Player(pos, m_textures.getTexture(BOMBER), this);
			else if (c == GIFT || c == ROCKGIFT)
			{//create randomize gift
				if (c == GIFT)
					r = 1;
				else {
					r = 2;
				}
				gift_type = rand() % 3 + 1;
				switch (gift_type)
				{
				case 1: //no limit on time creat time gifts
					if (gameDittel.m_time != -1)
					{
						if (r == 1)
							m_statObj.push_back(std::make_unique<GiftTime>(pos, m_textures.getTexture(GIFT), *this));
						else
						{
							m_statObj.push_back(std::make_unique<GiftTime>(pos, m_textures.getTexture(GIFT), *this));
							m_statObj.push_back(std::make_unique<Rock>(pos, m_textures.getTexture(ROCK)));
						}
						break;
					}
				case 2:
					if (gameDittel.m_bombNumInitial != -1)
					{
						if (r == 1)
							m_statObj.push_back(std::make_unique<GiftBomb>(pos, m_textures.getTexture(GIFT), *this));
						else
						{

							m_statObj.push_back(std::make_unique<GiftBomb>(pos, m_textures.getTexture(GIFT), *this));
							m_statObj.push_back(std::make_unique<Rock>(pos, m_textures.getTexture(ROCK)));
						}
						break;
					}
				case 3:
					if (r == 1)
						m_statObj.push_back(std::make_unique<GiftLife>(pos, m_textures.getTexture(GIFT), *this));
					else
					{
						m_statObj.push_back(std::make_unique<GiftLife>(pos, m_textures.getTexture(GIFT), *this));
						m_statObj.push_back(std::make_unique<Rock>(pos, m_textures.getTexture(ROCK)));

					}
					break;
				}
			}
			else if (c == DOOR)
				m_statObj.push_back(std::make_unique<Door>(pos, m_textures.getTexture(DOOR), *this));

		gameDittel.m_bombNumTemp = gameDittel.m_bombNumInitial;
}

//----------------------------------------------------
void GameController::clearCharactersArray()
{
	m_ArrGuard.clear();
	m_statObj.clear();
	m_ArrBomb.clear();
}

//----------------------------------------------------
//if guard catch the player restart withou read from file
void GameController::restartWitoutMat()
{
	for (size_t i = 0; i < m_ArrGuard.size(); i++)
		m_ArrGuard[i]->setPos({ m_ArrGuard[i]->getInitialPos().x, m_ArrGuard[i]->getInitialPos().y });
	m_player.setPos({ m_player.getInitialPos().x, m_player.getInitialPos().y });
	m_player.setLife(-1);
	clock.restart();
}

//-------------------------------------------------------------------------------
void GameController::createBomb( const sf::Vector2f & pos)
{
	m_ArrBomb.push_back(std::make_unique<Bomb>(m_textures.getTexture(BOMB),
		m_textures.getTexture(FLAME), pos, *this));

}

//----------------------------------------------------------------------------------
void GameController::setInitialBomb(int num)
{
	gameDittel.m_bombNumInitial = num;
}

//------------------------------------------------------------------
void GameController::setTime(int num)
{
	gameDittel.m_time = num;
}

//-------------------------------------------------------
void GameController::addTime(int num)
{
	gameDittel.m_time += num;
}

//-------------------------------------------------------
int GameController::getStage()const
{
	return gameDittel.m_level;
}

//-------------------------------------------------------
int GameController::getScore()const
{
	return gameDittel.m_score;
}

//-------------------------------------------------------
int GameController::getLevel()const
{
	return gameDittel.m_level;
}

//-------------------------------------------------------
//if G - game over massage - mean player lost all live
//if not player with the game
void GameController::startEndMassage(char c)
{
	if(c== 'G')
	{
		m_massage.setTexture(m_textures.getTexture(GAMEOVER));
		m_massage.setOrigin(m_massage.getGlobalBounds().width / 2,
			m_massage.getGlobalBounds().height / 2);
		m_massage.setPosition(m_fileMang.getLevelSize().x / 2, m_fileMang.getLevelSize().y / 2);
	}
	else 
	{
		m_massage.setTexture(m_textures.getTexture(WINGAME));
		m_massage.setOrigin(m_massage.getGlobalBounds().width / 2,
			m_massage.getGlobalBounds().height / 2);
		m_massage.setPosition(m_fileMang.getLevelSize().x / 2, m_fileMang.getLevelSize().y / 2);
	}
	clock.restart();
	float time = 0;//make the window of the massage stay few secound
	while (time < 6)
	{
		time = clock.getElapsedTime().asSeconds();
		m_window.clear();
		m_window.draw(m_massage);
		m_window.display();
	}
}
