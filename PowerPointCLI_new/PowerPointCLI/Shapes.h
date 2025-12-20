#pragma once
#include "IShape.h"
#include <string>
#include <iostream>
#include <memory>

class RectangleShape : public IShape {
	int width;
	int height;
	std::string color;
	bool filled;

public:
	RectangleShape(int w, int h, const std::string& c, bool f = false)
		: width(w), height(h), color(c), filled(f) {}

	std::string type() const override { return "Rectangle"; }

	void draw() const override {
		std::cout << "Drawing Rectangle: " << width << "x" << height
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
};

class SquareShape : public IShape {
	int size;
	std::string color;
	bool filled;

public:
	SquareShape(int s, const std::string& c, bool f = false)
		: size(s), color(c), filled(f) {}

	std::string type() const override { return "Square"; }

	void draw() const override {
		std::cout << "Drawing Square: " << size << "x" << size
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getSize() const { return size; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
};

class TriangleShape : public IShape {
	int side;
	std::string color;
	bool filled;

public:
	TriangleShape(int s, const std::string& c, bool f = false)
		: side(s), color(c), filled(f) {}

	std::string type() const override { return "Triangle"; }

	void draw() const override {
		std::cout << "Drawing Triangle: side=" << side
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getSide() const { return side; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
};

class CircleShape : public IShape {
	int radius;
	int x;
	int y;
	bool filled;

public:
	CircleShape(int r, int cx, int cy, bool f = false)
		: radius(r), x(cx), y(cy), filled(f) {}

	std::string type() const override { return "Circle"; }

	void draw() const override {
		std::cout << "Drawing Circle: radius=" << radius
			<< ", center=(" << x << "," << y << ")"
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getRadius() const { return radius; }
	int getX() const { return x; }
	int getY() const { return y; }
	bool isFilled() const { return filled; }
};