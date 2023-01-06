#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class node {
public:
   char key;
   int count;
   node* leftChild = nullptr;
   node* rightChild = nullptr;
};

class minHeap {
public:
   node* nodeArray[150];

   int size = -1;

   void insert(node* newNode);

   node* removeMin();
};

void minHeap::insert(node* newNode) {
   size++;

   nodeArray[size] = newNode;

   int tempInt = size;

   while (size > 1 && nodeArray[tempInt]->count < nodeArray[tempInt / 2]->count) {
      node *tempNode = nodeArray[tempInt / 2];
      nodeArray[tempInt / 2] = nodeArray[tempInt];
      nodeArray[tempInt] = tempNode;
      tempInt /= 2;
   }
}

node* minHeap::removeMin() {
   node* rtrn = nodeArray[0];

   nodeArray[0] = nodeArray[size];
   size--;

   int p=0;
   while ((2*p <= size && nodeArray[2*p]->count < nodeArray[p]->count) || (2*p+1 <= size && nodeArray[2*p+1]->count < nodeArray[p]->count)) {
      int c = 2*p;
      if (2*p+1 <= size && nodeArray[2*p+1]->count < nodeArray[2*p]->count) {
         c = 2*p+1;
      }
      node* tempNode = nodeArray[c];
      nodeArray[c] = nodeArray[p];
      nodeArray[p] = tempNode;
      p = c;
   }

   return rtrn;
}

node* newNode(char key, int count, node* left, node* right) {
   node* tempNodePtr = new node;

   tempNodePtr->leftChild = left;
   tempNodePtr->rightChild = right;
   tempNodePtr->count = count;
   tempNodePtr->key = key;

   return tempNodePtr;
}

void traverse(node* curNode, int* codeLenArr, vector<char> vectChar, int sum) {
   if (curNode == nullptr) {
      return;
   }
   if (curNode->leftChild == nullptr) {
      for (int i=0; i<vectChar.size(); i++) {
         if (vectChar[i] == curNode->key) {
            codeLenArr[i] = sum;
         }
      }
   }
   if (curNode->leftChild != nullptr) {
      sum++;
      traverse(curNode->leftChild, codeLenArr, vectChar, sum);
   }
   sum--;
   if (curNode->rightChild != nullptr) {
      sum++;
      traverse(curNode->rightChild, codeLenArr, vectChar, sum);
   }
}

int main(int argc, char *argv[]) {
   // read file and create vectors for the characters and the number each character appears
   ifstream file(argv[1]);
   file.unsetf(ios_base::skipws);
   char tempChar;
   vector<char> vectChar(0);
   vector<int> vectCount(0);
   long int fileCharSize = 0;
   vector<char> fullTxt(0);

   while (file >> tempChar) {
      //cout << fileCharSize << " ";
      fullTxt.push_back(tempChar);
      fileCharSize++;
      bool found = false;
      for (long unsigned int i=0; i<vectChar.size(); i++) {
         if (tempChar == vectChar[i]) {
            found = true;
            vectCount[i]++;
            break;
         }
      }
      if (found == false) {
         vectChar.push_back(tempChar);
         vectCount.push_back(1);
      }
   }
   
   //insert characters and counts into min heap
   minHeap heap;

   for (int i=0; i<vectChar.size(); i++) {
      node* tempNodePtr = newNode(vectChar[i], vectCount[i], nullptr, nullptr);
      heap.insert(tempNodePtr);
   }
    //create huffman code
   node *tempNodeLeft;
   node *tempNodeRight;
   node* parent;
   while (heap.size > 0) {      

      tempNodeLeft = heap.removeMin();   

      tempNodeRight = heap.removeMin();

      parent = newNode('P', tempNodeLeft->count + tempNodeRight->count, tempNodeLeft, tempNodeRight);
      heap.insert(parent);
   }

   //find code length
   int codeLenArr[vectChar.size()] = {0};
   int sum = 0;
   
   traverse(heap.nodeArray[0], codeLenArr, vectChar, sum);

   //output
   cout << "Uncompressed length: " << fileCharSize * 8 << " bits" << endl;

   long int compLen = 0;
   for (int i=0; i<fileCharSize; i++) {
      for (int j=0; j<vectChar.size(); j++) {
         if (vectChar[j] == fullTxt[i]) {
            compLen += codeLenArr[j];
         }
      }
   }
   cout << "Compressed length: " << compLen << " bits" << endl;

   cout << "CHAR|FREQ|CODE_LEN" << endl;

   for (int i=0; i<=127; i++) {
      for (int j=0; j<vectChar.size(); j++) {
         if (vectChar[j] == i) {
            cout << "'" << vectChar[j] << "'|" << vectCount[j] << "|" << codeLenArr[j] << endl;
         }
      }
   }

   return 0;
}