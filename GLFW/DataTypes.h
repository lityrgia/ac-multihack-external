#pragma once

struct ColorA {
	float R{};
	float G{};
	float B{};
	float A{};

	ColorA() {};
	ColorA(float r, float b, float g, float a) : R(r), G(g), B(b), A(a) {};
};

struct Vec2 {
	float X;
	float Y;
};

struct Vec3 {
	float X;
	float Y;
	float Z;
};

Vec3 operator- (const Vec3& first, const Vec3& second);
Vec2 operator- (const Vec2& first, const Vec2& second);

struct Vec4 {
	float X;
	float Y;
	float Z;
	float W;
};

struct Matrix {
	float VMatrix[16];
};