#pragma once
#include "IView.h"
#include "ILogger.h"
#include <iostream>

class ConsoleView : public IView {
	ILogger& logger;

public:
	explicit ConsoleView(ILogger& log) : logger(log) {}

	void showAddedSlide(const std::string& title, int totalSlides) override {
		std::string msg =
			"Added slide: " + title +
			" (Total slides: " + std::to_string(totalSlides) + ")";

		std::cout << msg << "\n";
		logger.info(msg);
	}

	void showRemovedSlide(const std::string& title) override {
		std::string msg = "Removed slide: " + title;
		std::cout << msg << "\n";
		logger.info(msg);
	}

	void showInvalidSlideIndex() override {
		std::string msg = "Invalid slide index.";
		std::cout << msg << "\n";
		logger.warn(msg);
	}

	void showNoSlides() override {
		std::string msg = "No slides to remove.";
		std::cout << msg << "\n";
		logger.warn(msg);
	}

	void showAddedShape(const std::string& type, int width, int height,
		const std::string& slideTitle, bool filled) override {

		std::string msg =
			"Added shape: " + type +
			" (" + std::to_string(width) + "x" + std::to_string(height) + ")" +
			" to slide \"" + slideTitle + "\"";

		std::cout << msg << "\n";
		logger.info(msg);

		if (filled) {
			std::string filledMsg = "Shape is filled.";
			std::cout << filledMsg << "\n";
			logger.info(filledMsg);
		}
	}

	void showCannotAddShapeNoSlide() override {
		std::string msg = "Cannot add shape. Add a slide first.";
		std::cout << msg << "\n";
		logger.warn(msg);
	}

	void showMessage(const std::string& msg) override {
		std::cout << msg << "\n";
		logger.info(msg);
	}

	void showSlide(int index, const std::string& title) override {
		std::string msg =
			std::to_string(index) + ": " + title;

		std::cout << msg << "\n";
		logger.info(msg);
	}
};