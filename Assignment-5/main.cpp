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

    // read letter and morse code data from a file and add to a morse code map 
    map<char,string> morse_code_map = read_data_from_file("letter.txt");
    
    // build a morse code tree using binary tree and morse_code_map
    Binary_Tree<string>* morse_code_tree = new Binary_Tree<string>();
    morse_code_tree->build_morse_code_tree(morse_code_map);
    
    // enter a message
    string message = " ";
    cout << "Enter a message" <<endl;
    getline(cin,message);

    // encode the entered messsage into morse code using morse code map
    string encoded_message = morse_code_tree->encode_message(message,morse_code_map);
    cout << "Coded message: " << endl;
    cout << encoded_message << endl;

    // decode the encoded messsage using morse tree
    string decoded_message = morse_code_tree->decode_message(encoded_message);
    cout << "Decoded message: " << endl;
    cout << decoded_message << endl;
    
    return 0;
}