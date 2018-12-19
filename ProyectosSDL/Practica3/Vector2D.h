#pragma once

#include <iostream>

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
	Vector2D(const Vector2D &v) : x_(v.x_), y_(v.y_) {}
	~Vector2D() {}

	double getX() const { return x_; }
	double getY() const { return y_; }
	void setX(const double& x) { x_ = x; }
	void setY(const double& y) { y_ = y; }

	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator/(double d) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& v) const;
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
	friend std::istream& operator>>(std::istream& is, Vector2D& v);

	double normalize();
};