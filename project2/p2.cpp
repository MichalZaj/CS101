#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <cctype>
#include <limits.h>

using namespace std;
void Merge(int numbers[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}
void MergeString(string words[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   string* mergedWords = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedWords = new string[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (words[leftPos] < words[rightPos]) {
         mergedWords[mergePos] = words[leftPos];
         ++leftPos;
      }
      else {
         mergedWords[mergePos] = words[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedWords[mergePos] = words[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedWords[mergePos] = words[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      words[i + mergePos] = mergedWords[mergePos];
   }
   delete[] mergedWords;
}

void MergeSortString(string words[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortString(words, i, j);
      MergeSortString(words, j + 1, k);
      
      // Merge left and right partition in sorted order
      MergeString(words, i, j, k);
   }
}

int main(int argc, char *argv[]){

ifstream inFile1;
ifstream inFile2;
char input;

input = *argv[1];

inFile1.open(argv[2]);
inFile2.open(argv[3]);

//if the two files cant open then return 1
if (!inFile1.is_open()) {
      return 1;
   }
if (!inFile2.is_open()) {
      return 1;
   }

//sort based on the first argument
if(input == 'i'){
int file1Len = 0;
int file2Len = 0;
int temp = 0;

while(inFile1 >> temp){
    file1Len++;
}
//len of second file
while(inFile2 >> temp){
    file2Len++;
}
//close and open again to fill new arrays
inFile1.close();
inFile1.open(argv[2]);
inFile2.close();
inFile2.open(argv[3]);

int arrint1[file1Len];
int arrint2[file2Len];
//loops to fill
for(int i = 0; i < file1Len; i++){
    inFile1 >> arrint1[i];
}
for(int i = 0; i < file2Len; i++){
    inFile2 >> arrint2[i];
}
inFile1.close();
inFile2.close();

//variables for function call
//int startInt1 = 0;
//int endInt1 = file1Len - 1;
//int startInt2 = 0;
//int endInt2 = file2Len - 1;
//sort both
//MergeSort(arrint1, startInt1, endInt1);
//MergeSort(arrint2, startInt2, endInt2);

//remove duplicates from arrays.

int bothSize = 0;
int count = 0;
//loop to get the array size
for(int i = 0; i < file1Len; i++){
    for(int j = 0; j < file2Len; j++){
        if(arrint1[i] == arrint2[j]){
            bothSize++;
        }
    }
}

int arrayBoth[bothSize];
//loop to insert same elements into arrayboth
for(int i = 0; i < file1Len; i++){
    for(int j = 0; j < file2Len; j++){
        if(arrint1[i] == arrint2[j]){
            arrayBoth[count] = arrint1[i];
            count++;
        }
    }
}
int startboth = 0;
int endboth = bothSize - 1;
MergeSort(arrayBoth, startboth, endboth);
for(int i = 0; i < bothSize; i++){
    if((i == bothSize-1) || (arrayBoth[i]!= arrayBoth[i+1])){
        cout << arrayBoth[i] << endl;
    }
    
}

}

if(input == 's'){
int file1Len = 0;
int file2Len = 0;
string temporary;

while(inFile1 >> temporary){
    file1Len++;
}
//len of second file
while(inFile2 >> temporary){
    file2Len++;
}
//close and open again to fill new arrays
inFile1.close();
inFile1.open(argv[2]);
inFile2.close();
inFile2.open(argv[3]);

string arrstr1[file1Len];
string arrstr2[file2Len];
//loops to fill
for(int i = 0; i < file1Len; i++){
    inFile1 >> arrstr1[i];
}
for(int i = 0; i < file2Len; i++){
    inFile2 >> arrstr2[i];
}
inFile1.close();
inFile2.close();

int bothSize = 0;
int count = 0;
//loop to get the array size
for(int i = 0; i < file1Len; i++){
    for(int j = 0; j < file2Len; j++){
        if(arrstr1[i] == arrstr2[j]){
            bothSize++;
        }
    }
}

string arrayBoth[bothSize];
//loop to insert same elements into arrayboth
for(int i = 0; i < file1Len; i++){
    for(int j = 0; j < file2Len; j++){
        if(arrstr1[i] == arrstr2[j]){
            arrayBoth[count] = arrstr1[i];
            count++;
        }
    }
}
int startboth = 0;
int endboth = bothSize - 1;
MergeSortString(arrayBoth, startboth, endboth);
for(int i = 0; i < bothSize; i++){
    if((i == bothSize-1) || (arrayBoth[i]!= arrayBoth[i+1])){
        cout << arrayBoth[i] << endl;
    }
    
}




}


}