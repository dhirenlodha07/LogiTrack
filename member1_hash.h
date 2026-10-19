#ifndef MEMBER1_HASH_H
#define MEMBER1_HASH_H

#include "Parcel.h"
#include <iostream>
#include <string>   // Includes the string data type for storing text.
#include <fstream>  // Includes file handling classes for reading and writing files.
#include <sstream>  // Includes stringstream for parsing file data.
#include <iomanip>

const int TABLE_SIZE = 20;
const char *FILE_NAME = "shipments.csv";

inline string lowercase(string s)
{
    for (int i = 0; i < (int)s.length(); i++) // traversing through each character of string
    {
        s[i] = tolower(s[i]);
    }
    return s; // return string
}

class ParcelManager
{
private:
    Parcel parcels[TABLE_SIZE]; // stores parcels in a fixed-size hash table of 20 slots.
    bool occupied[TABLE_SIZE];  // Tracks whether each hash table slot contains a valid parcel.
    int nextTrackingID;         // Next automatically assigned tracking ID.

    int hashFunction(int trackingID) const
    {
        return trackingID % TABLE_SIZE;
    }

public:
    ParcelManager()
    {
        // Initialize all hash table slots as empty.
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            occupied[i] = false;
        }

        // Start automatic tracking IDs at 1001.
        nextTrackingID = 1001;

        // Restore previously saved parcels and update the next tracking ID.
        loadFromFile();
    }

    int generateTrackingID();                       // Automatically generates a tracking ID.
    bool bookParcel(Parcel &bookedParcel);          // Declares a function to book a new parcel and pass it to other modules.
    void trackParcel(int trackingID);               // Declares a function to search for a parcel by tracking ID.
    void displayParcels();                          // Declares a function to display all booked parcels.
    bool insertParcel(Parcel p);                    // Declares a function to insert a parcel using linear probing.
    void updateStatus(int id, string newStatus);    // Updates status when dispatched or undone.
    int getActiveParcels(Parcel arr[]);             // Copies occupied parcels into an array for Member 4 sorting/searching.
    void saveToFile();                              // Declares a function to save parcel records to a file.
    void loadFromFile();                            // Declares a function to load parcel records from a file.
};

int ParcelManager::generateTrackingID() {
    return nextTrackingID++;
}

bool ParcelManager::bookParcel(Parcel &p)
{
    bool valid = true;

    // Automatically assign a tracking ID.
    p.id = generateTrackingID();

    cin.ignore(10000, '\n'); // Clear input buffer before getline

    // --- Receiver Name ---
    do
    {
        valid = true;
        cout << "\nEnter Receiver Name: ";
        getline(cin, p.name);

        // Validate: name must not be empty and must contain only letters and spaces.
        if (p.name.empty())
        {
            cout << "Invalid! Receiver name cannot be empty." << endl;
            valid = false;
        }
        else
        {
            for (char c : p.name)
            {
                if (!isalpha(c) && c != ' ')
                {
                    cout << "Invalid! Receiver name should contain only letters and spaces." << endl;
                    valid = false;
                    break;
                }
            }
        }

        if (valid)
        {
            p.name = lowercase(p.name); // Convert to lowercase.
        }

    } while (!valid);


    // --- Destination Zone ---
    do
    {
        valid = true;

        cout << "Enter Destination Zone: ";
        getline(cin, p.zone);

        if (p.zone.empty())
        {
            cout << "Invalid! Destination zone cannot be empty.\n";
            valid = false;
        }
        else
        {
            for (char c : p.zone)
            {
                if (!isalpha(c) && c != ' ')
                {
                    cout << "Invalid! Destination zone should contain only alphabets and spaces.\n";
                    valid = false;
                    break;
                }
            }
        }

        if (valid)
        {
            p.zone = lowercase(p.zone);
        }

    } while (!valid);

    // --- Parcel Weight ---
    do
    {
        valid = true;

        cout << "Enter Parcel Weight (kg): ";
        cin >> p.weight;

        if (cin.fail())
        {
            cout << "Invalid weight! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');

            valid = false;
        }
        else if (p.weight <= 0)
        {
            cout << "Invalid weight! Weight must be greater than zero.\n";
            valid = false;
        }

    } while (!valid);

    // --- Priority ---
    do
    {
        valid = true;
        cout << "Enter Priority (3 = Express, 2 = Standard, 1 = Economy): ";
        cin >> p.priority;

        if (cin.fail())
        {
            cout << "Invalid input! Please enter 1, 2, or 3.\n";

            cin.clear();
            cin.ignore(10000, '\n');
            valid = false;

            p.priority = 0;
        }
        else if (p.priority < 1 || p.priority > 3)
        {
            cout << "Invalid priority! Please enter 1, 2, or 3.\n";
            valid = false;
        }
        else
        {
            p.status = "booked";
        }

    } while (!valid);

    // Store the parcel in the hash table.
    if (insertParcel(p))
    {
        cout << "\nParcel booked successfully!\n";
        cout << "Tracking ID: " << p.id << '\n';
        cout << "Status: " << p.status << '\n';
        saveToFile();
        return true;
    }
    else
    {
        cout << "Booking failed! The hash table is full.\n";
        return false;
    }
}

