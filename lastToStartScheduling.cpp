/************************************************************************
** Author: James Meehan
** Course: CS 325
** Assignment: Homework #4, Question 5
** Date: February 2, 2018
************************************************************************/

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


struct Activity {
	int number, start, finish;
};


//comparator helper function for sort
int compare(Activity x, Activity y)
{
    return x.start > y.start;
}

/***********************************************************************
** Description: lastToStart() finds the optimal solution to maximizing
** the amount of activities but finding the activity that starts last
** and working backwards toward the front and choosing the activity with 
** the next closest starting time that doesn't conflict with already
** selected options.
*************************************************************************/
void lastToStart(vector<Activity>& vec)
{
    sort(vec.begin(), vec.end(), compare);
    /*for (int i = 0; i < vec.size(); i++)
        cout << vec[i].number << " " << vec[i].start << " " << vec[i].finish << endl;
    verify sort (debug)*/
    int actCounter = 0;
    vector<Activity> tracker;
    //add the first activity to the vector unless there are no activities in the activity.
    if (vec.size() <= 0){
        cout << "There are no activities";
        return;
    }
    else {
        tracker.push_back(vec[0]);
        actCounter++;
    }

    //continue to add the activity with the next closest start time that does not conflict
    //with activities already added
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].start != vec[i-1].start && vec[i].finish <= tracker.back().start)
        {
            tracker.push_back(vec[i]);
            actCounter++;
        }
    }
    
    cout << "Number of activities selected = " << actCounter << endl;

    //print out activity numbers selected
    for (int j = tracker.size() - 1; j >= 0; j--)
        cout << tracker[j].number << " ";
    cout << endl << endl;
    
}

int main() {

    ifstream inFile;

    inFile.open("act.txt");
    if (!inFile)
    {
        cout << "Unable to open file!";
        return 1;
    }
 
    int setCount = 1;
    while (!inFile.eof()) {

        int n;
        inFile >> n;
        Activity a[n];
        vector<Activity> vec(n);
        for (int i = 0; i < n; i++) {
        	inFile >> a[i].number >> a[i].start >> a[i].finish;
        	vec[i] = a[i];
        }

        cout << "Set " << setCount << endl;
        lastToStart(vec);
        setCount++;     
    }

    
        inFile.close();
        return 0;
}