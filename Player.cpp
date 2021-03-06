#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <list>


Player::Player(sf::Vector2f p_position, int p_pNum, sf::Sprite p_spr) :
m_position(p_position),
m_pNum(p_pNum),
m_spr(p_spr)
{
	m_touchingWall = false;
	m_hasJumped = false;
	m_doubleJump = true;
	m_shoot = true;
	m_fire = false;

	m_spr.setPosition(m_position);
	m_spr.scale(1,1);
	m_counter = 0;
	m_lives = 3;
	if (p_pNum == 0)
		m_yOffset = m_RIGHT;
	else
		m_yOffset = m_LEFT;

	m_xOffset = 0;

}

void Player::Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle, std::vector<bool>p_buttons)
{

	if (!m_shoot)
	{
		m_counter++;
		if (m_counter == 50)
		{
			m_shoot = true;
			m_counter = 0;
		}
	}


	// Drawing Purposes
	////////////////////////////////
	m_position += m_velocity;
	m_collisionBox = sf::IntRect(m_position.x, m_position.y, 30, 36);


	if (p_buttons.at(1) && !p_buttons.at(11) && m_shoot)
	{
		m_shoot = false;
		m_fire = true;
	}


	m_velocity.x = p_leftStick.x * p_deltaTime * 5;
	if (m_velocity.x > 0)
		m_yOffset = 1;
	else if (m_velocity.x < 0)
		m_yOffset = 0;



	if (p_buttons.at(0) && !p_buttons.at(10) && m_doubleJump && m_touchingWall && m_hasJumped && m_prevPosition.y >= m_position.y)
	{
		m_velocity.y -= 10;
		m_hasJumped = true;
		m_doubleJump = false;
	}



	if (p_buttons.at(0) && !p_buttons.at(10) && !m_hasJumped)
	{
		m_velocity.y -= 10;
		m_hasJumped = true;
		m_xOffset = 1;

		//std::list<int> x;
	}


	if (m_hasJumped)
		m_velocity.y += 0.5;
	else if (!m_hasJumped)
		m_velocity.y = 0;

	if (m_position.y > 450)
	{
		m_hasJumped = false;
		m_position.y = 450;
		m_doubleJump = true;
		m_xOffset = 0;
	}

	if (m_position.x < m_WALLSIZEA)
	{
		m_position.x = m_WALLSIZEA;
		m_touchingWall = true;
	}
	else if (m_position.x + 30 > m_WALLSIZEB)
	{
		m_position.x = m_WALLSIZEB - 30;
		m_touchingWall = true;
	}
	else if (m_position.x  < m_WALLSIZEB - 30 || m_position.x + 30 > m_WALLSIZEA)
		m_touchingWall = false;

	m_spr.setTextureRect(sf::IntRect(m_xOffset * 30 + m_xOffset, m_yOffset * 36 + m_yOffset, 30, 36));
	m_spr.setPosition(m_position);

	m_prevPosition.y = m_position.y;
}

sf::Sprite Player::GetSprite()
{
	return m_spr;
}

sf::IntRect Player::GetCollision()
{
	return m_collisionBox;
}

void Player::setPosition(float p_positionX)
{
	m_position.x = p_positionX;
	m_spr.setPosition(m_position.x, m_position.y);
}

bool Player::GetFire()
{
	return m_fire;
}


void Player::SetFire(bool p_fire)
{
	m_fire = p_fire;
}

bool Player::GetLives()
{
	return m_lives;
}

void Player::SetLives(int p_lives)
{
	m_lives = p_lives;
}

