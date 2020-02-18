//
// bstree.h  Binary Search Tree
//
// NOTES:
// The public methods utilize several private helper methods to perform the desired tasks.
//

#ifndef BSTREE_H
#define BSTREE_H

#include <cstddef>
#include <new>
#include <string>
#include <queue>

using namespace std;

// Exception classes
class FullBSTree: public std::exception { };        // Exception class models full BSTree condition
class EmptyBSTree: public std::exception  { };      // Exception class models empty BSTree condition
class NotFoundBSTree: public std::exception  { };   // Exception class models not found in BSTree condition
class FoundInBSTree: public std::exception  { };    // Exception class models found in BSTree condition
class NoParentBSTree: public std::exception  { };   // Exception class models no parent in BSTree condition


template<typename SomeType>
struct BSTreeNode {                      // Node of BSTree
    SomeType data;                       // Data stored in node
    BSTreeNode<SomeType> *leftPtr;       // Pointer to left subtree
    BSTreeNode<SomeType> *rightPtr;      // Pointer to right subtree
};

template<typename SomeType>
class BSTree {                         // BSTree Abstract Data Type
private:
    BSTreeNode<SomeType> *rootPtr;       // Pointer to root of BSTree
    void Delete(BSTreeNode<SomeType> *&treePtr, SomeType &item);
    void DeleteNode(BSTreeNode<SomeType> *&treePtr);
    void Insert(BSTreeNode<SomeType> *&ptr, SomeType item);
    void Destroy(BSTreeNode<SomeType> *&ptr);
    void CopyTree(BSTreeNode<SomeType> *&copy, const BSTreeNode<SomeType> *originalTree);
    SomeType GetPredecessor(BSTreeNode<SomeType> *treePtr) const;
    int CountNodes(BSTreeNode<SomeType> *treePtr) const;
    int LevelCount(BSTreeNode<SomeType> *treePtr) const;
    int FindLevel(BSTreeNode<SomeType> *treePtr, SomeType item) const;
    void SearchForParent(BSTreeNode<SomeType> *treePtr, SomeType item) const;

public:
    BSTree();
    BSTree(const BSTree<SomeType> &someTree);
    void operator=(const BSTree<SomeType> &originalTree);
    ~BSTree();
    void InsertItem(SomeType item);
    SomeType DeleteItem(SomeType item);
    void MakeEmpty();
    int Size() const;
    bool IsFull() const;
    bool IsEmpty() const;
    SomeType Min() const;
    SomeType Max() const;
    int TotalLevels() const;
    int Level(SomeType item) const;
    SomeType Parent(SomeType item);
    void Print() const;
};

// PreOrder()
// Post: preorder contains the tree items in preorder.
template<typename SomeType>
void PreOrder(BSTreeNode<SomeType> *tree, queue<SomeType> &preorder) {
    if (tree != NULL) {
        preorder.push(tree->data);
        PreOrder(tree->leftPtr, preorder);
        PreOrder(tree->rightPtr, preorder);
    }
}

// InOrder()
// Post: inorder contains the tree items in inorder.
template<typename SomeType>
void InOrder(BSTreeNode<SomeType> *tree, queue<SomeType> &inorder) {
    if (tree != NULL) {
        InOrder(tree->leftPtr, inorder);
        inorder.push(tree->data);
        InOrder(tree->rightPtr, inorder);
    }
}

// PostOrder()
// Post: postorder contains the tree items in postorder.
template<typename SomeType>
void PostOrder(BSTreeNode<SomeType> *tree, queue<SomeType> &postorder) {
    if (tree != NULL) {
        PostOrder(tree->leftPtr, postorder);
        PostOrder(tree->rightPtr, postorder);
        postorder.push(tree->data);
    }
}

