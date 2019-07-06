// g++ -std="c++17" -pthread main.cpp && ./a.out

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;



enum class Dir {E=0, W=90, N=180, S=270};
enum class Move{L, R, M};

struct Pose {
    int X;
    int Y;
    int theta;      // degrees

    Pose(): X(0), Y(0), theta(0)  {}
};

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

int normalizeTheta(int theta){
    theta = theta % 360 ;
    if(theta < 0) {
        theta += 360;
    }
    return theta;
}


void printpose(const Pose p) {
    cout <<p.X << " " << p.Y << " " << convert_ThetatoDir(p.theta)<< "\n";
}
void printcmd(const Move cmd){
    switch (cmd)
    {
    case Move::L :
        cout << "< ";
        return;
    case Move::R :
        cout <<  "> ";
        return;
    case Move::M :
        cout <<  "^ ";
        return;
    default: 
        cout <<  "0   "; 
        return;
    }
}

Pose ParseposeLine(string line) {
    istringstream sline(line);
    int x, y;
    char c;
    sline >> x >> y >> c ;
    Pose p;
    p.X = x;
    p.Y = y;
    if      (c == 'E') p.theta = 0;
    else if (c == 'N') p.theta = 90;
    else if (c == 'W') p.theta = 180;
    else if (c == 'S') p.theta = 270;
    else cout << " Direction not found \n";
    return p;
}

static double constexpr pi = 3.14159265;

vector<Move> ParseCmdLine(string line) {
    istringstream sline(line);
    char c;
    vector<Move> cmds;
    while (sline >> c ) {
        if(c == 'L') cmds.push_back(Move::L);
        else if (c == 'R') cmds.push_back(Move::R);
        else if (c == 'M') cmds.push_back(Move::M);
        else cout << " Move command not found \n";
    }
    return cmds;
}

void executeCommand(Pose &pose, Move cmd) {
    switch (cmd)
    {
    case Move::L :
        // cout << "L " ;
        pose.theta += 90 ;
        pose.theta = normalizeTheta(pose.theta);
        break;
    case Move::R :
        // cout << "R " ;
        pose.theta -= 90 ;
        pose.theta = normalizeTheta(pose.theta);
        break;
    case Move::M :
        // cout << "M " ;
        // cout << pose.theta << " " << int(cos(pose.theta*pi/180)) << " ";
        pose.X += int(cos(pose.theta*pi/180)) ;
        pose.Y += int(sin(pose.theta*pi/180)) ;
        break;
    default:
        cout << "command not found !! " ;
        break;
    }
}

void ReadFile(string path) {
    ifstream myfile (path);
    if (myfile) {
        string line;
        getline(myfile, line);
        Pose p = ParseposeLine(line);
        getline(myfile, line);
        vector<Move> cmds = ParseCmdLine(line);
        cout << "Initial pose: \n";
        cout << p.theta << " ";
        printpose(p);
        for(auto cmd : cmds)
            printcmd(cmd);
        cout << "\n";
        cout << "start of execution: \n" ;
        for (auto cmd : cmds) {
            executeCommand(p, cmd);
            // cout << p.theta << " ";
            printpose(p);
        }
    }
}

// TODO: check if the cell is valid.

int main() 
{   
    Pose rover1_pose;
    // Debug
    // out << "X: " << rover1_pose.X << " Y: " << rover1_pose.Y << " dir: " ;

    ReadFile("cmd.txt");

    return 0;
}
