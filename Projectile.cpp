#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(sf::Vector2f p_pos, float p_vel, sf::Sprite p_spr, int p_rand, int playerNum):
m_position(p_pos),
m_spr(p_spr),
m_playerNum(playerNum)
{
	m_velocity.x = p_vel;
	m_spr.setPosition(m_position);
	m_spr.setTextureRect(sf::IntRect(p_rand * 44 + p_rand, 0, 44, 48));

}


Projectile::~Projectile()
{
}

sf::IntRect Projectile::GetCollisionBox()
{
	return m_collisionBox;
}

int Projectile::GetPlayerNum()
{
	return m_playerNum;
}

void Projectile::Update(float p_delta)
{
	m_collisionBox = sf::IntRect(m_position.x, m_position.y, 48, 48);

	m_position += m_velocity;
	m_spr.setPosition(m_position);

	m_velocity.y += 0.2;

}

sf::Sprite Projectile::GetSprite()
{
	return m_spr;
}
