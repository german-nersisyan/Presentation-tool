#pragma once
#include "IShape.h"
#include <string>
#include <iostream>
#include <memory>

class RectangleShape : public IShape {
	int width;
	int height;
	int x;
	int y;
	std::string color;
	bool filled;

public:
	RectangleShape(int w, int h, int xPos, int yPos, const std::string& c, bool f = false)
		: width(w), height(h), x(xPos), y(yPos), color(c), filled(f) {}

	std::string type() const override { return "Rectangle"; }

	void draw() const override {
		std::cout << "Drawing Rectangle: " << width << "x" << height
			<< " at (" << x << "," << y << ")"
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getX() const { return x; }
	int getY() const { return y; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
};

class SquareShape : public IShape {
	int size;
	int x;
	int y;
	std::string color;
	bool filled;

public:
	SquareShape(int s, int xPos, int yPos, const std::string& c, bool f = false)
		: size(s), x(xPos), y(yPos), color(c), filled(f) {}

	std::string type() const override { return "Square"; }

	void draw() const override {
		std::cout << "Drawing Square: " << size << "x" << size
			<< " at (" << x << "," << y << ")"
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getSize() const { return size; }
	int getX() const { return x; }
	int getY() const { return y; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
};

class TriangleShape : public IShape {
	int side;
	int x;
	int y;
	std::string color;
	bool filled;

public:
	TriangleShape(int s, int xPos, int yPos, const std::string& c, bool f = false)
		: side(s), x(xPos), y(yPos), color(c), filled(f) {}

	std::string type() const override { return "Triangle"; }

	void draw() const override {
		std::cout << "Drawing Triangle: side=" << side
			<< " at (" << x << "," << y << ")"
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getSide() const { return side; }
	int getX() const { return x; }
	int getY() const { return y; }
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