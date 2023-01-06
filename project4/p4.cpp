#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
};

class HashTable {
    int bucket;    // Number of buckets in Hashtable
public:
    vector<Person> *table;

    HashTable(int V);

    void insertPerson(Person person, string key);
 
    int hashFunc(uint64_t key) {
        return key % bucket;
    }
 
};

HashTable::HashTable(int tableSize)
{
    this->bucket = tableSize;
    table = new vector<Person>[bucket]; //create the hashtable and make it the tableSize
}
 
void HashTable::insertPerson(Person person, string key)
{
    int i = 0;
    if (key == "Id") {
        i = hashFunc(djb2(person.id));
    }
    else if (key == "FirstName") {
        i = hashFunc(djb2(person.first));
    }
    else if (key == "LastName") {
        i = hashFunc(djb2(person.last));
    }
    else if (key == "Email") {
        i = hashFunc(djb2(person.email));
    }
    else if (key == "Phone") {
        i = hashFunc(djb2(person.phone));
    }
    else if (key == "City") {
        i = hashFunc(djb2(person.city));
    }
    else if (key == "State") {
        i = hashFunc(djb2(person.state));
    }
    else if (key == "PostalCode") { 
        i = hashFunc(djb2(person.postalCode));
    }
    table[i].push_back(person);
}


void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
    HashTable h(tableSize);
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);
        Person p; //person object
        //each getline takes in the token and inserts it into the person obj
        getline(iss, token, '\t');
        p.id = token;

        getline(iss, token, '\t');
        p.first = token;

        getline(iss, token, '\t');
        p.last = token;

        getline(iss, token, '\t');
        p.email = token;

        getline(iss, token, '\t');
        p.phone = token;

        getline(iss, token, '\t');
        p.city = token;

        getline(iss, token, '\t');
        p.state = token;

        getline(iss, token, '\t');
        p.postalCode = token;
        //after getting the information of each person insert it into the hashtable
        h.insertPerson(p, key);

    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            int counter = 0;
            for(int i = 0; i < tableSize; i++){ //loop for the hashtable
                
                if(h.table[i].size() != 0){ // as long as it contains something
                int visited[h.table[i].size()] = { 0 };
                cout << i << ": ";
                if (key == "State") {
                    
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].state == h.table[i][j].state){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].state << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;
                
                }
                if (key == "Id") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].id == h.table[i][j].id){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].id << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "FirstName") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].first == h.table[i][j].first){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].first << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "LastName") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].last == h.table[i][j].last){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].last << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "Email") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].email == h.table[i][j].email){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].email << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "Phone") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].phone == h.table[i][j].phone){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].phone << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "City") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].city == h.table[i][j].city){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].city << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }
                if (key == "PostalCode") {
                    for(int k = 0; k < h.table[i].size(); k++){
                        
                        if(visited[k] == 1)
                            continue;
                        counter = 0;
                        for(int j = 0; j < h.table[i].size(); j++){
                            if(h.table[i][k].postalCode == h.table[i][j].postalCode){
                                visited[j] = 1;
                                counter++;
                            }
                        }
                    
                    cout << h.table[i][k].postalCode << "(" << counter << "), ";
                    
                    }
                    
                    cout << endl;

                }

            }
          }
            // print code here
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            int index = (djb2(val) % tableSize);
            int done = 0;
                if (key == "State") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].state){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }


                }
                if (key == "Id") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].id){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "FirstName") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].first){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "LastName") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].last){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "Email") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].email){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "Phone") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].phone){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "City") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].city){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if (key == "PostalCode") {
                    if(h.table[index].size() != 0){
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                        for(int j = 0; j < h.table[index].size(); j++){
                            if(val == h.table[index][j].postalCode){
                                cout << h.table[index][j].id << "," << h.table[index][j].first << "," << h.table[index][j].last << "," << h.table[index][j].email << "," << h.table[index][j].phone << "," << h.table[index][j].city << "," << h.table[index][j].state << "," << h.table[index][j].postalCode << endl;
                                done = 1;
                            }
                        }
                    }

                }
                if(done == 0){
                            cout << "No results" << endl;
                    }
           
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
