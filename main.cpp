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

void printpose(pose p) {
    cout <<p.X << " " << p.Y << " ";
    switch (p.dir)
    {
    case Dir::E : 
        cout <<"E \n";
        return;
    case Dir::W : 
        cout <<"W \n";
        return;
    case Dir::N :
        cout <<"N \n";
        return;
    case Dir::S : 
        cout <<"S \n";
        return;
    default: 
        cout << "0  ";
        return;
    }
}
void printcmd(Move cmd){
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

pose ParseposeLine(string line) {
    istringstream sline(line);
    int x, y;
    char c;
    sline >> x >> y >> c ;
    pose p;
    p.X = x;
    p.Y = y;
    if      (c == 'E') p.dir = Dir::E;
    else if (c == 'W') p.dir = Dir::W;
    else if (c == 'N') p.dir = Dir::N;
    else if (c == 'S') p.dir = Dir::S;
    else cout << " Direction not found \n";
    return p;
}



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


void ReadFile(string path) {
    ifstream myfile (path);
    if (myfile) {
        string line;
        // while (getline(myfile, line)) {
        //     cout << "Read line: "<< line << "\n"; 
        //     // vector<Move> cmds = ParseCmdLine(line);
        //     // cout << "size of commands: "<< cmds.size() << "\n"; 
        //     // for(auto cmd : cmds)
        //     //     cout << printcmd(cmd);
        //     pose p = ParseposeLine(line);
        //     printpose(p);
        // }

        getline(myfile, line);
        pose p = ParseposeLine(line);
        getline(myfile, line);
        vector<Move> cmds = ParseCmdLine(line);
        printpose(p);
        for(auto cmd : cmds)
            printcmd(cmd);
        cout << "\n";
    }
}

// TODO: check if the cell is valid.

int main() 
{   
    pose rover1_pose;
    // Debug
    cout << "X: " << rover1_pose.X << " Y: " << rover1_pose.Y << " dir: " ;
    if(rover1_pose.dir == Dir::E)
        cout << "yes \n";
    else
        cout << "no \n";

    ReadFile("cmd.txt");

    return 0;
}
