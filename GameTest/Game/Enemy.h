#pragma once

#include <string>
#include "Physics.h"
#include "app.h"
using namespace std;

class Enemy
{
private:
	float m_r = 0.0f;
	float m_b = 0.0f;
	float m_g = 0.0f;
	float m_x;
	float m_y;
	float m_tar_x;
	float m_tar_y;
	float m_speed = 0.003f;
	bool m_expired = false;
	string m_team;
	float m_age = 0.0f;
	float m_maxAge = 200.0f;
	float m_value = 0.0f;
	float m_attack = 10.0f;
	char* m_char;
	bool m_explosive = false;
	float m_explosive_range = 100.0f;
	float m_explosion_indicator_cooldown = 0.0f;

public:
	Enemy(float origin_x, float origin_y);
	void Update();
	void Draw();
	bool isExpired() { return m_expired; }
	bool isExplosive() { return m_explosive; }
	string getTeam() { return m_team; }
	float getX() { return m_x; }
	float getY() { return m_y; }
	void setExpired(bool b) { m_expired = b; }
	float getValue() { return m_value; }
	float getAttack() { return m_attack; }
	float getAge() { return m_age; }
	float getExplosiveRange() { return m_explosive_range; }
	~Enemy();
};

