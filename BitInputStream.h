#include <iostream>
#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

class BitInputStream {
  private:
    char buf; // one byte buffer of bits
    int nbits; // how many bits have been written to buf
    std::istream & in; // reference to the input stream to use

  public:
    /** Initialize a BitOuputStream that will use the given ostream
     * for output */
    BitInputStream(std::istream & is) : in(is), buf(0), nbits(8) {}

    /** Fill the buffer from the input */
    void fill();

    /** Read and return the next bit from the bit buffer.
     *  Fill it first if necessary. */
    int readBit();

    int eof();
};

#endif //BITINPUTSTREAM_H