bool ParcelManager::insertParcel(Parcel p)
{
    // Calculate the initial hash table index.
    int index = hashFunction(p.id);
    int startIndex = index;

    // Search for an empty slot or an existing tracking ID.
    do
    {
        if (occupied[index])
        {
            // Reject duplicate tracking IDs.
            if (parcels[index].id == p.id)
            {
                return false;
            }
        }
        else
        {
            // Store the parcel in the available slot.
            parcels[index] = p;
            occupied[index] = true;
            return true;
        }

        // Linear probing: move to the next slot.
        index = (index + 1) % TABLE_SIZE;

    } while (index != startIndex);

    // Every slot has been checked and the table is full.
    return false;
}

void ParcelManager::updateStatus(int id, string newStatus)
{
    int index = hashFunction(id);
    int startIndex = index;

    while (occupied[index])
    {
        if (parcels[index].id == id)
        {
            parcels[index].status = newStatus;
            saveToFile();
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex)
            break;
    }
}

int ParcelManager::getActiveParcels(Parcel arr[])
{
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (occupied[i])
        {
            arr[count] = parcels[i];
            count++;
        }
    }
    return count;
}

void ParcelManager::trackParcel(int id)
{
    // Calculate the initial hash table index.
    int index = hashFunction(id);
    int startIndex = index;

    // Search using linear probing until the parcel is found or all slots are checked.
    while (occupied[index])
    {
        if (parcels[index].id == id)
        {
            cout << "\n--- Parcel Details ---\n";
            cout << "Tracking ID    : " << parcels[index].id << '\n';
            cout << "Receiver Name  : " << parcels[index].name << '\n';
            cout << "Destination    : " << parcels[index].zone << '\n';
            cout << "Weight         : " << parcels[index].weight << " kg\n";
            cout << "Priority       : " << parcels[index].priority << '\n';
            cout << "Status         : " << parcels[index].status << '\n';
            return;
        }

        // Move to the next slot, wrapping around at the end of the table.
        index = (index + 1) % TABLE_SIZE;

        // Stop if the search has completed a full cycle.
        if (index == startIndex)
        {
            break;
        }
    }

    cout << "\nParcel with Tracking ID " << id << " not found.\n";
}

void ParcelManager::displayParcels()
{
    bool found = false;

    cout << "\n============================== BOOKED PARCELS ==============================\n";

    cout << left
         << setw(12) << "Tracking ID"
         << setw(20) << "Receiver Name"
         << setw(15) << "Destination"
         << setw(10) << "Weight"
         << setw(10) << "Priority"
         << setw(12) << "Status"
         << '\n';

    cout << string(85, '-') << '\n';

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (occupied[i])
        {
            found = true;

            cout << left
                 << setw(12) << parcels[i].id
                 << setw(20) << parcels[i].name
                 << setw(15) << parcels[i].zone
                 << setw(10) << parcels[i].weight
                 << setw(10) << parcels[i].priority
                 << setw(12) << parcels[i].status
                 << '\n';
        }
    }

    if (!found)
    {
        cout << "No parcels have been booked yet.\n";
    }

    cout << string(85, '-') << '\n';
}

void ParcelManager::saveToFile()
{
    ofstream outFile{std::string(FILE_NAME)};

    if (!outFile.is_open())
    {
        cout << "Error: Unable to open CSV file.\n";
        return;
    }

    // Write CSV column headers
    outFile << "Tracking ID,Receiver Name,"
            << "Destination Zone,Weight,"
            << "Priority,Status\n";

    // Write all occupied parcels
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (occupied[i])
        {
            outFile << parcels[i].id << ','
                    << parcels[i].name << ','
                    << parcels[i].zone << ','
                    << parcels[i].weight << ','
                    << parcels[i].priority << ','
                    << parcels[i].status << '\n';
        }
    }

    outFile.close();

    cout << "Parcel records saved successfully to "
         << FILE_NAME << ".\n";
}

void ParcelManager::loadFromFile()
{
    ifstream inFile{std::string(FILE_NAME)};

    // If the file doesn't exist, start with an empty hash table.
    if (!inFile)
    {
        return;
    }

    string line;
    int loadedCount = 0;

    // Read the file one parcel record at a time.
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string tracking, receiverName;
        string destination, weightStr, priorityStr, statusStr;

        // Extract fields separated by ','.
        if (!getline(ss, tracking, ',') ||
            !getline(ss, receiverName, ',') ||
            !getline(ss, destination, ',') ||
            !getline(ss, weightStr, ',') ||
            !getline(ss, priorityStr, ',') ||
            !getline(ss, statusStr))
        {
            continue;
        }

        Parcel p;

        // Convert the text fields to their required data types.
        try
        {
            p.name = receiverName;
            p.zone = destination;
            p.status = statusStr;

            p.id = stoi(tracking);
            p.weight = stof(weightStr);
            p.priority = stoi(priorityStr);
        }
        catch (const exception &)
        {
            continue;
        }

        // Restore the parcel to the hash table.
        if (insertParcel(p))
        {
            loadedCount++;
        }

        // Ensure the next tracking ID exceeds the loaded ID.
        if (p.id >= nextTrackingID)
        {
            nextTrackingID = p.id + 1;
        }
    }

    inFile.close();

    if (loadedCount > 0)
    {
        cout << loadedCount << " parcel(s) loaded from file.\n";
    }
}

#endif