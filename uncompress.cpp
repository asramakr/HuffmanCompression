/**
 * Description: This file is used to uncompress the encoded file that
 * compress creates. This would mean you would get the same input file
 * as the user put into compress.
 * Authors: Arun Ramakrishnan, Alexis Atianzar
 * Date: 11/1/2016
 */

#include "HCNode.h"
#include "HCTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
#include <math.h>
#define HEADERSIZE 256
using namespace std;

int main(int argc, char** argv) 
{
  std::ifstream infile; // file to read from
  unsigned char nextChar; // char taken from file
  int nextByte; // nextChar to int
  int freqCount; // freqs read from infile
  vector<int> freqs; // vector of which symbs appear in the file
  HCTree newTree; // tree to build using freqs
  string readLine; // var to hold each read in freq
  vector<int> totalFreq; // vector for actual freq values for each symb
  int counter = 0; // counter for all bytes in original file
  int totalSize = 0; // how many bytes were in original file

  // initialize freqs to 0
  for (int i = 0; i < HEADERSIZE; i++) {
    freqs.push_back(0);
  }
  
  // open file to read from
  infile.open(argv[1], std::ios::binary);
  BitInputStream in(infile);

  // read in the flags for which ASCII symbols appear  
  for(int i = 0; i<8; i++){
    getline(infile, readLine); 
    freqCount = stoi(readLine);

    // single out each flag and set it in the vector of
    // symbols that appear in the file
    for(int j = 0; j<32; j++){
      freqs.at((i*32)+j) = freqCount & (int)(pow(2, 31-j));

      // get the actual frequency of each symbol and put it in
      // a separate vector
      if(freqs.at((i*32)+j) != 0){
        totalFreq.push_back((i*32)+j);
      }
    }
  }

  // read in the actual freq values from the header
  for(int i=0; i<totalFreq.size(); i++){
    getline(infile, readLine);
    freqCount = stoi(readLine);

    // set the freq for that specific symb
    freqs.at(totalFreq.at(i)) = freqCount;
    //cout << "Chars In Message: " << totalFreq.at(i) << endl;
    //cout << "Number of Chars: " << freqs[totalFreq.at(i)] << endl;    
  }

  // count how many bytes were in original file
  for(int i=0; i<freqs.size(); i++){
    totalSize+=freqs[i];
  }
  

  // build tree from frequencies
  newTree.build(freqs);

  // open file to write to
  std::ofstream outfile;
  outfile.open(argv[2], std::ios::binary);

  // go through and decode the file message
  while(counter < totalSize) {

    // exit if reached end of file
    if(infile.eof()) {
      break;
    }    

    // decode infile byte by byte
    int dRet = newTree.decode(in);

    // exit if reached end of file
    if(infile.eof()){
      break;
    }

    // convert int to unsigned char
    unsigned char decodedChar = (unsigned char)dRet;

//    cout << "return: " << decodedChar << endl;

    // write decoded symbol to file
    //cout << "Decoded Char: " << decodedChar << endl;
    outfile << decodedChar;
    //cout << "ENCODING: " << decodedChar << endl; 
    counter++;   
  }

  // close files
  outfile.close();
  infile.close();
}
