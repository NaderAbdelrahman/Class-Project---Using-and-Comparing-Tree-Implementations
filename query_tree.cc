// Nader Abdelrahman
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  ifstream myfile(db_filename);
  if(myfile.is_open()){
    string db_line;
    for(int i = 0; i < 10; ++i){
      getline(myfile, db_line);
    }
    while(std::getline(myfile, db_line)){
      stringstream ss(db_line);
      string token;

      int counter = 1;
      string enzyme_acronym;
      while(getline(ss, token, '/')){
        if(token == ""){
          break;
        }
        if(counter == 1){
          enzyme_acronym = token;
        }
        else{
          SequenceMap obj(token, enzyme_acronym);
          a_tree.insert(obj);
        }
        ++counter;
      }
    }
    myfile.close();
  }
  else cout << "Unable to open file";
  string input1, input2, input3;
  // cout << "Please enter recognition sequence 1: " << endl << "> ";
  getline(cin, input1);
  // cout << "Please enter recognition sequence 2: " << endl << "> ";
  getline(cin, input2);
  // cout << "Please enter recognition sequence 3: " << endl << "> ";
  getline(cin, input3);
  SequenceMap a(input1, "");
  a_tree.find(a, a);
  if(a_tree.contains(a)){
    cout << a;
  }else{
    cout << "Not Found" << endl;
  }
  SequenceMap b(input2, "");
  a_tree.find(b, b);
  if(a_tree.contains(b)){
    cout << b;
  }else{
    cout << "Not Found" << endl;
  }
  SequenceMap c(input3, "");
  a_tree.find(c, c);
  if(a_tree.contains(c)){
    cout << c;
  }else{
    cout << "Not Found" << endl;
  }
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }

  return 0;
}
