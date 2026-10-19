#ifndef MEMBER4_SORT_H
#define MEMBER4_SORT_H

#include <iostream>
#include "Parcel.h"
#include "member1_hash.h"

// Function to display the details of all parcels
inline void display(Parcel p[], int n)
{
    if (n == 0)
    {
        std::cout << "\nNo parcels available to display.\n";
        return;
    }

    std::cout << "\nID\tReceiver\tZone\tWeight\n";

    // Visit each parcel one by one
    for (int i = 0; i < n; i++)
    {
        std::cout << p[i].id << "\t"
                  << p[i].name << "\t"
                  << p[i].zone << "\t"
                  << p[i].weight << "\n";
    }
}

// Bubble Sort: Arrange parcels by weight
inline void sortByWeight(Parcel p[], int n)
{
    if (n == 0)
    {
        std::cout << "\nNo parcels available to sort.\n";
        return;
    }

    // Repeat the process for n-1 rounds
    for (int i = 0; i < n - 1; i++)
    {
        // Compare adjacent parcels in each round
        for (int j = 0; j < n - i - 1; j++)
        {
            // If the first parcel is heavier, swap the two parcels
            if (p[j].weight > p[j + 1].weight)
            {
                Parcel temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Display the parcels after sorting
    std::cout << "\nParcels sorted by weight:\n";
    display(p, n);
}

// Insertion Sort: Arrange parcels by destination zone
inline void sortByZone(Parcel p[], int n)
{
    if (n == 0)
    {
        std::cout << "\nNo parcels available to sort.\n";
        return;
    }

    // Start from the second parcel
    for (int i = 1; i < n; i++)
    {
        // Store the current parcel temporarily
        Parcel key = p[i];

        // Point to the parcel just before the key
        int j = i - 1;

        // Shift zones that come alphabetically after the key one position right
        while (j >= 0 && p[j].zone > key.zone)
        {
            p[j + 1] = p[j];
            j--;
        }

        // Insert the key at its correct position
        p[j + 1] = key;
    }

    // Display the parcels after sorting
    std::cout << "\nParcels sorted by destination zone:\n";
    display(p, n);
}

// Linear Search: Find parcels by receiver name
inline void searchByReceiver(Parcel p[], int n)
{
    if (n == 0)
    {
        std::cout << "\nNo parcels available to search.\n";
        return;
    }

    std::string receiverName;
    bool found = false;

    // Ask the user for the receiver's name
    std::cout << "Enter receiver name: ";
    std::cin >> std::ws;
    std::getline(std::cin, receiverName);
    receiverName = lowercase(receiverName);

    // Check the receiver name of each parcel
    for (int i = 0; i < n; i++)
    {
        // The shared Parcel record stores the receiver in its name field
        if (p[i].name == receiverName)
        {
            std::cout << "\nParcel found!\n";
            std::cout << "Tracking ID: " << p[i].id << "\n";
            std::cout << "Receiver: " << p[i].name << "\n";
            std::cout << "Zone: " << p[i].zone << "\n";
            std::cout << "Weight: " << p[i].weight << "\n";
            found = true;
        }
    }

    // Display a message if no matching parcel exists
    if (!found)
    {
        std::cout << "\nReceiver not found.\n";
    }
}

#endif