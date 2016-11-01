/**
 * Description: The Node class for the Huffman tree, it has the < operator
 * for the priority queue in HCTree. This class has two children nodes,
 * one parent, a symbol unsigned char, and a frequency.
 *
 * Authors: Alexis Atianzar, Arun Ramakrishnan
 *
 * Date: 11/1/16
 *
 */

#include <iostream>
#include "HCNode.h"

using namespace std;

/**
 * This function is used to compare nodes against each other
 */
bool HCNode::operator<(const HCNode& other){
  if(count!=other.count){
    return count > other.count; //compares the counts against each other
  }

  return symbol < other.symbol; //if a tie among counts, compares chars
}

