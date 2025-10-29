#pragma once
#include "ICommand.h"
#include "Shapes.h"
#include "RectangleShape.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <memory>

class AddSlideCommand : public ICommand {
	std::map<std::string, std::string> options;
	std::set<std::string> flags;

public:
	AddSlideCommand(const std::map<std::string, std::string>& opts,
		const std::set<std::string>& fl)
		: options(opts), flags(fl) {}

	void execute() override {
		std::cout << "Executing AddSlideCommand...\n";
		if (options.count("-title"))
			std::cout << "Title: " << options.at("-title") << "\n";
		if (options.count("-background"))
			std::cout << "Background: " << options.at("-background") << "\n";
		if (flags.count("-public"))
			std::cout << "This slide is public.\n";
	}
};

class RemoveSlideCommand : public ICommand {
	std::map<std::string, std::string> options;

public:
	RemoveSlideCommand(const std::map<std::string, std::string>& opts)
		: options(opts) {}

	void execute() override {
		std::cout << "Executing RemoveSlideCommand...\n";
		if (options.count("-index"))
			std::cout << "Removing slide at index: " << options.at("-index") << "\n";
	}
};

class AddShapeCommand : public ICommand {
	std::map<std::string, std::string> options;
	std::set<std::string> flags;
	Shapes& shapesContainer;

public:
	AddShapeCommand(const std::map<std::string, std::string>& opts,
		const std::set<std::string>& fl,
		Shapes& shapes)
		: options(opts), flags(fl), shapesContainer(shapes) {}

	void execute() override {
		std::cout << "Executing AddShapeCommand...\n";

		std::string type = options.count("-type") ? options.at("-type") : "rectangle";
		int width = options.count("-width") ? std::stoi(options.at("-width")) : 100;
		int height = options.count("-height") ? std::stoi(options.at("-height")) : 100;

		if (type == "rectangle") {
			shapesContainer.addShape(std::make_shared<RectangleShape>(width, height));
		}

		if (flags.count("-filled"))
			std::cout << "Shape is filled.\n";

		std::cout << "Added shape: " << type << " (" << width << "x" << height << ")\n";
	}
};