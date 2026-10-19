#include<iostream>
#include "member2_pq.h"

using namespace std;

int main() {
    PriorityQueue q;
    Parcel p;
    p.id = 101;
    p.name = "Amit";
    p.zone = "Pune";
    p.weight = 2.5;
    p.priority = 1;
    p.status = "Booked";
    q.enqueue(p);

    p.id = 102;
    p.name = "Neha";
    p.zone = "Mumbai";
    p.weight = 1.5;
    p.priority = 3;
    p.status = "Booked";
    q.enqueue(p);

    p.id = 103;
    p.name = "Rahul";
    p.zone = "Nashik";
    p.weight = 4.0;
    p.priority = 2;
    p.status = "Booked";
    q.enqueue(p); 
    q.display();
    cout << "\n";
    q.dequeue(p);
    q.display();
    return 0;
}
