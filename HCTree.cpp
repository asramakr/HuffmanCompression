#include <queue>
#include <vector>
#include <fstream>
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

}

int HCTree::decode(BitInputStream& in) const{

}

int HCTree::decode(ifstream& in) const{

}
