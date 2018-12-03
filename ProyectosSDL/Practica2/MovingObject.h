#pragma once
#include "ArkanoidObject.h"

class MovingObject :
	public ArkanoidObject
{
protected:
	Vector2D dir_,
		vel_;

	double speed_;

public:
	MovingObject();
	MovingObject(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture);
	virtual ~MovingObject();

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};