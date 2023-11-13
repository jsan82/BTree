#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
#include <deque>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <filesystem>

class tree
{
    private: 

        class Node 
        {
            public:
                std::deque<double> values;
                std::deque<int>children;
                bool isLeaf() { return children.empty(); }
                int parent;
                int index;
                unsigned int order;
        };
        std::unordered_map<int, Node> nodes; // map of nodes
        int root;                            // index of root node
        int order;

    public :

    /**
     * @brief Construct a new tree object
     * 
     * @param _order order of our bTree
     */
    tree(int _order);

    /**
     * @brief Checking if tree isn't empty and going to print
     * 
     */
    void print();


    /**
     * @brief Going to childrens if exist and printing values for current node
     * 
     * @param currentNode node which is gonna print
     */
    void print(int currentNode);

    /**
     * @brief Checking if tree isn't empty and going to print in file
     * 
     * @param file name of file in which is gonna print values
     */
    void print(std::string &file);

    /**
     * @brief Going to childrens if exist and printing values for current node in file
     * 
     * @param currentNode node which is gonna print
     * @param os file in which is gonna print values
     */
    void print(int currentNode, std::ofstream &os);

    /**
     * @brief  Checking if tree isn't empty and going to graph
     * 
     */
    void graph();

    /**
     * @brief  Going to childrens if exist and printing values for current node as graph
     * 
     * @param currentNode node which is gonna print
     * @param tab distance from root
     */
    void graph(int currentNode, int tab);

    /**
     * @brief Checking if tree isn't empty and going to graph
     * 
     * @param file name of file in which is gonna print values
     */
    void graph(std::string &file);

    /**
     * @brief Going to childrens if exist and printing values for current node as graph in file
     * 
     * @param currentNode node which is gonna print
     * @param tab distance from root
     * @param os file in which is gonna print values
     */
    void graph(int currentNode, int tab, std::ofstream &os);

    /**
     * @brief checking if root exist and sending value to insert
     * 
     * @param value value which is gonna be inserted into our bTree
     */
    void add(double value);

    /**
     * @brief inserting in bTree
     * 
     * @param val value which is gonna be inserted into our bTree
     */
    void insert(double val);
    
    /**
     * @brief loop to checking full nodes
     * 
     * @param currentNode node to check 
     */
    void splitChilds(int currentNode);

    /**
     * @brief checking if current node is full
     * 
     * @param currentNode node to check
     * @return value of parent node to check 
     */
    int splitChild(int currentNode);


    /**
     * @brief Get the Median object
     * 
     * @param node adress of node
     * @return value which is going to parnt node
     */
    double getMedian(int node);

};


#endif