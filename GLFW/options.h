#pragma once
#include "imgui/imgui.h"

namespace menu {
	inline bool bMenuVisible{ true };
	inline bool bShowTeam{ false };
	inline bool bEnableLines{ false };
	inline bool bEnableBoxes{ false };
	inline bool bEnableBoxes3D{ false };
	inline bool bEnableBoxesFill{ false };
	inline bool bEnableViewDirection{ false };
	inline bool bEnableHealth{ false };
	inline bool bEnableAim{ false };
	inline bool bFriendlyFire{ false };
	inline bool bGrenadeDelay{ false };
	inline bool bSmooth{ false };
	inline bool bNoRecoil{ false };
	inline bool bFireRate{ false };
	inline bool bAutoGuns{ false };
	inline bool bInfiniteAmmo{ false };
	inline bool bMagicBullets{ false };
	inline bool bFOV{ false };
	inline bool bNoGunKnockback{ false };
	inline bool bFlyHack{ false };
	inline bool bTrip{ false };
}

namespace options {
	inline ImVec4 linesColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	inline ImVec4 boxesColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	inline ImVec4 boxes3DColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	inline ImVec4 boxesFillColor = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	inline ImVec4 viewDirection = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	inline ImVec4 teamBoxesColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
	inline float fovCircle{ 1.0f };
	inline float smoothness{ 1.0f };
}

namespace toggled {
	inline bool grenadeDelay{ false };
	inline bool autoGuns{ false };
	inline bool trip{ false };
	inline bool flyHack{ false };
	inline bool noFireRate{ false };
	inline bool noRecoil{ false };
	inline bool infiniteAmmo{ false };
	inline bool noGunKnockback{ false };
	inline bool magicBullets{ false };
}