// Print()
// Prints binary search tree contents in inorder, preorder, and postorder forms
template<typename SomeType>
void BSTree<SomeType>::Print() const {
    queue<SomeType> preorder, inorder, postorder;

    PreOrder(rootPtr, preorder);
    InOrder(rootPtr, inorder);
    PostOrder(rootPtr, postorder);

    cout << "Print() \n-- Inorder = { ";
    while (!inorder.empty()) {
        cout << inorder.front() << " ";
        inorder.pop();
    }
    cout << "}   \n-- Preorder = { ";
    while (!preorder.empty()) {
        cout << preorder.front() << " ";
        preorder.pop();
    }
    cout << "}   \n-- Postorder = { ";
    while (!postorder.empty()) {
        cout << postorder.front() << " ";
        postorder.pop();
    }
    cout << "}" << endl;
}

/********  Start of Private Interface Functions  *********/

// Delete()
// Recursive function that traverses the tree starting at treePtr to locate the data value to be removed
// Once located, DeleteNode is invoked to remove the value from the tree
// If tree is not empty and item is NOT present, throw NotFoundBSTree
template<typename SomeType>
void BSTree<SomeType>::Delete(BSTreeNode<SomeType> *&treePtr, SomeType &item) {
    if (item < treePtr->data)
        Delete(treePtr->leftPtr, item);
    else if (item > treePtr->data)
        Delete(treePtr->rightPtr, item);
    else
        DeleteNode(treePtr);
}

// DeleteNode()
// Removes the node pointed to by treePtr from the tree
template<typename SomeType>
void BSTree<SomeType>::DeleteNode(BSTreeNode<SomeType> *&treePtr) {
    if (treePtr->rightPtr == nullptr && treePtr->leftPtr == nullptr) {
        delete treePtr;
        treePtr = nullptr;
    } else if (treePtr->leftPtr == nullptr) {
        BSTreeNode<SomeType> *tmp = treePtr;
        treePtr = treePtr->rightPtr;
        delete tmp;
    } else if (treePtr->rightPtr == nullptr) {
        BSTreeNode<SomeType> *tmp = treePtr;
        treePtr = treePtr->leftPtr;
        delete tmp;
    } else {
        // Two Children
        SomeType tmp = GetPredecessor(treePtr->leftPtr);
        treePtr->data = tmp;
        Delete(treePtr->leftPtr, tmp);  // Delete duplicate that was just made
    }
}

// Insert()
// Recursive function that finds the correct position of item and adds it to the tree
// Throws FoundInBSTree if item is already in the tree
template<typename SomeType>
void BSTree<SomeType>::Insert(BSTreeNode<SomeType> *&ptr, SomeType item) {
    if (ptr == nullptr) {
        auto *newNode = new BSTreeNode<SomeType>;
        *newNode = {item, nullptr, nullptr};
        ptr = newNode;
    } else if (item < ptr->data) {
        Insert(ptr->leftPtr, item);
    } else if (item > ptr->data) {
        Insert(ptr->rightPtr, item);
    } else {
        // Item to insert must be equal to the current item
        throw FoundInBSTree();
    }

}

// Destroy()
// Recursively deallocates every node in the tree pointed to by ptr
template<typename SomeType>
void BSTree<SomeType>::Destroy(BSTreeNode<SomeType> *&ptr) {
    if (ptr->rightPtr == nullptr && ptr->leftPtr == nullptr) {
        DeleteNode(ptr);
    } else if (ptr->rightPtr == nullptr) {
        Destroy(ptr->leftPtr);
        DeleteNode(ptr);
    } else if (ptr->leftPtr == nullptr) {
        Destroy(ptr->rightPtr);
        DeleteNode(ptr);
    } else {
        // Two children
        Destroy(ptr->rightPtr);
        Destroy(ptr->leftPtr);
        DeleteNode(ptr);
    }
}

// CopyTree()
// Recursively copies all data from original tree into copy
template<typename SomeType>
void BSTree<SomeType>::CopyTree(BSTreeNode<SomeType> *&copy, const BSTreeNode<SomeType> *originalTree) {
    if (originalTree == nullptr) {
        copy = nullptr;
    } else {
        copy = new BSTreeNode<SomeType>;
        copy->data = originalTree->data;
        copy->leftPtr = originalTree->leftPtr;
        copy->rightPtr = originalTree->rightPtr;

        CopyTree(copy->leftPtr, originalTree->leftPtr);
        CopyTree( copy->rightPtr, originalTree->rightPtr);
    }
}

