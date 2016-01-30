#include "stdafx.h"
#include "Player.h"


Player::Player(sf::Vector2f p_position, int p_pNum, sf::Sprite p_spr):
m_position(p_position),
m_pNum(p_pNum),
m_spr(p_spr)
{
	m_spr.setTextureRect(sf::IntRect(0, m_SIZE * m_pNum, m_SIZE, m_SIZE));
	m_spr.setPosition(m_position);
}


void Player::Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle)
{
	m_position.x += p_leftStick.x * p_deltaTime;
	m_spr.setPosition(m_position);
}

sf::Sprite Player::GetSprite()
{
	return m_spr;
}


