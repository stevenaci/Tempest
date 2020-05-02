#include "stdafx.h"
#include "Star.h"

Star::Star(float origin_x,float origin_y) 
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
	m_brightness = float(rand() % 5);
	m_speed = float(rand() % 10) / 1000;
	m_r = 0.1f * m_brightness;
	m_g = 0.1f * m_brightness;
	m_b = 0.1f * m_brightness;
}

void Star::Update()
{
	m_age += 1;
	if (m_age > 70) {
		m_g = 0.50f;
		m_r = 0.20f;
	}
	m_y = Physics::LerpPoint(m_y, m_tar_y, m_speed);
	m_x = Physics::LerpPoint(m_x, m_tar_x, m_speed);
	if (m_age >= m_maxAge)
		m_expired = true;
}

void Star::Draw()
{
	App::DrawLine(m_x, m_y, m_x + 1, m_y - 1, m_r, m_g, m_b);
	return;
}
