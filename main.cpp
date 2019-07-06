// g++ -std="c++17" -pthread main.cpp && ./a.out

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class Dir {E, W, N, S};

struct pose {
    int X;
    int Y;
    Dir dir;

    pose(): X(0), Y(0), dir(Dir::E)  {}
};


int main() 
{   
    pose rover1_pose;
    cout << "X: " << rover1_pose.X << " Y: " << rover1_pose.Y << " dir: " ;
    if(rover1_pose.dir == Dir::E)
        cout << "yes \n";
    else
        cout << "no \n";
    cout << "Rover test \n";
    return 0;
}
