/**
 * Authors: Alexis Atianzar & Arun Ramakrishnan
 * Date: 11/7/16
 * Description: Contains the implementations for the methods associated
 * under all BitOutputStream objects, which derives from the ostream class
 */

#include <iostream>
#include <math.h>
#include "BitOutputStream.h"
#include <fstream>
#include <bitset>
using namespace std;

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf); // write the buffer bits into the actual ostream file
  out.flush(); // flush the buffer
  buf = nbits = 0; // reset the buffer index
}

/** Write the least significant bit of the argument to
 *  the bit buffer, and increment the bit buffer index.
 *  But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i) {  
  // Write the least significant bit of i into the buffer
  // at the current index
  
  // insert 1 as bit into buffer
  if(i & 1 == 1){
    buf = (buf | ((int)pow(2, nbits)));
  }

  // insert 0 as bit into buffer
  if(i & 1 == 0){
    buf = (buf & (~((int)pow(2, nbits))));
  }

  nbits++; // increment the index
  //cout << "OutputStream Buffer: "<< std::bitset<8>(buf) << endl;
  
  // Is the bit buffer full? Then flush it.
  if(nbits==8){
    flush();
  }  
}
