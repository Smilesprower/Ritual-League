#pragma once
#include <SFML\System\Vector2.hpp>
#include <vector>


class Controller
{
public:
	//Controller();
	~Controller();


	Controller(int p_currentController);
	void Update();
	sf::Vector2f GetLeftStickAxis();
	float GetLeftStickAngle();

private:

	sf::Vector2f m_leftAnalogStick, m_rightAnalogStick;
	float m_leftAnalogAngle, m_rightAnalogAngle;
	std::vector<bool>m_buttons;
	std::vector<bool>m_buttonsPrev;
	int m_DEADZONEA, m_DEADZONEB;
	int m_buttonCount;
	bool m_leftStickEnabled;
	bool m_rightStickEnabled;
	int m_joypadNum;
};

