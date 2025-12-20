#pragma once
#include <string>
#include <vector>

class IView {
public:
	virtual ~IView() = default;

	virtual void showAddedSlide(const std::string& title, int totalSlides) = 0;

	virtual void showRemovedSlide(const std::string& title) = 0;
	virtual void showInvalidSlideIndex() = 0;
	virtual void showNoSlides() = 0;

	virtual void showAddedShape(const std::string& type,
		int width,
		int height,
		const std::string& slideTitle,
		bool filled) = 0;
	virtual void showCannotAddShapeNoSlide() = 0;

	virtual void showMessage(const std::string& msg) = 0;

	virtual void showSlide(int index, const std::string& title) = 0;
};