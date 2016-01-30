#pragma once
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Vector2.hpp"


class Player
{
public:
	Player(sf::Vector2f p_position, int p_num, sf::Sprite p_spr);
	void Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle);
	sf::Sprite GetSprite();

private:
	sf::Sprite m_spr;
	sf::Vector2f m_velocity, m_position;


	const int m_GROUND = 0, m_JUMPING = 1, m_FALLING = 2;
	const int m_SIZE = 50;
	int m_cState;
	int m_pNum;


};

