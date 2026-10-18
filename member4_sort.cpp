#include <iostream>
#include <string>

#include "Parcel.h"
#include "member4_sort.h"

using namespace std;

int main()
{
    // Create an array that can store up to 100 parcels
    Parcel p[100];
    int n, choice;

    // Ask how many parcels the user wants to enter
    cout << "Enter number of parcels (1-100): ";
    cin >> n;

    // Check whether the number of parcels is valid
    if (n < 1 || n > 100)
    {
        cout << "Invalid number of parcels.\n";
        return 0;
    }

    // Enter the details of each parcel
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter parcel ID: ";
        cin >> p[i].id;

        cout << "Enter receiver name: ";
        cin >> ws;
        getline(cin, p[i].name);

        cout << "Enter destination zone: ";
        getline(cin, p[i].zone);

        cout << "Enter weight: ";
        cin >> p[i].weight;

        cout << "Enter priority (3=Express, 2=Standard, 1=Bulk): ";
        cin >> p[i].priority;
    }

    // Continue showing the menu until the user selects Exit
    do
    {
        cout << "\n--- MANIFEST MENU ---\n";
        cout << "1. Display Parcels\n";
        cout << "2. Sort by Weight\n";
        cout << "3. Sort by Destination Zone\n";
        cout << "4. Search by Receiver Name\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Call the appropriate function based on the user's choice
        switch (choice)
        {
        case 1:
            display(p, n);
            break;
        case 2:
            sortByWeight(p, n);
            break;
        case 3:
            sortByZone(p, n);
            break;
        case 4:
            searchByReceiver(p, n);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
