#pragma once

#include "stdafx.h"
#include <cmath>
#include <string>
#include <Missle.h>
#include "Physics.h"
#include "EntityGenerator.h"
#include "app.h"
#include <iostream>
#include <sstream>
#include <algorithm>


using namespace std;
class Ship
{
	private:
		float m_score;
		float m_health;
		int m_cannon_level;
		bool m_warning_flag = false;
		bool m_defeat_flag = false;

		float m_center_x;
		float m_center_y;

		float m_x;
		float m_y;

		float m_r;
		float m_g;
		float m_b;

		vector<Missle*> m_Missles;
		bool m_missles_armed = false;
		int m_missle_cooldown = 0;
		vector<string> m_missle_SFX[3];

		float m_ring_speed;
		float m_ring_size;
		float m_ring_size_max;
		float m_ring_size_min;

		float m_rot_direction;

		float m_x_min;
		float m_x_max;
		float m_y_min;
		float m_y_max;

		float m_rot = 0.0f;

		EntityGenerator* m_generator;

	public:
		Ship(float cx, float cy, float ring_size, EntityGenerator* generator);
		void Attack();
		void FireMissle(float offset_rot);
		void Update();
		void Draw();
		void AdjustSize(float ds);
		string getCoordString();
		void Rotate(float dr);
		float getScore() { return m_score; }
		float getHealth() { return m_health; }
		bool isDefeated() { return m_defeat_flag; }
		bool isWarning() { return m_warning_flag; }
};

