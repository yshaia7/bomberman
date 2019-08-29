
#include "Player.h"
#include "GameController.h"

//----------------
Player::Player()
{
}

//------------------------------------------------------
Player::Player(sf::Vector2f &pos, sf::Texture &tex,
	GameController *crtl)
	: DynamObj(pos, tex),
	m_life(3), m_ctrl(crtl)
{
	setUp();
	m_pic.setOrigin(0.f, 0.f);//set defult origin for spritsheet
	m_clock.restart();
}

//------------------------------------------------------
void Player::setUp()
{
	m_speed = 90;
	m_nextDirection = Stand;
	m_lastMove = m_pos;
}

//------------------------------------------------------
//for colision
const sf::FloatRect Player::getPlayerRect() const
{
	return m_pic.getGlobalBounds();
}

//------------------------------------------------------
void Player::setLife(int num)
{
	m_life += num;
}

//------------------------------------------------------
void Player::resetLife(int num)
{
	m_life = num;
}
//------------------------------------------------------
int Player::getLife()const
{
	return m_life;
}

//------------------------------------------------------
bool Player::collision(const sf::FloatRect & rect)const
{
	return m_pic.getGlobalBounds().intersects(rect);
}

//-----------------
void Player::move()
{
	//calc distance will move
	m_distance = m_clock.getElapsedTime().asSeconds() * m_speed;
	m_lastMove = m_pos;


	if (m_nextDirection != Stand )
	{//if can move to next direction
		switch (m_nextDirection)
		{
		case Up:
			m_pos.y = m_pos.y - m_distance;
			break;
		case Down:
			m_pos.y = m_pos.y + m_distance;
			break;
		case Right:
			m_pos.x = m_pos.x + m_distance;
			break;
		case left:
			m_pos.x = m_pos.x - m_distance;
			break;
		}
		//choose next inmation for next direction
		switchAnimation();
	
	}

	m_clock.restart();
	m_pic.setPosition(m_pos);

	//if cannot go, pos = last pos
	if (m_nextDirection != Stand &&
		(!m_ctrl->can_go_player(m_pic.getGlobalBounds())))
	{
		m_pic.setPosition(m_lastMove);
		m_pos = m_lastMove;
	}
}

//-------------------------------------------------------------
void Player::keyPreset(sf::Event &keypres)
{

	if (keypres.key.code == sf::Keyboard::Left)
		m_nextDirection = left;
	else if (keypres.key.code == sf::Keyboard::Right)
		m_nextDirection = Right;
	else if (keypres.key.code == sf::Keyboard::Up)
		m_nextDirection = Up;
	else if (keypres.key.code == sf::Keyboard::Down)
		m_nextDirection = Down;
	else if (keypres.key.code == sf::Keyboard::B)
		m_ctrl->addBomb( m_pos);//put bomb
	
	else if (keypres.key.code == sf::Keyboard::Space)
	{//if press space- restart the level decreas life
		m_ctrl->setRestartLevel();
	}

}

//--------------------------------------------------
void Player::KeyRelease(sf::Event &KeyRels)
{//make the player stay in place
	if (KeyRels.key.code == sf::Keyboard::Left ||
		KeyRels.key.code == sf::Keyboard::Right ||
		KeyRels.key.code == sf::Keyboard::Up ||
		KeyRels.key.code == sf::Keyboard::Down)
		m_nextDirection = Stand;

}


