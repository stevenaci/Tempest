#include "stdafx.h"
#include "EntityGenerator.h"

using namespace std;

EntityGenerator::EntityGenerator(float origin_x, float origin_y)
{
	m_x = origin_x;
	m_y = origin_y;
}

float EntityGenerator::CheckMissleCollision(float x, float y)
{
	float runningscore = 0.0f;
	vector<Enemy*>::iterator eit = m_enemies.begin();
	for (; eit != m_enemies.end();)
	{
		// Check for a collision, getAge() prevents exploiting enemies that just spawned
		if ((*eit)->getAge() > 10 && Physics::PointCollision((*eit)->getX(), (*eit)->getY(), x, y))
		{
			// Destroy enemy
			(*eit)->setExpired(true);
			// Add the enemies value to the score
			runningscore += (*eit)->getValue();

			if ((*eit)->isExplosive())
			{
				for (auto k : m_enemies)
				{
					// If the enemy is explosive, check radial collisions around it.
					// And destroy colliding enemies/ record points for them.
					if (Physics::RadialCollision((*eit)->getX(), (*eit)->getY(), k->getX(), k->getY(), (*eit)->getExplosiveRange()))
					{
						runningscore += k->getValue();
						App::PlaySound(".\\TestData\\coin2.wav");
						k->setExpired(true);
					}
				}
				//Explosion Sound Effect
				App::PlaySound(".\\TestData\\explosion.wav");
			}
			else {
				// Normal Sound Effect
				App::PlaySound(".\\TestData\\coin1.wav");
			}
		}
		++eit;
	}
	return runningscore;
}

float EntityGenerator::CheckShipCollision(float x, float y)
{
	float runningdamage = 0.0f;
	vector<Enemy*>::iterator eit = m_enemies.begin();
	for (; eit != m_enemies.end();)
	{
		if (Physics::PointCollision((*eit)->getX(), (*eit)->getY(), x, y))
		{
			// Destroy enemy
			(*eit)->setExpired(true);
			// Add the enemy's damage
			runningdamage += (*eit)->getAttack();
			// Play Sound
			App::PlaySound(".\\TestData\\alienscream.wav");
		}
		++eit;
	}
	return runningdamage;
}

void EntityGenerator::Update()
{
	// Update Nested Entities
	for (auto i : m_stars)
		i->Update();

	for (auto i : m_enemies)
		i->Update();

	// Generate New Entities

	// Generate Enemies
	if (m_enemy_cooldown <= 0)
	{
		m_enemy_cooldown = 1 / m_difficulty * 100; // Higher Difficulty means more enemy spawns. 
		m_enemies.push_back(new Enemy(m_x, m_y));
	}
	else m_enemy_cooldown--;


	// Generate Stars
	if (m_star_cooldown <= 0)
	{
		m_star_cooldown = 22;
		// Generate some number of stars in a constellation
		for (int i = rand() % Star::CONSTELLATION_MAX; i > 0; i--)
		{
			int x_mod = rand() % 20;
			int y_mod = rand() % 20;
			m_stars.push_back(new Star(m_x + x_mod, m_y + y_mod));
		}
	}
	else m_star_cooldown--;
}

// Clean up Expired Entities
void EntityGenerator::Clean()
{
	vector<Star*>::iterator sit = m_stars.begin();
	for (; sit != m_stars.end();)
	{
		if ((*sit)->isExpired())
		{
			delete(*sit);
			sit = m_stars.erase(sit);
		}
		else { ++sit; }
	}

	vector<Enemy*>::iterator eit = m_enemies.begin();
	for (; eit != m_enemies.end();)
	{
		if ((*eit)->isExpired())
		{
			delete(*eit);
			eit = m_enemies.erase(eit);
		}
		else { ++eit; }
	}
}

void EntityGenerator::Draw()
{
	for (auto k : m_stars)
	{
		k->Draw();
	}
	for (auto k : m_enemies)
	{
		k->Draw();
	}
}
