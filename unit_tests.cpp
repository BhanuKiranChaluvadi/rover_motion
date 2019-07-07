#include "include/Rover.h"
#include <iostream>
#include <gtest/gtest.h>


TEST(RoverTests,  DirtoTheta)
{   
    char dir = 'E';
    EXPECT_EQ(0, Rover::convertDirToTheata(dir));
    dir = 'W';
    EXPECT_EQ(180, Rover::convertDirToTheata(dir));
    dir = 'N';
    EXPECT_EQ(90, Rover::convertDirToTheata(dir));
    dir = 'S';
    EXPECT_EQ(270, Rover::convertDirToTheata(dir));
}

TEST(RoverTests,  ThetatoDir)
{   
    int Theta = 0;
    EXPECT_EQ('E',   Rover::convertThetaToDir(Theta));
    Theta = 90;
    EXPECT_EQ('N', Rover::convertThetaToDir(Theta));
    Theta = 180;
    EXPECT_EQ('W',  Rover::convertThetaToDir(Theta));
    Theta = 270;
    EXPECT_EQ('S', Rover::convertThetaToDir(Theta));
}

TEST(RoverTests, chartoCmd) 
{
    std::string chars = "LRM";
    static std::queue<Move> commands = Rover::chartoCmd(chars);
    EXPECT_TRUE(Move::L == commands.front());
    commands.pop();
    EXPECT_TRUE(Move::R == commands.front());
    commands.pop();
    EXPECT_TRUE(Move::M == commands.front());
    commands.pop();
    EXPECT_TRUE(commands.empty());
}

// happy test
TEST(RoverTests,  commandExecution)
{   
    // Grid size
    int xMax = 5;
    int yMax = 5;
    
    // rover init pose & commands
    int x = 3;
    int y = 3;
    char dir = 'E';
    Position position;
    position.x = x;
    position.y = y;
    position.theta = Rover::convertDirToTheata(dir);
    std::string charCommands = "MMRMMRMRRM";

    // make a grid
    Grid grid(xMax, yMax);
    // build rover
    Rover rover(position);
    // set commands
    rover.setCommands(Rover::chartoCmd(charCommands));
    // set grid
    rover.setGrid(&grid);

    // check for proper commands inputs
    std::queue<Move> commands = rover.getCommands();
    EXPECT_TRUE( charCommands == Rover::cmdtoChar(commands));
    // execute
    rover.executeCommnds();
    Position finalPosition = rover.getPosition();
    EXPECT_EQ(5,  finalPosition.x);
    EXPECT_EQ(1,  finalPosition.y);
    EXPECT_EQ('E',  Rover::convertThetaToDir(finalPosition.theta));

    EXPECT_TRUE(true);
}

TEST(RoverTests,  outGridCommandTest)
{   
    // Grid size
    int xMax = 3;
    int yMax = 3;
    
    // rover init pose & commands
    int x = 2;
    int y = 2;
    char dir = 'E';
    Position position;
    position.x = x;
    position.y = y;
    position.theta = Rover::convertDirToTheata(dir);
    std::string charCommands = "MML";

    // make a grid
    Grid grid(xMax, yMax);
    // build rover
    Rover rover(position);
    // set commands
    rover.setCommands(Rover::chartoCmd(charCommands));
    // set grid
    rover.setGrid(&grid);

    // check for proper commands inputs
    std::queue<Move> commands = rover.getCommands();
    EXPECT_TRUE( charCommands == Rover::cmdtoChar(commands));
    // execute
    rover.executeCommnds();
    Position finalPosition = rover.getPosition();
    EXPECT_EQ(3,  finalPosition.x);
    EXPECT_EQ(2,  finalPosition.y);
    EXPECT_EQ('N',  Rover::convertThetaToDir(finalPosition.theta));

    EXPECT_TRUE(true);
} 




