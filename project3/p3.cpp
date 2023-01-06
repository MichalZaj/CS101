#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {

    Contact *curNode = headContactList;

    while (curNode != nullptr) {
        if (curNode->first == first && curNode->last == last) {
            Info *curInfo = curNode->headInfoList;
            os << "Contact Name: " << curNode->first << " " << curNode->last << endl;
            while (curInfo != nullptr) {
                os << "    " << curInfo->name << " | " << curInfo->value << endl;
                curInfo = curInfo->next;
            }
            return true;
        }
        curNode = curNode->next;
    }
     return false; 
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {

    if (headContactList != nullptr) {
        Contact *curNode = headContactList; //initialize the current pointer
        while (curNode != nullptr) {
            os << "Contact Name: " << curNode->first << " " << curNode->last << endl;
            Info *curInfo = curNode->headInfoList;
            while (curInfo != nullptr) {
                os << "    " << curInfo->name << " | " << curInfo->value << endl;
                curInfo = curInfo->next;
            }
            curNode = curNode->next;
        }
    }
    

}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    
    Contact *addition = new Contact(first, last, nullptr);

    if(headContactList == nullptr){
        headContactList = addition;
        count++;
        return true;
    }

    //loop through to check if it does not exist in the list
    Contact *curNode = headContactList; //create a cur node
    while (curNode != nullptr) {
        if (curNode->first == first && curNode->last == last) {
            return false; //if the contact exists return false
        }
        if(curNode->next == nullptr){
            break;
        }
        curNode = curNode->next;
    }
    curNode->next = addition;
    count++;
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    

    Contact *curNode = headContactList;
    Info *addition = new Info(infoName, infoVal, nullptr);

    while (curNode != nullptr) {   //while loop to check if a contact matches
    if (curNode->first == first && curNode->last == last){ //if the contact matches
        Info *curInfo = curNode->headInfoList; //pointer to the first head
        if(curInfo == nullptr){ //if the first info is null make it the newinfo
            curNode->headInfoList = addition;
            return true;
        }

        while(curInfo != nullptr){
            if(curInfo->name == infoName){ //if the name is the same just change value
                curInfo->value = infoVal;
                return true;
            }
            if(curInfo->next == nullptr){
                curInfo->next = addition;
                return true;
            }
            curInfo = curInfo->next;
        }
        
    }
        curNode = curNode->next;
    }
    return false;
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact *curNode = headContactList;
    Contact *addition = new Contact(first, last, nullptr);

    if(curNode == nullptr){ //if its null just make the first node the addition
        headContactList = addition;
        count++;
        return true;
    }
    if(curNode->last > last){
            addition->next = curNode;
            headContactList = addition;
            count++;
            return true;
    }
    else if(curNode->last == last){
        if(curNode->first > first){
            addition->next = curNode;
            headContactList = addition;
            count++;
            return true;
        }
        else if(curNode->first == first){
            return false;
        }
    }
    while(curNode != nullptr){
        if(curNode->next == nullptr){
            break;
        }
        if(curNode->next->last > last){
            Contact *temp = curNode->next;
            curNode->next = addition;
            addition->next = temp;
            count++;
            return true;
        }
        else if(curNode->next->last == last){
            if(curNode->next->first > first){
                Contact *temp = curNode->next;
                curNode->next = addition;
                addition->next = temp;
                count++;
                return true;
            }
            else if(curNode->next->first == first){
                return false;
            }
        }
        curNode = curNode->next;
    }
    curNode->next = addition;
    count++;
    return true;

}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact *curNode = headContactList;
    Info *addition = new Info(infoName, infoVal, nullptr);

    while (curNode != nullptr) {   //while loop to check if a contact matches
    if (curNode->first == first && curNode->last == last){ //if the contact matches
        Info *curInfo = curNode->headInfoList; //pointer to the first head

        if(curInfo == nullptr){ //if the first info is null make it the newinfo
            curNode->headInfoList = addition;
            return true;
        }
        if(curInfo->name > infoName){
            addition->next = curInfo;
            curNode->headInfoList = addition;
            return true;
        }
        else if(curInfo->name == infoName){
            curInfo->value = infoVal;
            return true;
        }

        while(curInfo != nullptr){
            if(curInfo->next == nullptr){ //end of linked list
                curInfo->next = addition;
                return true;
            }
            if(curInfo->next->name > infoName){
                Info *temp = curInfo->next;
                curInfo->next = addition;
                addition->next = temp;
                return true;
            }
            else if(curInfo->next->name == infoName){
                curInfo->next->value = infoVal;
                return true;
            }
            curInfo = curInfo->next;
        }
        
    }
        curNode = curNode->next;
    }
    return false;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    Contact *curNode = headContactList;
    if(curNode == nullptr){
        return false;
    }
    if(curNode->first == first && curNode->last == last){
        headContactList = curNode->next;
        delete curNode;
        count--;
        return true;
    }
    while(curNode->next != nullptr){
        if(curNode->next->first == first && curNode->next->last == last){
            Contact *temp = curNode->next;
            curNode->next = curNode->next->next;
            delete temp;
            count--;
            return true;
        }
        curNode = curNode->next;
    }

    return false;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact *curNode = headContactList;

    while(curNode != nullptr){
        if(curNode->first == first && curNode->last == last){
            Info *curInfo = curNode->headInfoList;
            if(curInfo == nullptr){
                return false;
            }

            if(curInfo->name == infoName){ //if first node is the name
                curNode->headInfoList = curInfo->next;
                delete curInfo;
                return true;
            }
            while(curInfo->next != nullptr){

                if(curInfo->next->name == infoName){
                    Info *temp = curInfo->next;
                    curInfo->next = curInfo->next->next;
                    delete temp;
                    return true;
                }
                curInfo = curInfo->next;
            }
            
        }
        curNode = curNode->next;
    }

    return false;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    
    while(headContactList != nullptr){
        Contact *curNode = headContactList;
        while(curNode->headInfoList != nullptr){
            Info *curInfo = curNode->headInfoList;
            curNode->headInfoList = curNode->headInfoList->next;
            delete curInfo;
        }
        headContactList = headContactList->next;
        delete curNode;
    }
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {
    headContactList = nullptr;

    count = 0;
    for(Contact *cur = src.headContactList; cur != nullptr; cur = cur->next){
        addContact(cur->first, cur->last);
        for(Info *curInfo = cur->headInfoList; curInfo != nullptr; curInfo = curInfo->next){
            addInfo(cur->first, cur->last, curInfo->name, curInfo->value);
        }
    }
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {
        while(headContactList != nullptr){ //remove all the contacts code
        Contact *curNode = headContactList;
        while(curNode->headInfoList != nullptr){
            Info *curInfo = curNode->headInfoList;
            curInfo = curInfo->next;
            delete curInfo;
        }
        headContactList = headContactList->next;
        delete curNode;
    }
    headContactList = nullptr;
    count = 0;
    for(Contact *cur = src.headContactList; cur != nullptr; cur = cur->next){ //deep copy code
        addContact(cur->first, cur->last);
        for(Info *curInfo = cur->headInfoList; curInfo != nullptr; curInfo = curInfo->next){
            addInfo(cur->first, cur->last, curInfo->name, curInfo->value);
        }
    }

    }
    return *this;
}
