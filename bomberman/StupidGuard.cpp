#include "StupidGuard.h"
#include "GameController.h"

#include <Windows.h>

//---------------------------------------------------------------
void StupidGuard::move()
{
	if (catchPlayer())
		kill_robot();

	//for how much pixel move
	m_distance = m_clock.getElapsedTime().asSeconds() * m_speed;
	m_lastMove = m_pos;

	if(m_colide)
	{//if cant moov, random new direction
		m_nextDirection = rand() % 4;
		m_colide = false;

	}
		switch (m_nextDirection)
		{//chose next direction
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

	
	m_clock.restart();
	m_pic.setPosition(m_pos);
	
	//choose next inmation each direction go
	switchAnimation();

			if (!canMove())
			{//last move be the next move, mean stay in place
				m_colide = true;
				m_pic.setPosition(m_lastMove);
				m_pos = m_lastMove;
			}
	
}
