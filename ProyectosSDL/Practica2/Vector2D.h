#pragma once
#include "checkML.h"
#include <iostream>

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D() : x_(), y_() {}
	Vector2D(double x, double y) : x_(x), y_(y) {}
	~Vector2D() {}

	// Gets
	double getX() const { return x_; }
	double getY() const { return y_; }

	// Sets
	void setXY(double x, double y) { x_ = x; y_ = y; }
	void setX(double x) { x_ = x; }
	void setY(double y) { y_ = y; }

	// Normaliza el vector
	void normalize();
	// Operando suma de vectores
	Vector2D operator+(const Vector2D& v) const;
	// Operando resta de vectores
	Vector2D operator-(const Vector2D& v) const;
	// Operando producto escalar de vectores
	Vector2D operator*(double d)const;
	// Operando producto de un vector por un escalar
	double operator*(const Vector2D& d) const;

	/// Para debug: operando para el cout
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};