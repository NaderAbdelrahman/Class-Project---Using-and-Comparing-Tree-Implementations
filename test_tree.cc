// Nader Abdelrahman
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  ifstream myfile(db_filename);
  if(myfile.is_open()){
    string db_line;
    for(int i = 0; i < 10; ++i){
      getline(myfile, db_line);
    }
    while(getline(myfile, db_line)){
      stringstream ss(db_line);
      string token;

      int counter = 1;                  // TREE BUILD
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
    cout << "2:  " << a_tree.numberOfNodes() << endl;                                                                                      // 2
                                                                                                                                             

    cout << "3a: " << static_cast<double>(a_tree.internalPathLength()) / a_tree.numberOfNodes() << endl;                                  // 3a
    cout << "3b: " << (static_cast<double>(a_tree.internalPathLength()) / a_tree.numberOfNodes()) / log2(a_tree.numberOfNodes()) << endl; // 3b

    myfile.close();
  }
  else {cout << "Unable to open file";}
  ifstream file(seq_filename);
  if(file.is_open()){
    string seq_line;
    float sucessful = 0;
    while(getline(file, seq_line)){
      SequenceMap c(seq_line, ""), d;
      if(a_tree.find(c, d)){                // FIND
        ++sucessful;
      }
    }
    // cout << "4a: " << a_tree.total_rec_calls_getter_() << endl;
    cout << "4a: " << sucessful << endl;
    cout << "4b: " << a_tree.total_rec_calls_getter_() / sucessful << endl; 
    file.close();
  }
  else{cout << "Unable to open file";}
  ifstream thisfile(seq_filename);
  if(thisfile.is_open()){
    string seq_line2;
    float sucessful = 0;
    for(;;){
      getline(thisfile, seq_line2); // SKIPPING 1ST LINE
      if(thisfile.eof()){break;}
      getline(thisfile, seq_line2); // REMOVING 2ND LINE
      if(!thisfile.eof()){
        SequenceMap a(seq_line2, "");
        a_tree.find(a, a);
        if(a_tree.contains(a)){ 
          a_tree.remove(a);
          ++sucessful;
        }
      }else{break;}
    }
    // cout << "5a: " << sucessful << endl                 // 5a
    // << "5b: " << total/sucessful << endl;               // 5b
    // cout << "5a: " << a_tree.remove_calls_getter_() << endl;
    cout << "5a: " << sucessful << endl;
    cout << "5b: " << a_tree.remove_calls_getter_() / sucessful << endl; 
    
    cout << "6a: " << a_tree.numberOfNodes() << endl;   // 6a
    // string a = "6b", b = "6c";                                  // 6b, 6c
    // a_tree.averageDepthPrinter(a, b);
    cout << "6b: " << static_cast<double>(a_tree.internalPathLength()) / a_tree.numberOfNodes() << endl;                                  // 6a
    cout << "6c: " << (static_cast<double>(a_tree.internalPathLength()) / a_tree.numberOfNodes()) / log2(a_tree.numberOfNodes()) << endl; // 6b
    file.close();
  }
  else{cout << "Unable to open file";}
}
}// namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }

  return 0;
}
