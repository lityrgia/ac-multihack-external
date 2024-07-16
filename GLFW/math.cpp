#include "DataTypes.h"
#include <cmath>
#include "globals.h"

void ConvertToRange(Vec2& Point) {
	Point.X /= globals::screenWidth;
	Point.X *= 2.0f;
	Point.X -= 1.0f;

	Point.Y /= globals::screenHeight;
	Point.Y *= 2.0f;
	Point.Y -= 1.0f;
}

bool WorldToScreen(const Vec3& VecOrigin, Vec2& VecScreen, float* Matrix) {
	Vec2 clipCoords;
	clipCoords.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[4] + VecOrigin.Z * Matrix[8] + Matrix[12];
	clipCoords.Y = VecOrigin.X * Matrix[1] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[9] + Matrix[13];
	float W = VecOrigin.X * Matrix[3] + VecOrigin.Y * Matrix[7] + VecOrigin.Z * Matrix[11] + Matrix[15];

	if (W < 0.01f)
		return false;

	Vec2 NDC;
	NDC.X = clipCoords.X / W;
	NDC.Y = clipCoords.Y / W;

	VecScreen.X = (globals::screenWidth / 2 * NDC.X) + (NDC.X + globals::screenWidth / 2);
	VecScreen.Y = (globals::screenHeight / 2 * NDC.Y) + (NDC.Y + globals::screenHeight / 2);

	return true;
}

float getDistanceToEnemy3D(const Vec3& absCoords) {
	return sqrt(absCoords.X * absCoords.X + absCoords.Y * absCoords.Y + absCoords.Z * absCoords.Z);
}