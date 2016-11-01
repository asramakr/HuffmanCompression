/**
 * Description: This file compresses a given text file into an encoded
 * file, that is in theory smaller than the original. 
 * Authors: Alexis Atianzar, Arun Ramakrishnan
 * Date: 11/1/16
 */

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
  std::ifstream infile; //the input file
  unsigned char nextChar; //the next char to be read
  int nextByte; //the next byte, which checks EOF
  vector<int> freqs; //the vector of frequencies of each letter in the tree
  HCTree newTree; //the HCTree
  //unsigned int numOfSymbols = 0;

  //cout << "Reading from file "' << argv[1] << '"' << "...";

  infile.open(argv[1], std::ios::binary); //opens the file
  //cout << "done." << endl;

  for(int i=0; i<256; i++){
    freqs.push_back(0); //pushes each letter into the vector
  }

  while ((nextByte = infile.get()) != EOF) {
    nextChar = (unsigned char)nextByte;
    freqs[(int)nextChar] += 1; //then increments the index of a char read in
    //cout << "nextByte: " << nextByte << endl;
    //cout << "nextChar: " << nextChar << endl;
  }

  infile.close(); //closes the infile when done reading

  newTree.build(freqs); //builds the tree

  std::ofstream outfile; //creates the outfile
  outfile.open(argv[2], std::ios::binary); //opens it so it can write to it

  //writes the header to the outfile, aka the freqs of each character
  for(int i=0; i<256; i++){
    outfile << freqs[i];
    outfile << '\n';
  }

  infile.open(argv[1], std::ios::binary); //opens the file again
 
  //pulls the bytes from the infile
  while((nextByte = infile.get()) != EOF){
    nextChar = (unsigned char)nextByte; 
//    cout << "ENCODING " << nextChar << endl;
    newTree.encode( nextChar, outfile); //encodes the byte
//    cout << "nextChar: " << nextChar << endl;
    if(infile.eof()){
      break; //breaks if end of file
    }

  }

  outfile.close(); //closes both files
  infile.close();
  
}
