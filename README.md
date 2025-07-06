# brunch - Graphical Application Launcher

<img src="src/bl.png" alt="brunch logo" width="128" height="128">

## Overview

brunch is an independently maintained fork of xlunch that aims to be more usable. It's a lightweight, customizable graphical application launcher for X11 systems. It provides a full-screen or windowed interface for quickly launching applications, similar to dmenu or rofi, but with a graphical icon-based interface.

### Key Features

- **Graphical Interface**: Icon-based application selection with customizable layouts
- **Multiple Display Modes**: Full-screen, windowed, or desktop background modes
- **Search Functionality**: Real-time filtering of applications as you type
- **Customizable Appearance**: Background images, colors, fonts, and layout options
- **Cross-Platform Support**: Works on Linux and macOS
- **Lightweight**: Built with pure Xlib and Imlib2, no heavy dependencies

## Architecture

### Core Components

#### 1. Main Application (`src/brunch.c`)
The main application file containing:
- X11 window management and event handling
- User interface rendering with Imlib2
- Application launching and command execution
- Input handling (keyboard and mouse)

#### 2. Configuration System (`src/config.c`)
Handles all configuration options including:
- Command-line argument parsing
- Configuration file reading
- Default value management
- Option validation

#### 3. Utility Modules (`src/utils/`)
- **`calcutils.c`**: Layout calculations and positioning
- **`fontutils.c`**: Font loading and text rendering
- **`strutils.c`**: String manipulation utilities
- **`errutils.c`**: Error handling and logging

#### 4. Application Discovery (`src/binfinder.py`)
Python script that:
- Scans system for installed applications
- Extracts application metadata (name, icon, command)
- Generates DSV (Delimiter-Separated Values) format entries
- Supports both Linux (.desktop files) and macOS (.app bundles)
- Automatically generates application entries for better usability

### Data Structures

#### Entry Structure (`src/types.h`)
```c
typedef struct node {
    char title[256];    // Application name
    char icon[256];     // Icon file path
    char cmd[512];      // Command to execute
    int hovered;        // Hover state
    int clicked;        // Click state
    int hidden;         // Visibility state
    int x, y;          // Position coordinates
    struct node *next;  // Linked list pointer
} node_t;
```

#### Button Structure
```c
typedef struct button {
    char icon_normal[256];    // Normal state icon
    char icon_highlight[256]; // Highlighted state icon
    char cmd[512];           // Command to execute
    int hovered, clicked;    // State flags
    int x, y, w, h;         // Position and size
    struct button *next;     // Linked list pointer
} button_t;
```

## Installation

### Prerequisites

**Ubuntu/Debian:**
```bash
sudo apt install libimlib2-dev libx11-dev
```

**Fedora:**
```bash
sudo dnf install imlib2-devel libX11-devel
```

**macOS:**
```bash
brew install imlib2 x11
```

### Building

```bash
cd src
make
```

### Testing

```bash
make test
```

## Usage

### Basic Usage

```bash
# Launch with default settings
./brunch

# Launch with custom entries file
./brunch -i /path/to/entries.dsv
```

### Configuration

brunch reads configuration from:
1. Command-line arguments
2. `~/.config/brunch/brunch.conf`
3. `/etc/brunch/default.conf`

### Entry File Format

Entries are stored in DSV (Delimiter-Separated Values) format:
```
Application Name;icon/path.png;command to run
```

Example:
```
Firefox;/usr/share/icons/firefox.png;firefox
Terminal;/usr/share/icons/terminal.png;gnome-terminal
```


## Development

### Project Structure

```
brunch/
├── src/                    # Source code
│   ├── brunch.c           # Main application
│   ├── config.c           # Configuration handling
│   ├── types.h            # Data structures
│   ├── logo.c             # Logo rendering
│   ├── binfinder.py       # Application discovery
│   ├── Makefile           # Build configuration
│   └── utils/             # Utility modules
├── docs/                  # Documentation
├── default.conf           # Default configuration
└── README.md             # Project overview
```

### Building from Source

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-repo/xlunch.git
   cd xlunch
   ```

2. **Install dependencies:**
   ```bash
   # Ubuntu/Debian
   sudo apt install libimlib2-dev libx11-dev
   
   # Fedora
   sudo dnf install imlib2-devel libX11-devel
   
   # macOS
   brew install imlib2 x11
   ```

3. **Build:**
   ```bash
   cd src
   make
   ```

4. **Test:**
   ```bash
   make test
   ```

### Code Architecture

#### Event Loop
The main event loop in `brunch.c` handles:
- X11 events (keyboard, mouse, window management)
- Input method events (for UTF-8 support)
- Application state updates
- Rendering updates

#### Rendering Pipeline
1. **Background**: Load and render background image
2. **Icons**: Load application icons and render at calculated positions
3. **Text**: Render application names with shadow effects
4. **Highlighting**: Render hover effects and selections
5. **Prompt**: Render search prompt and input text

#### Application Discovery
The `binfinder.py` script:
1. Scans system directories for applications
2. Extracts metadata from .desktop files (Linux) or .app bundles (macOS)
3. Resolves icon paths using standard icon themes
4. Generates DSV format output
5. Provides automatic application discovery for improved usability

### Debugging

#### Common Issues
- **No applications found**: Check entries file format and paths
- **Icons not loading**: Verify icon file paths and permissions
- **Font rendering issues**: Check font installation and paths
- **X11 connection errors**: Verify DISPLAY environment variable

#### Debug Options
```bash
# Enable debug compilation
make CFLAGS="-ggdb -g3"

# Test with sample data
make test
```

### Testing

```bash
# Run basic tests
make test

# Run live test with generated entries
make livetest

# Test with custom configuration
./brunch --config custom.conf
```

## License

This project is licensed under the GNU GPL v3. See the LICENSE file for details.


## Version History

- **v4.0**: Current version with enhanced customization options
- **v3.x**: Added extensive customization features
- **v2.x**: Basic functionality and stability improvements
- **v1.x**: Initial release

## Related Projects

- **xlunch**: Original project that brunch is forked from
- **dmenu**: Text-based application launcher
- **rofi**: Feature-rich application launcher
- **synapse**: GNOME application launcher
- **albert**: Cross-platform application launcher

## Support

For issues and questions:
- Check the documentation in `docs/`
- Review the usage examples in `docs/usage.txt`
- Test with the provided sample configurations
- Report bugs with detailed system information
