#include "CommandFactories.h"
#include "ICommandFactory.h"
#include "Commands.h"
#include "Model.h"
#include "IView.h"
#include "CommandRegistry.h"
#include "ShapeFactory.h"
#include "CommandHistory.h"
#include "IRenderer.h"

#include <memory>
#include <map>
#include <set>
#include <string>
#include <functional>

// Concrete factories

class AddSlideFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& /*flags*/,
        Model& model,
        IView& view) override
    {
        std::string title = options.count("-title") ? options.at("-title") : "Untitled Slide";
        return std::make_unique<AddSlideCommand>(title, model, view);
    }
};

class RemoveSlideFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& /*flags*/,
        Model& model,
        IView& view) override
    {
        int index = options.count("-index") ? std::stoi(options.at("-index")) : -1;
        return std::make_unique<RemoveSlideCommand>(index, model, view);
    }
};

class AddShapeFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& flags,
        Model& model,
        IView& view) override
    {
        ShapeFactory sf;
        auto shape = sf.create(options, flags);
        if (!shape) {
            throw std::runtime_error("Failed to create shape");
        }
        return std::make_unique<AddShapeCommand>(shape, model, view);
    }
};

class ListSlidesFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& /*options*/,
        const std::set<std::string>& /*flags*/,
        Model& model,
        IView& view) override
    {
        return std::make_unique<ListSlidesCommand>(model, view);
    }
};

class HelpFactory : public ICommandFactory {
    CommandRegistry& registry;

public:
    HelpFactory(CommandRegistry& r) : registry(r) {}

    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& /*options*/,
        const std::set<std::string>& /*flags*/,
        Model& /*model*/,
        IView& view) override
    {
        return std::make_unique<HelpCommand>(view, registry);
    }
};

class MoveShapeFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& /*flags*/,
        Model& model,
        IView& view) override
    {
        int slideIndex = options.count("-index") ? std::stoi(options.at("-index")) : 0;
        int shapeIndex = options.count("-shape") ? std::stoi(options.at("-shape")) : 0;
        int x = options.count("-x") ? std::stoi(options.at("-x")) : 0;
        int y = options.count("-y") ? std::stoi(options.at("-y")) : 0;

        return std::make_unique<MoveShapeCommand>(model, view, slideIndex, shapeIndex, x, y);
    }
};

class DeleteShapeFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& /*flags*/,
        Model& model,
        IView& view) override
    {
        int slideIndex = options.count("-index") ? std::stoi(options.at("-index")) : 0;
        int shapeIndex = options.count("-shape") ? std::stoi(options.at("-shape")) : 0;

        return std::make_unique<DeleteShapeCommand>(model, view, slideIndex, shapeIndex);
    }
};

class SaveJsonFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>&,
        Model& model,
        IView& view) override {

        auto it = options.find("-file");
        if (it == options.end())
            throw std::runtime_error("Missing -file option");

        return std::make_unique<SaveJsonCommand>(it->second, model, view);
    }
};

class LoadJsonFactory : public ICommandFactory {
public:
    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>&,
        Model& model,
        IView& view) override {

        auto it = options.find("-file");
        if (it == options.end())
            throw std::runtime_error("Missing -file option");

        return std::make_unique<LoadJsonCommand>(it->second, model, view);
    }
};

class ExportSvgFactory : public ICommandFactory {
    IRenderer& renderer;
public:
    explicit ExportSvgFactory(IRenderer& r) : renderer(r) {}

    std::unique_ptr<ICommand> create(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>&,
        Model& model,
        IView& view) override
    {
        auto itFile = options.find("-file");
        auto itIndex = options.find("-index");
        if (itFile == options.end() || itIndex == options.end())
            throw std::runtime_error("export-svg requires -file and -index");

        int index = std::stoi(itIndex->second);
        std::string file = itFile->second;

        class ExportSvgCommandLocal : public ICommand {
            IRenderer& renderer;
            Model& model;
            IView& view;
            int index;
            std::string file;
        public:
            ExportSvgCommandLocal(IRenderer& r, Model& m, IView& v, int idx, std::string f)
                : renderer(r), model(m), view(v), index(idx), file(std::move(f)) {}

            void execute() override {
                if (renderer.renderSlide(model, index, file)) {
                    view.showMessage(std::string("SVG saved to ") + file);
                } else {
                    view.showMessage("Failed to export SVG");
                }
            }
            void undo() override {}
            bool isUndoable() const override { return false; }
        };

        return std::make_unique<ExportSvgCommandLocal>(renderer, model, view, index, file);
    }
};

// Additional command implementations that need external services:
class UndoCommand : public ICommand {
    CommandHistory& history;
    IView& view;
public:
    UndoCommand(CommandHistory& h, IView& v) : history(h), view(v) {}
    void execute() override { history.undo(view); }
    void undo() override {}
    bool isUndoable() const override { return false; }
};

