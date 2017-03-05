#pragma once

class Point2
{
public:
	Point2(): x(0), y(0) {}
	Point2(float xy) : x(xy), y(xy) {}
	Point2(float xx, float yy) : x(xx), y(yy) {}
	Point2(const Point2& v) : x(v.x), y(v.y) {}

	Point2& operator=(const Point2& p);
	Point2& operator=(float xy);

	Point2& operator+=(const Point2& b);
	Point2& operator-=(const Point2& b);
	Point2& operator*=(float f);
	Point2& operator/=(float f);

	float length() const;
	float distanceTo(const Point2& p) const;
	Point2 normal() const;
	float angle() const;

	friend const Point2& operator+(const Point2& p);
	friend const Point2 operator-(const Point2& p);

	friend Point2 operator+(const Point2& a, const Point2& b);
	friend Point2 operator-(const Point2& a, const Point2& b);

	friend Point2 operator*(const Point2& a, float b);
	friend Point2 operator*(float a, const Point2& b);
	friend Point2 operator/(const Point2& a, float b);

	// скалярное произведение
	friend float operator&(const Point2& a, const Point2& b);
	friend bool operator==(const Point2& a, const Point2& b);

	float x, y;
};

typedef Point2 Vector2;