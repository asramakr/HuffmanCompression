#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

/**
 * A 'function class' for use as the Compare class in a
 * priority_queue<HCNode*>. For this to work, operator< must be defined
 * to do the right thing on HCNodes.
 */

HCTree::~HCTree(){
  deleteAll(root);
  delete leaves;
}

void HCTree::build(const vector<int>& freqs){
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
  for (unsigned int i = 0; i < freqs.size(); i++) {
    //HCNode * c0, c1, p;
    HCNode* p = new HCNode(freqs[i], i, 0, 0, 0);
    pq.push(p);
  }

  // loop while more than 1 tree in forest
  while (pq.size() > 1) {

    // get and remove the 2 nodes w lowest counts
    auto bot1 = pq.top();
    pq.pop();
    auto bot2 = pq.top();
    pq.pop();

    if(bot1->symb){
      leaves.insert(bot1);
    }
    if(bot2->symb){
      leaves.insert(bot2);
    }

    unsigned int summedCount = bot1->count + bot2->count;

    byte emptySym = 0;

    HCNode* sumNode = new HCNode(summedCount, emptySym, bot1, bot2, 0);
    bot1->parent = sumNode;
    bot2->parent = sumNode;
    pq.push(sumNode);
  }
  root = pq.top();
  pq.pop();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const{


}

void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode * currentNode; // node to traverse through tree
  HCNode * parentNode; // parent of currentNode
  unsigned char bit; // decoded bit of symbol
  std::stack<char> bits; // temp stack to hold bits encoded bits

  // look in tree for symbol's node
  for(int i=0; i<leaves.size(); i++){
    if(leaves.at(i)->symb == symbol){
      currentNode = leaves.at(i);
    }
  }

  // loop through from symbol node to root and find bit reverse bit
  // sequence
  while (currentNode->parent) {
    parentNode = currentNode->p;

    // if right child, bit is 0
    if (currentNode == parentNode->c0) {
      bits.push('0');
    }
    // if left child, bit is 1
    else {
      bits.push('1');
    }
    currentNode = parentNode;
  }

  // pop off all bits in stack to get sequence in correct order
  for(int i=0; i<bits.size(); i++){
    bit = bits.top();
    out << bit; // write into file
    bits.pop();
  }

}

int HCTree::decode(BitInputStream& in) const{
}

int HCTree::decode(ifstream& in) const{
  unsigned char readBit;
  HCNode * currentNode = root;
  while(1){
    readBit = in.get();
    if(readBit == '0'){
      currentNode = currentNode->c0;
    }

    else{
      currentNode = currentNode->c1
    }

    if (!currentNode->c0 && !currentNode->c1) {
      break;
    }

    if(in.eof()){
      break;
    }
  }
  return currentNode->symbol;
}

void HCTree::deleteAll(HCNode * currentNode){
  if(currentNode->c0){
    deleteAll(currentNode->c0);
  }
  if(currentNode->c1){
    deleteAll(currentNode->c0);
  }
  delete currentNode;
}
