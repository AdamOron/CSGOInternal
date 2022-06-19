#pragma once
#include <cmath>

#define PI 3.1415926535897932384626f

#define _RAD_TO_DEG (180.f / PI)
#define _DEG_TO_RAD (PI / 180.f)

float RadToDeg(float rad);
float DegToRad(float deg);
