#pragma once
#include "IView.h"
#include <iostream>

class ConsoleView : public IView {
public:
	void showAddedSlide(const std::string& title, int totalSlides) override {
		std::cout << "Added slide: " << title
			<< " (Total slides: " << totalSlides << ")\n";
	}

	void showRemovedSlide(const std::string& title) override {
		std::cout << "Removed slide: " << title << "\n";
	}

	void showInvalidSlideIndex() override {
		std::cout << "Invalid slide index.\n";
	}

	void showNoSlides() override {
		std::cout << "No slides to remove.\n";
	}

	void showAddedShape(const std::string& type, int width, int height,
		const std::string& slideTitle, bool filled) override {
		std::cout << "Added shape: " << type
			<< " (" << width << "x" << height << ")"
			<< " to slide \"" << slideTitle << "\"\n";
		if (filled) std::cout << "Shape is filled.\n";
	}

	void showCannotAddShapeNoSlide() override {
		std::cout << "Cannot add shape. Add a slide first.\n";
	}

	void showMessage(const std::string& msg) override {
		std::cout << msg << "\n";
	}

	void showSlide(int index, const std::string& title) override {
		std::cout << index << ": " << title << "\n";
	}
};