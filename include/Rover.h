#ifndef ROVER_H_
#define ROVER_H_

#include <queue>
#include <cmath>
using std::queue;

#define PI 3.14159265

enum class Move{L, R, M};

struct Position {
    int X;
    int Y;
    int theta;      // degrees
    Position(): X(0), Y(0), theta(0)  {}
};

class Grid {
    int x_bound;
    int y_bound;
    
    Grid(int x, int y) {
        this->x_bound = x;
        this->y_bound = y;
    }
    
public:
    bool isValidPosition(int x, int y) {
        if (x >= 0 && y >= 0 && x < x_bound && y < y_bound) {
            return true;
        }
        return false;
    }
};





# endif // ROVER_H_


