# PowerPoint CLI

**PowerPoint CLI** is a command-line tool written in C++ that allows you to create, edit, and export simple presentations. It implements **Command pattern**, **Undo/Redo**, **SVG export**, **Logging**.

This project is intended as an educational and portfolio-level project.

---

## ✨ Features

- 📑 Create and remove slides
- 🔺 Add shapes (Rectangle, Square, Triangle, Circle)
- ↩️ Undo / Redo
- 🕓 Command history
- 🖼 Export slides to SVG
- 🧾 Logger (`cli.log`)
- 📜 Command journal (`cli.jou`)
- 🧠 Clean MVC + Command architecture

### Description

- **CLI_Prsr** – Core parser, tokenizer, command factories, command history, and controller.
- **Model** – Represents slides, shapes, and presentation data.
- **Logger** – Handles logging of CLI actions and maintains command journal.
- **Visualization** – Handles SVG rendering of slides.
- **View** – Handles console output.
- **src/CLI_Parser** – Implementation of parser, tokenizer, and commands.
- **src/Logger.cpp** – Implementation of logging system.
- **PowerPointCLI.cpp** – Main entry point for CLI application.
- **SVGRenderer.cpp** – Implementation of SVG export.

#File structure in Visual Studio

```text
include/
├─ CLI_Prsr/
│ ├─ CommandFactories.h
│ ├─ CommandHistory.h
│ ├─ CommandRegistry.h
│ ├─ Commands.h
│ ├─ Controller.h
│ ├─ ICommand.h
│ ├─ ICommandFactory.h
│ ├─ Parser.h
│ ├─ Token.h
│ └─ Tokenizer.h
├─ Model/
│ ├─ IShape.h
│ ├─ Model.h
│ └─ Shapes.h
├─ Logger/
│ ├─ CommandJournal.h
│ └─ Logger.h
├─ Visualization/
│ └─ SVGRenderer.h
├─ View/
│ ├─ ConsoleView.h
│ └─ IView.h

src/
├─ CLI_Parser/
│ ├─ Commands.cpp
│ ├─ Parser.cpp
│ └─ Tokenizer.cpp
├─ Logger.cpp
├─ PowerPointCLI.cpp
└─ SVGRenderer.cpp
```

## Example Usage

add-slide -title Demo
add-shape -type rectangle -width 120 -height 60 -color red -filled
add-shape -type square -size 40 -color blue
export-svg -index 0 -file demo.svg
undo
redo
exit