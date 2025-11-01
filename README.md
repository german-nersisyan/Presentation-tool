# 🖥️ CLI Presentation Tool

**CLI Presentation Tool** is a console-based application for managing presentation slides directly from the terminal.  
Currently, it supports a basic set of commands to explore and manipulate slides.

---

## 📌 Available Commands

The current version provides the following commands:

- **add-slide** : Add a new slide with optional `-title` and `-background`.
- **remove-slide** : Remove a slide by `-index`.
- **add-shape** : Add a shape to the current slide (`-type`, `-width`, `-height`, `-filled` flag).
- **list-slides** : List all slide titles.
- **show-slide** : Show a slide's content. Options: `-index N` or `-all` flag.
- **help** : Show help message with available commands.

You can see these commands in action by running the CLI and typing:

```text
help

## You can run the program using:

```bash
PowerPointCLI/Release/PowerPointCLI.exe

## Example Usage

# Add a new slide with a title
add-slide -title "My First Slide"

# Add another slide
add-slide -title "Conclusion" -background blue

# List all slides
list-slides
# Output:
# 0: My First Slide
# 1: Conclusion

# Show first slide
show-slide -index 0

# Show second slide
show-slide -index 1

# Show all slides
show-slide -all

# Display help for available commands
help