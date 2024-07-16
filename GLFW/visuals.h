#pragma once

#include "DataTypes.h"
#include "Memory.h"
#include "imgui/imgui.h"

void drawEsp(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList);
void drawLine(Vec2& end, ImVec4 color);
void drawBox(Vec2& coordsHead, Vec2& coordsFeet, ImVec4 color);
void drawHealth(Vec2& coordsHead, Vec2& coordsFeet, short entityHealth);
void drawBoxFill(Vec2& coordsHead, Vec2& coordsFeet, ImVec4 color);
void drawBox3D(Matrix& ViewMatrix, Vec2& entityAngles, Vec3& entityLocationFeet, Vec3& entityLocationHead, ImVec4 color);
void drawViewDirection(Vec2& coordsHead, Vec2& entityViewAngles, Vec3& entityLocationHead, Matrix& ViewMatrix, ImVec4 color);