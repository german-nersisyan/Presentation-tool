# PowerPoint CLI

**PowerPoint CLI** is a command-line tool written in C++ that allows you to create, edit, and export simple presentations. It implements **Command pattern**, **Undo/Redo**, **SVG export**, **Logging**, **JSONSerializer**.

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
- 📑 JSON Serialization
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
- **JSONSerializer.cpp** - Handles saving and loading presentations using JSON format.

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
├─ Serializer/
│ └─ JSONSerializer.h
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
├─ JSONSerializer.cpp
├─ Logger.cpp
├─ PowerPointCLI.cpp
└─ SVGRenderer.cpp
```

## Example Usage

```bash
# Create first presentation
add-slide -title "Title Slide"
add-shape -type rectangle -width 200 -height 100 -x 50 -y 50 -color red -filled
add-shape -type circle -radius 40 -x 300 -y 150 -color blue
show-slides -index 0

# Create second slide
add-slide -title "Content Slide"
add-shape -type square -size 80 -x 100 -y 100 -color green -filled
add-shape -type triangle -side 60 -x 250 -y 200 -color purple

# View all slides
show-slides

# Navigate and edit
select-slide -index 0
add-shape -type circle -radius 25 -x 150 -y 250 -color yellow
show-slides -index 0

# Delete and undo
select-slide -index 1
delete-shape -index 1 -shape 0
show-slides -index 1
undo
show-slides -index 1

# Export and save
export-svg -index 0 -file slide_1.svg
export-svg -index 1 -file slide_2.svg
save-json -file my_presentation.json

# History and redo
history
redo
undo

# Load and view saved presentation
load-json -file my_presentation.json
list-slides
show-slides

# Help and exit
help
exit
```
