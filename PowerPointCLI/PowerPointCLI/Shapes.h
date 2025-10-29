#pragma once
#include "IShape.h"
#include <vector>
#include <memory>

class Shapes {
	std::vector<std::shared_ptr<IShape>> shapes;

public:
	void addShape(std::shared_ptr<IShape> shape) {
		shapes.push_back(shape);
	}

	void removeShape(size_t index) {
		if (index < shapes.size())
			shapes.erase(shapes.begin() + index);
	}

	void drawAll() const {
		for (const auto& shape : shapes) {
			shape->draw();
		}
	}

	size_t count() const { return shapes.size(); }
};