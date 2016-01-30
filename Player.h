#pragma once
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Vector2.hpp"


class Player
{
public:
	Player(sf::Vector2f p_position, int p_num, sf::Sprite p_spr);
	void Update(float p_deltaTime, sf::Vector2f p_leftStick, float leftStickAngle, std::vector<bool>p_buttons);
	sf::Sprite GetSprite();
	sf::IntRect GetCollision();
	void setPosition(float p_positionX);
	bool GetFire();
	void SetFire(bool p_fire);

	bool GetLives();
	void SetLives(int p_lives);


private:
	sf::Sprite m_spr;
	sf::Vector2f m_velocity, m_position, m_prevPosition;
	sf::IntRect m_collisionBox;

	bool m_hasJumped;
	const int m_WALLSIZEA = 104;
	const int m_WALLSIZEB = 696;
	const int m_GROUNDLEFT = 0, m_GROUNDRIGHT = 1, m_JUMPING = 2, m_FALLING = 3;
	const int m_SIZE = 50;
	int m_cState;
	int m_pNum;
	const int m_OFFSETBUTTONS = 10;
	bool m_doubleJump;
	bool m_touchingWall;

	int m_counter;
	bool m_fire;
	bool m_shoot;
	int m_lives;

};

