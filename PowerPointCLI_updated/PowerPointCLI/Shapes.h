#pragma once
#include "IShape.h"
#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include "IShape.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
	std::string toSvg() const override {
		std::ostringstream oss;
		oss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width
			<< "\" height=\"" << height << "\" fill=\"" << (filled ? color : "none")
			<< "\" stroke=\"" << color << "\" />";
		return oss.str();
	}

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
	json toJson() const override {
		json j;
		j["type"] = "Rectangle";
		j["width"] = width;
		j["height"] = height;
		j["x"] = x;
		j["y"] = y;
		j["color"] = color;
		j["filled"] = filled;
		return j;
	}
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
	std::string toSvg() const override {
		std::ostringstream oss;
		oss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << size
			<< "\" height=\"" << size << "\" fill=\"" << (filled ? color : "none")
			<< "\" stroke=\"" << color << "\" />";
		return oss.str();
	}

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
	json toJson() const override {
		json j;
		j["type"] = "Square";
		j["size"] = size;
		j["x"] = x;
		j["y"] = y;
		j["color"] = color;
		j["filled"] = filled;
		return j;
	}
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
	std::string toSvg() const override {
		std::ostringstream oss;
		oss << "<polygon points=\"" << x << "," << y << " " << x + side << "," << y << " "
			<< x + side/2 << "," << (y - side) << "\" fill=\"" << (filled ? color : "none")
			<< "\" stroke=\"" << color << "\" />";
		return oss.str();
	}

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
	json toJson() const override {
		json j;
		j["type"] = "Triangle";
		j["side"] = side;
		j["x"] = x;
		j["y"] = y;
		j["color"] = color;
		j["filled"] = filled;
		return j;
	}
};

class CircleShape : public IShape {
	int radius;
	int x;
	int y;
	std::string color;
	bool filled;

public:
	CircleShape(int r, int cx, int cy, const std::string& c, bool f = false)
		: radius(r), x(cx), y(cy), color(c), filled(f) {}

	std::string type() const override { return "Circle"; }
	std::string toSvg() const override {
		std::ostringstream oss;
		oss << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << radius
			<< "\" fill=\"" << (filled ? color : "none") << "\" stroke=\"" << color << "\" />";
		return oss.str();
	}

	void draw() const override {
		std::cout << "Drawing Circle: radius=" << radius
			<< ", center=(" << x << "," << y << ")"
			<< ", color: " << color
			<< (filled ? ", filled" : ", not filled") << "\n";
	}

	int getRadius() const { return radius; }
	int getX() const { return x; }
	int getY() const { return y; }
	const std::string& getColor() const { return color; }
	bool isFilled() const { return filled; }
	json toJson() const override {
		json j;
		j["type"] = "Circle";
		j["radius"] = radius;
		j["x"] = x;
		j["y"] = y;
		j["color"] = color;
		j["filled"] = filled;
		return j;
	}
};