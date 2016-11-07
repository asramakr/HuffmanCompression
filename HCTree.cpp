/**
 * Description: This class is the Huffman tree class and is responsible
 * for character encoding and decoding. It creates a Huffman tree to do this
 * and uses that to encode the input file.
 * Author: Arun Ramakrishnan, Alexis Atianzar
 * Date: 11/1/16
 */

#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include "HCTree.h"

using namespace std;

/**
 * This method is used to delete the HCTree from memory, removing all the
 * nodes and the leaves vector.
 */
HCTree::~HCTree(){
  
  // if root exists (if there is any content in the file)
  // then delete everything
  if (root) {
    deleteAll(root);
  }
}

/**
 * This method builds the HUffman tree used to encode.
 */
void HCTree::build(const vector<int>& freqs){

  // make a priority queue to build the tree using Huffman algorithm
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;

  // put symbols that appear in the file into the pq
  for (unsigned int i = 0; i < freqs.size(); i++) {
    if(freqs.at(i) > 0){
      HCNode* p = new HCNode(freqs[i], i, 0, 0, 0);
      pq.push(p);
      leaves.at(i) = p;
      //cout << "p->symbol: " << p->symbol << endl;
    }
  }

  // loop while more than 1 tree in forest
  while (pq.size() > 1) {

    // get and remove the 2 nodes w lowest counts
    auto bot1 = pq.top();
    //cout << "lowest symbol: " << bot1->symbol << endl;
    pq.pop();
    auto bot2 = pq.top();
    //cout << "second lowest symbol: " << bot2->symbol << endl;
    pq.pop();

    unsigned int summedCount = bot1->count + bot2->count;


    // create a parent node from the smallest nodes
    HCNode* sumNode = new HCNode(summedCount, bot2->symbol, bot1, bot2, 0);
    bot1->p = sumNode;
    bot2->p = sumNode;
    pq.push(sumNode);
  }

  // set root if file is not empty
  if (!pq.empty()) {
    root = pq.top();
    pq.pop();
  }
}

/**
 * This method encodes individual bits and writes them to the output file
 */

void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode * currentNode; // node to traverse through tree
  HCNode * parentNode; // parent of currentNode
  std::stack<int> bits; // temp stack to hold encoded bits
  int bit; // bit in encoded sequence for symbol
  unsigned int bits_size = 0; // number of bits in sequences for each symb

  // look in tree for symbol's node
  for (int i = 0; i < leaves.size(); i++) {
    if (leaves.at(i) && (leaves.at(i)->symbol == symbol)) {
      currentNode = leaves.at(i);
    }
  }

  // loop through from symbol node to root and find bit reverse bit
  // sequence
  if(currentNode->p){
    while (currentNode->p) {
      parentNode = currentNode->p;
      // if right child, bit is 0
      if (currentNode == parentNode->c0) {
        bits.push(0);
        bits_size++;
      }
      // if left child, bit is 1
      else {
        bits.push(1);
        bits_size++;
      }
      currentNode = parentNode;
    }
  }

  // if only one node in tree, bit sequence is 1
  else if(root == currentNode){
    bits.push(1);
    bits_size++;
  }
  // pop off all bits in stack to get sequence in correct order
  for(int i=0; i<bits_size; i++){
    //cout << bits_size << endl;
    bit = bits.top();
    //cout << "Bits Printed: "<< bit << endl;
    out.writeBit(bit); // write to file's buffer as bit
    bits.pop();
  }
}

/**
 * This method encodes individual bytes and writes them to the output file
 */
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode * currentNode; // node to traverse through tree
  HCNode * parentNode; // parent of currentNode
  unsigned char bit; // decoded bit of symbol
  std::stack<char> bits; // temp stack to hold bits encoded bits
  unsigned int bits_size = 0;

  // look in tree for symbol's node
  for(int i=0; i<leaves.size(); i++){
    if( leaves.at(i) && leaves.at(i)->symbol == symbol){
      currentNode = leaves.at(i);
    }
  }

  // loop through from symbol node to root and find bit reverse bit
  // sequence
  while (currentNode->p) {
    parentNode = currentNode->p;
//    cout << "currentNode: " << currentNode->symbol << endl;
//    cout << "parentNode: " << parentNode->symbol << endl;

    // if right child, bit is 0
    if (currentNode == parentNode->c0) {
//      cout << "pushing 0" << endl;
      bits.push('0');
      bits_size++;
    }
    // if left child, bit is 1
    else {
//      cout << "pushing 1" << endl;
      bits.push('1');
      bits_size++;
    }
    currentNode = parentNode;
  }


  // pop off all bits in stack to get sequence in correct order
  for(int i=0; i<bits_size; i++){
    bit = bits.top();
//    cout << bit << endl;
    out << bit; // write into file
    bits.pop();
  }

}

/**
 * This method decodes bits of data from the outfile of encode
 */

int HCTree::decode(BitInputStream& in) const{
  unsigned char readBit;
  int readNum; // number being read in from the input file
  HCNode * currentNode = root; // set root as working node

  // keep reading the bits and following tree 
  // while currentNode has children
  while(currentNode->c0 && currentNode->c1){
    readNum = in.readBit(); // read in a byte from file

    // break loop if end of file reached
    if(readNum == EOF){
      break;
    }
    //readBit = (unsigned char)readNum;
    //cout << "readBit: " << readNum << endl;

    // if 0 read in, travel down right child
    if(readNum == 0){
      currentNode = currentNode->c0;
    }

    // if 1 read in, travel down left child
    else{
      currentNode = currentNode->c1;
    }

//    if (!currentNode->c0 && !currentNode->c1) {
//      break;
//    }

    // break loop if end of file is reached
    if(in.eof()){
      break;
    }
  }

  return currentNode->symbol;
  
}

/**
 * This method decodes bytes of data from the outfile of encode
 */
int HCTree::decode(ifstream& in) const{
  unsigned char readBit;
  int readNum;
  HCNode * currentNode = root;
  while(currentNode->c0 && currentNode->c1){
    readNum = in.get();
    if(readNum == EOF){
      break;
    }
    readBit = (unsigned char)readNum;
 //   cout << "readBit: " << readBit << endl;
    if(readBit == '0'){
      currentNode = currentNode->c0;
    }

    else{
      currentNode = currentNode->c1;
    }

//    if (!currentNode->c0 && !currentNode->c1) {
//      break;
//    }

    if(in.eof()){
      break;
    }
  }
  return currentNode->symbol;
}

/**
 * This method is used by the destructor to delete all the nodes
 * Uses recursion in order to do so.
 */
void HCTree::deleteAll(HCNode * currentNode){
  //deletes left children
  if(currentNode->c0){
    deleteAll(currentNode->c0);
  }
  //deletes right children
  if(currentNode->c1){
    deleteAll(currentNode->c1); 
  }
  delete currentNode;
}
