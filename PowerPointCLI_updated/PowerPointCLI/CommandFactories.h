#pragma once
#include <map>
#include <memory>
#include <functional>

class CommandRegistry;
class CommandHistory;
class IRenderer;

// Registers the default command factories into the provided registry.
// The `history` is used for undo/redo/history commands, `exitCallback`
// is called when the exit command is executed, and `renderer` is used
// by factories that need to export slides to SVG.
void registerDefaultFactories(CommandRegistry& registry, CommandHistory& history, std::function<void()> exitCallback, IRenderer& renderer);