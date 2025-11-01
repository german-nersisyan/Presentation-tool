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

	void addSlide(const std::string& title) {
		slides.push_back(title);
		slideShapes.emplace_back();
		currentSlide = slides.size() - 1;
	}

	bool removeSlide(int index) {
		if (index < 0 || index >= static_cast<int>(slides.size()))
			return false;
		slides.erase(slides.begin() + index);
		slideShapes.erase(slideShapes.begin() + index);
		if (slides.empty()) currentSlide = -1;
		else if (currentSlide >= static_cast<int>(slides.size()))
			currentSlide = slides.size() - 1;
		return true;
	}

	int getSlideCount() const { return slides.size(); }
	const std::string& getSlideTitle(int index) const { return slides.at(index); }
	int getCurrentSlide() const { return currentSlide; }
	bool hasSlides() const { return !slides.empty(); }

	void addShapeToCurrentSlide(std::shared_ptr<IShape> shape) {
		if (currentSlide >= 0)
			slideShapes[currentSlide].push_back(shape);
	}

	const std::vector<std::shared_ptr<IShape>>& getShapes(int slideIndex) const {
		return slideShapes.at(slideIndex);
	}
};