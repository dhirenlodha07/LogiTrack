#ifndef PARCEL_H
#define PARCEL_H

#include <string>
using namespace std;

// shared parcel class for all modules
class Parcel {
public:
    int id;
    string name;
    string zone;
    float weight;
    int priority;
    string status;

    Parcel() {
        id = -1;
        name = "";
        zone = "";
        weight = 0.0;
        priority = 0;
        status = "In-Hub";
    }
};

#endif