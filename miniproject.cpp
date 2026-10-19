
#include <iostream>
using namespace std;

class Parcel {
    public:
    int trackingID;
    string receiverName;
    string destZone;
    float weight;
    int priority;
    string status;
};

const int MAX = 20;

class PriorityQueue {
private:
    Parcel pq[MAX];
    int pqCount;  //keeps track of how many parcels are currently in the queue

public:
    PriorityQueue() {
        pqCount = 0;
    }

    void enqueue(Parcel p) {
        if (pqCount == MAX) {  //checking whether the queue is full
            cout << "Dispatch queue is full"<<endl;
            return;
        }

        int i = pqCount - 1;  // starts at the index of the last occupied slot coz we need to compare the
                              //new parcel with existing parcels and move lower-priority parcels to the right

        // Shift lower-priority parcels to the right
        while (i >= 0 && pq[i].priority < p.priority) {   //checks whether the existing parcel has lower priority than the new parcel
            
            pq[i + 1] = pq[i];  //it copies the existing parcel one position to the right
            i--;
        }

        pq[i + 1] = p;  //insert parcel into correct position
        pqCount++;

        cout << "Parcel added to dispatch queue"<<endl;
    }

    void dequeue() {
        if (pqCount == 0) {
            cout << "dispatch queue is empty!"<<endl;
            return;
        }

        cout << "dispatched tracking id: "<< pq[0].trackingID << "\n";

        // remove the first parcel by shifting left
        for (int i = 0; i < pqCount - 1; i++) {
            pq[i] = pq[i + 1];
        }

        pqCount--;
    }

    void display() {  //displays all parcels currently in the queue
        if (pqCount == 0) {
            cout << "dispatch queue is empty!"<<endl;
            return;
        }
        cout << "\ndispatch queue:\n";

        for (int i = 0; i < pqCount; i++) {
        cout << "id:"<< pq[i].trackingID  //current parcel's tracking id
             << "|receiver:"<< pq[i].receiverName<<"|priority:"<< pq[i].priority<<endl;
        }
    }
};

int main() {
    PriorityQueue q;
    Parcel p;
    p.trackingID = 101;
    p.receiverName = "Amit";
    p.destZone = "Pune";
    p.weight = 2.5;
    p.priority = 1;
    p.status = "Booked";
    q.enqueue(p);

    p.trackingID = 102;
    p.receiverName = "Neha";
    p.destZone = "Mumbai";
    p.weight = 1.5;
    p.priority = 3;
    p.status = "Booked";
    q.enqueue(p);

    p.trackingID = 103;
    p.receiverName = "Rahul";
    p.destZone = "Nashik";
    p.weight = 4.0;
    p.priority = 2;
    p.status = "Booked";
    q.enqueue(p); 
    q.display();
    cout << "\n";
    q.dequeue();
    q.display();
    return 0;
}
