#pragma once

#include "GameObject.h"

class ArkanoidObject : public GameObject
{
protected:
	Texture* texture_;
	Vector2D pos_;
	double width_;
	double height_;

public:
	ArkanoidObject();
	ArkanoidObject(Texture* t, Vector2D p, double w, double h);
	virtual ~ArkanoidObject() {}

	Vector2D getPosition() const { return pos_; }
	void setPosition(const Vector2D& p) { pos_ = p; }
	double getWidth() const { return width_; }
	void setWidth(double w) { width_ = w; }
	double getHeight() const { return height_; }
	void setHeight(double h) { height_ = h; }
	SDL_Rect getRect();

	virtual void setInitialState();
	virtual bool collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};