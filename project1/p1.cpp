#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[])
{
ifstream inFS;
string text;   //initialize the string array to read in words

//if theres no file return 1
if(argc != 2){
    cout << endl << "No file" << endl;
    return 1;
}

//open the file

inFS.open(argv[1]);

//if the file cant be opened return 1
if (!inFS.is_open()) {
      cout << "Could not open file " << argv[1] << "." << endl;
      return 1;
   }

   //if it opens use getline to read all the lines
   string temp;
   while(!inFS.eof()){
       getline(inFS, temp);
       text += temp;
   }
   inFS.close();
   
   
   //search through the words array and seperate the words in each index
   for(int i = 0; i < text.length(); i++){
       if(!isalpha(text[i])){
           text[i] = ' ';
       }
       if(isupper(text[i])){
           text[i] = tolower(text[i]);
       }
   }
   

   stringstream words1(text);

   string temporary;
   int fullcount = 0;

   while(words1 >> temporary){
       fullcount++;
   }
   

   stringstream words2(text);
   string arrayofwords[fullcount];

   int j = 0;
   while(words2 >> temporary){
       arrayofwords[j] = temporary;
       j++;
   }
   string distinctwords[fullcount];
   int tempint = 0;

   for(int i = 0; i < fullcount; i++){

       for(int k = 0; k <= fullcount; k++){
           if(arrayofwords[i] == distinctwords[k]){
               break;
           }
           if(k == fullcount){
               distinctwords[tempint] = arrayofwords[i];
               tempint++;
           }
           
       }
   }

   string finalwords[tempint];
   //created the same array as distinct
   for(int i = 0; i < tempint; i++){
       finalwords[i] = distinctwords[i];
   }
   //printing message
   cout << "The number of words found was " << fullcount << endl;
   cout << "The number of distinct words was " << tempint << endl << endl;

   string query;
   int counterarray[tempint] = {0};
   for(int i = 0; i < tempint; i++){
       for(int j = 0; j < fullcount; j++){
           if(distinctwords[i] == arrayofwords[j]){
               counterarray[i]++;
           }
       }
       
   }
   while(1){
       cout << "Enter a word: ";
       cin >> query;
       if(query == "STOP"){
           break;
       }
       bool zero = false;
       for(int i = 0; i <= tempint; i++){
           if(i == tempint && zero == false){
               cout << "The word " << query << " appears 0 times" << endl;
           }
           for(int j = 0; j <= query.length(); j++){
               if(query.length() != distinctwords[i].length()) break;
               if(j == query.length()){
                   cout << "The word " << distinctwords[i] << " appears " << counterarray[i] << " times"<< endl;
                   zero = true;
               }
               if((query[j] != distinctwords[i][j]) && (query[j] != '?')){
                   break;
               }
           }
           
       }
       cout << endl;
   }


}
