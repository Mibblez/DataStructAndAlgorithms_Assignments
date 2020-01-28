//
// lfsr.h 
//
// Client code of queue container which implements a
// pseudo-random number generator by using a queue of integers 
// as a linear feedback shift register
//
//
// NOTE:
// Pattern of ones and zeros in the queue eventually repeats
//

#include "queue.h"
#include <iostream>

#ifndef LFSR_H
#define LFSR_H

using std::string;

class LFSR {
 private:
    Queue q;                    // Queue object
    int   t1, t2;               // Tap index values - two integers (peek offsets from front of queue)
    static bool  XOR(int a, int b);

 public:
    LFSR(const string& seed, int tap1, int tap2);
    void NextState();

    // Print() -- DO NOT MODIFY OR RELOCATE THIS FUNCTION
    // TODO: modify or relocate this function to use a for loop instead of this while loop bullshit
    void Print() {
        int k = 0;
        int num = q.Size();
        
        while (k < num) {
            int temp = q.Front();
            q.Dequeue();
            q.Enqueue(temp);
            printf("%i", temp);
            k++;
        }
    }
};

// Initializes t1 and t2 to tap1 and tap2, respectively
// and parses seed string to loading queue with starting values
bool LFSR::XOR(int a, int b) {
    return (!a && b) || (!b && a);
}

LFSR::LFSR(const string& seed, int tap1, int tap2) {
    this->q = Queue();

    for (char i : seed) {
        this->q.Enqueue((i == '1'));
    }

    this->t1 = tap1;
    this->t2 = tap2;
}

// Iterator method computes and queues next pseudo-random number in sequence
void LFSR::NextState() {
    bool tmp = XOR(q.Peek(t1), q.Peek(t2));
    q.Dequeue();
    q.Enqueue(tmp);
}

#endif



