// g++ -std="c++17" -pthread main.cpp && ./a.out

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


class rover {
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

    bool CheckValidCell(const Pose& pos, const std::tuple<int, int>& gridSize) {
        bool on_grid_x = (pos.X >= 0 && pos.X < std::get<0>(gridSize));
        bool on_grid_y = (pos.Y >= 0 && pos.Y < std::get<1>(gridSize));
        if (on_grid_x && on_grid_y)
            return true;
        return false;
    }

    int convert_DirtoTheata(const char dir) const {
        if      (dir == 'E') return 0;
        else if (dir == 'N') return 90;
        else if (dir == 'W') return 180;
        else if (dir == 'S') return 270;
        else {
            cout << " Direction not found !! \n";
            return -1;
        }
    }

    char convert_ThetatoDir(const int theta) const {
        if (theta == 0  || theta == 360) return 'E';
        else if (theta == 90)   return 'N';
        else if (theta == 180)  return 'W';
        else if (theta == 270)  return 'S';
        else {
            cout << "theta is out of scope !! \n" ;
            return 'x';
        }
    }

    int normalizeTheta(int theta){
        theta = theta % 360 ;
        if(theta < 0) {
            theta += 360;
        }
        return theta;
    }
    void executeCommand(Pose &pose, Move cmd) {
        switch (cmd)
        {
        case Move::L :
            pose.theta += 90 ;
            pose.theta = normalizeTheta(pose.theta);
            break;
        case Move::R :
            pose.theta -= 90 ;
            pose.theta = normalizeTheta(pose.theta);
            break;
        case Move::M :
            pose.X += round(cos(pose.theta*pi/180)) ;
            pose.Y += round(sin(pose.theta*pi/180)) ;
            break;
        default:
            cout << "command not found !! " ;
            break;
        }
    }
    void printcmd(const Move cmd) const {
        switch (cmd)
        {
        case Move::L :
            cout << "L ";
            return;
        case Move::R :
            cout <<  "R ";
            return;
        case Move::M :
            cout <<  "M ";
            return;
        default:
            cout <<  "0 "; 
            return;
        }
    }


public:

    rover () {}
    rover (int grid_x, int grid_y) : gridSize_(std::make_tuple (grid_x, grid_y)) {}

    void setGridSize(const int x, const int y) {
        gridSize_ = std::make_tuple(x, y);
    }

    void parsePoseLine(string line) {
        istringstream sline(line);
        int x, y;
        char c;
        sline >> x >> y >> c ;
        pose_.X = x;
        pose_.Y = y;
        pose_.theta = convert_DirtoTheata(c);
        return;
    }

    void parseCmdsLine(string line) {
        istringstream sline(line);
        cmds_.clear();      // making sure nothing exists.
        char c;
        while (sline >> c ) {
            if(c == 'L') cmds_.push_back(Move::L);
            else if (c == 'R') cmds_.push_back(Move::R);
            else if (c == 'M') cmds_.push_back(Move::M);
            else cout << " Move command not found \n";
        }
        return;
    }

    void executeCmds() {
        for(auto cmd: cmds_)
            executeCommand(pose_, cmd);
    }

    // Debug
    void printPose() const {
        cout <<pose_.X << " " << pose_.Y << " " << convert_ThetatoDir(pose_.theta)<< "\n";
    }
    // Debug
    void printCmds() const {
        for (auto cmd : cmds_)
            printcmd(cmd);
    }

};


int main() 
{   
    string path = "cmd.txt";
    ifstream myfile (path);
    if (myfile) {
        // Get the first line and set grid size.
        int grid_x, grid_y;
        string line;
        getline(myfile, line);
        istringstream sline(line);
        sline >> grid_x >> grid_y ;
        rover r(grid_x, grid_y);
        // get position line
        getline(myfile, line);
        r.parsePoseLine(line);
        r.printPose();
        // get commands line
        getline(myfile, line);
        r.parseCmdsLine(line);
        r.printCmds();
        cout << "\n";
        // execute.
        r.executeCmds();
        r.printPose();
    }
    return 0;
}
