#pragma once
#include "IShape.h"

class RectangleShape : public IShape {
	int width;
	int height;

public:
	RectangleShape(int w, int h) : width(w), height(h) {}

	void draw() const override {
		std::cout << "Drawing Rectangle: " << width << "x" << height << "\n";
	}

	std::string type() const override { return "Rectangle"; }
};