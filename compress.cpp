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
#include <math.h>
using namespace std;


int main(int argc, char** argv)
{
  std::ifstream infile; //the input file
  unsigned char nextChar; //the next char to be read
  int nextByte; //the next byte, which checks EOF
  vector<int> freqs; //the vector of frequencies of each letter in the tree
  vector<int> freqsInit;
  HCTree newTree; //the HCTree
  //unsigned int numOfSymbols = 0;

  //cout << "Reading from file "' << argv[1] << '"' << "...";

  infile.open(argv[1], std::ios::binary); //opens the file
  //cout << "done." << endl;

  for(int i=0; i<256; i++){
    freqs.push_back(0); //pushes each letter into the vector
    freqsInit.push_back(0);
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
  BitOutputStream out(outfile);

  /*
  //writes the header to the outfile, aka the freqs of each character
  for(int i=0; i<256; i++){
    outfile << freqs[i];
    outfile << '\n';
  }
  */

  //new header tests

  int header1 = 0;
  int header2 = 0;
  int header3 = 0;
  int header4 = 0;
  int header5 = 0;
  int header6 = 0;
  int header7 = 0;
  int header8 = 0;

  for(int i=0; i<256; i++){
    if(freqs[i] != 0){
      cout << "Chars In Message: " << i << endl;
      cout <<"Number of Chars: " << freqs[i] << endl;
      freqsInit[i] = 1;
    }
  }

  for(int i=0; i<32; i++){
    header1 = header1 | (int)(freqsInit[i]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header2 = header2 | (int)(freqsInit[i+32]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header3 = header3 | (int)(freqsInit[i+64]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header4 = header4 | (int)(freqsInit[i+96]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header5 = header5 | (int)(freqsInit[i+128]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header6 = header6 | (int)(freqsInit[i+160]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header7 = header7 | (int)(freqsInit[i+192]*pow(2, 31-i));
  }
  for(int i=0; i<32; i++){
    header8 = header8 | (int)(freqsInit[i+224]*pow(2, 31-i));
  }

  outfile << header1 << endl;
  outfile << header2 << endl;
  outfile << header3 << endl;
  outfile << header4 << endl;
  outfile << header5 << endl;
  outfile << header6 << endl;
  outfile << header7 << endl;
  outfile << header8 << endl;



  for(int i=0; i<256; i++){
    if(freqs[i] != 0){
      outfile << freqs[i] << endl;
    }
  }

  

  //opens file again
  infile.open(argv[1], std::ios::binary);
 
  //pulls the bytes from the infile
  while((nextByte = infile.get()) != EOF){
    if (infile.eof()) {
      break;
    }    
    nextChar = (unsigned char)nextByte; 
    cout << "NextByte: " << nextChar << endl;
    //cout << "ENCODING " << nextChar << endl;
    newTree.encode( nextChar, out); //encodes the byte
//    cout << "nextChar: " << nextChar << endl;
    
    if(infile.eof()){
      break; //breaks if end of file
    }

  }

  out.flush();

  outfile.close(); //closes both files
  infile.close();
  
}
