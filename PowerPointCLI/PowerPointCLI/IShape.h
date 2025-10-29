#pragma once
#include <string>
#include <iostream>

class IShape {
public:
	virtual ~IShape() = default;
	virtual void draw() const = 0;
	virtual std::string type() const = 0;
};