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
	m_cState = m_GROUNDRIGHT;
	m_spr.setTextureRect(sf::IntRect(0, m_SIZE * m_pNum, m_SIZE, m_SIZE));
	m_spr.setPosition(m_position);
}

void Player::Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle, std::vector<bool>p_buttons)
{
	// Drawing Purposes
	////////////////////////////////
	m_position += m_velocity;
	m_collisionBox = sf::IntRect(m_position.x, m_position.y, m_SIZE, m_SIZE);


	m_velocity.x = p_leftStick.x * p_deltaTime * 5;

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
	}

	if (m_position.x < m_WALLSIZEA)
	{
		m_position.x = m_WALLSIZEA;
		m_touchingWall = true;
	}
	else if (m_position.x + m_SIZE > m_WALLSIZEB)
	{
		m_position.x = m_WALLSIZEB - m_SIZE;
		m_touchingWall = true;
	}
	else if (m_position.x < m_WALLSIZEB - m_SIZE || m_position.x > m_WALLSIZEA)
		m_touchingWall = false;

	m_spr.setTextureRect(sf::IntRect(0, m_pNum * m_SIZE + m_pNum, m_SIZE, m_SIZE));
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

