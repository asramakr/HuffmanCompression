#include <iostream>
#include <math.h>
#include "BitOutputStream.h"
#include <fstream>
#include <bitset>

using namespace std;
/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to
 *  the bit buffer, and increment the bit buffer index.
 *  But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i) {  
  // Write the least significant bit of i into the buffer
  // at the current index
  
  if(i & 1 == 1){
    buf = (buf | ((int)pow(2, nbits)));
  }

  if(i & 1 == 0){
    buf = (buf & (~((int)pow(2, nbits))));
  }

  nbits++;
  cout << "OutputStream Buffer: "<< std::bitset<8>(buf) << endl;
  // Increment the index
  
  // Is the bit buffer full? Then flush it.
  if(nbits==8){
    flush();
  }  
}
