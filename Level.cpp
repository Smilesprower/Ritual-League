#include "stdafx.h"
#include "Level.h"

Level::Level()
{

}


Level::~Level()
{
}

std::vector<sf::IntRect> Level::GetCollision()
{
	return m_collisionRect;
}
sf::Sprite Level::GetSprite()
{
	return m_spr;
}

void Level::Init(sf::Sprite p_spr)
{

	m_spr = p_spr;
}