// GetPredecessor()
// Finds the largest data value in the tree pointed to by treePtr and returns that data value
template<typename SomeType>
SomeType BSTree<SomeType>::GetPredecessor(BSTreeNode<SomeType> *treePtr) const {
    BSTreeNode<SomeType> *tmp = treePtr;

    while (tmp->rightPtr != nullptr) {
        tmp = tmp->rightPtr;
    }

    return tmp->data;
}

// CountNodes()
// Recursive function that counts every node in the tree pointed to by treePtr and returns the count
template<typename SomeType>
int BSTree<SomeType>::CountNodes(BSTreeNode<SomeType> *treePtr) const {
    if (treePtr->rightPtr == nullptr && treePtr->leftPtr == nullptr)
        return 1;
    else if (treePtr->leftPtr == nullptr)
        return 1 + CountNodes(treePtr->rightPtr);
    else if (treePtr->rightPtr == nullptr)
        return 1 + CountNodes(treePtr->leftPtr);
    else
        // Two children
        return 1 + CountNodes(treePtr->rightPtr) + CountNodes(treePtr->leftPtr);
}

// LevelCount()
// Recursive function that traverses the entire tree to determine the total number of levels in the tree
template<typename SomeType>
int BSTree<SomeType>::LevelCount(BSTreeNode<SomeType> *treePtr) const {
    if (treePtr->rightPtr == nullptr && treePtr->leftPtr == nullptr)
        return 1;
    else if (treePtr->rightPtr == nullptr)
        return 1 + LevelCount(treePtr->leftPtr);
    if (treePtr->leftPtr == nullptr)
        return 1 + LevelCount(treePtr->rightPtr);
    else
        return 1 + max(LevelCount(treePtr->leftPtr), LevelCount(treePtr->rightPtr));
}

// FindLevel()
// Recursive function that traverses the tree looking for item and returns the level where
// item was found
template<typename SomeType>
int BSTree<SomeType>::FindLevel(BSTreeNode<SomeType> *treePtr, SomeType item) const {
    if (treePtr == nullptr)
        throw NotFoundBSTree();
    else if (treePtr->data == item)
        return 0;
    else if(treePtr->data < item)
        return 1 + FindLevel(treePtr->rightPtr, item);
    else
        return 1 + FindLevel(treePtr->leftPtr, item);
}

// SearchForParent()
// Recursive function that traverses the tree looking for item's parent and throws the value of
// item's parent if found.  Otherwise, throws NotFoundBSTree
template<typename SomeType>
void BSTree<SomeType>::SearchForParent(BSTreeNode<SomeType> *treePtr, SomeType item) const {
   if (treePtr->rightPtr == nullptr && treePtr->leftPtr == nullptr){
   } else if (treePtr->rightPtr == nullptr) {
        if (treePtr->leftPtr->data == item)
            throw *treePtr;
        else
            SearchForParent(treePtr->leftPtr, item);
    } else if (treePtr->leftPtr == nullptr) {
        if (treePtr->rightPtr->data == item)
            throw *treePtr;
        else
            SearchForParent(treePtr->rightPtr, item);
    } else {
        // Two children
        if (treePtr->rightPtr->data == item || treePtr->leftPtr->data == item) {
            throw *treePtr;
        } else {
            SearchForParent(treePtr->leftPtr, item);
            SearchForParent(treePtr->rightPtr, item);
        }
    }

}

/********  End of Private Interface Functions  *********/


/********  Start of Public Interface Functions  *********/

// BSTree()
// Default constructor initializes root pointer to NULL
template<typename SomeType>
BSTree<SomeType>::BSTree() {
    this->rootPtr = nullptr;
}

// BSTree()
// Copy constructor for BSTree
template<typename SomeType>
BSTree<SomeType>::BSTree(const BSTree<SomeType> &someTree) {
    CopyTree(this->rootPtr, someTree.rootPtr);
}

// operator=()
// Overloaded assignment operator for BSTree.
template<typename SomeType>
void BSTree<SomeType>::operator=(const BSTree<SomeType> &originalTree) {
    CopyTree(this->rootPtr, originalTree.rootPtr);
}

