#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include<cmath>

class Vector2
{
public:
	double x;
	double y;

public:
	Vector2(double x = 0, double y = 0) :x(x), y(y) {}
	~Vector2() = default;

public:
	Vector2 operator+(const Vector2& vec)const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec)
	{
		x += vec.x, y += vec.y;
	}

	Vector2 operator-(const Vector2& vec)const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x, y -= vec.y;
	}

	double operator*(const Vector2& vec)const
	{
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(double val)const
	{
		return Vector2(val * x, y * val);
	}

	void operator*=(double val)
	{
		x *= val, y *= val;
	}

	double length()const
	{
		return sqrt(x * x + y * y);
	}

	Vector2 normalize()const
	{
		double len = this->length();
		if (abs(len) <= 0.00001)
			return Vector2();

		return Vector2(x / len, y / len);
	}
};

#endif // !_VECTOR2_H_
