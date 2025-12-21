#pragma once
#include "Tokenizer.h"
#include "Parser.h"
#include "CommandRegistry.h"
#include "CommandFactories.h"
#include "Commands.h"
#include "IView.h"
#include "Model.h"
#include "CommandHistory.h"
#include "SVGRenderer.h"
#include "Logger.h"
#include "CommandJournal.h"

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
	CommandHistory history;
	SVGRenderer renderer;
	CommandJournal journal;
	bool isRunning = true;

public:
	Controller(IView& v, Model& m)
		: view(v), model(m) {

		registry.registerFactory("add-slide", std::make_unique<AddSlideFactory>());
		registry.registerFactory("remove-slide", std::make_unique<RemoveSlideFactory>());
		registry.registerFactory("add-shape", std::make_unique<AddShapeFactory>());
		registry.registerFactory("list-slides", std::make_unique<ListSlidesFactory>());
		registry.registerFactory("help", std::make_unique<HelpFactory>(registry));
		registry.registerFactory("move-shape", std::make_unique<MoveShapeFactory>());
		registry.registerFactory("delete-shape", std::make_unique<DeleteShapeFactory>());
		registry.registerFactory("save-json", std::make_unique<SaveJsonFactory>());
		registry.registerFactory("load-json", std::make_unique<LoadJsonFactory>());

		Logger::instance().info("Controller initialized");
	}

	void run() {
		view.showMessage("PowerPoint CLI started. Type 'exit' to quit.");
		Logger::instance().info("CLI started");

		while (isRunning) {
			try {
				std::cout << "> ";
				std::string input;
				std::getline(std::cin, input);

				Logger::instance().info("Input: " + input);

				if (!input.empty()) {
					journal.record(input);
				}

				if (input == "exit") {
					Logger::instance().info("Exit command received");
					exit();
					break;
				}

				if (input == "undo") {
					Logger::instance().info("Undo command");
					history.undo(view);
					continue;
				}

				if (input == "redo") {
					Logger::instance().info("Redo command");
					history.redo(view);
					continue;
				}

				if (input == "history") {
					Logger::instance().info("History command");
					history.showHistory(view);
					continue;
				}

				auto tokens = tokenizer.tokenize(input);
				auto data = parser.parse(tokens);

				if (data.name == "export-svg") {
					int index = std::stoi(data.options.at("-index"));
					std::string file = data.options.at("-file");

					Logger::instance().info(
						"export-svg index=" + std::to_string(index) +
						" file=" + file
					);

					if (renderer.renderSlide(model, index, file)) {
						view.showMessage("SVG saved to " + file);
						Logger::instance().info("SVG export success");
					}
					else {
						view.showMessage("Failed to export SVG");
						Logger::instance().error("SVG export failed");
					}
					continue;
				}

				auto& factory = registry.getFactory(data.name);
				auto command = factory.create(data.options, data.flags, model, view);

				Logger::instance().info("Execute command: " + data.name);
				history.execute(std::move(command), data.name);
			}
			catch (const std::exception& ex) {
				Logger::instance().error(ex.what());
				view.showMessage(std::string("Error: ") + ex.what());
			}
		}
	}

	void exit() {
		Logger::instance().info("CLI exiting");
		view.showMessage("Exiting PowerPoint CLI...");
		isRunning = false;
	}
};