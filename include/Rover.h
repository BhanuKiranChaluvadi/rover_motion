#ifndef ROVER_H_
#define ROVER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;



class Rover {
private:

    enum class Move{L, R, M};

    struct Pose {
        int X;
        int Y;
        int theta;      // degrees

        Pose(): X(0), Y(0), theta(0)  {}
    };

    static constexpr double pi = 3.14159265;

    Pose pose_;
    vector<Move> cmds_;
    std::tuple<int, int> gridSize_;

private:

    bool checkValidCell(const Pose& pos, const std::tuple<int, int>& gridSize);

    int convert_DirtoTheata(const char) const ;

    char convert_ThetatoDir(const int theta) const ;

    int normalizeTheta(int theta);

    void executeCommand(Pose &pose, Move cmd) ;

    void printcmd(const Move cmd) const ;


public:

    Rover () {}
    Rover (int grid_x, int grid_y) : gridSize_(std::make_tuple (grid_x, grid_y)) {}

    void setGridSize(const int x, const int y) ;

    void parsePoseLine(string line) ;

    void parseCmdsLine(string line) ;

    void executeCmds() ;

    // Debug
    void printPose() const ;
    // Debug
    void printCmds() const ;

};  

# endif // ROVER_H_


