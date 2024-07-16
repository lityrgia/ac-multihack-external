#include <GL/glew.h>

#include "DataTypes.h"
#include "Memory.h"
#include "offsets.h"
#include "math.h"
#include "visuals.h"
#include "options.h"
#include "globals.h"

#define M_PI 3.14159265358979323846

ColorA colorHealth(0.0f, 0.0f, 1.0f, 0.5f);

void drawEsp(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList) {
	Matrix ViewMatrix = mem.Read<Matrix>(offsets::viewMatrix);
	Vec3 playerLocation = mem.Read<Vec3>(localPlayer + offsets::m_XPos);
	short playerTeam = mem.Read<short>(localPlayer + offsets::teamNum);

    short playerNumber = mem.Read<uintptr_t>(offsets::playersNumber);
    for (short i = 0; i < playerNumber; ++i) {
        uintptr_t entity = mem.Read<uintptr_t>(entityList + i * 0x4);
		int isEntityDead = mem.Read<uintptr_t>(entity + offsets::isDead);

        if (entity == NULL || isEntityDead) continue;

		short entityHealth = mem.Read<short>(entity + offsets::health);

        short entityTeam = mem.Read<short>(entity + offsets::teamNum);

        bool onSameTeam = (entityTeam == playerTeam);

        if (onSameTeam && !menu::bShowTeam) continue;

        Vec3 entityLocationHead = mem.Read<Vec3>(entity + offsets::m_XPos);
		Vec3 entityLocationFeet = mem.Read<Vec3>(entity + offsets::m_feetXPos);
		entityLocationHead.Z += 0.5;
		entityLocationFeet.Z -= 0.5;

		Vec2 entityAngles = mem.Read<Vec2>(entity + offsets::yaw);
        
        Vec2 screenCoordsHead;
        Vec2 screenCoordsFeet;

        if (!WorldToScreen(entityLocationHead, screenCoordsHead, ViewMatrix.VMatrix)) continue;
		if (!WorldToScreen(entityLocationFeet, screenCoordsFeet, ViewMatrix.VMatrix)) continue;

		ConvertToRange(screenCoordsHead);
		ConvertToRange(screenCoordsFeet);

		if (menu::bEnableLines) {
			
			if (!onSameTeam) {
				drawLine(screenCoordsFeet, options::linesColor);
			}
			else {
				drawLine(screenCoordsFeet, options::teamBoxesColor);
			}
		}
		if (menu::bEnableBoxes) {
			if (!onSameTeam) {
				drawBox(screenCoordsHead, screenCoordsFeet, options::boxesColor);
			}
			else {
				drawBox(screenCoordsHead, screenCoordsFeet, options::teamBoxesColor);
			}
		}
		if (menu::bEnableBoxesFill) {
			if (!onSameTeam) {
				drawBoxFill(screenCoordsHead, screenCoordsFeet, options::boxesFillColor);
			}
			else {
				drawBoxFill(screenCoordsHead, screenCoordsFeet, options::teamBoxesColor);
			}
		}
		if (menu::bEnableBoxes3D) {
			if (!onSameTeam) {
				drawBox3D(ViewMatrix, entityAngles, entityLocationFeet, entityLocationHead, options::boxes3DColor);
			}
			else {
				drawBox3D(ViewMatrix, entityAngles, entityLocationFeet, entityLocationHead, options::teamBoxesColor);
			}
		}
		if (menu::bEnableViewDirection) {
			if (!onSameTeam) {
				drawViewDirection(screenCoordsHead, entityAngles, entityLocationHead, ViewMatrix, options::viewDirection);
			}
			else {
				drawViewDirection(screenCoordsHead, entityAngles, entityLocationHead, ViewMatrix, options::teamBoxesColor);
			}
		}
		if (menu::bEnableHealth) {
			drawHealth(screenCoordsHead, screenCoordsFeet, entityHealth);
		}
    }
}

void drawLine(Vec2& end, ImVec4 color) {
	Vec2 lineOrigin;
	lineOrigin.X = 0.0f;
	lineOrigin.Y = -1.0f;

	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(color.x, color.y, color.z, color.w);
	glVertex2f(lineOrigin.X, lineOrigin.Y);
	glVertex2f(end.X, end.Y);
	glEnd();
};

