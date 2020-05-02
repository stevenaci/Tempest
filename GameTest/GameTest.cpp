//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "Ship.h"
#include <vector>
#include "Star.h"
#include "EntityGenerator.h"
#include <sstream>
//------------------------------------------------------------------------

Ship *ship;
EntityGenerator *generator;

enum {
	STATE_INTRO,
	STATE_GAME,
	STATE_OUTRO
};

int m_state = 0;
float last_score = 0.0f;
float level = 0.0f;
stringstream ss;

const float MID_X = APP_VIRTUAL_WIDTH / 2;
const float MID_Y = APP_VIRTUAL_HEIGHT / 2;
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// Set the game state
	m_state = STATE_GAME;

	level = 0.0f;
	last_score = 0.0f;
	generator = new EntityGenerator(MID_X, MID_Y);
	ship = new Ship(MID_X, MID_Y, 50.0f, generator);

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if(m_state == STATE_GAME){
		
		// Update Game Objects
		generator->Update();
		generator->Clean();
		ship->Update();

		// Check Controls
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
		{
			ship->AdjustSize(-10);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
		{
			ship->Rotate(-0.5);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
		{
			ship->Rotate(0.5);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
		{
			ship->AdjustSize(10);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false))
		{
			ship->Attack();
		}

		//  Increase difficulty of the EntityGenerator,
		//  After so many points.
		if (last_score + 30000.0f < ship->getScore())
		{
			last_score += 30000.0f;
			// Increment Current Level
			level++;
			// Adjust difficulty
			generator->adjustDifficulty(3);
			App::PlaySound(".\\TestData\\levelup.wav");
		}

		// Check if Player is Defeated
		if (ship->isDefeated())
			m_state = STATE_OUTRO;
	}
	if (m_state == STATE_OUTRO)
	{
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, false))
		{
			// Free Pointers
			delete ship;
			delete generator;
			// Restart this Game
			Init();
		}
	}
}

void Render()
{
	// Clear "HUD" Stringstream
	ss.str("");
	if(m_state == STATE_GAME)
	{
		// Score Display
		ss << "SCORE : ";
		ss << ship->getScore();
		App::Print(50, 100, ss.str().c_str(), 0.5f, 0.5f,0.2f);


		// Health Display
		ss.str("");
		ss << "HEALTH : ";
		ss << ship->getHealth();

		// Health is Red when in Warning
		if (ship->isWarning()) App::Print(APP_VIRTUAL_WIDTH - 200, 100, ss.str().c_str(), 1.0f, 0.1f, 0.2f);
		else App::Print(APP_VIRTUAL_WIDTH - 200, 100, ss.str().c_str(), 0.5f, 0.5f, 0.2f);

		// Level Display
		ss.str("");
		ss << "LEVEL : ";
		ss << level;
		App::Print(MID_X - 40, 10, ss.str().c_str(), 0.5f, 0.5f, 0.2f);

		// Display game objects
		generator->Draw();
		ship->Draw();
	}
	else if(m_state == STATE_OUTRO)
	{
		// End Screen

		// Display Level
		ss << "LEVEL REACHED : ";
		ss << level;
		App::Print(MID_X -30 , MID_Y, ss.str().c_str(), 0.5f, 0.5f, 0.2f);

		// Display Score
		ss.str("");
		ss << "FINAL SCORE : ";
		ss << ship->getScore();
		App::Print(MID_X - 30, MID_Y + 30, ss.str().c_str(), 0.5f, 0.5f, 0.2f);

		ss.str("");
		ss << "Press Insert key to Play Again";
		App::Print(MID_X - 30, MID_Y + 60, ss.str().c_str(), 0.5f, 0.5f, 0.9f);
	}
}

// Called before app exits
void Shutdown()
{	
	// Free our pointers
	delete ship;
	delete generator;

}