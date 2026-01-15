#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IShape.h"

struct Slide {
	std::string title;
	std::vector<std::shared_ptr<IShape>> shapes;
};

class Model {
	std::vector<Slide> slides;
	int currentSlide = -1;

public:
	Model() = default;

	int addSlide(const std::string& title) {
		slides.push_back(Slide{title, {}});
		currentSlide = static_cast<int>(slides.size()) - 1;
		return currentSlide;
	}

	bool removeSlide(int index) {
		if (!isValidSlide(index))
			return false;

		slides.erase(slides.begin() + index);

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

		slides.insert(slides.begin() + index, Slide{title, shapes});
		currentSlide = index;
	}

	bool isValidSlide(int index) const {
		return index >= 0 && index < static_cast<int>(slides.size());
	}

	int getSlideCount() const {
		return static_cast<int>(slides.size());
	}

	const std::string& getSlideTitle(int index) const {
		return slides.at(index).title;
	}

	int getCurrentSlide() const {
		return currentSlide;
	}

	bool setCurrentSlide(int index) {
		if (!isValidSlide(index)) return false;
		currentSlide = index;
		return true;
	}

	bool hasSlides() const {
		return !slides.empty();
	}

	// Adds a shape to the current slide. Returns true on success.
	bool addShapeToCurrentSlide(std::shared_ptr<IShape> shape) {
		if (currentSlide >= 0 && currentSlide < static_cast<int>(slides.size())) {
			slides[currentSlide].shapes.push_back(shape);
			return true;
		}
		return false;
	}

	// Removes the last shape from the current slide and returns it (or nullptr).
	std::shared_ptr<IShape> removeLastShapeFromCurrentSlide() {
		if (currentSlide >= 0 && currentSlide < static_cast<int>(slides.size()) && !slides[currentSlide].shapes.empty()) {
			auto shp = slides[currentSlide].shapes.back();
			slides[currentSlide].shapes.pop_back();
			return shp;
		}
		return nullptr;
	}

	const std::vector<std::shared_ptr<IShape>>& getShapes(int slideIndex) const {
		return slides.at(slideIndex).shapes;
	}

	// Removes a shape and returns it; returns nullptr if indexes invalid.
	std::shared_ptr<IShape> removeShape(int slideIndex, int shapeIndex) {
		if (slideIndex < 0 || slideIndex >= getSlideCount()) return nullptr;
		auto& shapes = slides[slideIndex].shapes;
		if (shapeIndex < 0 || shapeIndex >= static_cast<int>(shapes.size())) return nullptr;
		auto shp = shapes[shapeIndex];
		shapes.erase(shapes.begin() + shapeIndex);
		return shp;
	}

	// Inserts or appends a shape. Returns true on success.
	bool addShape(int slideIndex, int shapeIndex, std::shared_ptr<IShape> shape) {
		if (slideIndex < 0 || slideIndex >= getSlideCount()) return false;
		auto& shapes = slides[slideIndex].shapes;
		if (shapeIndex < 0 || shapeIndex > static_cast<int>(shapes.size())) {
			shapes.push_back(shape);
		} else {
			shapes.insert(shapes.begin() + shapeIndex, shape);
		}
		return true;
	}

	void clear() {
		slides.clear();
		currentSlide = -1;
	}
};