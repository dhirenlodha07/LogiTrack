#include <iostream>
#include "Parcel.h"
#include "member1_hash.h"
#include "member2_pq.h"
#include "member3_stack.h"
#include "member4_sort.h"

using namespace std;

/*-----------------Main Function------------- */
int main()
{
    ParcelManager manager;  // Member 1: Hash Table manager
    PriorityQueue dispatch; // Member 2: Priority Queue for dispatch
    HistoryLogs history;    // Member 3: Linked List Stack & File Logs

    int choice;             // stores the menu option entered by the user.
    bool correct = true;

    do
    { // repeats the menu until the user chooses to exit.

        cout << "\n================ LOGITRACK HUB SYSTEM ================\n";
        cout << "1. Book a New Parcel (Hash Table + Priority Queue)" << endl;
        cout << "2. Track a Parcel by ID (Hash Table Lookup)" << endl;
        cout << "3. Display All Booked Parcels" << endl;
        cout << "4. View Smart Dispatch Queue (Priority Order)" << endl;
        cout << "5. Dispatch Next Parcel (Dequeue + Push to Stack)" << endl;
        cout << "6. Undo Last Dispatch (Stack Pop)" << endl;
        cout << "7. View Last Dispatched Parcel (Stack Peek)" << endl;
        cout << "8. Sort Parcels by Weight (Bubble Sort)" << endl;
        cout << "9. Sort Parcels by Destination Zone (Insertion Sort)" << endl;
        cout << "10. Search Parcel by Receiver Name (Linear Search)" << endl;
        cout << "11. View Permanent Shipment Text Logs (File Handling)" << endl;
        cout << "0. Exit" << endl;
        cout << "======================================================\n";

        do
        {
            correct = true;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                correct = false;
            }

        } while (!correct);

        switch (choice)
        {
        case 1:
        {
            Parcel newParcel;
            // Member 1 books the parcel into Hash Table
            if (manager.bookParcel(newParcel))
            {
                // Member 2 adds it to Priority Queue for dispatch
                dispatch.enqueue(newParcel);
                // Member 3 logs it to shipments.txt
                history.writeFile(newParcel.id, newParcel.name, newParcel.zone, newParcel.weight, newParcel.priority);
            }
            break;
        }

        case 2:
        {
            int id;
            bool valid;

            do
            {
                valid = true;
                cout << "Enter Tracking ID: ";
                cin >> id;

                if (cin.fail())
                {
                    cout << "Please enter a valid integer Tracking ID!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    valid = false;
                }
                else
                {
                    char extra;
                    if (cin.get(extra) && extra != '\n')
                    {
                        cout << "Invalid input! Enter only an integer Tracking ID.\n";
                        cin.ignore(10000, '\n');
                        valid = false;
                    }
                }
            } while (!valid);

            manager.trackParcel(id);
            break;
        }

        case 3:
            manager.displayParcels(); // Displays all booked parcels in Hash Table.
            break;

        case 4:
            dispatch.display(); // Displays Priority Queue.
            break;

        case 5:
        {
            Parcel dispatchedParcel;
            // Member 2 dequeues highest priority parcel
            if (dispatch.dequeue(dispatchedParcel))
            {
                // Member 1 updates status in Hash Table
                manager.updateStatus(dispatchedParcel.id, "dispatched");
                // Member 3 pushes dispatched parcel onto Undo Stack
                history.push(dispatchedParcel.id, dispatchedParcel.name, dispatchedParcel.zone, dispatchedParcel.weight, dispatchedParcel.priority);
            }
            break;
        }

        case 6:
        {
            Parcel undoneParcel;
            // Member 3 pops the last dispatched parcel from Stack
            if (history.pop(undoneParcel))
            {
                // Member 1 updates status back to booked
                manager.updateStatus(undoneParcel.id, "booked");
                // Member 2 puts the parcel back into Priority Queue
                dispatch.enqueue(undoneParcel);
            }
            break;
        }

        case 7:
            history.peek(); // Member 3 views top of stack.
            break;

        case 8:
        {
            Parcel tempArr[TABLE_SIZE];
            int count = manager.getActiveParcels(tempArr);
            sortByWeight(tempArr, count); // Member 4 Bubble Sort by weight.
            break;
        }

        case 9:
        {
            Parcel tempArr[TABLE_SIZE];
            int count = manager.getActiveParcels(tempArr);
            sortByZone(tempArr, count); // Member 4 Insertion Sort by zone.
            break;
        }

        case 10:
        {
            Parcel tempArr[TABLE_SIZE];
            int count = manager.getActiveParcels(tempArr);
            searchByReceiver(tempArr, count); // Member 4 Linear Search by receiver name.
            break;
        }

        case 11:
            history.readFile(); // Member 3 reads sequential log file.
            break;

        case 0:
            cout << "Exiting the program..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0; // Indicates successful program termination.
}