// ~BSTree()
// Destructor deallocates all tree nodes
template<typename SomeType>
BSTree<SomeType>::~BSTree() {
    if (!this->IsEmpty())
        Destroy(this->rootPtr);
}

// InsertItem()
// Inserts item into BSTree;  if tree already full, throws FullBSTree exception
// If item is already in BSTree, throw FoundInBSTree exception
template<typename SomeType>
void BSTree<SomeType>::InsertItem(SomeType item) {
    if (this->IsFull())
        throw FoundInBSTree();

    Insert(this->rootPtr, item);
}

// DeleteItem()
// Deletes item from BSTree if item is present AND returns object
// If tree is empty, throw the EmptyBSTree exception
// If tree is not empty and item is NOT present, throw NotFoundBSTree
template<typename SomeType>
SomeType BSTree<SomeType>::DeleteItem(SomeType item) {
    if (this->IsEmpty())
        throw EmptyBSTree();

    SomeType itemCopy = item;

    Delete(this->rootPtr, item);

    return itemCopy;
}

// MakeEmpty()
// Deallocates all BSTree nodes and sets root pointer to NULL
template<typename SomeType>
void BSTree<SomeType>::MakeEmpty() {
    if (!this->IsEmpty())
        Destroy(this->rootPtr);
}

// Size()
// Returns total number of data values stored in tree
template<typename SomeType>
int BSTree<SomeType>::Size() const {
    if (this->rootPtr == nullptr)
        return 0;
    else
        return CountNodes(this->rootPtr);
}

// IsFull()
// Returns true if BSTree is full; returns false otherwise
template<typename SomeType>
bool BSTree<SomeType>::IsFull() const {
    return false;
}

// IsEmpty()
// Returns true if BSTree is empty; returns false otherwise
template<typename SomeType>
bool BSTree<SomeType>::IsEmpty() const {
    return rootPtr == nullptr;
}

// Min()
// Returns minimum value in tree; throws EmptyBSTree if tree is empty
template<typename SomeType>
SomeType BSTree<SomeType>::Min() const {
    if (this->IsEmpty())
        throw EmptyBSTree();

    BSTreeNode<SomeType> *tmp = this->rootPtr;

    // The leftmost node contains the lowest value
    while (tmp->leftPtr != nullptr)
        tmp = tmp->leftPtr;

    return tmp->data;
}

// Max()
// Returns maximum value in tree; throws EmptyBSTree if tree is empty
template<typename SomeType>
SomeType BSTree<SomeType>::Max() const {
    if (this->IsEmpty())
        throw EmptyBSTree();

    BSTreeNode<SomeType> *tmp = this->rootPtr;

    // The rightmost node contains the highest value
    while (tmp->rightPtr != nullptr)
        tmp = tmp->rightPtr;

    return tmp->data;
}

// TotalLevels()
// Returns the maximum level value for current tree contents
// Throws EmptyBSTree if empty
template<typename SomeType>
int BSTree<SomeType>::TotalLevels() const {
    if (this->IsEmpty())
        throw EmptyBSTree();

    return LevelCount(this->rootPtr);
}

// Level()
// Returns the level within the BSTree at which the value item is found
// If tree is empty, throws EmptyBSTree
// If tree is not empty and item is not found, throws NotFoundBSTree
template<typename SomeType>
int BSTree<SomeType>::Level(SomeType item) const {
    if (this->IsEmpty())
        throw EmptyBSTree();

    return FindLevel(this->rootPtr, item);
}

// Parent()
// Returns the value of item's parent from BSTree if item is present AND returns object
// If tree is empty, throw the EmptyBSTree exception
// If tree is not empty and item is NOT present, throw NotFoundBSTree
template<typename SomeType>
SomeType BSTree<SomeType>::Parent(SomeType item) {
    if (this->IsEmpty())
        throw EmptyBSTree();

    // Is this really what it wants me to do?
    try {
        SearchForParent(this->rootPtr, item);
    } catch (BSTreeNode<SomeType>& foundParent) {
        return foundParent.data;
    }

    throw NotFoundBSTree();

}

/********  End of Public Interface Functions  *********/

#endif
