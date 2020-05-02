#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(float origin_x, float origin_y)
{
	m_x = origin_x;
	m_y = origin_y;

	// Choose a wall to lock to.
	int wall = rand() % 4;
	switch (wall)
	{
	case 0:
		// lock to top
		m_tar_y = 0;
		m_tar_x = rand() % APP_VIRTUAL_WIDTH;
		break;
	case 1:
		// lock to bottom
		m_tar_y = APP_VIRTUAL_HEIGHT;
		m_tar_x = rand() % APP_VIRTUAL_WIDTH;
		break;
	case 2:
		// lock to left
		m_tar_x = 0;
		m_tar_y = rand() % APP_VIRTUAL_HEIGHT;
		break;
	case 3:
		// lock to right
		m_tar_x = APP_VIRTUAL_WIDTH;
		m_tar_y = rand() % APP_VIRTUAL_HEIGHT;
		break;
	}

	int type = rand() % 4;
	m_char = new char[2];
	switch (type)
	{
	case 0:
		m_team = "Blue";
		m_r = 0.0f;
		m_g = 0.0f;
		m_b = 1.0f;
		m_value = 100.0f;
		strcpy(m_char,"*");
		break;
	case 1:
		m_team = "Yellow";
		m_r = 1.0f;
		m_g = 1.0f;
		m_b = 0.0f;
		m_value = 200.0f;
		strcpy(m_char, "*");
		break;
	case 2:
		m_team = "Green";
		m_r = 0.0f;
		m_g = 1.0f;
		m_b = 0.3f;
		strcpy(m_char, "*");
		m_value = 500.0f;
		break;
	case 3:
		m_team = "Pink";
		m_r = 1.0f;
		m_g = 0.1f;
		m_b = 0.4f;
		m_value = 1500.0f;
		strcpy(m_char, "*");
		break;
	}
	m_explosive = !(rand() % 2);
	m_speed = 0.003f * (rand() % 5 + 1);

}

void Enemy::Update()
{
	m_age += 1;
	if(m_explosive)
		m_explosion_indicator_cooldown--;
	m_y = Physics::LerpPoint(m_y, m_tar_y, m_speed);
	m_x = Physics::LerpPoint(m_x, m_tar_x, m_speed);

	if (m_age >= m_maxAge)
		m_expired = true;
}

void Enemy::Draw()
{

	// Explosive Enemies will flash red ..
	if (m_explosive && m_explosion_indicator_cooldown <= 0) {
		App::Print(m_x, m_y, m_char, 1.0f, 0.0f, 0.0f);
		// ...for 8 frames
		if (m_explosion_indicator_cooldown <= -8)
			m_explosion_indicator_cooldown = 8;
	}
	else {
		App::Print(m_x, m_y, m_char, m_r, m_g, m_b);
	}
}

Enemy::~Enemy() {
	delete[] m_char;
}