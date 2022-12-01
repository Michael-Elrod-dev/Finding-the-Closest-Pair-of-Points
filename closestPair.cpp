/*
 * Name: Michael Elrod
 * Date Submitted: 10/20/2022
 * Lab Section: 002
 * Assignment Name: Lab 6 - Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

struct point
{
    double x;
    double y;
};

double closestPair(string filename);
bool isChecked(point, point, set<vector<point>>const&);
double calcDistance(point, vector<point>&, set<vector<point>>);

double closestPair(string filename)
{
    //Open file and read in number of points from first line
    ifstream inputFile (filename);
    int numPoints;
    inputFile >> numPoints;
    // Split grid cells by #cells, rounded to int
    int cells = sqrt(numPoints);
    point pValue;

    // Grid
    vector<vector<vector<point>>> grid(cells, vector<vector<point>>(cells));

    // Input values to grid for all values
    for (int i=0;i<numPoints;i++)
    {
        inputFile >> pValue.x;
        inputFile >> pValue.y;

        // Cast hash keys to rounded integer within grid parameters
        // pValues are always: 0 < pValue < 1, so no need to use % for hashing
        int hashX = (int)(pValue.x * cells);
        int hashY = (int)(pValue.y * cells);

        grid[hashX][hashY].push_back(pValue);
    }

    // Looking for minimum values, start with value higher than all points
    double min      = 100;
    double testMin  = 100;
    double distance = 100;

    set<vector<point>> checkedP;

    // Check all positions in #grid up to #cells
    for(int i=0;i<cells;i++) {
        for (int k=0;k<cells;k++) {
            for (auto pValue: grid[i][k]) {
                testMin = calcDistance(pValue, grid[i][k], checkedP);

                // If the cell is not against the left wall of grid, compare left
                if (k > 0) {
                    distance = calcDistance(pValue, grid[i][k-1], checkedP);
                    testMin = (distance < testMin)? distance:testMin;
                    // If the cell is not against the right wall of grid, compare top/left
                    if (i < cells - 1) {
                        distance = calcDistance(pValue, grid[i+1][k-1], checkedP);
                        testMin = (distance < testMin)? distance:testMin;

                    }
                }
                // If the cell is not against the right wall of grid, compare right
                if (k < cells - 1) {
                    distance = calcDistance(pValue, grid[i][k+1], checkedP);
                    testMin = (distance < testMin)? distance:testMin;
                    // If the cell is not against the right wall of grid, compare top/right
                    if (i < cells - 1) {
                        distance = calcDistance(pValue, grid[i+1][k+1], checkedP);
                        testMin = (distance < testMin)? distance:testMin;

                    }
                }
                // If the cell is not against the bottom of grid, compare down
                if (i > 0) {
                    distance = calcDistance(pValue, grid[i-1][k], checkedP);
                    testMin = (distance < testMin)? distance:testMin;
                    // If the cell is not against the bottom/left of grid, compare down/left
                    if (k > 0) {
                        distance = calcDistance(pValue, grid[i-1][k-1], checkedP);
                        testMin = (distance < testMin)? distance:testMin;
                    }
                    // If the cell is not against the bottom/right of grid, compare down/right
                    if (k < cells-1) {
                        distance = calcDistance(pValue, grid[i-1][k+1], checkedP);
                        testMin = (distance < testMin)? distance:testMin;
                    }
                }
                // Compare top
                if (i < cells-1) {
                    distance = calcDistance(pValue, grid[i+1][k], checkedP);
                    testMin = (distance < testMin)? distance:testMin;
                }
                // Check for new minimum value
                if (testMin < min)
                    min = testMin;
            }
        }
    }
    return min;
}

// Checks Set to see if points' distance has already been calculated
bool isChecked(point left, point right, set<vector<point>>const& inSet)
{
    // Two possible arrangements of points
    vector<point> tmp1 = {left, right};
    vector<point> tmp2 = {right, left};

    // .find() returns an iterator up to the element found
    // If not found, return element after last-> .end()
    // Since point is a struct we will need to overload the operator<
    // Check if elements were already checked
    if (inSet.find(tmp1) != inSet.end() || inSet.find(tmp2) != inSet.end())
        return true;

    return false;
}

// Calculates the distance between two coordinate points and tracks the minimum
double calcDistance(point pValue, vector<point>& group, set<vector<point>> checkedPoints)
{
    double min = 100;

    // For all elements in vector group
    for (auto compPoint:group)
    {// if values are not the same and have not already been checked
        if ((compPoint.x != pValue.x) && (compPoint.y != pValue.y) && (!isChecked(pValue, compPoint, checkedPoints)))
        {
            vector<point> compare (2);// Vector of two points to be compared
            compare.push_back(pValue);// Original
            compare.push_back(compPoint); // Point to be compared to
            checkedPoints.insert(compare);// Add to Set of points for comparison

            // Distance = geometric distance of two coordinates on a plane
            // square root of (x2-x1)^2 + (y2-y1)^2
            double distance = sqrt(pow(pValue.x - compPoint.x, 2) + pow(pValue.y - compPoint.y, 2));

            //Track minimum distance
            if (distance < min)
                min = distance;
        }
    }
    return min;
}

// Overloaded operator< for isChecked() function
bool operator<(const point& one, const point& two){
    if (one.x < two.x)
        if (one.x < two.x)
            return true;
    return false;
}