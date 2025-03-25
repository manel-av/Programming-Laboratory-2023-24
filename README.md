# Programming Laboratory - OpenStreetMap Pathfinder
## About This Course
This programming course focuses on implementing efficient data structures and algorithms for geographic pathfinding using real-world OpenStreetMap (OSM) data. Through this project, I developed skills in C++ programming, inheritance, dynamic data structures, and graph algorithms.

## Project Overview
**OSM Pathfinder** is a two-part system that:
1. Parses and visualizes OSM map data (nodes, paths, points of interest)
2. Finds the shortest path between any two points of interest using:
    - Ball Tree data structure for nearest neighbor search
    - Graph algorithms for pathfinding
    - Haversine distance calculations

## Technical Implementation
### System Architecture
The solution consists of several key components:

### Part 1: Data Parsing and Visualization
- **XML Parsing:** Processes OSM XML files into internal data structures
- **Class Hierarchy:**
  - PuntDeInteresBase (Base class for points of interest)
    - PuntDeInteresBotigaSolucio (Shop implementation)
    - PuntDeInteresRestaurantSolucio (Restaurant implementation)
  - CamiBase (Base class for paths) with CamiSolucio implementation
  - MapaBase (Base map class) with MapaSolucio implementation

### Part 2: Pathfinding
- **Graph Construction:** Creates a weighted graph of path nodes
- **Ball Tree:** Spatial partitioning structure for efficient nearest neighbor search
- **Shortest Path Algorithm:** Dijkstra's algorithm implementation

### Key Features
- Custom point of interest types with different visual representations
- Efficient data structures for storing map elements
- Haversine distance calculations for accurate geographic measurements
- Visual interface for map exploration and path visualization
