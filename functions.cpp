/**
 * @file functions.cpp
 * @author Jakub Sanecki
 * @brief 
 * @version 1.0
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "structures.h"

//checking if input is correct 
int decodeArgs(int argc, char *argv[], std::string &inputFile)
{   
    int x;
    if(argc > 2)
    {
        std::string a = argv[1];
        if(a == "-i")
            {
                std::ifstream input_file(argv[2]);
                if (!input_file.is_open()) 
                {
                    std::cerr << " Could not open input file '" << argv[2] << "'!\n";
                    x=1;
                }
                else if(input_file.is_open())
                {
                    inputFile = argv[2];
                    x=0;
                }
            }
            else
            {
                std::cout<<" Wrong switch for program "<<std::endl;
                x=1;
            }
    }
    else 
        x=1;
    return x;
}

//inserting lines of file into map
std::unordered_map<int, std::vector<std::string> > readFile(std::string &inputFile)
{    
    int x;
    int y = 0;
    std::vector<std::string> words;
    std::unordered_map<int, std::vector<std::string> > holder; 
    std::ifstream file(inputFile);
    std::string line, word1, word2;
    while (getline(file,line))
    {  
        words.clear();
        std::stringstream line1(line);
        x = 0;
        while(line1>>word1&& x!=1)
        {
            word2.clear();
            if(x !=1 )
            {
                for(int i = 0; i < word1.size();i++)
                {
                    if(word1[i] != '%')
                    {   
                        if (words.empty())
                            word2 += tolower(word1[i]);
                        else
                        {
                            if (word1[i]== ',')
                                word2 += '.';
                            else    
                                word2 += word1[i];
                        }
                    }
                    else if (word1[i] == '%')
                    {
                        x++;
                    }
                }
                if(!word2.empty())
                {
                    words.push_back(word2);
                }
            }

        }
        if(!words.empty())
        {
            holder.insert(std::make_pair(y, words));
            y++;
        }

        }    
    return holder;
}

//finding order of tree
int findOrder(std::unordered_map<int , std::vector<std::string> > map )
{
    bool digit,t;
    int order, y;
    for(int i =0; i < map.size(); i++)//checking in witch line is order of bTree
    {
            if (map[i].size() == 1)
            {
                for(int h = 0; h < map[i][0].size(); h++)
                {
                    if (std::isdigit(map[i][0][h]) == 0)
                    {
                        continue;
                    }
                    else 
                    {
                        digit = true;
                        y=i;
                    }
                }
            }
    }
    if(digit == true) //Reading order of tree
    {
        order = stoi(map[y][0]);
    }
    else
    {
        std::cout<<"Wrong maked file. Please put in file order of tree "<<std::endl;
        order = 0;
    }
    if (order <2)
    {
        std::cout<< " Minimum order of Tree is equal to 2 "<<std::endl;
        order = 0;
    }
   
    return order;
}

//doing operations from file on bTree
void findFunction(std::unordered_map<int, std::vector<std::string> > map, int order)
{

    if (order != 0)
    {
        tree bTree(order);
        for(int i = 0; i < map.size(); i++)
        {
            if(map[i][0] == "add")
                {
                    for (int j = 1; j < map[i].size(); j++)
                    {
                        double number = stod(map[i][j]);
                        std::cout<< number; //idc why but yes
                        std::cout<<"\r";
                        bTree.add(number);
                    }
                }
            else if(map[i][0] =="print" && map[i].size()==1)
            {
                bTree.print();
            }
            else if(map[i][0] =="print")
            {
                bTree.print(map[i][1]);
            }
            else if(map[i][0]=="graph" && map[i].size()==1)
            {
                bTree.graph();
            }
            else if(map[i][0]=="graph")
            {
                bTree.graph(map[i][1]);
            }
        }
    }
}   
