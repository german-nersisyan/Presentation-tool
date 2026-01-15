
#pragma once
#include "Tokenizer.h"
#include "Parser.h"
#include "CommandRegistry.h"
#include "IView.h"
#include "Model.h"
#include "CommandHistory.h"
#include "IRenderer.h"
#include "ILogger.h"
#include "ISerializer.h"
#include "ICommandJournal.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Controller {
	Tokenizer tokenizer;
	Parser parser;
	CommandRegistry& registry;
	Model& model;
	IView& view;
	CommandHistory& history;
	IRenderer& renderer;
	ILogger& logger;
	ISerializer& serializer;
	ICommandJournal& journal;
	bool isRunning = true;

public:
	Controller(IView& v, Model& m, CommandRegistry& reg, ILogger& log, ISerializer& ser, IRenderer& rend, ICommandJournal& jou, CommandHistory& hist)
		: view(v), model(m), registry(reg), history(hist), renderer(rend), logger(log), serializer(ser), journal(jou) {
		logger.info("Controller initialized");
	}

	void run() {
		view.showMessage("PowerPoint CLI started. Type 'exit' to quit.");
		logger.info("CLI started");

		while (isRunning) {
			try {
				std::cout << "> ";
				std::string input;
				std::getline(std::cin, input);

				logger.info("Input: " + input);

				if (!input.empty()) {
					journal.record(input);
				}


				auto tokens = tokenizer.tokenize(input);
				auto data = parser.parse(tokens);

				ICommandFactory* factory = registry.getFactory(data.name);
				if (!factory) {
					logger.warn("Unknown command: " + data.name);
					view.showMessage("Unknown command: " + data.name);
					continue;
				}

				auto command = factory->create(data.options, data.flags, model, view);

				logger.info("Execute command: " + data.name);
				history.execute(std::move(command), data.name);
			}
			catch (const std::exception& ex) {
				logger.error(ex.what());
				view.showMessage(std::string("Error: ") + ex.what());
			}
		}
	}

	void exit() {
		logger.info("CLI exiting");
		view.showMessage("Exiting PowerPoint CLI...");
		isRunning = false;
	}
};