// g++ -std="c++17" -pthread main.cpp && ./a.out

#include <iostream>

#include "Rover.h"

int main (int argc, const char **argv) {
    // std::string input_file = "";
    // if( argc > 1 ) {
    //     for( int i = 1; i < argc; ++i )
    //         if( std::string_view{argv[i]} == "-f" && ++i < argc )
    //             input_file = argv[i];
    // }
    // else {
    //     std::cout << "Usage: [executable] [-f input_file.txt]" << std::endl;    
    // }

    string path = "../single_rover.txt";
    ifstream myfile (path);
    if (myfile) {
        // Get the first line and set grid size.
        int grid_x, grid_y;
        string line;
        getline(myfile, line);
        istringstream sline(line);
        sline >> grid_x >> grid_y ;
        Rover R(grid_x, grid_y);
        // get position line
        getline(myfile, line);
        R.parsePoseLine(line);
        R.printPose();
        // get commands line
        getline(myfile, line);
        R.parseCmdsLine(line);
        R.printCmds();
        cout << "\n";
        // execute.
        R.executeCmds();
        R.printPose();
    }
    else
        cout << "File not found /n";
}