#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Node{
   public:
   char key;
   int freq;
   Node* left = nullptr;
   Node* right = nullptr;
};

class BinaryHeap {
   public:
   Node* fullHeap[130]; //number of ASCI characters
   int total = -1;
   void insert(Node* newNode);
   Node* removeMin();
   void swap(int q);
   void swapAgain(int c, int p);
   

};
Node* newNode(char key, int freq, Node *left, Node *right) { //necessary to create the new node
   Node* aNode = new Node;
   aNode->left = left;
   aNode->right = right;
   aNode->freq = freq;
   aNode->key = key;

   return aNode;
}

void BinaryHeap::swap(int q){
   Node *temporary = fullHeap[q / 2];
   fullHeap[q / 2] = fullHeap[q];
   fullHeap[q] = temporary;
} 

void BinaryHeap::insert(Node* aNode){
   /* insert(x) {
  if (n == MAX) throw exception;
  // maintain structure property
  n += 1;
  A[n] = x;
  // maintain order property with sift-up
  q = n;
  while (q > 1  &&  A[q] < A[q/2]) {
    swap(A[q], A[q/2]);
    q /= 2;
  }
} //pseudoCode from the slides
*/

total +=1;
fullHeap[total] = aNode;

int q = total;

while( total > 1 && fullHeap[q]->freq < fullHeap[q/2]->freq){
   swap(q);
   q /= 2;
   }
}
void BinaryHeap::swapAgain(int c, int p){
      Node *forNow = fullHeap[c];
      fullHeap[c] = fullHeap[p];
      fullHeap[p] = forNow;
}
Node* BinaryHeap::removeMin() {
   /*removeMin() {
  if (n == 0) throw exception;
  // root value = deepest, rightmost leaf value
  x = root.key;
  find rightmost leaf node q on deepest level;
  root.key = q.key;
  // remove q
  remove node q from tree;
  n -= 1;
  // sift-down root
  p = root;
  while ((p.left != null && p.left.key < p.key) ||
        (p.right != null && p.right.key < p.key)) {
    c = p.left;
    if (p.right != null && p.right.key < p.left.key)
      c = p.right;
    swap(p.key, c.key);
    p = c;
  }
  return x;
}                PseudoCode from slides for removeMin traversal (make it so it works for array)
 */
   Node* ans = fullHeap[0];
   fullHeap[0] = fullHeap[total];
   total--;

   int p = 0;

   //use 2*p and +1 for L and R nodes
   while ((2*p + 1 <= total && fullHeap[2*p + 1]->freq < fullHeap[p]->freq) || (2*p <= total && fullHeap[2*p]->freq < fullHeap[p]->freq)) {
      int c = 2 * p;
      if (2*p + 1 <= total && fullHeap[2*p + 1]->freq < fullHeap[2*p]->freq) {
         c = 2 * p + 1;
      }
      //Swap
      swapAgain(c,p);
      p = c;
   }

   return ans;
   
}

void huffManRec(Node *curNode, int *huffLen, vector<char> charStorage, int codeLen) {
   if (curNode == nullptr) {
      return;
   }
   if (curNode->left == nullptr) {
      for (int i = 0; i < charStorage.size(); i++) {
         if (charStorage.at(i) == curNode->key) {
            huffLen[i] = codeLen;
         }
      }
   }
   //codeLen needs to be changed depending on if you are going up or down
   if (!(curNode->left == nullptr)) {
      codeLen++;
      huffManRec(curNode->left, huffLen, charStorage, codeLen);
   }
   codeLen--;
   if (!(curNode->right == nullptr)) {
      codeLen++;
      huffManRec(curNode->right, huffLen, charStorage, codeLen);
   }
  
}

void output(vector<char> charStorage, vector<int> counter, int* huffLen){
      for (int i = 0; i <= 127; i++) { //This is for the output since the ascii count is 127
      for (int j = 0; j < charStorage.size(); j++) {
         if (charStorage.at(j) == i) {
            cout << "'" << charStorage.at(j) << "'|" << counter.at(j) << "|" << huffLen[j] << endl;
         }
      }
   } 


}

int main(int argc, char *argv[]) {
   // read file and create vectors for the characters and the number each character appears(frequency table)
   
   ifstream text(argv[1]);

   char c;
   vector<char> original(0); //for the whole text file

   while (text.get(c)) {
      original.push_back(c); //This stores the whole text
   }

   vector<char> charStorage(0); //for the individual chars
   vector<int> counter(0); //frequencies
   int uncompLen = original.size() * 8;

   for(int i = 0; i < original.size(); i++){
      char curChar = original.at(i);
      int done = 0;
      for (int i = 0; i < charStorage.size(); i++) { // This is storing the different characters and their frequencies in the original text
         if (curChar == charStorage[i]) {
            done = 1;
            counter[i]++;
            break;
         }
      }
      if (done == 0) {
         charStorage.push_back(curChar);
         counter.push_back(1);
      }
   }

   /*for(int i = 0; i < charStorage.size(); i++){
      cout << charStorage.at(i) << endl;
      cout << counter.at(i) << endl;
   } */ 

   BinaryHeap minHeap;

   for (int i = 0; i < charStorage.size(); i++) {
      Node* insertion = newNode(charStorage[i], counter[i], nullptr, nullptr);
      minHeap.insert(insertion);
   }
    //create huffman code
   Node *tLeft;
   Node *tRight;
   Node* tparent;

   while (minHeap.total > 0) {      
      tLeft = minHeap.removeMin();   
      tRight = minHeap.removeMin();
      tparent = newNode('B', tLeft->freq + tRight->freq, tLeft, tRight);
      minHeap.insert(tparent);
   }
   

   cout << "Uncompressed length: " << uncompLen << " bits" << endl;


   int huffLen[charStorage.size()] = {0};
   int codeLen = 0;
   
   huffManRec(minHeap.fullHeap[0], huffLen, charStorage, codeLen);

   int newLen = 0;
   for (int i = 0; i < original.size(); i++) {
      for (int k = 0; k < charStorage.size(); k++) {
         if (charStorage.at(k) == original.at(i)){
            newLen += huffLen[k]; 
      }
    }
   }
   cout << "Compressed length: " << newLen << " bits" << endl;
   cout << "CHAR|FREQ|CODE_LEN" << endl;
   output(charStorage, counter, huffLen);

   return 0;
}
