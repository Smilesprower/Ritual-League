//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "P1Controls.h"
#include "P2Controls.h"

sf::Time deltaTime;
sf::Clock myClock;

sf::Texture tex;
sf::Sprite spr;

sf::Text text1, text2;


// Game Modes
//////////////////
const byte MAINMENU = 0, GAME = 1, OPTIONS = 2, SCORE = 3, GAMEOVER = 4, DISCONNECTED = 5;
byte gameMode = MAINMENU;



void Init()
{

}

void LoadContent()
{
	// Load shtuff
}



void UpdateMainMenu()
{
		text1.setString(std::to_string(P1Controls::Instance().m_leftAnalogAngle));
		text2.setString(std::to_string(P2Controls::Instance().m_leftAnalogAngle));
}
void UpdateGame()
{

}
void UpdateGameOver()
{

}
void Update()
{
	deltaTime = myClock.getElapsedTime();
	myClock.restart();


	P1Controls::Instance().Update();
	P2Controls::Instance().Update();
	// Update Game Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		UpdateMainMenu();
		break;
	case GAME:
		UpdateGame();
		break;
	case GAMEOVER:
		UpdateGameOver();
		break;
	}
}

void(DrawMainMenu(sf::RenderWindow &p_window))
{
	p_window.draw(spr);
	p_window.draw(text1);
	p_window.draw(text2);
}
void(DrawGame(sf::RenderWindow &p_window))
{
}
void(DrawGameOver(sf::RenderWindow &p_window))
{

}

void Draw(sf::RenderWindow &p_window)
{
	// Clear Window
	p_window.clear();

	// Update Draw Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		DrawMainMenu(p_window);
		break;
	case GAME:
		DrawGame(p_window);
		break;
	case GAMEOVER:
		DrawGameOver(p_window);
		break;
	}

	// Display Window
	p_window.display();
}

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");


	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	////create a formatted text string
	text1.setFont(font);
	text1.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text1.setPosition(20, 40);
	text1.setCharacterSize(20);

	text2.setFont(font);
	text2.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text2.setPosition(200, 40);
	text2.setCharacterSize(20);



	// Initialize
	/////////////////////////////
	Init();


	// Start game loop 
	while (window.isOpen())
	{

		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		// Update World, Events, Game
		/////////////////////////////
		Update();

		// Draw World, Events, Game
		/////////////////////////////
		Draw(window);

	} //loop back for next frame

	return EXIT_SUCCESS;
}
