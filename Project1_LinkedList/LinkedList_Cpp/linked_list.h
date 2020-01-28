#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <functional>

using namespace std;

// Define a structure to use as the list item
struct ListItem {
     int      key;
     float    theData;
     ListItem *next;
};

class Linked_List {
     private:
          ListItem *head;               // Pointer to the start of the list

     public:
          Linked_List();
          ~Linked_List();
          void ClearList();                     // Remove all items from the list
          bool Insert(int key, float f);        // Add an item to the end of the list
          bool Delete(int keyToDelete);         // Delete an item from the list
          bool Search(int key, float *retVal); // Search for an item in the list
          int ListLength();                    // Return number of items in list
          bool isEmpty();                      // Return true if list is empty
          bool isFull();                       // Return true if list is full
          void PrintList();                    // Print all items in the list
};

Linked_List::Linked_List() {
    head = nullptr;
}

Linked_List::~Linked_List() {
    this->ClearList();
}

void Linked_List::ClearList() {
    if (this->isEmpty()){
        return;
    }

    ListItem *next = head->next;
    delete [] head;

    while (next->next) {
        head = next;
        next = head->next;
        delete [] head;
    }

    head = nullptr;
}

bool Linked_List::Insert(int key, float f) {
    // Set head to new item if list is empty
    if (this->isEmpty()) {
        head = new ListItem;
        *head = {key, f, nullptr};
        return true;
    }

    std::function<bool(ListItem*, int, float)> InsertRecursion = [&InsertRecursion] (ListItem *item, int key, float f) -> bool {
        if(!item->next){
            item->next = new ListItem;
            *item->next = {key, f, nullptr};
            return true;
        } else if (item->key == key) {
            return false;   // Key already exists
        } else {
            return InsertRecursion(item->next, key, f);
        }
    };

    return InsertRecursion(head, key, f);
}

bool Linked_List::Delete(int keyToDelete) {
    // Special cases (List is empty or deleting head)
    if (this->isEmpty()) {
        return false;
    } else if (head->key == keyToDelete) {
        head = head->next;
        return true;
    }

    std::function<bool(ListItem*, int)> InsertRecursion = [&InsertRecursion] (ListItem *item, int keyToDelete) -> bool {
        if(!item->next){
            return false;
        } else if (item->next->key == keyToDelete) {
            ListItem *newNext;

            if (item->next->next) {
                newNext = item->next->next;
            } else {
                newNext = nullptr;
            }

            item->next = newNext;

            return true;
        } else {
            return InsertRecursion(item->next, keyToDelete);
        }
    };

    return InsertRecursion(head, keyToDelete);
}

bool Linked_List::Search(int key, float *retVal) {
    std::function<bool (ListItem*, int)> SearchRecursion = [&SearchRecursion, retVal] (ListItem *item, int key) -> bool {
        if(!item){
            return false;
        } else if (item->key == key) {
            *retVal = item->theData;
            return true;
        } else {
            return SearchRecursion(item->next, key);
        }
    };

    return SearchRecursion(head, key);
}

int Linked_List::ListLength() {
    if (this->isEmpty())
        return 0;

    ListItem *tmpItem = head;
    int count = 1;

    while (tmpItem->next){
        count++;
        tmpItem = tmpItem->next;
    }

    return count;
}

bool Linked_List::isEmpty() {
    return head == nullptr;
}

bool Linked_List::isFull() {
    try {
        this->Insert(-1, -1);
        this->Delete(-1);
        return true;
    } catch(...) {
        return false;
    }

}

void Linked_List::PrintList() {
    if (this->isEmpty()) {
        printf("{}\n");
        return;
    }

    std::function<string (ListItem*)> PrintListRecursion = [&PrintListRecursion] (ListItem *item) -> string {
        if(!item){
            return "";
        } else {
            // TODO: find a better way to string format, maybe put listString in lambda globals and append to that
            string listString = "[";
            listString.append(std::to_string(item->key));
            listString.append(":");

            // Use stringstream to print float data without trailing 0s
            stringstream ss;
            ss << item->theData;
            listString.append(ss.str());
            listString.append("]");
            return listString + PrintListRecursion(item->next);
        }
    };

    printf("{%s}\n", PrintListRecursion(head).c_str());

}

#endif