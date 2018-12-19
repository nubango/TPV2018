#include "Vector2D.h"

Vector2D Vector2D::operator -(const Vector2D& v) const
{
	Vector2D r;
	r.x_ = x_ - v.x_;
	r.y_ = y_ - v.y_;
	return r;
}

Vector2D Vector2D::operator +(const Vector2D& v) const
{
	Vector2D r;
	r.x_ = x_ + v.x_;
	r.y_ = y_ + v.y_;
	return r;
}

Vector2D Vector2D::operator /(double d) const
{
	Vector2D r;
	r.x_ = x_ / d;
	r.y_ = y_ / d;
	return r;
}

Vector2D Vector2D::operator *(double d) const
{
	Vector2D r;
	r.x_ = x_ * d;
	r.y_ = y_ * d;
	return r;
}

double Vector2D::operator *(const Vector2D& d) const
{
	return d.x_ * x_ + d.y_ * y_;
}

bool Vector2D::operator==(const Vector2D & v) const
{
	return x_ == v.getX() && y_ == v.getY();
}

bool Vector2D::operator!=(const Vector2D & v) const
{
	return x_ != v.getX() || y_ != v.getY();
}

double Vector2D::normalize()
{
	// Normalize the vector in-place and return the magnitude
	double magnitude = sqrt(pow(x_, 2) + pow(y_, 2));
	if (magnitude > 0.0)
	{
		x_ /= magnitude;
		y_ /= magnitude;
	}
	return magnitude;
}

std::ostream & operator<<(std::ostream & os, const Vector2D & v)
{
	os << v.x_ << " " << v.y_;
	return os;
}

std::istream & operator>>(std::istream & is, Vector2D & v)
{
	is >> v.x_ >> v.y_;
	return is;
}
