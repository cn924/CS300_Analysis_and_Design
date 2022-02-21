//============================================================================
// Name        : LinkedList.cpp
// Author      : Craig Nelson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Updated     : January 23, 2022
// Description : Lab 3-3 Lists and Searching
// Assignment  : Module Three Assignment
//============================================================================


#include <algorithm>
#include <iostream>
#include <time.h>

// Added for manipulators--formatting etc.
#include <iomanip>

//CSV Parser header file
#include "CSVparser.hpp"


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations

double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};


//============================================================================
// Linked-List class definition
//============================================================================


/* Define a class containing data members and methods to
 * implement a linked-list.
 */

class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables

    struct Node {
        Bid bid;
        Node* next;

        // Default Constructor
        Node() {
            next = nullptr;
        }

        // Initialize a node with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/*Default Constructor
*/
LinkedList::LinkedList() {

    // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to null

//============================================================================
// Start FIXME (1)
//============================================================================
    head = tail = nullptr;
//============================================================================
 //End FIXME (1)
//============================================================================
}




/*Destructor
*/
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/*Append a new bid to the end of the list
*/
void LinkedList::Append(Bid bid) {
    //FIXED (2): Implement append logic

//============================================================================
// Start FIXME (2)
//============================================================================
// 
         //Create new node
    Node* node = new Node(bid);

    //if there is nothing at the head...
    if (head == nullptr) {
        head = node;
    }
    // new node becomes the head and the tail
    else {
        if (tail != nullptr) {
            tail->next = node;
        }
    }

    // make current tail node point to the new node
    tail = node;

    //increase size count
    size++;
}
//============================================================================
//End FIXME (2)
//============================================================================

/*Prepend a new bid to the start of the list
*/
void LinkedList::Prepend(Bid bid) {
    // FIXED (3): Implement prepend logic
//============================================================================
// Start FIXME (3)
//============================================================================
// 
    // Create new node
    Node* node = new Node(bid);

    // if there is already something at the head...          
    if (head != nullptr) {
        node->next = head;
    }

    // new node points to current head as its next node
    head = node;

    //increase size count
    size++;
}
//============================================================================
//End FIXME (3)
//============================================================================

/*Simple output of all bids in the list
*/
void LinkedList::PrintList() {
    // FIXED (4): Implement print logic
//============================================================================
// Start FIXME (4)
//============================================================================
// 
    // start at the head
    Node* current = head;

    // while loop over each node looking for a match
    //Set width for nice outout in Console Columns
    while (current != nullptr) {
        //output current bidID, title, amount and fund
        cout << setw(6) << current->bid.bidId << ": "
            << setw(55) << current->bid.title << " | "
            << setw(9) << fixed << setprecision(2) << current->bid.amount << " | "
            << setw(12) << current->bid.fund << endl;

        //set current equal to next
        current = current->next;
    }
}
//============================================================================
//End FIXME (4)
//============================================================================

/*Remove a specified bid
* @param bidId The bid id to remove from the list
*/


void LinkedList::Remove(string bidId) {
    // FIXED (5): Implement remove logic
//============================================================================
// Start FIXME (5)
//============================================================================
// 
    // special case if matching node is the head
    if (head != nullptr) {
        if (head->bid.bidId.compare(bidId) == 0 && head->next != nullptr) {

            // make head point to the next node in the list
            Node* tempNode = head->next;
            delete head;
            head = tempNode;
        }
    }
    else
    {
        // start at the head
        Node* current = head;
        //take a temp node
        Node* temp = current;//this is to save location of search
        // while loop over each node looking for a match
        while (current->bid.bidId.compare(bidId) != 0)
            //check if there is no match, 
            //if so move to next node in list, otherwise
            //while loop exits
        {
            
            temp = current;//update temp here
            current = current->next;//move to next node to continue search
        }
        //while loop end means compare==0 condition is met so try deleting the current node using temp
        temp->next = current->next;
        delete current;

        // reduce count
        size--;

        return;

    }

}
//============================================================================
//End FIXME (5)
//============================================================================



/**
* Search for the specified bidId
*
* @param bidId The bid id to search for
*/
Bid LinkedList::Search(string bidId) {
    // FIXED (6): Implement search logic
//============================================================================
// Start FIXME (6)
//============================================================================
// 
    // special case if matching node is the head
    Node* current = head;
    Node* temp = new Node;
    temp->bid.bidId = "";

    // loop over each node looking for a match
    while (current != nullptr) {
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        current = current->next;
    }
    return temp->bid;
}
//============================================================================
// End FIXME (6)
//============================================================================
// 

/**
* Returns the current size (number of elements) in the list
*/
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/*Display the bid information
* @param bid struct containing the bid info
*/
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
        << " | " << bid.fund << endl;
    return;
}

/**
* Prompt user for bid information
* @return Bid struct containing the bid info
*/
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
* Load a CSV file containing bids into a LinkedList
*
* @return a LinkedList containing all the bids read
*/
void loadBids(string csvPath, LinkedList* list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
* Simple C function to convert a string to a double
* after stripping out unwanted char
*
* credit: http://stackoverflow.com/a/24875936
*
* @param ch The character to strip out
*/
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
* The one and only main() method
*
* @param arg[1] path to CSV file to load from (optional)
* @param arg[2] the bid Id to use when searching the list (optional)
*/
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        //bidKey = "97990";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
        //bidKey = "97990";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << " 1. Enter a Bid" << endl;
        cout << " 2. Load Bids" << endl;
        cout << " 3. Display All Bids" << endl;
        cout << " 4. Find Bid" << endl;
        cout << " 5. Remove Bid" << endl;

        //Add Prepend to menu
        cout << " 6. Prepend a Bid" << endl;
        cout << " 9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
            // add prepend case for bid
        case 6:
            bid = getBid();
            bidList.Prepend(bid);
            displayBid(bid);

            break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}