// g++ -std="c++17" -pthread main.cpp && ./a.out

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class Dir {E, W, N, S};
enum class Move{L, R, M};

struct pose {
    int X;
    int Y;
    Dir dir;

    pose(): X(0), Y(0), dir(Dir::E)  {}
};


string printcmd(Move cmd){
    switch (cmd)
    {
    case Move::L : return "<- ";
    case Move::R : return "-> ";
    case Move::M : return "^ ";
    default: return "0   "; 
    }
}

vector<Move> ParseCmdLine(string line) {
    istringstream sline(line);
    char c;
    vector<Move> cmds;
    while (sline >> c ) {
        if(c == 'L')
            cmds.push_back(Move::L);
        else if (c == 'R')
            cmds.push_back(Move::R);
        else if (c == 'M')
            cmds.push_back(Move::M);
        else 
            cout << " Move command not found \n";
    }
    return cmds;
}


void ReadFile(string path) {
    ifstream myfile (path);
    if (myfile) {
        string line;
        while (getline(myfile, line)) {
            cout << "Read line: "<< line << "\n"; 
            vector<Move> cmds = ParseCmdLine(line);
            cout << "size of commands: "<< cmds.size() << "\n"; 
            for(auto cmd : cmds)
                cout << printcmd(cmd);
        }
    }
}


// TODO: check if the cell is valid.

int main() 
{   
    pose rover1_pose;
    cout << "X: " << rover1_pose.X << " Y: " << rover1_pose.Y << " dir: " ;
    if(rover1_pose.dir == Dir::E)
        cout << "yes \n";
    else
        cout << "no \n";
    cout << "Rover test \n";

    ReadFile("cmd.txt");

    return 0;
}
