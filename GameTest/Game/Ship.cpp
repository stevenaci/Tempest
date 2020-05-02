
#include "stdafx.h"
#include "Ship.h"

using namespace std;

Ship::Ship(float cx, float cy, float ring_size, EntityGenerator* generator)
{
	// Starting player Values
	m_score = 0.0f;
	m_health = 50.0f;
	m_cannon_level = 1;

	// Movement Boundaries
	m_x_min = 0 + ring_size;
	m_x_max = APP_VIRTUAL_WIDTH - ring_size;
	m_y_min = 0 + ring_size;
	m_y_max = APP_VIRTUAL_HEIGHT - ring_size;

	// Center Axis of Rotation
	m_center_x = cx;
	m_center_y = cy;

	// Default Colours
	m_r = 0.0f;
	m_b = 180.0f;
	m_g = 0.0f;

	m_rot_direction = 1.0f;
	m_ring_speed = 0.02f;
	m_ring_size = 180.0f;
	m_ring_size_max = 500.0f;
	m_ring_size_min = 80.0f;

	// Ship Starting Location
	m_x = cx + ring_size /2;
	m_y = cy - ring_size / 2;

	// Arm Missles!
	m_missles_armed = true;
	// Set Missle SFX
	m_missle_SFX->push_back(".\\TestData\\cannon1.wav");
	m_missle_SFX->push_back(".\\TestData\\cannon2.wav");
	m_missle_SFX->push_back(".\\TestData\\cannon3.wav");

	// Reference to Other Game Objects
	m_generator = generator;
}

void Ship::Attack()
{
	if(m_missles_armed){
		m_missle_cooldown = 8;
		m_missles_armed = false;
		// The Cannons are parallel to the ships Hull
		float left_rot = m_rot + (m_ring_speed * 2);
		float right_rot = m_rot + (m_ring_speed * -1 * 2);

		if(m_cannon_level > 0){
			FireMissle(left_rot);
			FireMissle(right_rot);
		}
		if (m_cannon_level > 1)
		{
			// Add more cannons
			float left2_rot = left_rot + (m_ring_speed * 3);
			float right2_rot = right_rot + (m_ring_speed * -1 * 3);
			FireMissle(left2_rot);
			FireMissle(right2_rot);
		}
		if (m_cannon_level > 2)
		{
			float left3_rot = left_rot + (m_ring_speed * 4);
			float right3_rot = right_rot + (m_ring_speed * -1 * 4);
			FireMissle(left3_rot);
			FireMissle(right3_rot);
		}
	}
}

void Ship::FireMissle(float offset_rot)
{
	App::PlaySound(m_missle_SFX->at(m_cannon_level - 1.0f).c_str());
	m_Missles.push_back(new Missle(Physics::OrbitXAxis(m_center_x, offset_rot, m_ring_size),
		Physics::OrbitYAxis(m_center_y, offset_rot, m_ring_size), m_center_x, m_center_y, 0.0f, 0.0f, 100.0f));
}

void Ship::Update()
{
	// Cooldown missles
	if(!m_missles_armed){
		m_missle_cooldown--;
		if (m_missle_cooldown <= 0) m_missles_armed = true;
	}

	// Orbit by our Speed and Direction 
	// around Horizon Point
	m_x = Physics::OrbitXAxis(m_center_x, m_rot, m_ring_size);
	m_y = Physics::OrbitYAxis(m_center_y, m_rot, m_ring_size);
	if (m_rot > 6.28) m_rot = 0.0f;
	m_rot += m_ring_speed * m_rot_direction;

	// Update Missles
	for (auto i : m_Missles)
		i->Update();

	vector<Missle*>::iterator it = m_Missles.begin();
	for (; it != m_Missles.end();)
	{
		//Check Enemy Collision with Missles
		m_score += m_generator->CheckMissleCollision((*it)->getX(), (*it)->getY());

		// Delete missles that reached their target or expired
		if((*it)->TargetReached() || (*it)->isExpired())
		{
			delete(*it);
			it = m_Missles.erase(it);
		}
		else {	++it;}
	}

	// Check Enemy Collision with Ship
	m_health -= m_generator->CheckShipCollision(m_x, m_y);

	// Level up Cannons
	if (m_cannon_level == 2 && m_score >= 80000.0f){
		m_cannon_level = 3;
	}
	if (m_cannon_level == 1 && m_score >= 50000.0f){
		m_cannon_level = 2;
	}

	if (m_health < 30 && !m_warning_flag) {
		App::PlaySound(".\\TestData\\warning.wav");
		m_warning_flag = true;
	}
	if (m_health <= 0 && !m_defeat_flag) {
		App::PlaySound(".\\TestData\\death.wav");
		m_defeat_flag = true;
	}
}

void Ship::Draw()
{
	float ex = m_x + 20;
	float ey = m_y + 20;

	App::DrawLine(m_x, m_y, ex, ey, m_r, m_g, m_b);

	for (auto i : m_Missles)
		i->Draw();
}

void Ship::Rotate(float dr)
{
	// Adjust our direction of rotation, by a certain degree of rotation
	m_rot += dr * m_ring_speed;
	if (dr > 0) m_rot_direction = 1.0f;
	if (dr < 0) m_rot_direction = -1.0f;
}

void Ship::AdjustSize(float ds)
{
	// Adjusting our orbit,
	// Checking to make sure it is within bounds
	if (m_ring_size + ds > m_ring_size_max) 
	{
		m_ring_size = m_ring_size_max;
	}
	if (m_ring_size + ds < m_ring_size_min)
	{
		m_ring_size = m_ring_size_min;
	}
	else 
	{
		m_ring_size += ds;
	}
}

string Ship::getCoordString()
{
	stringstream ss;
	ss << m_x;
	ss << ":";
	ss << m_y;
	return ss.str();
}