#include "Vector2D.h"
#include <math.h>

void Vector2D::normalize()
{
	double mag = sqrt(pow(x_, 2) + pow(y_, 2));
	if (mag > 0.0)
	{
		x_ = x_ / mag;
		y_ = y_ / mag;
	}
}

Vector2D Vector2D::operator+(const Vector2D & v) const
{
	Vector2D r;
	r.x_ = x_ + v.x_;
	r.y_ = y_ + v.y_;
	return r;
}

Vector2D Vector2D::operator-(const Vector2D & v) const
{
	Vector2D r;
	r.x_ = x_ - v.x_;
	r.y_ = y_ - v.y_;
	return r;
}

Vector2D Vector2D::operator*(double d) const
{
	Vector2D r;
	r.x_ = x_ * d;
	r.y_ = y_ * d;
	return r;
}

double Vector2D::operator*(const Vector2D & d) const
{
	return d.x_ * x_ + d.y_ * y_;
}

std::ostream & operator<<(std::ostream & os, const Vector2D & v)
{
	os << "(" << v.x_ << "," << v.y_ << ")";
	return os;
}