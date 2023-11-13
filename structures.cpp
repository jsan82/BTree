/**
 * @file structures.cpp
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
#include <deque>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <filesystem>

#include "structures.h"

//Construct a new tree::tree object
tree::tree(int _order)
{
    {
        root = 0; 
        order = _order;
    } 
}


void tree::splitChilds(int currentNode){
        while (currentNode != -1)
        {
            currentNode = splitChild(currentNode);
        }

    }

//geting value to go to parent node
double tree::getMedian(int node)
    {
        int median = std::ceil(nodes[node].values.size()/2);
        return nodes[node].values[median];
    }

//creating tree in necessary and inserting values
void tree::add(double value)
{
    if(nodes.empty()){
        Node node;
        node.index=0; //creating index of node
        node.parent=-1; //creating index of parent
        root = node.index; //saving index of root
        node.values.push_back(value); //inserting our value into branch
        nodes.insert(std::make_pair(node.index, node)); //saving our brench in map
    }
    else  
    {   
        insert(value);
    }
    
    
};

//inserting value in right node
void tree::insert(double value)
{   
    int currentNode = root;
    int i = nodes[currentNode].values.size();
    while (bool running = true)
    {   
        for (int i = 0; (i < nodes[currentNode].values.size()) && running; i++)
        {
            if (nodes[currentNode].isLeaf())
            {
                for (auto i = nodes[currentNode].values.begin(); i != nodes[currentNode].values.end(); i++)
                {       
                    if (value <= *i)
                    {
                        if (value == *i)
                        {
                            return;
                        }
                        else
                        {
                            nodes[currentNode].values.insert(i, value);
                            splitChilds(currentNode);
                            return;
                        }
                    }
                }
                nodes[currentNode].values.push_back(value);
                splitChilds(currentNode);
                return;
            }
            if(i+1 < nodes[currentNode].values.size())
            {
                if(value == nodes[currentNode].values[i])
                {
                    return;
                }
                else if(value < nodes[currentNode].values[i])
                {
                    currentNode = nodes[currentNode].children[i];
                    running = false;
                }
            }
            else
            {
                if (value == nodes[currentNode].values[i])
                {
                    return;
                }
                else
                {
                    if(value < nodes[currentNode].values[i])
                    {
                        currentNode = nodes[currentNode].children[i];
                        running = false;
                    }
                    else if(value > nodes[currentNode].values[i])
                    {
                        currentNode = nodes[currentNode].children[i+1];
                        running = false;
                    }
                }
                
            }
        }
    }
    
};

//spliting node if necessary
int tree::splitChild(int nodeId)
{
    Node &node = nodes[nodeId];
    
    if(node.values.size() > order)
    {   
        double median = getMedian(nodeId);
        Node newNode;
        newNode.parent=node.parent;
        newNode.index = nodes.size();
        if(node.parent == -1)
        {
            Node newRoot;
            newRoot.parent = -1;
            newRoot.values.push_back(median);
            newRoot.children.push_back(node.index);
            newRoot.children.push_back(newNode.index);
            for (auto value = node.values.end(); value != node.values.begin(); value--)
            {
                if (*value == median)
                {
                    node.values.erase(value);
                }
                else if(*value > median)
                {
                    newNode.values.push_front(*value);
                    node.values.erase(value);
                }
            }
            for (auto child = node.children.end(); child != node.children.begin() ; child--)
                {
                   if (*child >= order +1)
                   {    
                        newNode.children.push_front(*child);
                        node.children.erase(child);
                   }

                }
            for(int i = 0; i< newNode.children.size(); i++)
            {
                nodes[newNode.children[i]].parent = newNode.index;
            }
                nodes.insert(std::make_pair(newNode.index, newNode));
                newRoot.index = nodes.size();
                root = newRoot.index;
                nodes.insert(std::make_pair(newRoot.index, newRoot));

                nodes[newNode.index].parent = newRoot.index;
                node.parent = newRoot.index;
            
            return -1;
        }
        for (auto value = node.values.end()-1; value != node.values.begin(); value--)
            {
                if (*value == median)
                {
                    node.values.erase(value);
                    break;
                }
                else if (*value > median)
                {
                    newNode.values.push_back(*value);
                    node.values.erase(value);
                }
            }
            nodes.insert(std::make_pair(newNode.index, newNode));
            int i = 0;
            bool addMedian = true;
             std::deque<int>::iterator it = nodes[node.parent].children.begin();
        for (auto value = nodes[node.parent].values.begin(); value != nodes[node.parent].values.end(); value++) //heere is problem
            {
                i++;
                if (*value > median)
                {
                    it = it + i;
                    nodes[node.parent].values.insert(value, median);
                    nodes[node.parent].children.insert(it, newNode.index );
                    addMedian = false;
                    break;
                }
            }
            if (addMedian == true)
            {
                nodes[node.parent].values.push_back(median);
                nodes[node.parent].children.push_back(newNode.index);
            }
            splitChilds(node.parent);
        

    }
    else
    {

        return -1;
    }
}

//checking if tree no empty and going to printing;
void tree::print()
    {
        if(nodes.empty())
        {
            std::cout<<"Tree is empty"<<std::endl;
        }
        else 
        {
            int currentNode = root;
            print(currentNode);
        }
        std::cout<<std::endl;
    }

//checking if tree no empty and going to printing;
void tree::print(std::string &file)
    {
        std::ofstream os;
        os.open(file);
        if(nodes.empty())
        {
            os<<"Tree is empty"<<std::endl;
        }
        else 
        {
            int currentNode = root;
            print(currentNode, os);
        }
        os<<std::endl;
        os.close();
        
    }

//printing values of tree in one line in file
void tree::print(int currentNode,std::ofstream &os)
    {
            for (int i = 0; i <= nodes[currentNode].values.size(); i++)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        for (int j = 0; j<nodes[currentNode].values.size(); j++)
                        {       
                            os<< nodes[currentNode].values[j] <<" ";
                        }
                        return;
                    }
                    else
                    {
                        print(nodes[currentNode].children[i], os);
                        if (i < nodes[currentNode].values.size())
                            os<< nodes[currentNode].values[i] <<" ";
                        
                    }
                }
    }    

//printing values of tree in one line
void tree::print(int currentNode)
    {
            for (int i = 0; i <= nodes[currentNode].values.size(); i++)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        for (int j = 0; j<nodes[currentNode].values.size(); j++)
                        {       
                            std::cout<< nodes[currentNode].values[j] <<" ";
                        }
                        return;
                    }
                    else
                    {
                        print(nodes[currentNode].children[i]);
                        if (i < nodes[currentNode].values.size())
                            std::cout<< nodes[currentNode].values[i] <<" ";
                        
                    }
                }
    }

//checking if tree is not empty and start printing graph
void tree::graph()  
    {
        if(nodes.empty())
        {
            std::cout<<"Tree is empty"<<std::endl;
        }
        else 
        {
            int currentNode = root;
            int tab = 0;
            for (int i = nodes[currentNode].values.size()-1; i >=0; i--)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        
                        for (int j = nodes[currentNode].values.size()-1; j>=0; j--)
                        {       
                            for(int tab1=tab;tab1 >=0 ; tab1--)
                                std::cout<<"    ";
                            if(j == 0)
                                std::cout<<"[";
                            std::cout<< nodes[currentNode].values[j];
                             if(j == nodes[currentNode].values.size()-1)
                                std::cout<<"]";
                            std::cout<<"\n";
                        }
                        
                        return;
                    }
                    else
                    {
                        tab++;
                        graph(nodes[currentNode].children[i+1],tab);
                        tab--;

                        
                        for(int tab1=tab; tab1>0; tab1--)
                            std::cout<<"    ";
                        if(i == 0)
                                std::cout<<"[";
                        std::cout<< nodes[currentNode].values[i];
                        if(i == nodes[currentNode].values.size()-1)
                                std::cout<<"]";
                            std::cout<<"\n";
                        if(i==0)
                        {
                            tab++;
                            graph(nodes[currentNode].children[i],tab);
                            tab--;
                        }
                    }
                }
        std::cout<<std::endl;
        }
    }

////checking if tree is not empty and start printing graph for nodes
void tree::graph(int currentNode, int tab)
    {
        for (int i = nodes[currentNode].values.size()-1; i >=0; i--)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        
                        for (int j = nodes[currentNode].values.size()-1; j>=0; j--)
                        {       
                            for(int tab1=tab;tab1 >=0 ; tab1--)
                                std::cout<<"    ";
                            if(j == 0)
                                std::cout<<"[";
                            std::cout<< nodes[currentNode].values[j];
                             if(j == nodes[currentNode].values.size()-1)
                                std::cout<<"]";
                            std::cout<<"\n";
                        }
                        
                        return;
                    }
                    else
                    {
                        tab++;
                        graph(nodes[currentNode].children[i+1],tab);
                        tab--;

                        
                        for(int tab1=tab; tab1>0; tab1--)
                            std::cout<<"    ";
                        if(i == 0)
                                std::cout<<"[";
                        std::cout<< nodes[currentNode].values[i];
                        if(i == nodes[currentNode].values.size()-1)
                                std::cout<<"]";
                            std::cout<<"\n";
                        if(i==0)
                        {
                            tab++;
                            graph(nodes[currentNode].children[i],tab);
                            tab--;
                        }
                    }
                }
        std::cout<<std::endl;
    }
//checking if tree is not empty and start printing graph in file
void tree::graph(std::string &file)  
    {
        std::ofstream os;
        os.open(file);
        if(nodes.empty())
        {
            os<<"Tree is empty"<<std::endl;
        }
        else 
        {
            int currentNode = root;
            int tab = 0;
            for (int i = nodes[currentNode].values.size()-1; i >=0; i--)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        
                        for (int j = nodes[currentNode].values.size()-1; j>=0; j--)
                        {       
                            for(int tab1=tab;tab1 >=0 ; tab1--)
                                os<<"    ";
                            if(j == 0)
                                os<<"[";
                            os<< nodes[currentNode].values[j];
                             if(j == nodes[currentNode].values.size()-1)
                                os<<"]";
                            os<<"\n";
                        }
                        
                        return;
                    }
                    else
                    {
                        tab++;
                        graph(nodes[currentNode].children[i+1], tab, os);
                        tab--;
                        for(int tab1=tab; tab1>0; tab1--)
                            os<<"    ";
                        if(i == 0)
                            os<<"[";
                        os<< nodes[currentNode].values[i];
                        if(i == nodes[currentNode].values.size()-1)
                            os<<"]";
                            os<<"\n";
                        if(i==0)
                        {
                            tab++;
                            graph(nodes[currentNode].children[i], tab, os);
                            tab--;
                        }
                    }
                }
        os<<std::endl;
        }
        os.close();
    }

//checking if tree is not empty and start printing graph of nodes in file
void tree::graph(int currentNode, int tab, std::ofstream &os)
    {
        for (int i = nodes[currentNode].values.size()-1; i >=0; i--)
                {
                    if (nodes[currentNode].isLeaf())
                    {
                        
                        for (int j = nodes[currentNode].values.size()-1; j>=0; j--)
                        {       
                            for(int tab1=tab;tab1 >=0 ; tab1--)
                                os<<"    ";
                            if(j == 0)
                                os<<"[";
                            os<< nodes[currentNode].values[j];
                             if(j == nodes[currentNode].values.size()-1)
                                os<<"]";
                            os<<"\n";
                        }
                        
                        return;
                    }
                    else
                    {
                        tab++;
                        graph(nodes[currentNode].children[i+1], tab, os);
                        tab--;

                        
                        for(int tab1=tab; tab1>0; tab1--)
                            os<<"    ";
                        if(i == 0)
                                os<<"[";
                        os<< nodes[currentNode].values[i];
                        if(i == nodes[currentNode].values.size()-1)
                                os<<"]";
                            os<<"\n";
                        if(i==0)
                        {
                            tab++;
                            graph(nodes[currentNode].children[i], tab, os);
                            tab--;
                        }
                    }
                }
        os<<std::endl;
    }