void drawBox(Vec2& coordsHead, Vec2& coordsFeet, ImVec4 color) {
	float boxHeight = coordsHead.Y - coordsFeet.Y;
	float boxWidth = boxHeight / 3.5f;

	float halfBoxWidth = boxWidth / 2.5f;

	glLineWidth(1.5f);
	glBegin(GL_LINE_LOOP);
	glColor4f(color.x, color.y, color.z, color.w);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsFeet.Y);
	glVertex2f(coordsHead.X + halfBoxWidth, coordsFeet.Y); 
	glVertex2f(coordsHead.X + halfBoxWidth, coordsHead.Y);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsHead.Y);
	glEnd();
}

void drawBoxFill(Vec2& coordsHead, Vec2& coordsFeet, ImVec4 color) {
	float boxHeight = coordsHead.Y - coordsFeet.Y;
	float boxWidth = boxHeight / 3.5f;

	float halfBoxWidth = boxWidth / 2.5f;

	glBegin(GL_QUADS);
	glColor4f(color.x, color.y, color.z, color.w);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsFeet.Y);
	glVertex2f(coordsHead.X + halfBoxWidth, coordsFeet.Y);
	glVertex2f(coordsHead.X + halfBoxWidth, coordsHead.Y);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsHead.Y);
	glEnd();
}

void drawBox3D(Matrix& ViewMatrix, Vec2& entityAngles, Vec3& entityLocationFeet, Vec3& entityLocationHead, ImVec4 color) {
	float h = entityLocationHead.Z - entityLocationFeet.Z;
	float w = h / 3.0f;

	float cx = (entityLocationHead.X + entityLocationFeet.X) / 2.0f;
	float cy = (entityLocationHead.Y + entityLocationFeet.Y) / 2.0f;
	float cz = (entityLocationHead.Z + entityLocationFeet.Z) / 2.0f;

	Vec3 vertices[8] = {
		{cx - w / 2, cy - w / 2, cz - h / 2},
		{cx + w / 2, cy - w / 2, cz - h / 2},
		{cx + w / 2, cy + w / 2, cz - h / 2},
		{cx - w / 2, cy + w / 2, cz - h / 2},
		{cx - w / 2, cy - w / 2, cz + h / 2},
		{cx + w / 2, cy - w / 2, cz + h / 2},
		{cx + w / 2, cy + w / 2, cz + h / 2},
		{cx - w / 2, cy + w / 2, cz + h / 2}
	};

	Vec2 screenCoord3DParts[8];

	for (int i = 0; i < 8; ++i) {
		WorldToScreen(vertices[i], screenCoord3DParts[i], ViewMatrix.VMatrix); 
		ConvertToRange(screenCoord3DParts[i]);
	}

	Vec2 tempLines[4] = {
		screenCoord3DParts[4] - screenCoord3DParts[0],
		screenCoord3DParts[5] - screenCoord3DParts[1],
		screenCoord3DParts[6] - screenCoord3DParts[2],
		screenCoord3DParts[7] - screenCoord3DParts[3],
	};

	//animation lines

	static float counter = 0;
	static float speed = 0.01;

	counter += speed;

	float sineValue = (sin(counter) + 1) / 2;
	sineValue = sineValue * sineValue * (10 - 2 * sineValue);
	sineValue = sineValue * 8 + 1;

	// i know here could be less code but idc

	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(color.x, color.y, color.z, color.w);

	//down

	glVertex2f(screenCoord3DParts[0].X, screenCoord3DParts[0].Y);
	glVertex2f(screenCoord3DParts[1].X, screenCoord3DParts[1].Y);

	glVertex2f(screenCoord3DParts[1].X, screenCoord3DParts[1].Y);
	glVertex2f(screenCoord3DParts[2].X, screenCoord3DParts[2].Y);

	glVertex2f(screenCoord3DParts[2].X, screenCoord3DParts[2].Y);
	glVertex2f(screenCoord3DParts[3].X, screenCoord3DParts[3].Y);

	glVertex2f(screenCoord3DParts[3].X, screenCoord3DParts[3].Y);
	glVertex2f(screenCoord3DParts[0].X, screenCoord3DParts[0].Y);

	//up

	glVertex2f(screenCoord3DParts[4].X, screenCoord3DParts[4].Y);
	glVertex2f(screenCoord3DParts[5].X, screenCoord3DParts[5].Y);

	glVertex2f(screenCoord3DParts[5].X, screenCoord3DParts[5].Y);
	glVertex2f(screenCoord3DParts[6].X, screenCoord3DParts[6].Y);

	glVertex2f(screenCoord3DParts[6].X, screenCoord3DParts[6].Y);
	glVertex2f(screenCoord3DParts[7].X, screenCoord3DParts[7].Y);

	glVertex2f(screenCoord3DParts[7].X, screenCoord3DParts[7].Y);
	glVertex2f(screenCoord3DParts[4].X, screenCoord3DParts[4].Y);

	//tempLines

	glVertex2f(screenCoord3DParts[4].X - tempLines[0].X / sineValue, screenCoord3DParts[4].Y - tempLines[0].Y / sineValue);
	glVertex2f(screenCoord3DParts[5].X - tempLines[1].X / sineValue, screenCoord3DParts[5].Y - tempLines[1].Y / sineValue);

	glVertex2f(screenCoord3DParts[5].X - tempLines[1].X / sineValue, screenCoord3DParts[5].Y - tempLines[1].Y / sineValue);
	glVertex2f(screenCoord3DParts[6].X - tempLines[2].X / sineValue, screenCoord3DParts[6].Y - tempLines[2].Y / sineValue);

	glVertex2f(screenCoord3DParts[6].X - tempLines[2].X / sineValue, screenCoord3DParts[6].Y - tempLines[2].Y / sineValue);
	glVertex2f(screenCoord3DParts[7].X - tempLines[3].X / sineValue, screenCoord3DParts[7].Y - tempLines[3].Y / sineValue);

	glVertex2f(screenCoord3DParts[7].X - tempLines[3].X / sineValue, screenCoord3DParts[7].Y - tempLines[3].Y / sineValue);
	glVertex2f(screenCoord3DParts[4].X - tempLines[0].X / sineValue, screenCoord3DParts[4].Y - tempLines[0].Y / sineValue);
	
	//central

	glVertex2f(screenCoord3DParts[0].X, screenCoord3DParts[0].Y);
	glVertex2f(screenCoord3DParts[4].X, screenCoord3DParts[4].Y);

	glVertex2f(screenCoord3DParts[1].X, screenCoord3DParts[1].Y);
	glVertex2f(screenCoord3DParts[5].X, screenCoord3DParts[5].Y);

	glVertex2f(screenCoord3DParts[2].X, screenCoord3DParts[2].Y);
	glVertex2f(screenCoord3DParts[6].X, screenCoord3DParts[6].Y);

	glVertex2f(screenCoord3DParts[3].X, screenCoord3DParts[3].Y);
	glVertex2f(screenCoord3DParts[7].X, screenCoord3DParts[7].Y);
	glEnd();
}

