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
    
    static constexpr double pi = 3.14159265;

    enum class Move{L, R, M};

    struct Pose {
        int X;
        int Y;
        int theta;      // degrees

        Pose(): X(0), Y(0), theta(0)  {}
    };

    Pose pose_;
    vector<Move> cmds_;
    std::tuple<int, int> gridSize_;
    
public:

    rover () {}
    // rover (int x, int y, int theta) : pose_.X(x), pose_.Y(y), pose_.theta(theta) {}
    void setGridSize(const int x, const int y) {
        gridSize_ = std::make_tuple(x, y);
    }

    bool CheckValidCell(const Pose& pos, const std::tuple<int, int>& gridSize) {
        bool on_grid_x = (pos.X >= 0 && pos.X < std::get<0>(gridSize));
        bool on_grid_y = (pos.Y >= 0 && pos.Y < std::get<1>(gridSize));
        if (on_grid_x && on_grid_y)
            return true;
        return false;
    }

    int convert_DirtoTheata(const char dir) {
        if      (dir == 'E') return 0;
        else if (dir == 'N') return 90;
        else if (dir == 'W') return 180;
        else if (dir == 'S') return 270;
        else {
            cout << " Direction not found !! \n";
            return -1;
        }
    }

    char convert_ThetatoDir(const int theta) {
        if (theta == 0  || theta == 360) return 'E';
        else if (theta == 90)   return 'N';
        else if (theta == 180)  return 'W';
        else if (theta == 270)  return 'S';
        else {
            cout << "theta is out of scope !! \n" ;
            return 'x';
        }
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
            pose.X += int(cos(pose.theta*pi/180)) ;
            pose.Y += int(sin(pose.theta*pi/180)) ;
            break;
        default:
            cout << "command not found !! " ;
            break;
        }
    }

    void executeCmds() {
        for(auto cmd: cmds_)
            executeCommand(pose_, cmd);
    }

    // Debug
    void printcmd(const Move cmd){
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

    void printCmds() {
        for (auto cmd : cmds_)
            printcmd(cmd);
    }
    // Debug
    void printpose(const Pose p) {
        cout <<p.X << " " << p.Y << " " << convert_ThetatoDir(p.theta)<< "\n";
    }

    void printCurrentPose() {
        cout <<pose_.X << " " << pose_.Y << " " << convert_ThetatoDir(pose_.theta)<< "\n";
    }

};


void ReadFile(string path) {
    ifstream myfile (path);
    if (myfile) {
        rover r;
        string line;
        getline(myfile, line);
        r.parsePoseLine(line);
        r.printCurrentPose();
        getline(myfile, line);
        r.parseCmdsLine(line);
        r.printCmds();
        cout << "\n";
        r.executeCmds();
        r.printCurrentPose();
    }
}


int main() 
{   

    ReadFile("cmd.txt");

    return 0;
}
