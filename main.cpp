/**
 * @file main.cpp
 * @author Jakub Sanecki
 * @brief 
 * @version 1.0
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */



#include <iostream>
#include <string>
#include <unordered_map>

#include "functions.h"

int main(int argc, char *argv[])
{
    std::string inputFile;
    int i;
    int deArgs = decodeArgs(argc, argv, inputFile);
    if (deArgs)
    {
        std::cout << " How to use bTree program. btree.exe -i [input file]" << std::endl;
        std::cout << " File should be created using the following commands, with the first line being the degree of the tree." << std::endl;
        std::cout << "      add - for adding numbers to a set (numbers a separated with white spaces), eg add 34 6.6 -4  \n";
        std::cout << "      print - for printing sorted numbers to the standard output \n";
        std::cout << "      print with a file name - prints sorted numbers in the file, eg. print my-sorted-numbers \n";
        std::cout << "      graph - prints a bTree (with indented levels) to the standard output. \n Numbers in branches are prrinted in square brackets.\n";
        std::cout << "      graph with a file name – the same as graph, but a tree is printed into the file \n";
        std::cout << "  NOTE: In one line should be only ONE command to program proper work\n";
        return 0;
    }
    else
    {   
            std::unordered_map<int, std::vector<std::string> > read = readFile(inputFile);
            i = findOrder(read);
            findFunction(read, i); 
            return 1;
    }
}
