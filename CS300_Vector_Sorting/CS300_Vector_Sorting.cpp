//============================================================================
// Name        : VectorSorting.cpp
// Author      : Craig Nelson
// Version     : 1.0
// Copyright   : Copyright © 2017 (update 2022) SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
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
// Static methods used for testing
//============================================================================

/**
* Display the bid information to the console (std::out)
*
* @param bid struct containing the bid info
*/

void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
* Prompt user for bid information using console (std::in)
*
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

* Load a CSV file containing bids into a container
*
* @param csvPath the path to the CSV file to load
* @return a container holding all the bids read
*/

vector<Bid> loadBids(string csvPath) {

    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file

        for (int i = 0; i < file.rowCount(); i++) {
            // Create a data structure and add to the collection of bids

            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);

        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }

    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
* Partition the vector of bids into two parts, low and high
*
* @param bids Address of the vector<Bid> instance to be partitioned
* @param begin Beginning index to partition
* @param end Ending index to partition
*/

int partition(vector<Bid>& bids, int begin, int end) {
//***********************************************************************************************************
//     START----THE FIX FOR (2a)
//***********************************************************************************************************
    //set low and high equal to begin and end
    int lo = begin;
    int hi = end;

    // picking the pivot point
    int pivot = begin + (end - begin) / 2;

    bool done = false;

    while (!done) {

        // keep incrementing low as long as its less than pivot
        while (bids.at(lo).title.compare(bids.at(pivot).title) < 0) {

            ++lo;
        }

        //keep decrementing high as long as its less than pivot
        while (bids.at(pivot).title.compare(bids.at(hi).title) < 0) {

            --hi;
        }
        // low meets high in the middle
        if (lo >= hi) {

            done = true;
        }

        else {

            //swap low and high bids using build in vector method
            swap(bids.at(lo), bids.at(hi));

            //move end points closer
            ++lo;
            --hi;
        }
    }
    //return high;
    return hi;
}
//***********************************************************************************************************
// END----THE FIX FOR (2a)
//***********************************************************************************************************

/**
* Perform a quick sort on bid title
* Average performance: O(n log(n))
* Worst case performance O(n^2))
*
* @param bids address of the vector<Bid> instance to be sorted
* @param begin the beginning index to sort on
* @param end the ending index to sort on
*/

void quickSort(vector<Bid>& bids, int begin, int end) {

    int mid = 0;

    //if zero or one bids to sort, then done.
    if (begin >= end) {

        return;
    }

    // partition bids into low and high parts
    mid = partition(bids, begin, end);

    //recursively call quicksort using midpoint value
    quickSort(bids, begin, mid);

    //recursively call quicksory using midpoint val
    quickSort(bids, mid + 1, end);
}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
* Perform a selection sort on bid title
* Average performance: O(n^2))
* Worst case performance O(n^2))
*
* @param bid address of the vector<Bid>
* instance to be sorted
*/

void selectionSort(vector<Bid>& bids) {
//***********************************************************************************************************
    // START---THE FIX FOR (1a)
//***********************************************************************************************************

    //define min as int (index of the current minimum bid)
    int min;

    //pos is position in Bid that marks sorted/unsorted
    // check size of bids vector
    // just used bid.size
    for (unsigned pos = 0; pos < bids.size(); ++pos) {

        // set min = pos
        min = pos;

        // loop over remaining elements to the right of position
                
        for (unsigned j = pos + 1; j < bids.size(); ++j) {

            // if this element's title is less than minimum title
            if (bids.at(j).title.compare(bids.at(min).title) < 0) {

                min = j;
            }
        }

        // swap the current minimum with smaller one found
         // swap is a built in vector method
        if (min != pos) {
            swap(bids.at(pos), bids.at(min));
        }
    }
}

//***********************************************************************************************************
    // END---THE FIX FOR (1a)
//***********************************************************************************************************

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
*/

int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;

    switch (argc) {

    case 2:
        csvPath = argv[1];
        break;
    default:

        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        // OR------------csvPath = "eBid_Monthly_Sales.csv"; 
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;
    int choice = 0;

    while (choice != 9) {

        cout << "Menu:" << endl;
        cout << " 1. Load Bids" << endl;
        cout << " 2. Display All Bids" << endl;
        cout << " 3. Selection Sort All Bids" << endl;
        cout << " 4. Quick Sort All Bids" << endl;
        cout << " 9. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);
            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            // Loop and display the bids read

            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }

            cout << endl;
            break;

            // FIXME (1b): Invoke the selection sort and report timing results
//***********************************************************************************************************
    // START---THE FIX FOR (1b)
//***********************************************************************************************************

        case 3:

            // Initialize a timer variable
            ticks = clock();

            // Method call to load the bids for selection sort
            selectionSort(bids);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            //Display Time Results
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
//***********************************************************************************************************
    // END---THE FIX FOR (1b)
//***********************************************************************************************************

            // FIXME (2b): Invoke the quick sort and report timing results
 //***********************************************************************************************************
    // START---THE FIX FOR (2b)
//***********************************************************************************************************

        case 4:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Method call to load the bids for quick sort
            quickSort(bids, 0, bids.size() - 1);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            // Display  Time Result
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        }
    }
 //***********************************************************************************************************
    // END---THE FIX FOR (2b)
//***********************************************************************************************************

    cout << "Good bye." << endl;

    return 0;

}
