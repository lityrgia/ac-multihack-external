#pragma once

#include "DataTypes.h"

void ConvertToRange(Vec2& Point);
bool WorldToScreen(const Vec3& VecOrigin, Vec2& VecScreen, float* Matrix);
float getDistanceToEnemy3D(const Vec3& absCoords);