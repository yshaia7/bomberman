#include "SmartGuard.h"
#include "GameController.h"
#include <cstdlib>
#include <cmath>

//-----------------------------------------------------------------
void SmartGuard::move()
{
	if (catchPlayer())
		kill_robot();

	//look for the player pos for chase hem
	m_playerPos = m_ctrl.GetPlayerPos();

	//calc time
	m_distance = m_clock.getElapsedTime().asSeconds() * m_speed;
	m_lastMove = m_pos;

	float delta_x = (m_playerPos.x - m_pos.x),
		delta_y = m_playerPos.y - m_pos.y;

	if (abs(delta_x) > abs(delta_y))
		m_nextDirection = width;
	else
		m_nextDirection = hight;

	switch (m_nextDirection)
	{
	case(width):
	{//if length from player in x line > y line  go at x
		if ((delta_x) > 0.5)
		{
			m_pos.x = m_pos.x + m_distance;
			m_nextDirection = Right;
			}
		else
		{

			m_pos.x = m_pos.x - m_distance;
			m_nextDirection = left;
		}
		break;
	}
	case(hight):
		if (delta_y > 0.5)
		{//if length from player in y line > x line  go at y
			m_nextDirection = Down;
			m_pos.y = m_pos.y + m_distance;
		}
		else
		{
			m_nextDirection = Up;
			m_pos.y = m_pos.y - m_distance;
		}

	}

	m_clock.restart();
	m_pic.setPosition(m_pos);

	switchAnimation();//switch animation
	if(!canMove())//if cannot go - stay in place
	{
		m_colide = true;
		m_pic.setPosition(m_lastMove);
		m_pos = m_lastMove;
	}

}



