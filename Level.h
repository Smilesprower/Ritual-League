#pragma once
#include <vector>
#include <SFML\Graphics\Rect.hpp>
#include "SFML\Graphics\Sprite.hpp"
class Level
{
public:
	Level();
	~Level();

	void Init(sf::Sprite p_spr);
	std::vector<sf::IntRect> GetCollision();
	sf::Sprite GetSprite();

private:
	std::vector<sf::IntRect> m_collisionRect;
	sf::Sprite m_spr;
};

