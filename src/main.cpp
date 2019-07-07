#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <string>
#include <memory> // for std::unique_ptr

#include "Rover.h"
using std::cout;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;

namespace builder 
{
    // private utiltiy functions
    namespace {
        
        Position parsePosition(string line) {
            istringstream sline(line);
            int x, y;
            char c;
            sline >> x >> y >> c ;
            Position pos;
            pos.x = x;
            pos.y = y;
            pos.theta = Rover::convertDirToTheata(c);
            return pos;
        }
        
        queue<Move> parseCommands(string line) {
            istringstream sline(line);
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
    }
   
    Grid* buildGrid(ifstream &fin) {
        int x, y;
        string line;
        
        if(!getline(fin, line)) return NULL;
        istringstream sline(line);
        sline >> x >> y ;
        return new Grid(x, y);
    }
    
    std::unique_ptr<Rover> buildRover(ifstream &fin, Grid *grid) {
        // get position
        string line;
        if(!getline(fin, line)) return NULL;
        Position position = parsePosition(line);
        
        std::unique_ptr<Rover> rover(new Rover(position));
        // get commands
        if(!getline(fin, line)) return NULL;
        rover->setCommands(parseCommands(line));
        
        rover->setGrid(grid);
        return rover;
    }
}

int main(int argc, const char **argv) {
    // TODO: make this command line argument

    std::string input_file = "";
    std::string output_file = "";
    // if( argc > 1 ) {
    //     for( int i = 1; i < argc; ++i )
    //         if( std::string_view{argv[i]} == "-f" && ++i < argc )
    //             input_file = argv[i];
    // }
    // else {
    //     std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;    
    // }

    input_file = "../sample.txt";
    output_file = "../output.txt";

    ifstream infile (input_file);
    ofstream outfile (output_file);

    if (!infile || !outfile) return -1;
    
    Grid *grid = builder::buildGrid(infile);
    
    if (!grid) return -1;
    
    std::unique_ptr<Rover> rover ;
    while (rover = std::move( builder::buildRover(infile, grid))) {
        // execute.
        rover->executeCommnds();
        Position position = rover->getPosition();
        cout << position.x <<" "<< position.y << " "<< Rover::convertThetaToDir(position.theta) << "\n";
    }

    infile.close();
    outfile.close();

    return 0;
}