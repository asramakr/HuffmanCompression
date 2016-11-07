/**
 * Authors: Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/7/16
 * Description: Contains the implementations for the methods associated
 * under all BitInputStream objects, which derives from the istream class
 */

#include <iostream>
#include "BitInputStream.h"
#include <math.h>
#include <bitset>
using namespace std;

/** Fill the buffer from the input */
void BitInputStream::fill() {
  buf = in.get(); // get a byte from the istream file
  nbits = 0; // reset buffer index
}

/** Read the next bit from the bit buffer.
 *  Fill the buffer from the input stream first if needed.
 *  Return 1 if the bit read is 1;
 *  return 0 if the bit read is 0.
 *
 */
int BitInputStream::readBit() {
  int lastInt;
  // If all bits in the buffer are read, fill the buffer first
  if(nbits==8){
    fill();
  }
  
  // Get the bit at the appropriate location in the bit
  // buffer, and return the appropriate int
  
  lastInt = ((buf & (int)pow(2, nbits))/(int)pow(2, nbits));

  //cout << "InputStream Buffer: "<< std::bitset<8>(buf) << endl;  
  nbits++; // increment the index
  return lastInt;


}

/**
 * Checks if end of BitInputStream file is reached, calling istream's
 * eof()
 */
int BitInputStream::eof(){
  return in.eof();
}
