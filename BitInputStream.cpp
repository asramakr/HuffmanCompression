#include <iostream>
#include "BitInputStream.h"
#include <math.h>
#include <bitset>

using namespace std;
/** Constructor (Initialize a BitInputStream that will use
 *  the given istream for input.
 */
/*BitInputStream::BitInputStream(std::istream & is) {
  buf = 0; // clear buffer

  // CHANGE VALUE; NOT SUPPOSED TO EQUAL 0!!!!
  nbits = 8; // initialize bit index 
}
*/

/** Fill the buffer from the input */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
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

  cout << "InputStream Buffer: "<< std::bitset<8>(buf) << endl;  
  nbits++;
  return lastInt;


  // Increment the index
}

int BitInputStream::eof(){
  return in.eof();
}
