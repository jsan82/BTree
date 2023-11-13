#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <vector>
#include <unordered_map>

/** 
 * @brief decoding our input
 * 
 * @param argc 
 * @param argv 
 * @param inputFile 
 * @return 1: failed to open file; 0: OK 
 */
int decodeArgs(int argc, char *argv[], std::string &inputFile);

/**
 * @brief finding order of bTree in our file 
 * 
 * @param map map filled with vectors
 * @return  order of bTree
 */
int findOrder(std::unordered_map<int , std::vector<std::string> > map );

/**
 * @brief finding order of bTree in our file 
 * 
 * @param inputFile name of input
 * @return map filed with lines of file
 */
std::unordered_map<int, std::vector<std::string> >  readFile(std::string &inputFile);

/**
 * @brief reading commands from map and carrying out operations on bTree
 * 
 * @param map map filled with vectors
 * @param order order of bTree
 */
void findFunction(std::unordered_map<int, std::vector<std::string> > map,int order);



#endif
