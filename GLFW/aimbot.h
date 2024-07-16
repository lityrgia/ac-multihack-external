#pragma once

#include "Memory.h"

void aimEnable(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList);
uintptr_t getClosestTargetToCrosshair(Memory& mem, uintptr_t& entityList, uintptr_t& localPlayer, short& playerCount);
void drawFovCircle();