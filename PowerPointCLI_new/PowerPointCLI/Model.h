#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Shapes.h"

class Model {
	std::vector<std::string> slides;
	std::vector<std::vector<std::shared_ptr<IShape>>> slideShapes;
	int currentSlide = -1;

public:
	Model() = default;

	int addSlide(const std::string& title) {
		slides.push_back(title);
		slideShapes.emplace_back();
		currentSlide = static_cast<int>(slides.size()) - 1;
		return currentSlide;
	}

	bool removeSlide(int index) {
		if (!isValidSlide(index))
			return false;

		slides.erase(slides.begin() + index);
		slideShapes.erase(slideShapes.begin() + index);

		if (slides.empty())
			currentSlide = -1;
		else if (currentSlide >= static_cast<int>(slides.size()))
			currentSlide = static_cast<int>(slides.size()) - 1;

		return true;
	}

	void insertSlide(
		int index,
		const std::string& title,
		const std::vector<std::shared_ptr<IShape>>& shapes = {}
	) {
		if (index < 0 || index > static_cast<int>(slides.size()))
			index = static_cast<int>(slides.size());

		slides.insert(slides.begin() + index, title);
		slideShapes.insert(slideShapes.begin() + index, shapes);
		currentSlide = index;
	}

	bool isValidSlide(int index) const {
		return index >= 0 && index < static_cast<int>(slides.size());
	}

	int getSlideCount() const {
		return static_cast<int>(slides.size());
	}

	const std::string& getSlideTitle(int index) const {
		return slides.at(index);
	}

	int getCurrentSlide() const {
		return currentSlide;
	}

	bool hasSlides() const {
		return !slides.empty();
	}

	void addShapeToCurrentSlide(std::shared_ptr<IShape> shape) {
		if (currentSlide >= 0 &&
			currentSlide < static_cast<int>(slideShapes.size()))
		{
			slideShapes[currentSlide].push_back(shape);
		}
	}

	void removeLastShapeFromCurrentSlide() {
		if (currentSlide >= 0 &&
			currentSlide < static_cast<int>(slideShapes.size()) &&
			!slideShapes[currentSlide].empty())
		{
			slideShapes[currentSlide].pop_back();
		}
	}

	const std::vector<std::shared_ptr<IShape>>& getShapes(int slideIndex) const {
		return slideShapes.at(slideIndex);
	}

	bool removeShape(int slideIndex, int shapeIndex) {
		if (slideIndex < 0 || slideIndex >= getSlideCount()) return false;
		auto& shapes = slideShapes[slideIndex];
		if (shapeIndex < 0 || shapeIndex >= static_cast<int>(shapes.size())) return false;
		shapes.erase(shapes.begin() + shapeIndex);
		return true;
	}

	void addShape(int slideIndex, int shapeIndex, std::shared_ptr<IShape> shape) {
		if (slideIndex < 0 || slideIndex >= getSlideCount()) return;
		auto& shapes = slideShapes[slideIndex];
		if (shapeIndex < 0 || shapeIndex > static_cast<int>(shapes.size())) shapes.push_back(shape);
		else shapes.insert(shapes.begin() + shapeIndex, shape);
	}

	void clear() {
		slides.clear();
		slideShapes.clear();
		currentSlide = -1;
	}
};