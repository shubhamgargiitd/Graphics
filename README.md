# VectorSketch

A desktop vector graphics editor built with C++17 and Qt6. Draw shapes, style them, move and resize them, and save/load files in SVG format.

![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue)
![Framework](https://img.shields.io/badge/framework-Qt6-green)

---

## Features

### Drawing Tools
| Tool | Description |
|---|---|
| Circle | Click and drag — radius grows from center of drag |
| Rectangle | Click and drag to define bounding box |
| Rounded Rectangle | Like rectangle; prompts for corner radius on release |
| Hexagon | Click and drag — radius grows from center |
| Line | Click and drag start/end points |
| Freehand | Hold and drag to draw a continuous path |
| Text | Click to place, type to enter text, Escape to commit |

### Editing Tools
| Tool | Description |
|---|---|
| Move | Click a shape to select and drag it |
| Resize | Click a shape and drag to scale it from its center |
| Eraser | Click or drag over shapes to delete them |

### Styling (top toolbar)
- **Fill color** — color picker + toggle fill on/off
- **Stroke color** — color picker
- **Stroke width** — numeric input
- **Font size** — applies to Text tool

### File Operations
- **New** — clears canvas (prompts to save if unsaved changes)
- **Open** — loads a `.svg` file from `xml_directory/`
- **Save / Save As** — writes to SVG format
- Unsaved changes are indicated by `*` in the window title

### Keyboard Shortcuts
| Shortcut | Action |
|---|---|
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |
| `Ctrl+X` | Cut selected shape |
| `Ctrl+C` | Copy selected shape |
| `Ctrl+V` | Paste at current mouse position |

### Canvas Behavior
- Click any shape to select it (blue dashed bounding box appears)
- Click empty area to deselect
- Undo/Redo stack is capped at 50 snapshots

---

## Build & Run

**Requirements:** CMake 3.16+, Qt6 (Core, Gui, Widgets, Svg)

```bash
# Linux / macOS
mkdir -p build && cd build
cmake ..
make
./VectorEditor
```

```bash
# Windows (Qt Creator recommended)
# Open CMakeLists.txt in Qt Creator → Configure → Build
```

> **Linux:** install `qt6-svg-dev` if toolbar icons don't appear.

---

## Project Structure

```
vectorSketch/
├── include/                        # All header files
│   ├── Document.h                  # Application state
│   ├── main_window.h               # Main window
│   ├── types.h                     # ToolType & ShapeType enums
│   ├── shapes/
│   │   ├── shape.h                 # Abstract Shape base class
│   │   └── individual_shape/       # One header per shape (7 total)
│   ├── tools/
│   │   ├── tool.h                  # Abstract Tool base class
│   │   ├── drawing_tool.h          # Intermediate base for drawing tools
│   │   ├── manipulation_tool.h     # Intermediate base for move/resize
│   │   ├── tool_manager.h
│   │   └── individual_tools/       # One header per tool (10 total)
│   └── file_actions/
│       └── file_manager.h
│
├── src/                            # All implementation files
│   ├── main.cpp
│   ├── Document.cpp                # Undo/redo, cut/copy/paste, selection
│   ├── event.cpp                   # Mouse & keyboard routing
│   ├── paint.cpp                   # paintEvent + toolbar state sync
│   ├── horizontal_toolbar.cpp      # Style controls
│   ├── vertical_toolbar.cpp        # Tool buttons
│   ├── menubar.cpp                 # File & Edit menus
│   ├── shapes/                     # Shape implementations (7 files)
│   ├── tools/
│   │   ├── drawing_tool.cpp        # Shared MousePressed/Move/Released logic
│   │   ├── manipulation_tool.cpp   # Shared select-transform-commit logic
│   │   ├── tool_manager.cpp
│   │   └── individual_tools/       # 10 tool implementations
│   ├── file_actions/
│   │   ├── file_manager.cpp        # New/Open/Save/SaveAs all in one place
│   │   └── parser.cpp              # SVG → Shape parsing
│   └── utils/                      # split, trim, distance helpers
│
├── icons/                          # SVG toolbar icons
├── xml_directory/                  # Saved sketch files go here
├── CMakeLists.txt
└── CLAUDE.md                       # Developer guide (conventions, extension patterns)
```

---

## Architecture

### Class Hierarchy

```
Shape (abstract)
├── Circle
├── Rectangle
├── RoundedRectangle
├── Hexagon
├── Line
├── Freehand
└── Text

Tool (abstract)
├── DrawingTool (abstract — shared mouse skeleton)
│   ├── CircleTool
│   ├── RectangleTool
│   ├── RoundedRectangleTool
│   ├── HexagonTool
│   └── LineTool
├── ManipulationTool (abstract — shared select/transform/commit)
│   ├── MoveTool
│   └── ResizeTool
├── FreehandTool
├── TextTool
└── EraserTool
```

### Key Components

| Class | Role |
|---|---|
| `Document` | All application state: shape list (`vector<unique_ptr<Shape>>`), undo/redo stacks, clipboard, current selection, style settings. Every mutation goes through `Modified()` which snapshots state for undo. |
| `MainWindow` | Qt entry point. Owns `Document`, `ToolManager`, `FileManager`. Routes events to the active tool and triggers repaints. |
| `ToolManager` | Holds one instance of each tool. Toggling a tool button twice deselects it (returning to selection mode). |
| `DrawingTool` | Template method base: `MousePressed` creates the shape, `MouseMove` updates it live, `MouseReleased` commits it to the document. Subclasses only implement `MakeShape()` and `CalculateParameters()`. |
| `ManipulationTool` | Template method base: `MousePressed` finds and lifts the target shape, `MouseMove` calls `ApplyTransform()`, `MouseReleased` commits. Subclasses only implement `ApplyTransform()`. |
| `FileManager` | All file I/O in one place: parse SVG→shapes on open, serialize shapes→SVG on save. |
| `Shape` | Abstract base. All shapes implement `Paint`, `Serialize`, `Clone`, `Move`, `Resize`, `Distance` (hit-testing), `GetCenter`, `PaintSurroundingRectangle`. |

### Design Patterns

- **Template Method** — `DrawingTool` and `ManipulationTool` define the skeleton; subclasses fill in the shape-specific steps.
- **Polymorphism** — `Shape` and `Tool` are abstract base classes. The canvas loop calls `shape->Paint(painter)` without knowing the concrete type.
- **Typed enums** — `GetType()` returns `ToolType` / `ShapeType` (defined in `types.h`) instead of strings, so typos are caught at compile time.
- **Snapshot undo** — `Document::Modified()` deep-clones the entire shape list before each change. Stack is capped at 50.
- **Ownership** — `Document` owns shapes via `unique_ptr`. Tools hold in-progress shapes via `shared_ptr`. `MainWindow` owns top-level objects via `unique_ptr`.

---

## SVG File Format

Sketches are saved as SVG files. Each shape maps to one SVG element:

```xml
<svg width="800" height="600" xmlns="http://www.w3.org/2000/svg">

<circle
style="fill:#00ff00;fill-opacity:0;stroke:#ff00ff;stroke-width:4"
cx="300" cy="267.5" r="96.15"/>

<rect
style="fill:#00ff00;fill-opacity:0;stroke:#ff00ff;stroke-width:4"
x="234" y="255" width="127" height="159"/>

<rounded_rect
style="fill:none;stroke:#ff00ff;stroke-width:4"
x="172" y="169" width="293" height="279" r="50"/>

<polygon
style="fill:#00ff00;fill-opacity:0;stroke:#ff00ff;stroke-width:4"
cx="474" cy="357.5" r="215.83" shape-type="hexagon"/>

<line
style="stroke:#13ff00;stroke-width:4"
x1="129" y1="232" x2="475" y2="409"/>

<path
style="stroke:#13ff00;stroke-width:4"
d="M 96 482 L 96 489 L 96 505 L 97 523"/>

<text
style="stroke:#13ff00;stroke-width:4"
x="484" y="263" font-size="24">
Hello world
</text>

</svg>
```

> Note: `rounded_rect` and `polygon` (hexagon) use custom element names not in the SVG standard. These files are intended to be opened by VectorSketch itself, not general SVG viewers.

---

## Extending the Editor

### Add a new shape

1. `include/shapes/individual_shape/myshape.h` — extend `Shape`, declare all pure virtuals
2. `src/shapes/myshape.cpp` — implement `Paint`, `Serialize`, `GetType`, `Distance`, `GetCenter`, `Move`, `Resize`, `Clone`, `Clone_wrt_movedPosition`, `PaintSurroundingRectangle`
3. Add a `ParseMyShape` function in `src/file_actions/parser.cpp`
4. Wire it into `FileManager::ParseCommand` in the same file
5. Add `ShapeType::MyShape` to `include/types.h`

### Add a new drawing tool

1. `include/tools/individual_tools/mytool.h` — extend `DrawingTool`, declare `MakeShape()` and `CalculateParameters()`
2. `src/tools/individual_tools/mytool.cpp` — implement those two methods
3. Add `ToolType::MyTool` to `include/types.h`
4. Add `shared_ptr<MyTool>` to `ToolManager` and wire up a `SelectMyTool()` method
5. Add a toolbar button in `MainWindow::CreateVerticalToolbar` (`src/vertical_toolbar.cpp`)
