#pragma once
#include <cmath>

class Physics
{
public:
	static float LerpPoint(float origin, float target, float speed);
	static float OrbitXAxis(float center_x, float rot, float r);
	static float OrbitYAxis(float center_y, float rot, float r);
	static bool PointCollision(float ax, float ay, float bx, float by);
	static bool RadialCollision(float ax, float ay, float bx, float by, float rad);
	static bool OccupySamePosition(float ax, float ay, float bx, float by);
};

