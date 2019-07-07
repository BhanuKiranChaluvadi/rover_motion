#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <string>
#include "Rover.h"
using std::cout;
using std::ifstream;
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
    
    Rover* buildRover(ifstream &fin, Grid *grid) {
        // get position
        string line;
        if(!getline(fin, line)) return NULL;
        Position position = parsePosition(line);
        
        Rover *rover = new Rover(position);
        // get commands
        if(!getline(fin, line)) return NULL;
        rover->setCommands(parseCommands(line));
        
        rover->setGrid(grid);
        return rover;
    }
}

int main() {
    // TODO: make this command line argument
    string path = "../single_rover.txt";
    ifstream myfile (path);
    
    if (!myfile) return -1;
    
    Grid *grid = builder::buildGrid(myfile);
    
    if (!grid) return -1;
    
    while (Rover *rover = builder::buildRover(myfile, grid)) {
        // execute.
        rover->executeCommnds();
        Position position = rover->getPosition();
        cout << position.x <<" "<< position.y << " "<< Rover::convertThetaToDir(position.theta);
    }
}