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
} 


TEST(GridTests,  obstacleTest)
{
    // Grid size
    int xMax = 7;
    int yMax = 7;

    // make a grid
    Grid grid(xMax, yMax);
    EXPECT_TRUE(grid.isValidPosition(3, 3));
    grid.setObstacle(3, 3);
    EXPECT_FALSE(grid.isValidPosition(3, 3));
}

TEST(RoverTests,  multiRover)
{   
    // Grid size
    int xMax = 5;
    int yMax = 5;
    // make a grid
    Grid grid(xMax, yMax);
    
    // rover 1
    int x1 = 3;
    int y1 = 3;
    char dir1 = 'E';
    Position position1;
    position1.x = x1;
    position1.y = y1;
    position1.theta = Rover::convertDirToTheata(dir1);
    std::string charCommands1 = "MLM";
    // build rover1
    Rover rover1(position1);
    // set commands
    rover1.setCommands(Rover::chartoCmd(charCommands1));
    // set grid
    rover1.setGrid(&grid);
    // place obstacle
    grid.setObstacle(position1.x, position1.y);

    // rover 2
    int x2 = 4;
    int y2 = 3;
    char dir2 = 'N';
    Position position2;
    position2.x = x2;
    position2.y = y2;
    position2.theta = Rover::convertDirToTheata(dir2);
    std::string charCommands2 = "MLMML";
    // build rover2
    Rover rover2(position2);
    // set commands
    rover2.setCommands(Rover::chartoCmd(charCommands2));
    // set grid
    rover2.setGrid(&grid);
    // place obstacle
    grid.setObstacle(position2.x, position2.y);

    // execute: rover 1
    grid.removeObstacle(x1,y1);
    rover1.executeCommnds();
    Position finalPosition1 = rover1.getPosition();
    grid.setObstacle(finalPosition1.x, finalPosition1.y);
    EXPECT_EQ(3,  finalPosition1.x);
    EXPECT_EQ(4,  finalPosition1.y);
    EXPECT_EQ('N',  Rover::convertThetaToDir(finalPosition1.theta));
    EXPECT_FALSE(grid.isValidPosition(3, 4));

    // execute: rover 2
    grid.removeObstacle(x2,y2);
    rover2.executeCommnds();
    Position finalPosition2= rover2.getPosition();
    grid.setObstacle(finalPosition2.x, finalPosition2.y);
    EXPECT_EQ(4,  finalPosition2.x);
    EXPECT_EQ(4,  finalPosition2.y);
    EXPECT_EQ('S',  Rover::convertThetaToDir(finalPosition2.theta));
    EXPECT_FALSE(grid.isValidPosition(4, 4));
}