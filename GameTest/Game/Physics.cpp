#include "stdafx.h"
#include "Physics.h"

const float unitsize = 10.0f;

// Move towards a point
float Physics::LerpPoint(float origin, float target, float speed)
{
	float direction_x = target - origin;
	return origin + direction_x * speed;
}

// Return an orbit for the X Axis
float Physics::OrbitXAxis(float center_x, float rot, float r) 
{
	return center_x + cos(rot) * r;
}

// Return an orbit for the Y Axis
float Physics::OrbitYAxis(float center_y, float rot, float r)
{
	return center_y + sin(rot) * r;
}

// Point Collision
bool Physics::PointCollision(float ax, float ay, float bx, float by)
{
	if (ax < bx + unitsize &&
		ax + unitsize > bx &&
		ay < by + unitsize &&
		ay + unitsize > by)
		return true;

	return false;
}

// Radial Collision
bool Physics::RadialCollision(float ax, float ay, float bx, float by, float rad)
{
	if (ax < bx + rad &&
		ax + rad > bx &&
		ay < by + rad &&
		ay + rad > by)
		return true;

	return false;
}

// Check for Identical Locations between two objects
bool Physics::OccupySamePosition(float ax, float ay, float bx, float by)
{
	if (ax == bx && ay == by)
		return true;

	return false;
}
