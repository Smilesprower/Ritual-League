#include "stdafx.h"
#include "Player.h"
#include <iostream>


Player::Player(sf::Vector2f p_position, int p_pNum, sf::Sprite p_spr) :
m_position(p_position),
m_pNum(p_pNum),
m_spr(p_spr)
{
	m_hasJumped = false;
	m_cState = m_GROUNDRIGHT;
	m_spr.setTextureRect(sf::IntRect(0, m_SIZE * m_pNum, m_SIZE, m_SIZE));
	m_spr.setPosition(m_position);
}

void Player::Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle, std::vector<bool>p_buttons)
{
	// Drawing Purposes
	////////////////////////////////

	m_position += m_velocity;
	m_velocity.x = p_leftStick.x * p_deltaTime * 5;

	if (p_buttons.at(0) && !p_buttons.at(10) && !m_hasJumped)
	{
		m_velocity.y -= 10;
		m_hasJumped = true;
	}

	if (m_hasJumped)
		m_velocity.y += 0.5;
	else if (!m_hasJumped)
		m_velocity.y = 0;

	if (m_position.y > 500)
	{
		m_hasJumped = false;
		m_position.y = 500;
	}

	m_spr.setTextureRect(sf::IntRect(0, m_pNum * 50 + m_pNum, 50, 50));
	m_spr.setPosition(m_position);


	m_prevPosition.y = m_position.y;
}

sf::Sprite Player::GetSprite()
{
	return m_spr;
}


