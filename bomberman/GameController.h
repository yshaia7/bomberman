
#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObj.h"
#include <memory>
#include "Player.h"
#include "Guard.h"
#include "MapManager.h"
#include "Bomb.h"
#include "LevelDittels.h"
#include "OpenScreen.h"

class bomb;

struct GameDittels {
	int m_bombNumTemp=0;
	int m_numOfGuard = 0;
	int m_bombNumInitial = 0;
	int m_time=0;
	int m_score = 0;
	int m_level = 0;
	float m_timePass = 0;
};

struct signal {
	bool m_doorTuch=false;
	bool m_gameRun=true;
	bool m_giftFound=false;
	bool m_restartLevel=false;
	bool m_arm=true;
};

class GameController {
public:
	GameController();
	void reloadDittels();
	~GameController();
	void run();
	bool can_go_player(const sf::FloatRect & rect);
	bool can_go_guard(const sf::FloatRect & rect)const;
	const sf::FloatRect GetPlayerRect()const;
	const sf::Vector2f GetPlayerPos()const;
	void killThemAll(const sf::FloatRect & rect);
	void addBomb(const sf::Vector2f & pos);
	void setDoorTuch();
	void setLife(int num);
	void setBomb(int num);
	void setTime(int num);
	void addTime(int num);
	int getStage() const;
	int getScore() const;
	int getLevel() const;
	void startEndMassage(char c);
	void createBomb( const sf::Vector2f & pos);
	void setGiftFound();
	void setTouchDoor();
	void setRestartLevel();
	int getNumOfBombLeft();
	int getLife();
	void restartTheLevel();	
	float getTimePass();
	void createCharacters(sf::Vector2f pos, char c);
	void setInitialBomb(int num);
	
	
private:
	sf::SoundBuffer m_soundBuff;
	sf::Sound m_soundGift;
	GameDittels gameDittel;
	sf::Sprite m_massage;
	signal sig;
	Source  m_textures;
	OpenScreen  m_openScreen;
	sf::RenderWindow m_window;
	Player m_player;
	std::vector<std::unique_ptr<Guard>> m_ArrGuard;
	std::vector<std::unique_ptr<StaticObj >> m_statObj;
	std::vector<std::unique_ptr<Bomb>> m_ArrBomb;
	MapManager m_fileMang;
	void draw();
	LevelDittels m_levelDitel;
	sf::Clock clock;
	bool openScreenRutine();
	void clearCharactersArray();
	void setVisibleArea();
	void restartWitoutMat();
	sf::SoundBuffer m_SoundBuff;
	sf::Sound m_BackgSound;
	sf::SoundBuffer m_scoreBuff;
	sf::Sound m_scoreSound;
	sf::Sound m_finishGame;
	sf::SoundBuffer m_finishBuff;
	sf::Sound m_gameOver;
	sf::SoundBuffer m_gameOverBuff;
	
	//---------------------
};