// Author : Lewis Ward
// Date: 29/08/2017
#pragma once

struct Vec2
{
	float X;
	float Y;

	Vec2() : X(0.0f), Y(0.0f){};
	Vec2(float LocX, float LocY) : X(LocX), Y(LocY){};

	bool operator == (const Vec2& B) { return (X == B.X && Y == B.Y); }
	void operator = (const Vec2& B) { X = B.X; Y = B.Y; }
};

inline Vec2 operator + (Vec2 A, Vec2 B)
{
	Vec2 R; 
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	return R;
}

inline Vec2 operator + (Vec2 V, float F)
{
	Vec2 R;
	R.X = V.X + F;
	R.Y = V.Y + F;
	return R;
}

inline Vec2 operator - (Vec2 V)
{
	Vec2 R;
	R.X = -V.X;
	R.Y = -V.Y;
	return R;

}
inline Vec2 operator - (Vec2 A, Vec2 B)
{
	Vec2 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	return R;
}

inline Vec2 operator - (Vec2 V, float F)
{
	Vec2 R;
	R.X = V.X - F;
	R.Y = V.Y - F;
	return R;
}

inline Vec2 operator * (Vec2 V, float F)
{
	Vec2 R;
	R.X = V.X * F;
	R.Y = V.Y * F;
	return R;
}

inline Vec2 operator / (Vec2 V, float F)
{
	Vec2 R;
	R.X = V.X / F;
	R.Y = V.Y / F;
	return R;
}

inline Vec2 operator / (float F, Vec2 V)
{
	Vec2 R;
	R.X = F / V.X;
	R.Y = F / V.Y;
	return R;
}

inline float Dot(Vec2 A, Vec2 B)
{
	return (A.X * B.X) + (A.Y * B.Y);
}

inline float Length(Vec2 V)
{
	return std::sqrt((V.X * V.X) + (V.Y * V.Y));
}

inline Vec2 Normalize(Vec2 V)
{
	float Len = Length(V);

	if (Len > 000000.1f)
	{
		Len = 1.0f / Len;
	}
	else
	{
		Len = 0.0f;
	}

	return Vec2(Len * V.X, Len * V.Y);
}

inline bool WithinRange(Vec2 A, Vec2 B)
{
	float Tolerance = 000000.1f;
	if (A.X >= B.X - Tolerance && A.X <= B.X + Tolerance && A.Y >= B.Y - Tolerance && A.Y <= B.Y + Tolerance)
		return true;
	else
		return false;
}