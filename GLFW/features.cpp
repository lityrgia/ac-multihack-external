#include <Windows.h>
#include <iostream>

#include "Memory.h"
#include "math.h"
#include "DataTypes.h"
#include "options.h"
#include "offsets.h"

BYTE oldRecoil[] = {0xF3, 0x0F, 0x11, 0x56, 0x38};
BYTE newRecoil[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

BYTE oldAmmo[] = { 0xFF, 0x08 };
BYTE newAmmo[] = { 0x90, 0x90 };

BYTE oldFireRate[] = { 0x0F, 0xBF, 0x48, 0x54 };
BYTE newFireRate[] = { 0x0F, 0xBF, 0x48, 0x08 };

BYTE oldGunKnockback[] = { 0x0F ,0xBF, 0x70, 0x54 };
BYTE newGunKnockback[] = { 0x0F ,0xBF, 0x70, 0x08 };

BYTE oldTrip[] = { 0xF3, 0x0F, 0x10, 0x45, 0x04 };
BYTE newTrip[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

BYTE oldFlyHack[] = { 0x75, 0x69 };
BYTE newFlyHack[] = {  0x90, 0x90 };

BYTE oldMagicBullets[] = { 0x74, 0x12 };
BYTE newMagicBullets[] = { 0x90, 0x90 };

BYTE oldAutoGuns[] = { 0x80, 0x78, 0x66, 0x00 };
BYTE newAutoGuns[] = { 0x80, 0x78, 0x68, 0x00 };

BYTE oldGrenadeAnimation[] = { 0x8B, 0x46, 0x0C };
BYTE newGrenadeAnimation[] = { 0x90, 0x90, 0x90 };

BYTE oldGrenadeDecrement[] = { 0xFF, 0x08 };
BYTE newGrenaedDecrement[] = { 0x90, 0x90 };

BYTE oldGrenadeLoop[] = { 0x0F, 0x84, 0x6B, 0x01, 0x00, 0x00 };
BYTE newGrenadeLoop[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

void trip(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::trip, 5, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::trip, newTrip);
    }
    else {
        mem.Write(instructions::trip, oldTrip);
    }

    VirtualProtect((LPVOID)instructions::trip, 5, old, &old);
}

void noFireRate(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::gunFireRate, 5, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::gunFireRate, newFireRate);
    }
    else {
        mem.Write(instructions::gunFireRate, oldFireRate);
    }

    VirtualProtect((LPVOID)instructions::gunFireRate, 5, old, &old);
}

void noRecoil(Memory& mem, bool state)
{
    DWORD old;

    VirtualProtect((LPVOID)instructions::gunRecoil, 5, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::gunRecoil, newRecoil); 
    }
    else {
        mem.Write(instructions::gunRecoil, oldRecoil);
    }

    VirtualProtect((LPVOID)instructions::gunRecoil, 5, old, &old);
}

void infAmmo(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::gunAmmo, 2, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::gunAmmo, newAmmo);
    }
    else {
        mem.Write(instructions::gunAmmo, oldAmmo);
    }

    VirtualProtect((LPVOID)instructions::gunAmmo, 2, old, &old);
}

void noGunKnockback(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::gunKnockBack, 4, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::gunKnockBack, newGunKnockback);
    }
    else {
        mem.Write(instructions::gunKnockBack, oldGunKnockback);
    }

    VirtualProtect((LPVOID)instructions::gunKnockBack, 4, old, &old);
}

void flyHack(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::flyHack, 2, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::flyHack, newFlyHack);
    }
    else {
        mem.Write(instructions::flyHack, oldFlyHack);
    }

    VirtualProtect((LPVOID)instructions::flyHack, 2, old, &old);
}

void magicBullets(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::magicBullets, 2, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::magicBullets, newMagicBullets);
    }
    else {
        mem.Write(instructions::magicBullets, oldMagicBullets);
    }

    VirtualProtect((LPVOID)instructions::magicBullets, 2, old, &old);
}

void autoGuns(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::autoGuns, 4, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::autoGuns, newAutoGuns);
    }
    else {
        mem.Write(instructions::autoGuns, oldAutoGuns);
    }

    VirtualProtect((LPVOID)instructions::autoGuns, 4, old, &old);
}

void noGrenadeDelay(Memory& mem, bool state) {
    DWORD old;

    VirtualProtect((LPVOID)instructions::grenadeDecrement, 2, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::grenadeDecrement, newGrenaedDecrement);
    }
    else {
        mem.Write(instructions::grenadeDecrement, newGrenaedDecrement);
    }

    VirtualProtect((LPVOID)instructions::grenadeDecrement, 2, old, &old);

    VirtualProtect((LPVOID)instructions::grenadeAnimation, 3, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::grenadeAnimation, newGrenadeAnimation);
    }
    else {
        mem.Write(instructions::grenadeAnimation, oldGrenadeAnimation);
    }

    VirtualProtect((LPVOID)instructions::grenadeAnimation, 3, old, &old);

    VirtualProtect((LPVOID)instructions::grenadeLoop, 6, PAGE_EXECUTE_READWRITE, &old);

    if (state) {
        mem.Write(instructions::grenadeLoop, newGrenadeLoop);
    }
    else {
        mem.Write(instructions::grenadeLoop, oldGrenadeLoop);
    }

    VirtualProtect((LPVOID)instructions::grenadeLoop, 6, old, &old);
}