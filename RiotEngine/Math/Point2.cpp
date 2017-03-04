#include "Point2.h"
#include <cmath>

Point2& Point2::operator=(float xy)
{
	x = xy;
	y = xy;
	return (*this);
}

Point2& Point2::operator=(const Point2& p)
{
//	if (this == &p)
//		return (*this);
	x = p.x;
	y = p.y;
	return (*this);
}

Point2& Point2::operator+=(const Point2& b)
{
	x += b.x;
	y += b.y;
	return (*this);
}

Point2& Point2::operator-=(const Point2& b)
{
	x -= b.x;
	y -= b.y;
	return (*this);
}

Point2& Point2::operator*=(float f)
{
	x *= f;
	y *= f;
	return (*this);
}

Point2& Point2::operator/=(float f)
{
	x /= f;
	y /= f;
	return (*this);
}

float Point2::length() const
{
	return sqrt(x*x + y*y);
}

float Point2::distanceTo(const Point2& p) const
{
	return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
}

Point2 Point2::normal() const
{
	float len = length();
	if (len > 0.f)
		return Point2(x/len, y/len);
	return (*this);
}

const Point2& operator+(const Point2& p)
{
	return p;
}

const Point2 operator-(const Point2& p)
{
	return Point2(-p.x, -p.y);
}

Point2 operator+(const Point2& a, const Point2& b)
{
	return Point2(a.x + b.x, a.y + b.y);
}

Point2 operator-(const Point2& a, const Point2& b)
{
	return Point2(a.x - b.x, a.y - b.y);
}

Point2 operator*(const Point2& a, float b)
{
	return Point2(a.x * b, a.y * b);
}

Point2 operator*(float a, const Point2& b)
{
	return Point2(b.x * a, b.y * a);
}

Point2 operator/(const Point2& a, float b)
{
	return Point2(a.x / b, a.y / b);
}

float operator&(const Point2& a, const Point2& b)
{
	return (a.x * b.x + a.y * b.y);
}

bool operator==(const Point2& a, const Point2& b)
{
	return (a.x == b.x && a.y == b.y);
}