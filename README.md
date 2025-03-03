# Wildfire Simulation

## Overview
This project simulates a wildfire in a forest grid. The forest is represented as a grid of cells, each of which can be empty or contain a tree. The wildfire spreads from one tree to its neighboring trees, simulating a fire burning through a forest. The simulation provides an interactive view of the forest grid and tracks the spread of the fire.

## Features
- **Grid-based forest simulation**: A grid where each cell can contain a tree, empty space, or be on fire.
- **Burning mechanics**: Trees catch fire from neighboring burning trees and spread the fire across the grid.
- **Neighboring logic**: Cells are checked for neighbors to simulate fire spread and burning.
- **Dynamic update**: The fire spreads in discrete steps, allowing users to observe the wildfire over time.
- **Grid visualization**: The forest is displayed in a grid format, updating as the fire spreads.
- **Configuration options**: Users can set the size of the forest grid and initiate the simulation through configuration files.

## Installation
To build and run the wildfire simulation, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/wildfire-simulation.git
   cd wildfire-simulation
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the simulation:
   ```bash
   ./wildfire
   ```

## File Descriptions

- **wildfire.c**: The main file that runs the simulation, including functions for initializing the grid, updating it, and displaying it.
- **grid_forest.c**: Contains the logic for setting up and updating the forest grid, including the spread of fire.
- **grid_forest.h**: Header file defining the structure of the forest grid and the Cell struct.
- **Makefile**: Automates the building process.
- **.gitignore**: Excludes unnecessary files (e.g., build artifacts) from being committed to version control.
- **report.txt**: Contains a summary of changes and improvements to the project over time.

## Usage
- Configure the forest size and initial tree distribution in the configuration files or by modifying parameters in the code.
- The fire will spread through the forest with each simulation step. The simulation is visualized in the terminal, where each update represents the current state of the forest.

## Changelog
### [Latest Commit]
- Updated simulation logic to improve performance and fixed several minor bugs in the forest update mechanism.

### [Previous Commits]
- Fixed the logic for burning trees and spread mechanics.
- Added functionality to handle grid resizing dynamically based on user input.
- Improved forest grid visualization and added more configuration options.
