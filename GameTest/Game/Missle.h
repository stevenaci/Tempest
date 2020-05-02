#pragma once
#include "app.h"
#include "Physics.h"

class Missle
{

private:
	float m_age = 1.0f;
	int m_maxAge = 20;
	float m_x;
	float m_y;
	float m_r;
	float m_b;
	float m_g;
	float m_ex;
	float m_ey;
	float m_tar_x;
	float m_tar_y;
	float m_speed = 0.10f;
	bool m_x_resolve = false;
	bool m_y_resolve = false;
	bool m_expired = false;

public:
	Missle(float x, float y,float targetx, float targety, float r, float b, float g);
	void Update();
	void Draw();
	bool TargetReached();
	bool isExpired();
	float getX() { return m_x; }
	float getY() { return m_y; }
};