class RedoCommand : public ICommand {
    CommandHistory& history;
    IView& view;
public:
    RedoCommand(CommandHistory& h, IView& v) : history(h), view(v) {}
    void execute() override { history.redo(view); }
    void undo() override {}
    bool isUndoable() const override { return false; }
};

class HistoryCommand : public ICommand {
    CommandHistory& history;
    IView& view;
public:
    HistoryCommand(CommandHistory& h, IView& v) : history(h), view(v) {}
    void execute() override { history.showHistory(view); }
    void undo() override {}
    bool isUndoable() const override { return false; }
};

class ExitCommand : public ICommand {
    std::function<void()> exitCb;
public:
    ExitCommand(std::function<void()> cb) : exitCb(std::move(cb)) {}
    void execute() override { if (exitCb) exitCb(); }
    void undo() override {}
    bool isUndoable() const override { return false; }
};

void registerDefaultFactories(CommandRegistry& registry, CommandHistory& history, std::function<void()> exitCallback, IRenderer& renderer) {
    registry.registerFactory("add-slide", std::make_unique<AddSlideFactory>());
    registry.registerFactory("remove-slide", std::make_unique<RemoveSlideFactory>());
    registry.registerFactory("add-shape", std::make_unique<AddShapeFactory>());
    registry.registerFactory("list-slides", std::make_unique<ListSlidesFactory>());
    registry.registerFactory("help", std::make_unique<HelpFactory>(registry));
    registry.registerFactory("move-shape", std::make_unique<MoveShapeFactory>());
    registry.registerFactory("delete-shape", std::make_unique<DeleteShapeFactory>());
    registry.registerFactory("save-json", std::make_unique<SaveJsonFactory>());
    registry.registerFactory("load-json", std::make_unique<LoadJsonFactory>());
    registry.registerFactory("export-svg", std::make_unique<ExportSvgFactory>(renderer));
    
    // show-slides [-index N]
    class ShowSlidesFactory : public ICommandFactory {
    public:
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>& options, const std::set<std::string>&, Model& model, IView& view) override {
            int idx = -1;
            auto it = options.find("-index");
            if (it != options.end()) idx = std::stoi(it->second);
            return std::make_unique<ShowSlidesCommand>(model, view, idx);
        }
    };

    registry.registerFactory("show-slides", std::make_unique<ShowSlidesFactory>());
    
    // select-slide -index N
    class SelectSlideFactory : public ICommandFactory {
    public:
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>& options, const std::set<std::string>&, Model& model, IView& view) override {
            auto it = options.find("-index");
            if (it == options.end()) throw std::runtime_error("select-slide requires -index");
            int idx = std::stoi(it->second);
            return std::make_unique<SelectSlideCommand>(model, view, idx);
        }
    };

    registry.registerFactory("select-slide", std::make_unique<SelectSlideFactory>());

    // factories for history/undo/redo/exit that capture external services
    class UndoFactoryLocal : public ICommandFactory {
        CommandHistory& hist;
    public:
        explicit UndoFactoryLocal(CommandHistory& h) : hist(h) {}
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>&, const std::set<std::string>&, Model&, IView& view) override {
            return std::make_unique<UndoCommand>(hist, view);
        }
    };

    class RedoFactoryLocal : public ICommandFactory {
        CommandHistory& hist;
    public:
        explicit RedoFactoryLocal(CommandHistory& h) : hist(h) {}
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>&, const std::set<std::string>&, Model&, IView& view) override {
            return std::make_unique<RedoCommand>(hist, view);
        }
    };

    class HistoryFactoryLocal : public ICommandFactory {
        CommandHistory& hist;
    public:
        explicit HistoryFactoryLocal(CommandHistory& h) : hist(h) {}
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>&, const std::set<std::string>&, Model&, IView& view) override {
            return std::make_unique<HistoryCommand>(hist, view);
        }
    };

    class ExitFactoryLocal : public ICommandFactory {
        std::function<void()> cb;
    public:
        explicit ExitFactoryLocal(std::function<void()> c) : cb(std::move(c)) {}
        std::unique_ptr<ICommand> create(const std::map<std::string, std::string>&, const std::set<std::string>&, Model&, IView&) override {
            return std::make_unique<ExitCommand>(cb);
        }
    };

    registry.registerFactory("undo", std::make_unique<UndoFactoryLocal>(history));
    registry.registerFactory("redo", std::make_unique<RedoFactoryLocal>(history));
    registry.registerFactory("history", std::make_unique<HistoryFactoryLocal>(history));
    registry.registerFactory("exit", std::make_unique<ExitFactoryLocal>(exitCallback));
}
