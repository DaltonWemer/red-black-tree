// Dalton Wemer
// CSC 325 Algorithms and Advanced Data Structures
// Homework 7: Red/Black Tree
// April 14 2021

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RBT.h"

using namespace std;


// Due to the size of this program I have decided to splt it up into multiple files. To compile without any
// errors, you must compile it along with the file 'RBT.cpp'. That file contains all of the functions that will
// be referenced to perform operations on the Red and Black Tree. Due to the use of nullptr, the program also requires
// that you compile it using at least c++11. The command I used to compile was as follow:

// ++ -std=c++11  hw7.cpp RBT.cpp -o hw7
// ./hw7

// A red–black tree is a kind of self-balancing binary search tree in computer science. 
// Each node of the binary tree has an extra bit, and that bit is often interpreted as the color 
// (red or black) of the node. These color bits are used to ensure the tree remains approximately 
// balanced during insertions and deletions. Most operations on a Red Black Tree can be completed in
// O(log n)

int main() {
    string userInput;
    RBT tree;
    nodePtr TNIL = tree.getTNIL();

    while(true)
    {
        // Prompts user to select an operation from the list of available operations
        cout << '\n';
        cout << "Select an option below to perform an operation on a Red-Black Tree!" << "\n";
        cout << "[1] Display tree" << "\n";
        cout << "[2] Search for a value" << "\n";
        cout << "[3] Insert a new value" << "\n";
        cout << "[4] Delete a value" << "\n";
        cout << "[q] Quit the program" << "\n";

        // Stores the user's input into a string variable
        cin >> userInput;
        cout << endl;

        // Calls the function that corresponds to the users input
        if(userInput == "1"){
            // Checks to see if the tree is currently empty and displays a proper message to the 
            // user
            if(tree.getRoot() == TNIL)
            {
                cout << "The tree is currently empty, try adding values to it!" << endl << endl;
            }
            cout << "Displaying the current tree!" << endl;
            cout << "-------------------------------------------" << endl;
            tree.output(tree.getRoot());
            cout << "-------------------------------------------" << endl;
            cout << endl;
        }else if(userInput == "2"){
            int key;
            cout << "Please enter in the value you would like to search for: " << "\n";
            cin >> key;
            
            nodePtr node = tree.search(tree.getRoot(), key);
            if (node != TNIL){
                if(node == tree.getRoot()){
                    std::cout << "The key is the root of the red and black tree!" << "\n";
                }else {
                    if(node -> p -> key < node -> key){
                        cout << node -> key << " is in the right child of node" << node -> p -> key << "\n";
                    }else{
                        cout << node -> key << " is in the left child of node " << node -> p -> key << "\n";
                    }
                }
            }else{
                cout << "The key " << key << " does not exist within the tree";
            }
        }else if(userInput == "3"){
            nodePtr root = tree.getRoot();
            cout << "Please enter in the value you would like to insert: " << "\n";
            int key;
            cin >> key;
            // Covers the case that tree is empty and the newly inserted node
            // will become the root node
            if(root == TNIL){
                nodePtr new_node = RBT::new_node('B', key, TNIL, TNIL, TNIL);
                tree.setRoot(new_node);
                cout << "Successfully inserted: " << key << "!" << endl;
                cout << "-------------------------------------------" << endl;
                tree.output(tree.getRoot());
                cout << "-------------------------------------------" << endl;
            }else{
                // Checks to see if the key already exists in the tree and if so 
                // inform the user that the program could not successfully insert 
                // the node
                nodePtr is_duplicate = tree.search(root, key);                
                if(is_duplicate != TNIL){
                    cout << "Could not insert " << key << " because it is already present in the tree!" << endl << endl;
                }else{
                    tree.insert(key);
                    cout << "Successfully inserted: " << key << "!" << endl;
                    cout << "-------------------------------------------" << endl;
                    tree.output(tree.getRoot());
                    cout << "-------------------------------------------" << endl;
                }
            }
        }else if(userInput == "4"){
            cout << "Please enter in the value you would like to delete: " << "\n";
            int key;
            cin >> key;
            
            // Checks to see if the node is currently in the tree and if not, informs the user that
            // the deletion was unsuccessful
            if(tree.deleteKey(key) == false)
            {
                cout << "Could not delete the key " << key << " becuase it does not exist in the current tree." << '\n' << '\n';
            }else {
                tree.deleteKey(key);
                cout << "Key " << key << " was successfully deleted from the tree" << endl << endl;
                tree.output(tree.getRoot());
            }
        }else if(userInput == "q"){
            cout << "Closing the program..." << endl;
            // Closes the program
            exit(1);
        }
        else{
            cout << "Please enter one of the inputs recognized by the program" << endl;
        }
    }
}