void drawViewDirection(Vec2& coordsHead, Vec2& entityViewAngles, Vec3& entityLocationHead, Matrix& ViewMatrix, ImVec4 color) {
	float viewDistance = 4.0f;

	float yawRad = (entityViewAngles.X - 90.0f) * (M_PI / 180.0f); 
	float pitchRad = entityViewAngles.Y * (M_PI / 180.0f);

	Vec3 direction;
	direction.X = cosf(yawRad) * cosf(pitchRad);
	direction.Y = sinf(yawRad) * cosf(pitchRad);
	direction.Z = sinf(pitchRad);
	
	Vec3 endPoint;
	endPoint.X = entityLocationHead.X + direction.X * viewDistance;
	endPoint.Y = entityLocationHead.Y + direction.Y * viewDistance;
	endPoint.Z = entityLocationHead.Z + direction.Z * viewDistance;

	Vec2 screenCoordEnd;

	WorldToScreen(endPoint, screenCoordEnd, ViewMatrix.VMatrix);
		ConvertToRange(screenCoordEnd);

		glLineWidth(1.5f);
		glBegin(GL_LINES);
		glColor4f(color.x, color.y, color.z, color.w);

		glVertex2f(coordsHead.X, coordsHead.Y);
		glVertex2f(screenCoordEnd.X, screenCoordEnd.Y);

		glEnd();
}

void drawHealth(Vec2& coordsHead, Vec2& coordsFeet, short entityHealth) {
	if (entityHealth < 0) return;

	float boxHeight = coordsHead.Y - coordsFeet.Y;

	float halfBoxWidth = boxHeight / 8.5f;
	float halfBoxWidth2 = halfBoxWidth * 1.05f;

	float healthBarHeight = boxHeight * (entityHealth / 100.0f);
	float healthBarTopY = coordsFeet.Y + healthBarHeight;

	glBegin(GL_QUADS);
	glColor4f(colorHealth.R, colorHealth.G, colorHealth.B, colorHealth.A);
	glVertex2f(coordsHead.X - halfBoxWidth2, coordsFeet.Y);
	glVertex2f(coordsHead.X - halfBoxWidth, coordsFeet.Y); 
	glVertex2f(coordsHead.X - halfBoxWidth, healthBarTopY);
	glVertex2f(coordsHead.X - halfBoxWidth2, healthBarTopY); 
	glEnd();
}