#ifndef PARCEL_H
#define PARCEL_H

#include <string>

// Shared parcel record used by all project modules.
struct Parcel
{
    int id;
    std::string name;
    std::string zone;
    float weight;
    int priority;
    std::string status;

    Parcel()
        : id(-1), name(""), zone(""), weight(0.0f), priority(0), status("In-Hub")
    {
    }
};

#endif
