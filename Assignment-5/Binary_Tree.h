/** @file Binary_Tree.h
 * @author Swe Zin Oo
 * @date 26 Mar 2024
 * @brief A Binary Tree class which will be used to implment morse code tree, to encode message into morse code and to decode morse code
 * into a message.
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <map>
#include <cctype> 
#include "BTNode.h"

template<typename Item_Type>
  class Binary_Tree
{
  public:

  // Constructors and Functions

  /** Construct an empty Binary_Tree. */
Binary_Tree() : root(NULL) {}

  /** Construct a Binary_Tree with two subtrees.
      @param the_data The data at the root
      @param left_child The left subtree
      @param right_child The right subtree
  */
Binary_Tree(const Item_Type& the_data, 
            const Binary_Tree<Item_Type>& left_child
              = Binary_Tree(),
            const Binary_Tree<Item_Type>& right_child
               = Binary_Tree()):
  root(new BTNode<Item_Type>(the_data, left_child.root,
                             right_child.root)) {}

  /** Virtual destructor to avoid warnings */
  virtual ~Binary_Tree() {} // Do nothing.


  /** Return the left subtree. */
   Binary_Tree<Item_Type> get_left_subtree() const;

  /** Return the right subtree. */
  Binary_Tree<Item_Type> get_right_subtree() const;

  /** Return the data field of the root.
      @throws std::invalid_argument if empty tree
  */
  const Item_Type& get_data() const;

  void set_data(const Item_Type& new_data);
  /** Indicate that this is the empty tree. */
  bool is_null() const;

  /** Indicate that this tree is a leaf. */
  bool is_leaf() const;

  /** Return a string representation of this tree. */
  virtual std::string to_string() const;

  /** Read a binary tree */
  static Binary_Tree<Item_Type> read_binary_tree(std::istream& in);

  /** Return a string representation of the root */
  std::string root_to_string() const {
    return root->to_string();
  }

  /** Build a binary tree */
  void build_morse_code_tree(std::map<char, std::string> morseCode);
  /** Encode message into morse code */
  std::string encode_message(const std::string& message, std::map<char, std::string>& morseCode);
  /** Decode morse code into message */
  std::string decode_message(const std::string& morse);

  protected:

  // Protected constructor
  /** Construct a Binary_Tree with a given node as the root */
 Binary_Tree(BTNode<Item_Type>* new_root) : root(new_root) {}

  // Data Field
  BTNode<Item_Type>* root;

 private:

 
};  // End Binary_Tree

// Overloading the ostream insertion operator.
template<typename Item_Type>
  std::ostream& operator<<(std::ostream& out, 
                           const Binary_Tree<Item_Type>& tree)
{
  return out << tree.to_string();
}

// Overloading the istream extraction operator
template<typename Item_Type>
  std::istream& operator>>(std::istream& in, 
                           Binary_Tree<Item_Type>& tree)
{
  tree = Binary_Tree<Item_Type>::read_binary_tree(in);
  return in;
}

// Implementation of member functions

/** Return a string representation of this tree */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::to_string() const {
  std::ostringstream os;
  if (is_null())
    os << "NULL\n";
  else {
    os << *root << '\n';
    os << get_left_subtree().to_string();
    os << get_right_subtree().to_string();
  }
  return os.str();
}

/** Read a binary tree */
template<typename Item_Type>
  Binary_Tree<Item_Type> Binary_Tree<Item_Type>::
    read_binary_tree(std::istream& in) {
  std::string next_line;
  getline(in, next_line);
  if (next_line == "NULL") {
    return Binary_Tree<Item_Type>();
  } else {
    Item_Type the_data;
    std::istringstream ins(next_line);
    ins >> the_data;
    Binary_Tree<Item_Type> left = read_binary_tree(in);
    Binary_Tree<Item_Type> right = read_binary_tree(in);
    return Binary_Tree<Item_Type>(the_data, left, right);
  }
}

