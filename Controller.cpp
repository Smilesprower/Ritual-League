#include "stdafx.h"
#include "Controller.h"
#include <SFML\Window\Joystick.hpp>




Controller::Controller(int p_currentController):
m_joypadNum(p_currentController),
m_DEADZONEA(20),
m_DEADZONEB(20)
{
	m_buttonCount = sf::Joystick::getButtonCount(m_joypadNum);
	m_buttons = std::vector<bool>();

	for (int i = 0; i < 10; i++)
	{
		m_buttons.push_back(false);
		m_buttonsPrev.push_back(m_buttons.at(i));
	}
}

Controller::~Controller()
{
}

void Controller::Update()
{

	for (int i = 0; i < m_buttonCount; i++)
	{
		m_buttonsPrev.at(i) = m_buttons.at(i);

		if (sf::Joystick::isButtonPressed(m_joypadNum, i))
			m_buttons.at(i) = true;
		else
			m_buttons.at(i) = false;
	}

	m_leftAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(m_joypadNum, sf::Joystick::X), sf::Joystick::getAxisPosition(m_joypadNum, sf::Joystick::Y));
	m_rightAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(m_joypadNum, sf::Joystick::U), sf::Joystick::getAxisPosition(m_joypadNum, sf::Joystick::R));

	if (m_leftAnalogStick.x > m_DEADZONEA || m_leftAnalogStick.x < -m_DEADZONEA || m_leftAnalogStick.y > m_DEADZONEA || m_leftAnalogStick.y < -m_DEADZONEA)
		m_leftAnalogAngle = atan2(m_leftAnalogStick.y, m_leftAnalogStick.x);
	else
	{
		m_leftAnalogStick = sf::Vector2f(0, 0);
		m_leftAnalogAngle = 0;
	}
}

sf::Vector2f Controller::GetLeftStickAxis()
{
	return m_leftAnalogStick;
}
float Controller::GetLeftStickAngle()
{
	return m_leftAnalogAngle;
}
