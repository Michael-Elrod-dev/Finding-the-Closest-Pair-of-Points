# Finding-the-Closest-Pair-of-Points

This C++ program is designed to read a set of two-dimensional points from a file, and find the shortest distance between any pair of points in the set efficently.

## Program Structure

The program uses three main components:

1. A `point` struct to represent the points in the two-dimensional space.
2. The `closestPair` function that reads the points from a file, assigns them to a grid, and calculates the shortest distance between any pair of points.
3. The `calcDistance` function that calculates the distance between a point and all other points in its neighboring grid cells.

The `isChecked` function and an overloaded `<` operator for the `point` struct are used to efficiently track which pairs of points have already been compared.

## How it Works

The program reads a list of points from a file, where the number of points is specified in the first line of the file and each subsequent line contains the `x` and `y` coordinates of a point.

Points are then hashed into a two-dimensional grid. Each grid cell is checked against its adjacent cells to find the shortest distance between any pair of points. The grid uses a "closest cell" method where each cell checks only its adjacent cells (top, bottom, left, right and the diagonals) for the closest pair. This approach is a significant improvement over the O(n^2) comparison of each point with every other.

A set data structure is used to keep track of the pairs of points that have already been compared, to avoid unnecessary duplicate comparisons.

## Compiling and Running the Program

To compile and run the program, use the following commands in a terminal:

```bash
g++ -o closestPair closestPair.cpp
./closestPair data.txt
