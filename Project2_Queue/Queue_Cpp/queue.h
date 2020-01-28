//
// Queue class is a circular linked list implementation of the queue abstract data type
//

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <functional>
#include <exception>

// Exceptions
struct QueueEmpty : public std::exception {
    const char* what() const noexcept override{
        return "Queue is empty.";
    }
};

struct QueueFull : public std::exception {
    const char* what() const noexcept override{
        return "Queue is full.";
    }
};

struct QueueInvalidPeek : public std::exception {
    const char* what() const noexcept override{
        return "Peek node does not exist.";
    }
};

// Queue Node Structure
struct Node {                         // Linked circular queue node structure
	int         data;				// Field for storing data in the queue node
	Node*	    nextPtr;			// Points to successor node (node following current node)
};


class Queue {				            // Linked circular queue
private:
    Node* rearPtr;      // Points to rear of queue
	int count;          // Number of values stored in queue
	
public:
    Queue();
    ~Queue();
    void MakeEmpty();
    void Enqueue(int n);
    void Dequeue();
    int Front() const;
    int Rear() const;
    int Peek(int n) const;
    bool IsFull() const;
    bool IsEmpty() const;
    int Size() const;

    // Prints contents of queue rear to front without modifying its contents
    void PrintQ() const {
		printf("Rear { ");
        Node* tempPtr = rearPtr;

        for (int i = 0; i < count; ++i) {
            printf("%i ", tempPtr->data);
            tempPtr = tempPtr->nextPtr;
        }

		printf("} Front\n");
	}
};

// Initializes all private variables to indicate an empty queue
Queue::Queue() {
    this->rearPtr = nullptr;
    this->count = 0;
}

// Deallocates all queue nodes
Queue::~Queue() {
    MakeEmpty();
}

// Deallocates all queue nodes and returns queue to empty ready-to-use state
void Queue::MakeEmpty() {
    std::function<void (Node*&)> EmptyRecursion = [&EmptyRecursion] (Node*& node) {
        if (node) {
            EmptyRecursion(node->nextPtr);
            delete[](node);
            node = nullptr;
        }
    };

    EmptyRecursion(rearPtr);
    this->count = 0;
}

// Adds value n to rear of queue and increments count.
// If queue is already full, throws QueueFull exception
void Queue::Enqueue(int n) {
    if (this->IsFull()) {
        throw QueueFull();
    }

    Node* tmpPtr = rearPtr;
    rearPtr = new Node;
    rearPtr->data = n;
    rearPtr->nextPtr = tmpPtr;
    count++;
}

// Removes front value from queue and decrements count.
// If queue is empty, throws QueueEmpty exception
void Queue::Dequeue() {
    if (this->IsEmpty()) {
        throw QueueEmpty();
    }

    // Iterate through the queue from rear to front and remove front
    // *& is pointer by reference or some shit. I need it here otherwise things get fucky
    std::function<void (Node*&)> DequeueRecursion = [&DequeueRecursion] (Node*& node) {
        if (!node->nextPtr) {
            delete[](node);
            node = nullptr;
        } else {
            DequeueRecursion(node->nextPtr);
        }
    };

    DequeueRecursion(rearPtr);
    count--;
}

// Returns integer from front of queue
// If queue is empty, throws QueueEmpty exception
int Queue::Front() const {
    if (this->IsEmpty()) {
        throw QueueEmpty();
    }

    std::function<int (Node*)> FrontRecursion = [&FrontRecursion] (Node* node) -> int{
        if (!node->nextPtr){
            return node->data;
        } else {
            return FrontRecursion(node->nextPtr);
        }
    };

    return FrontRecursion(this->rearPtr);
}

// Returns integer from rear of queue
// If queue is empty, throws QueueEmpty exception
int Queue::Rear() const {
    if (this->IsEmpty()) {
        throw QueueEmpty();
    }
    return rearPtr->data;
}

// Returns integer n positions from front of queue
// If queue is empty, throws QueueEmpty
// If position n does not exist, throws QueueInvalidPeek
int Queue::Peek(int n) const {
    if (this->IsEmpty()) {
        throw QueueEmpty();
    } else if (n > this->count) {
       throw QueueInvalidPeek();
    }

    Node* node = this->rearPtr;
    for (int i = 0; i < this->count - n - 1; ++i) {
        node = node->nextPtr;
    }

    return node->data;
}

// Returns true if queue is full.  Returns false otherwise.
bool Queue::IsFull() const {
    // TODO: GOD LEFT ME UNFINISHED
    return false;
}

// Returns true if queue is empty.  Returns false otherwise.
bool Queue::IsEmpty() const {
    return !this->rearPtr;
}

// Returns number of items stored in queue.
int Queue::Size() const {
    return this->count;
}

#endif
