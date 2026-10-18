#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// node class for linked list stack
class Node
{
public:
    int id;
    string name;
    string zone;
    float weight;
    int priority;
    Node *next;
};

class HistoryLogs
{
    Node *top; // pointer to top node of stack

public:
    HistoryLogs()
    {
        top = NULL; // initialize stack as empty
    }

    // check if stack is empty
    int isEmpty()
    {
        if (top == NULL)
            return 1;
        else
            return 0;
    }

    // push dispatched parcel into stack
    void push(int id, string name, string zone, float weight, int priority)
    {
        Node *newNode = new Node;
        newNode->id = id;
        newNode->name = name;
        newNode->zone = zone;
        newNode->weight = weight;
        newNode->priority = priority;

        newNode->next = top;
        top = newNode;
        cout << "Parcel " << id << " added to dispatch history." << endl;
    }

    // pop last parcel to undo dispatch and return its ID
    int pop()
    {
        if (isEmpty() == 1)
        {
            cout << "Stack Underflow! Nothing to undo." << endl;
            return -1;
        }

        Node *temp = top;
        int poppedId = temp->id;
        top = top->next;
        delete temp; // free memory

        cout << "Undo successful for parcel ID: " << poppedId << endl;
        return poppedId;
    }

    // display top element of stack
    void peek()
    {
        if (isEmpty() == 1)
        {
            cout << "Stack is empty right now." << endl;
            return;
        }
        cout << "Last dispatched parcel details:" << endl;
        cout << "ID: " << top->id << "  Name: " << top->name << "  Zone: " << top->zone << endl;
    }

    // write parcel data into file
    void writeFile(int id, string name, string zone, float weight, int priority)
    {
        ofstream fout;
        fout.open("shipments.txt", ios::app); // append mode

        if (!fout)
        {
            cout << "Error in opening file!" << endl;
            return;
        }

        fout << id << " " << name << " " << zone << " " << weight << " " << priority << endl;
        fout.close();
        cout << "Saved in file successfully." << endl;
    }

    // read all records from file
    void readFile()
    {
        ifstream fin;
        fin.open("shipments.txt");

        if (!fin)
        {
            cout << "File not found!" << endl;
            return;
        }

        cout << "ID   Name   Zone   Weight   Priority" << endl;
        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }

        fin.close();
    }
};