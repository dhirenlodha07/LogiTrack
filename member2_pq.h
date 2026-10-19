#ifndef MEMBER2_PQ_H
#define MEMBER2_PQ_H

#include <iostream>
#include "Parcel.h"
using namespace std;

class PriorityQueue {
private:
    static const int MAX_SIZE = 20;

    // Stores parcels in descending priority order.
    Parcel queue[MAX_SIZE];

    // number of parcels currently stored.
    int pqCount;

public:
    // initialize an empty queue.
    PriorityQueue() {
        pqCount = 0;
    }

    // check if the queue is empty.
    bool isEmpty() {
        return pqCount == 0;
    }

    // check if the queue is full.
    bool isFull() {
        return pqCount == MAX_SIZE;
    }

    // insert a parcel according to its priority.
    void enqueue(Parcel p) {
        if (isFull()) {
            cout << "dispatch queue is full!\n";
            return;
        }

        int i = pqCount - 1;  // starts at the index of the last occupied slot coz we need to compare the
                              // new parcel with existing parcels and move lower-priority parcels to the right

        // Shift lower-priority parcels to the right.
        // Priority 3 comes before 2, and 2 before 1.
        while (i >= 0 && queue[i].priority < p.priority) {  // checks whether the existing parcel has lower priority than the new
            queue[i + 1] = queue[i];
            i--;
        }
        // insert at the correct position.
        // equal priorities retain arrival order.
        queue[i + 1] = p;
        pqCount++;

        cout << "Parcel added to dispatch queue.\n";
    }

    // display parcels in dispatch order.
    void display() {
        if (isEmpty()) {
            cout << "dispatch queue is empty!\n";
            return;
        }

        cout << "\n--- SMART DISPATCH QUEUE ---\n";

        for (int i = 0; i < pqCount; i++) {
            cout << "ID: " << queue[i].id
                 << " | name: " << queue[i].name
                 << " | zone: " << queue[i].zone
                 << " | weight: " << queue[i].weight
                 << " | priority: " << queue[i].priority
                 << " | status: " << queue[i].status
                 << '\n';
        }
    }

    // remove and return the highest-priority parcel.
    bool dequeue(Parcel &dispatchedParcel) {
        if (isEmpty()) {
            cout << "no parcels available for dispatch!\n";
            return false;
        }

        // the first parcel has the highest priority.
        dispatchedParcel = queue[0];

        // update the returned parcel's status.
        dispatchedParcel.status = "dispatched";

        // shift remaining parcels one position left.
        for (int i = 0; i < pqCount - 1; i++) {
            queue[i] = queue[i + 1];
        }

        pqCount--;

        cout << "Parcel dispatched: " << dispatchedParcel.id << '\n';
        return true;
    }
};

#endif