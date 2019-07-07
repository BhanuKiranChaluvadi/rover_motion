#ifndef ROVER_H_
#define ROVER_H_

#include <iostream>
#include <queue>
#include <cmath>
using std::cout;
using std::queue;

#define PI 3.14159265

enum class Move{L, R, M};

struct Position {
    int x;
    int y;
    int theta;      // degrees
    Position(): x(0), y(0), theta(0)  {}
};

class Grid {
    int x_bound;
    int y_bound;

public:

    Grid(int x, int y) {
        this->x_bound = x;
        this->y_bound = y;
    }
    bool isValidPosition(int x, int y) {
        if (x >= 0 && y >= 0 && x <= x_bound && y <= y_bound) {
            return true;
        }
        return false;
    }
};

class Rover {
    Position position;
    queue<Move> commands;
    Grid *grid;

    int normalizeTheta(int theta){
        theta = theta % 360 ;
        if(theta < 0) {
            theta += 360;
        }
        return theta;
    }

    void executeCommand(Move command) {
        switch (command)
        {
            case Move::L : {
                this->position.theta = normalizeTheta(this->position.theta + 90);
                break;
            }
            case Move::R : {
                this->position.theta = normalizeTheta(this->position.theta - 90);
                break;
            }
            case Move::M : {
                int newX = this->position.x + round(cos(this->position.theta * PI / 180)) ;
                int newY = this->position.y + round(sin(this->position.theta * PI / 180)) ;
                if (grid->isValidPosition(newX, newY)) {
                    this->position.x = newX;
                    this->position.y = newY;
                } 
                else {
                    cout << "Invalid move !! \n";    
                }
                break;
            }
            default: {
                cout << "command not found !! " ;
                break;
            }
        }
    }
    
public:
    Rover (Position position) {
        this->position = position;
    }
    void setCommands(queue<Move> commands) {
        this->commands = commands;
    }
    void setGrid(Grid *grid) {
        this->grid = grid;
    }
    void executeCommnds() {
        while (!commands.empty()) {
            executeCommand(commands.front());
            this->commands.pop();
        }
    }
    Position getPosition() {
        return this->position;
    }

    static int convertDirToTheata(const char dir) {
        if      (dir == 'E') return 0;
        else if (dir == 'N') return 90;
        else if (dir == 'W') return 180;
        else if (dir == 'S') return 270;
        else {
            cout << " Direction not found !! \n";
            return -1;
        }
    }

    static char convertThetaToDir(const int theta)  {
        if (theta == 0  || theta == 360) return 'E';
        else if (theta == 90)   return 'N';
        else if (theta == 180)  return 'W';
        else if (theta == 270)  return 'S';
        else {
            cout << "theta is out of scope !! \n" ;
            return 'x';
        }
    }
};

# endif // ROVER_H_