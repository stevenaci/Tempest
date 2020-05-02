#pragma once
#include "stdlib.h"
#include "app.h"
#include "Physics.h"

class Star
{
private:
	float m_r;
	float m_b;
	float m_g;
	float m_x;
	float m_y;
	float m_tar_x;
	float m_tar_y;
	float m_speed = 0.07f;
	float m_brightness = 0.0f;
	float m_age = 0.10f;
	float m_maxAge = 200;
	bool m_expired = false;

public:
	static const int CONSTELLATION_MAX = 7;
	Star(float origin_x, float origin_y);
	void Update();
	void Draw();
	bool isExpired() { return m_expired; }

};

