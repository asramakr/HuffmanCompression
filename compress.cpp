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
  vector<int> freqsInit; // flag counter for which ASCII symbs are in file
  HCTree newTree; //the HCTree
  //unsigned int numOfSymbols = 0;


  infile.open(argv[1], std::ios::binary); //opens the file

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

  // make header to hold bit flags for each 256 ASCII symbol

  int header1 = 0; // flags for 1-32 in ASCII
  int header2 = 0; // flags for 33-64 in ASCII
  int header3 = 0; // flags for 65-96 in ASCII
  int header4 = 0; // flags for 97-128 in ASCII
  int header5 = 0; // flags for 129-160 in ASCII
  int header6 = 0; // flags for 161-192 in ASCII
  int header7 = 0; // flags for 193-224 in ASCII
  int header8 = 0; // flags for 225-256 in ASCII

  // fill the flag for each ASCII symbol if it appears in file
  for(int i=0; i<256; i++){
    if(freqs[i] != 0){
      //cout << "Chars In Message: " << i << endl;
      //cout <<"Number of Chars: " << freqs[i] << endl;
      freqsInit[i] = 1;
    }
  }

  // set the header ints with flags for the according ASCII symbols 
  // in that range
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

  // print the header ints w flags in the output file
  outfile << header1 << endl;
  outfile << header2 << endl;
  outfile << header3 << endl;
  outfile << header4 << endl;
  outfile << header5 << endl;
  outfile << header6 << endl;
  outfile << header7 << endl;
  outfile << header8 << endl;


  // print out the frequencies for the existing symbols into 
  // the output file
  for(int i=0; i<256; i++){
    if(freqs[i] != 0){
      outfile << freqs[i] << endl;
    }
  }

  

  //opens file again
  infile.open(argv[1], std::ios::binary);
 
  //pulls the bytes from the infile
  while((nextByte = infile.get()) != EOF){

    // if end of file is reached, exit
    if (infile.eof()) {
      break;
    }    
    nextChar = (unsigned char)nextByte; 

    //cout << "NextByte: " << nextChar << endl;
    //cout << "ENCODING " << nextChar << endl;

    newTree.encode( nextChar, out); //encodes the byte

    //cout << "nextChar: " << nextChar << endl;
    
    // if end of file is reached, exit
    if(infile.eof()){
      break; //breaks if end of file
    }

  }

  out.flush(); // flush rest of buffer in outfile

  outfile.close(); //closes both files
  infile.close();
  
}
