#ifndef ROVER_H_
#define ROVER_H_

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <sstream>
using std::cout;
using std::vector;
using std::queue;

#define PI 3.14159265

enum class Move{L, R, M};
enum class State{kEmpty, kObstacle};

struct Position {
    int x;
    int y;
    int theta;      // degrees
    Position(): x(0), y(0), theta(0)  {}
};

class Grid {
    int x_bound;
    int y_bound;
    vector<vector<State>> board{};

public:

    Grid(int x, int y) {
        this->x_bound = x;
        this->y_bound = y;
        for(uint i=0; i<=x; ++i){
            vector<State> row{};
            for(uint j=0; j<=y; ++j){
                row.push_back(State::kEmpty);
            }
            this->board.push_back(row);
        }
    }
    bool inbound(int x, int y) {
        return (x >= 0 && y >= 0 && x <= x_bound && y <= y_bound) ? true : false ;
    }
    void setObstacle (int x, int y) {
        if (inbound(x, y)) {
            this->board[x][y] = State::kObstacle;
        }
    }
    void removeObstacle (int x, int y) {
        if (inbound(x, y)) {
            this->board[x][y] = State::kEmpty;
        }
    }
    bool isValidPosition(int x, int y) {
        // check if its currents reover position
        if (inbound(x, y)) {
            if (this->board[x][y] == State::kEmpty) {
                return true;
            }
            else
                return false;
        }
        return false;
    }
};

class Rover {
    Position position;
    queue<Move> commands;
    Grid *grid;

    /* Bounds the theta between 0-360 degrees. or Project all angles onto 0-360 degrees.*/
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
                    // cout << "Invalid move !! \n";    
                }
                break;
            }
            default: {
                // cout << "command not found !! " ;
                break;
            }
        }
    }
    
public:
    Rover (Position position) {
        this->position = position;
    }
    ~Rover() {
        // cout << "Rover destroyed !!  \n";
    }
    Position getPosition() {
        return this->position;
    }
    void setCommands(queue<Move> commands) {
        this->commands = commands;
    }
    std::queue<Move> getCommands (){
        return this->commands;
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

    // Helper function - unit test
    static std::queue<Move> chartoCmd(std::string line) {
        std::istringstream sline(line);
        queue<Move> commands;
        char c;
        while (sline >> c ) {
                    if(c == 'L') commands.push(Move::L);
                    else if (c == 'R') commands.push(Move::R);
                    else if (c == 'M') commands.push(Move::M);
                    else cout << " Move command not found \n";
                }
        return commands;
    }

    // Helper function - unit test
    static std::string cmdtoChar(std::queue<Move> cmds) {
        std::string chars="";
        while (!cmds.empty()) {
            Move cmd = cmds.front();
            switch (cmd) {
                case Move::L : {
                    chars = chars + 'L';
                    break;
                }
                case Move::R : {
                    chars = chars + 'R';
                    break;
                }
                case Move::M : {
                    chars = chars + 'M';
                    break;
                }
            }
            cmds.pop();
        }
        return chars;
    }

};

# endif // ROVER_H_