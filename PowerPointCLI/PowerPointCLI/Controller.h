#pragma once
#include "Tokenizer.h"
#include "Parser.h"
#include "CommandRegistry.h"
#include "CommandFactories.h"
#include "Commands.h"
#include "IView.h"
#include "Model.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Controller {
	Tokenizer tokenizer;
	Parser parser;
	CommandRegistry registry;
	Model& model;
	IView& view;
	bool isRunning = true;

public:
	Controller(IView& v, Model& m) : view(v), model(m) {
		registry.registerFactory("add-slide", std::make_unique<AddSlideFactory>());
		registry.registerFactory("remove-slide", std::make_unique<RemoveSlideFactory>());
		registry.registerFactory("add-shape", std::make_unique<AddShapeFactory>());
		registry.registerFactory("list-slides", std::make_unique<ListSlidesFactory>());
		registry.registerFactory("help", std::make_unique<HelpFactory>(registry));
		registry.registerFactory("show-slide", std::make_unique<ShowSlideFactory>());
	}

	void run() {
		view.showMessage("PowerPoint CLI started. Type 'exit' to quit.");

		while (isRunning) {
			try {
				std::cout << "> ";
				std::string input;
				std::getline(std::cin, input);

				if (input == "exit") {
					exit();
					break;
				}

				auto tokens = tokenizer.tokenize(input);
				auto data = parser.parse(tokens);

				auto& factory = registry.getFactory(data.name);
				auto command = factory.create(data.options, data.flags, model, view);

				command->execute();
			}
			catch (const std::exception& ex) {
				view.showMessage(std::string("Error: ") + ex.what());
			}
		}
	}

	void exit() {
		view.showMessage("Exiting PowerPoint CLI...");
		isRunning = false;
	}
};