/** Return the left subtree. */
template<typename Item_Type>
 Binary_Tree<Item_Type> Binary_Tree<Item_Type>::get_left_subtree() const{
   if (root == nullptr || root->left == nullptr) {
        return Binary_Tree<Item_Type>();
    } else {
        return Binary_Tree<Item_Type>(root->left);
    }
}

/** Return the right subtree. */
template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::get_right_subtree() const{
 if (root == nullptr || root->right == nullptr) {
        return Binary_Tree<Item_Type>();
    } else {
        return Binary_Tree<Item_Type>(root->right);
    }
}

/** Indicate that this is the empty tree. */
template<typename Item_Type>
 bool Binary_Tree<Item_Type>::is_null() const{
   return root == nullptr;
 }

/** Return the data field of the root.
    @throws std::invalid_argument if empty tree
*/
template<typename Item_Type>
const Item_Type& Binary_Tree<Item_Type>::get_data() const{
    if (is_null()) {
        throw std::invalid_argument("Tree is empty");
    }
    return root->data;
 }
 
/** Build a morse code tree. A Morse code tree is a tree built with a sequence of dots (.) and dashes (-) representing letters.
 * @param morse_code_map the map of morse code which includes pair of letter and morse code where the letters will be added
 * to tree based on the sequence of morse code (dot . and dash -)
 */
template<typename Item_Type>
void Binary_Tree<Item_Type>::build_morse_code_tree(std::map<char, std::string> morse_code_map){
  BTNode<Item_Type>* local_root = root;
        if (local_root == NULL){
            local_root = new BTNode<Item_Type>(" ");
        }
        for (const auto& pair : morse_code_map) {
            BTNode<Item_Type>*  current = local_root;
            for (char c : pair.second) {
                if (c == '.') {
                    if (current->left == nullptr)
                        current->left = new BTNode<Item_Type>(" ");
                    current = current->left;
                } else if (c == '-') {
                    if (current->right == nullptr)
                        current->right = new BTNode<Item_Type>(" ");
                    current = current->right;
                }
            }
            current->data = pair.first;
        }
  root = local_root;
}

/** Encode message into morse code by replacing the letter of message by its code symbol.
 * @param message Message to be encoded
 * @param morse_code_map the morse code symbol to be replaced
 * @return the encoded message
 */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::encode_message(const std::string& message, std::map<char, std::string>& morse_code_map) {
    std::string encodedMessage;
    // break down message into char to match with morse code map
    for (char c : message) {
       // convert char to lowercase
        c = std::tolower(static_cast<unsigned char>(c));
        // if found space, add space
        if (c == ' '){
            encodedMessage += " ";
        }
        else {
            // retrieve the morse code from morse code map which match with letter.
            std::string morse_code = morse_code_map[c];
            encodedMessage += morse_code; 
            // add space between morse code
            encodedMessage += " ";
        }
    }
    return encodedMessage;
}


/** Decode the coded message using morse tree. We will find position of letter in the tree by using the structure ( dot (.)
 * for left branch and dash (-) for right branch)
 * @param coded_message the coded message to be decoded
 * @return the decoded message
 */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::decode_message(const std::string& coded_message) {
        std::string decoded_message;
        // get the root (morse tree) which is previously build by build_morse_code_tree() function
        BTNode<Item_Type>* current_root = root;
        // break down coded message into morse code
        for (char c : coded_message) {
            // after reading each morse code and find space, retrieve letter
            if (c == ' ') {
                decoded_message += current_root->data;
                current_root = root;
            } 
            // if dot (.), go to the left branch and save the current branch
            else if (c == '.') {
                current_root = current_root->left;
            } 
            // if dash (-), go to the right branch and save the current brach
            else if (c == '-') {
                current_root = current_root->right;
            }
        }
        decoded_message += current_root->data;
        return decoded_message;
};

#endif

