/** @file main.cpp
 * @author Swe Zin Oo
 * @date 26 Mar 2024
 * @brief The main.cpp file is the entry point of the program. It includes reading data from a file for morse code, building a morse code
 * tree using that data, encoding and decoding a message using morse code tree.
*/

#include <iostream>
#include <map>
#include "string.h"
#include "utils.h"
#include "Binary_Tree.h"

using namespace std;

int main(){

    
    map<char,string> morse_code_map = read_data_from_file("letter.txt");
    

    Binary_Tree<string>* morse_code_tree = new Binary_Tree<string>();
    morse_code_tree->build_morse_code_tree(morse_code_map);
    

    string encoded_message = morse_code_tree->encode_message("Hello World",morse_code_map);
    cout << "Coded message: " << encoded_message << endl;

    string decoded_message = morse_code_tree->decode_message(encoded_message);
    cout << "Decoded message: " << decoded_message << endl;
    
    return 0;
}