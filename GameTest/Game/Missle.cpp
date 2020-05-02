#include "stdafx.h"
#include "Missle.h"


Missle::Missle(float x, float y, float targetx, float targety, float r, float b, float g)
{
	m_x = x;
	m_y = y;
	m_ex = x - m_age;
	m_ey = y - m_age;
	m_r = r;
	m_b = b;
	m_g = g;

	m_tar_x = targetx;
	m_tar_y = targety;
}

void Missle::Update()
{
	m_ex -= m_age;
	m_ey += m_age;

	m_x = Physics::LerpPoint(m_x, m_tar_x, m_speed);

	m_y = Physics::LerpPoint(m_y, m_tar_y, m_speed);

	m_age++;
	if (m_age >= m_maxAge)
		m_expired = true;

	// At a certain point the missle explodes. 
	if (m_age > 15) {
		m_g = 0.1f;
		m_b = 0.7f;
		m_r = 1.0f;
	}
}

void Missle::Draw()
{
	App::DrawLine(m_x, m_y, Physics::LerpPoint(m_x, m_tar_x, m_speed), Physics::LerpPoint(m_y, m_tar_y, m_speed), m_r, m_g, m_b);

	return;
}

bool Missle::isExpired()
{
	return m_expired;
}

bool Missle::TargetReached()
{
	if (m_x_resolve && m_y_resolve)
		return true;
	return false;
}
