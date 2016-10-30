#include "HCNode.h"
#include "HCTree.h"
#include<iostream>
#include <fstream>
#include<string>
#include<set>
#include<cstdlib>
using namespace std;


int main(int argc, char** argv)
{
  std::ofstream infile;
  unsigned char nextChar;
  vector<unsigned char> freqs;
  HCTree newTree;
  infile.open(argv[1], std::ios::binary);
  while (1) {
    nextChar = infile.get();
    if (infile.eof()) {
      break;
    }
    freqs.push_back(nextChar);
  }

  newTree.build(freqs);



  std::ofstream outfile;
  outfile.open(arg[2], std::ios::binary);


  
}
