/** @file utils.cpp
 * @author Swe Zin Oo
 * @date 26 Mar 2024
 * @brief The implementation file of "utils.h"
*/
#include "utils.h"
#include <iostream>
#include <fstream>

map<char,string> read_data_from_file(string filename){
  map<char,string> morse_code_map;
  ifstream inData("letter.txt");
    if (inData.is_open()) {
        char letter;
        string morsecode;
        while (inData >> letter >> morsecode) {
             morse_code_map[letter] = morsecode;
        }
        inData.close();
    } else {
        cout << "Unable to open the file for reading" << endl;
    }
  return morse_code_map;
}

