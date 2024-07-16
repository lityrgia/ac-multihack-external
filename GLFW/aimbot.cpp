#include <string>

#include "Memory.h"
#include "DataTypes.h"
#include "GLFW/glfw3.h"
#include "globals.h"
#include "offsets.h"
#include "math.h"
#include "options.h"
#include "aimbot.h"

#define M_PI 3.14159265358979323846

void aimEnable(Memory& mem, uintptr_t& localPlayer, uintptr_t& entityList) {

    short playerNumber = mem.Read<uintptr_t>(offsets::playersNumber);
    Vec3 playerLocation = mem.Read<Vec3>(localPlayer + offsets::m_XPos);

    Vec2 playerAngles = mem.Read<Vec2>(localPlayer + offsets::yaw);

    uintptr_t entity = getClosestTargetToCrosshair(mem, entityList, localPlayer, playerNumber);
    Vec3 entityLocation = mem.Read<Vec3>(entity + offsets::m_XPos);

    Vec3 absLocation = entityLocation - playerLocation;

    float yaw = -atan2(absLocation.X, absLocation.Y) * (180 / M_PI) + 180;
    float pitch = atan2(absLocation.Z, sqrt(absLocation.X * absLocation.X + absLocation.Y * absLocation.Y)) * (180 / M_PI);

    int isEnityDead = mem.Read<int>(entity + offsets::isDead);

        if (entity != NULL && isEnityDead != 1) {

            if (menu::bSmooth) {
                Vec2 calcAngles{ yaw - playerAngles.X, pitch - playerAngles.Y };
                yaw = playerAngles.X + calcAngles.X / options::smoothness;
                pitch = playerAngles.Y + calcAngles.Y / options::smoothness;
            }

            mem.Write<float>(localPlayer + offsets::yaw, yaw);
            mem.Write<float>(localPlayer + offsets::pitch, pitch);
        }
}
uintptr_t getClosestTargetToCrosshair(Memory& mem, uintptr_t& entityList, uintptr_t& localPlayer, short& playerCount)
{
    int playerTeam = mem.Read<int>(localPlayer + offsets::teamNum);

    Vec2 centerScreen{ globals::screenWidth / 2, globals::screenHeight / 2 };
    Vec2 entityHeadPos2D;

    uintptr_t bestTarget{};

    int closestToCrosshair{ 999999 };
    float fov{ 300 };

    for (int i{ 0 }; i < playerCount; ++i)
    {
        uintptr_t entity = mem.Read<uintptr_t>(entityList + 0x4 * i);
        Vec3 entityHeadPos = mem.Read<Vec3>(entity + offsets::m_XPos);

        int entityTeam = mem.Read<int>(entity + offsets::teamNum);
        int isSameTeam = entityTeam == playerTeam;

        if (isSameTeam && !menu::bFriendlyFire) continue;

        int isEnityDead = mem.Read<int>(entity + offsets::isDead);

        if (entity != NULL && isEnityDead != 1) {
            Matrix ViewMatrix = mem.Read<Matrix>(offsets::viewMatrix);
            WorldToScreen(entityHeadPos, entityHeadPos2D, ViewMatrix.VMatrix);

            float distance = sqrt((centerScreen.X - entityHeadPos2D.X) * (centerScreen.X - entityHeadPos2D.X) + (centerScreen.Y - entityHeadPos2D.Y) * (centerScreen.Y - entityHeadPos2D.Y));

            if (menu::bFOV) {
                if (distance < options::fovCircle && distance < closestToCrosshair)
                {
                    bestTarget = entity;
                    closestToCrosshair = distance;
                }
            }
            else {
                if (distance < fov)
                {
                    fov = distance;
                    bestTarget = entity;
                }
            }
        }

    }

    return bestTarget;
}

void drawFovCircle() {
    glOrtho(0, globals::screenWidth, 0, globals::screenHeight, -1, 1);
;
    glColor3f(1.0f, 1.0f, 1.0f);

    float x = globals::screenWidth / 2.0f;
    float y = globals::screenHeight / 2.0f - 10.0f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 50; i++) {
        float angle = 2.0f * M_PI * i / 50;
        float dx = options::fovCircle * cos(angle);
        float dy = options::fovCircle * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    float dx = options::fovCircle * cos(0);
    float dy = options::fovCircle * sin(0);
    glVertex2f(x + dx, y + dy);
    glEnd(); 
}