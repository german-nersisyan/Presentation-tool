#pragma once
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

class IShape {
public:
	virtual ~IShape() = default;
	virtual void draw() const = 0;
	virtual std::string type() const = 0;
	virtual std::string toSvg() const = 0;
	virtual json toJson() const = 0;
};