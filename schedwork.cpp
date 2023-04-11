#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(int row, int col, vector<size_t>& maxShifts, DailySchedule& sched, AvailabilityMatrix& avail, int dailyNeed);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    AvailabilityMatrix temp = avail;
    //fill sched with placeholders
    //and set maximum shifts for each worker

    for (int r = 0; r < avail.size(); r++){
        vector<Worker_T> temp(dailyNeed, -1);
        sched.push_back(temp);
    }

    //vector with max shifts, where each index connects to each worker #
    vector<size_t> maxShiftVector;
    for (int i = 0; i < avail[0].size(); i++) {
        maxShiftVector.push_back(maxShifts);
    }

    return scheduleHelper(0, 0, maxShiftVector, sched, temp, dailyNeed);
}

bool scheduleHelper(int row, int col, vector<size_t>& maxShifts, DailySchedule& sched, AvailabilityMatrix& avail, int dailyNeed) {
    //if reach the end of a "day", go to next day
    if (row == avail.size()) {
        return true;
    }
    //if size of the row = the max shifts, go to the next row
    else if (col == dailyNeed) {
        return scheduleHelper(row+1, 0, maxShifts, sched, avail, dailyNeed);
    }
    //if schedule has not been started yet
    else {
        for (int i = 0; i < avail[0].size(); i++) {
            //check if worker I is available for the day && if the worker has available shifts
            if (avail[row][i] == 1 && maxShifts[i] > 0) {
                // assign worker i to that day, 
                sched[row][col] = i;
                // remove availability for that day, (change avail value to 0 for that day)
                avail[row][i] = 0;
                // decrease total available shifts of WOrker I by 1,
                maxShifts[i]-=1;
                // recurse to the next available spot
                if (scheduleHelper(row, col+1, maxShifts, sched, avail, dailyNeed)) {
                    //reached end, so return true
                    return true;
                }
                sched[row][col] = -1;
                avail[row][i] = 1;
                maxShifts[i] += 1;
                //and set max shifts to +1
            }
        }
    }
    return false;
}

