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
	std::vector<bool>GetButtonsOne();
	std::vector<bool>GetButtonsTwo();
	float GetLeftStickAngle();

private:

	sf::Vector2f m_leftAnalogStick, m_rightAnalogStick;
	float m_leftAnalogAngle, m_rightAnalogAngle;
	std::vector<bool>m_buttonsOne;
	std::vector<bool>m_buttonsTwo;
	int offset = 10;
	int m_DEADZONEA, m_DEADZONEB;
	int m_buttonCount;
	bool m_leftStickEnabled;
	bool m_rightStickEnabled;
	int m_joypadNum;
};

