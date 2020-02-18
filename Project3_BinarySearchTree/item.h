//
// item.h    
//

#include <iostream>
#include <iomanip>
#include <utility>

using namespace std;

#ifndef ITEM_H
#define ITEM_H

// Models a single item from the catalog
class Item {
private:
    int itemID;                // Item ID number (search key)
    string itemName;          // Item name
    float itemPrice;         // Item price

public:
    Item();
    Item(int id, string name, float price);
    Item(const Item &otherItem);
    friend bool operator==(const Item &leftop, const Item &rightop);
    friend bool operator<(const Item &leftop, const Item &rightop);
    friend bool operator>(const Item &leftop, const Item &rightop);
    void operator=(const Item &op);

    // Overloaded >> operator
    // This allows all data associated with a Item object to be input simultaneously from an input stream
    friend istream &operator>>(istream &leftop, Item &rightop) {
        leftop >> rightop.itemID >> rightop.itemName >> rightop.itemPrice;

        return leftop;
    }

    // Overloaded << operator
    // This allows all data associated with a Item object to be output simultaneously to an output stream
    friend ostream &operator<<(ostream &leftop, const Item &rightop) {
        leftop << "[" << rightop.itemID << ", " << rightop.itemName << ", $"
               << fixed << showpoint << setprecision(2) << rightop.itemPrice << "]";

        return leftop;
    }

    // Print()
    // Outputs Item information in desired format.
    void Print() const {
        cout << "[" << itemID << ", " << itemName << ",$"
             << fixed << showpoint << setprecision(2) << itemPrice << "]";

    }  // End Print()
};

// Default constructor initializes itemID to -1, itemPrice to -1.00, and itemName to empty string
Item::Item() {
    this->itemID = -1;
    this->itemName = "";
    this->itemPrice = -1.00;
}

// Constructor initializes itemID, itemName, itemPrice to id, name, and price respectively
Item::Item(int id, string name, float price) {
    this->itemID = id;
    this->itemName = std::move(name);
    this->itemPrice = price;
}

// Copy constructor -- copies attributes of item into attribute variables of current object
Item::Item(const Item &otherItem) {
    this->itemID = otherItem.itemID;
    this->itemName = otherItem.itemName;
    this->itemPrice = otherItem.itemPrice;
}

// Overloaded SAME AS operator
// Returns true if leftop.itemID == rightop.itemID.  Returns false otherwise
bool operator==(const Item &leftop, const Item &rightop) {
    return leftop.itemID == rightop.itemID;
}

// Overloaded LESS THAN operator
// Returns true if leftop.itemID < rightop.itemID.  Returns false otherwise
bool operator<(const Item &leftop, const Item &rightop) {
    return leftop.itemID < rightop.itemID;
}

// Overloaded GREATER THAN operator
// Returns true if leftop.itemID > rightop.itemID.  Returns false otherwise
bool operator>(const Item &leftop, const Item &rightop) {
    return leftop.itemID > rightop.itemID;
}

// Overloaded ASSIGNMENT operator
// Sets this->itemID = op.itemID,	this->itemName = op.itemName, this->itemPrice = op.itemPrice
void Item::operator=(const Item &op) {
    this->itemID = op.itemID;
    this->itemName = op.itemName;
    this->itemPrice = op.itemPrice;
}

#endif




