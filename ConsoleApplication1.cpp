/*
This game is built for fun in a rushed enviroment
No effort at all was giving 

*/










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
#include "Controller.h"
#include "Player.h"
#include "Level.h"
#include "Projectile.h"

std::vector<Player> players;
Level level;
sf::Time deltaTime;
sf::Clock myClock;
sf::Text text1, text2;
std::vector<Controller> controllers;
std::vector<Projectile> projectiles;

sf::Texture tex, texLevel, proTex, livesTex;
sf::Sprite spr, sprLevel, proSpr, heartSpr;


std::vector<sf::Sprite> pOneHearts;
std::vector<sf::Sprite> pTwoHearts;

bool playerOneWins = false;
bool playerTwoWins = false;
int pOneLives = 3;
int pTwoLives = 3;

const int MAX = 2;

// Game Modes
//////////////////
const byte MAINMENU = 0, GAME = 1, OPTIONS = 2, SCORE = 3, GAMEOVER = 4, DISCONNECTED = 5;
byte gameMode = GAME;



void Init()
{
	tex.loadFromFile("resources/player.png");
	tex.setSmooth(true);
	spr.setTexture(tex);

	texLevel.loadFromFile("resources/level.png");
	texLevel.setSmooth(true);
	sprLevel.setTexture(texLevel);

	proTex.loadFromFile("resources/proj.png");
	proTex.setSmooth(true);
	proSpr.setTexture(proTex);

	livesTex.loadFromFile("resources/hearts.png");
	livesTex.setSmooth(true);
	heartSpr.setTexture(livesTex);

	for (int i = 0; i < 3; i++)
	{

		heartSpr.setPosition(sf::Vector2f(50 * i + 50, 50));
		heartSpr.setTextureRect(sf::IntRect(0, 0, 50, 40));
		pOneHearts.push_back(heartSpr);

		heartSpr.setPosition(sf::Vector2f(50 * i + 600, 50));
		heartSpr.setTextureRect(sf::IntRect(0, 0, 50, 40));
		pTwoHearts.push_back(heartSpr);

	}


	// Vector of Controllers and Players
	////////////////////////////
	for (int i = 0; i < MAX; i++)
	{
		controllers.push_back(i);
		Player player(sf::Vector2f(i * 450 + 150, 450), i, spr);
		players.push_back(player);
	}

	level.Init(sprLevel);


}

void LoadContent()
{
	// Load shtuff
}



void UpdateMainMenu()
{





}


void UpdateGame()
{
	if (players.at(0).GetFire())
	{
		sf::Vector2f pos = players.at(0).GetSprite().getPosition();
		pos.x += 13;
		float velX = controllers.at(0).GetLeftStickAxis().x * 0.08;
		Projectile projectile(pos, velX, proSpr, rand() % 4 , 0);
		projectiles.push_back(projectile);
		players.at(0).SetFire(false);
	}
	if (players.at(1).GetFire())
	{
		sf::Vector2f pos = players.at(1).GetSprite().getPosition();
		pos.x += 13;
		float velX = controllers.at(1).GetLeftStickAxis().x * 0.08;
		Projectile projectile(pos, velX, proSpr, rand() % 4, 1);
		projectiles.push_back(projectile);
		players.at(1).SetFire(false);
	}


	for (int i = 0; i < MAX; i++)
		controllers.at(i).Update();

	players.at(0).Update(deltaTime.asSeconds(), controllers.at(0).GetLeftStickAxis(), controllers.at(0).GetLeftStickAngle(), controllers.at(0).GetButtonsOne());
	players.at(1).Update(deltaTime.asSeconds(), controllers.at(1).GetLeftStickAxis(), controllers.at(1).GetLeftStickAngle(), controllers.at(1).GetButtonsTwo());


	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i).Update(deltaTime.asSeconds());


		// Remove Vector
		/////////////////////
		if (projectiles.at(i).GetCollisionBox().left < -50 || projectiles.at(i).GetCollisionBox().left > 850 || projectiles.at(i).GetCollisionBox().height > 650)
			projectiles.erase(projectiles.begin() + i);

		// Check Collision P1
		/////////////////////
		else if (projectiles.at(i).GetCollisionBox().intersects(players.at(0).GetCollision()) && projectiles.at(i).GetPlayerNum() != 0)
		{
			pOneLives--;
			if (pOneLives == 0)
			{
				gameMode = GAMEOVER;
				playerTwoWins = true;
			}
			else
				pOneHearts.at(pOneLives).setTextureRect(sf::IntRect(51, 0, 50, 40));
			projectiles.erase(projectiles.begin() + i);
		}
		// Check Collision P2
		/////////////////////
		else if (projectiles.at(i).GetCollisionBox().intersects(players.at(1).GetCollision()) && projectiles.at(i).GetPlayerNum() != 1)
		{
			pTwoLives--;
			if (pTwoLives == 0)
			{
				gameMode = GAMEOVER;
				playerTwoWins = true;
			}
			else
				pTwoHearts.at(pTwoLives).setTextureRect(sf::IntRect(51, 0, 50, 40));
			projectiles.erase(projectiles.begin() + i);
		}
	}
}


void CheckCollisions(int p_currentProj, int playerNum)
{
	// Check Collision
	/////////////////////
	if (projectiles.at(p_currentProj).GetCollisionBox().intersects(players.at(playerNum).GetCollision()) && projectiles.at(p_currentProj).GetPlayerNum() != 0)
	{
		int lives = players.at(playerNum).GetLives();
		players.at(playerNum).SetLives(lives - 1);
		if (players.at(playerNum).GetLives() < 0)
		{
			gameMode = GAMEOVER;
			playerTwoWins = true;
		}
		else if (playerNum == 0)
			pOneHearts.at(lives).setTextureRect(sf::IntRect(51, 0, 50, 40));
		else if (playerNum == 1)
			pTwoHearts.at(lives).setTextureRect(sf::IntRect(51, 0, 50, 40));

		projectiles.erase(projectiles.begin() + p_currentProj);
	}
}


void UpdateGameOver()
{

}
void Update()
{
	deltaTime = myClock.getElapsedTime();
	myClock.restart();

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
}
void(DrawGame(sf::RenderWindow &p_window))
{
	p_window.draw(level.GetSprite());


	for (int i = 0; i < 3; i++)
	{
		p_window.draw(pOneHearts.at(i));
		p_window.draw(pTwoHearts.at(i));
	}


	for (int i = 0; i < MAX; i++)
		p_window.draw(players.at(i).GetSprite());

	for (int i = 0; i < projectiles.size(); i++)
		p_window.draw(projectiles.at(i).GetSprite());




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

	window.setVerticalSyncEnabled(true);
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
