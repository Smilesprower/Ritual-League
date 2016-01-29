#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Time.hpp"
#include <vector>
class P1Controls
{
public:

	const int m_DEADZONEA, m_DEADZONEB;
	bool m_leftStickEnabled;
	bool m_rightStickEnabled;
	bool m_rightBumperPressed, m_leftBumperPressed, m_anyKeyPressed;
	sf::Vector2f m_leftAnalogStick, m_rightAnalogStick, m_leftAnalogStickPrev;
	float m_leftAnalogAngle, m_rightAnalogAngle;
	void Update();
	sf::Vector2f GetLeftStickAxis();
	sf::Vector2f GetRightStickAxis();
	static P1Controls& Instance();
	int m_counter;
	int m_buttonCount;
	std::vector<bool>m_buttons;
	std::vector<bool>m_buttonsPrev;
	bool m_isControllerConnected;

	bool CheckIfControllerIsConnected();

private:
	P1Controls();
};


