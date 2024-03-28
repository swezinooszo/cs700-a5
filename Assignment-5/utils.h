/** @file utils.h
 * @author Swe Zin Oo
 * @date 26 Mar 2024
 * @brief This is the utility class of the program, emcompassing all functions necessary for building a binary tree.
*/
#pragma once

#include <map>
using namespace std;

/** Read the data (letter and morse code) from a file
 * @param filename filename
 * @return return the map which include letter as char and morse code as string
*/ 
map<char,string> read_data_from_file(string filename);