#pragma once
#include <vector>
#include "Enemy.h"
#include "Physics.h"
#include "Star.h"
#include <vector>

using namespace std;
class EntityGenerator
{
private:
	vector<Star*> m_stars;
	vector<Enemy*> m_enemies;
	float m_x;
	float m_y;
	float m_star_cooldown = 0.0f;
	float m_enemy_cooldown = 0.0f;
	float m_difficulty = 15.0f;

public:
	EntityGenerator(float origin_x, float origin_y);
	float CheckMissleCollision(float x, float y);
	float CheckShipCollision(float x, float y);
	void Update();
	void Draw();
	void Clean();
	void adjustDifficulty(float difficulty) { m_difficulty += difficulty; };
};

