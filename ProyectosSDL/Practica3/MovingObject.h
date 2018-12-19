#pragma once

#include "ArkanoidObject.h"

class MovingObject : public ArkanoidObject
{
protected:
	Vector2D dir_;
	Vector2D vel_;
	uint speed_;

public:
	MovingObject();
	MovingObject(Texture* t, Vector2D p, Vector2D d, Vector2D v, uint s, double w, double h);
	virtual ~MovingObject() {};

	Vector2D getDirection() const { return dir_; }
	void setDirection(const Vector2D& d) { dir_ = d; }
	Vector2D getVelocity() const { return vel_; }
	void setVelocity(const Vector2D& v) { vel_ = v; }
	uint getSpeed() const { return speed_; }
	void setSpeed(uint s) { speed_ = s; }

	virtual void update();
	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};