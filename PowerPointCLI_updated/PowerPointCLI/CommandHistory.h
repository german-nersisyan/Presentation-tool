#pragma once
#include "ICommand.h"
#include "IView.h"
#include <stack>
#include <vector>
#include <memory>
#include <string>

class CommandHistory {
	std::stack<std::unique_ptr<ICommand>> undoStack;
	std::stack<std::unique_ptr<ICommand>> redoStack;

	std::vector<std::string> undoNames;
	std::vector<std::string> redoNames;

public:
	void execute(std::unique_ptr<ICommand> cmd, const std::string& name) {
		if (!cmd) return;

		cmd->execute();

		if (cmd->isUndoable()) {
			undoStack.push(std::move(cmd));
			undoNames.push_back(name);

			// new command clears redo
			while (!redoStack.empty()) redoStack.pop();
			redoNames.clear();
		}
	}

	void undo(IView& view) {
		if (undoStack.empty()) {
			view.showMessage("Nothing to undo");
			return;
		}

		auto cmd = std::move(undoStack.top());
		undoStack.pop();

		std::string name = undoNames.back();
		undoNames.pop_back();

		cmd->undo();

		redoStack.push(std::move(cmd));
		redoNames.push_back(name);

		view.showMessage("Undo: " + name);
	}

	void redo(IView& view) {
		if (redoStack.empty()) {
			view.showMessage("Nothing to redo");
			return;
		}

		auto cmd = std::move(redoStack.top());
		redoStack.pop();

		std::string name = redoNames.back();
		redoNames.pop_back();

		cmd->execute();

		undoStack.push(std::move(cmd));
		undoNames.push_back(name);

		view.showMessage("Redo: " + name);
	}

	void showHistory(IView& view) const {
		view.showMessage("Undo stack:");
		if (undoNames.empty())
			view.showMessage("  (empty)");
		else
			for (size_t i = 0; i < undoNames.size(); ++i)
				view.showMessage("  " + std::to_string(i) + ": " + undoNames[i]);

		view.showMessage("Redo stack:");
		if (redoNames.empty())
			view.showMessage("  (empty)");
		else
			for (size_t i = 0; i < redoNames.size(); ++i)
				view.showMessage("  " + std::to_string(i) + ": " + redoNames[i]);
	}
};