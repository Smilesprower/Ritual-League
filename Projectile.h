#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include "SFML\System\Vector2.hpp"
#include <SFML\Graphics\Rect.hpp>
class Projectile
{
public:
	Projectile(sf::Vector2f p_pos, float p_vel, sf::Sprite p_spr, int p_rand, int playerNum);
	~Projectile();

	sf::IntRect GetCollisionBox();
	int GetPlayerNum();
	void Update(float p_delta);
	sf::Sprite GetSprite();



private:
	sf::Sprite m_spr;
	sf::Vector2f m_velocity, m_position, m_direction;
	sf::IntRect m_collisionBox;
	int m_playerNum;
};

